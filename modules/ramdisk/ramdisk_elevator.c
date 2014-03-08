#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* everything... */
#include <linux/errno.h>	/* error codes */
#include <linux/timer.h>
#include <linux/types.h>	/* size_t */
#include <linux/fcntl.h>	/* O_ACCMODE */
#include <linux/hdreg.h>	/* HDIO_GETGEO */
#include <linux/kdev_t.h>
#include <linux/vmalloc.h>
#include <linux/genhd.h>
#include <linux/blkdev.h>
#include <linux/buffer_head.h>	/* invalidate_bdev */
#include <linux/bio.h>
#include <linux/major.h>
#include <linux/version.h>
#include <linux/elevator.h>



#define SIMP_BLKDEV_DEVICEMAJOR		COMPAQ_SMART2_MAJOR 
#define SIMP_BLKDEV_DISKNAME        	"cc"
#define SIMP_BLKDEV_BYTES        	(16 * 1024 * 1024)

static struct request_queue *simp_blkdev_queue;
static struct gendisk *simp_blkdev_disk;
unsigned char simp_blkdev_data[SIMP_BLKDEV_BYTES];
/*
 * simp_blkdev_make_request
 */
static void simp_blkdev_do_request(struct request_queue *q)
{
	struct request *req;
	struct req_iterator ri;
	struct bio_vec *bvec;
	char *disk_mem;
	char *buffer;
		
	while ((req = blk_fetch_request(q)) != NULL) {
		if ((blk_rq_pos(req) << 9) + blk_rq_cur_bytes(req)
			> SIMP_BLKDEV_BYTES) {
			printk(KERN_ERR SIMP_BLKDEV_DISKNAME
				": bad request: block=%llu, count=%u\n",
				(unsigned long long)blk_rq_pos(req),
				blk_rq_cur_bytes(req));
				blk_end_request_all(req, -EIO);
			continue;
		}
		
		disk_mem = simp_blkdev_data + (blk_rq_pos(req) << 9);
		switch (rq_data_dir(req)) {
		case READ:	
			rq_for_each_segment(bvec, req, ri)
			{
				buffer = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(buffer, disk_mem, bvec->bv_len);
				kunmap(bvec->bv_page);
				disk_mem += bvec->bv_len;
			}
			
			/*memcpy(req->buffer,
			simp_blkdev_data + (blk_rq_pos(req) << 9),
			blk_rq_cur_bytes(req));*/
			__blk_end_request_all(req, 0);
			break;
		case WRITE:		
			rq_for_each_segment(bvec, req, ri)
			{
				buffer = kmap(bvec->bv_page) + bvec->bv_offset;
				memcpy(disk_mem, buffer, bvec->bv_len);
				kunmap(bvec->bv_page);
				disk_mem += bvec->bv_len;
			}
			/*memcpy(simp_blkdev_data + (blk_rq_pos(req) << 9),
			req->buffer, blk_rq_cur_bytes(req));*/
			__blk_end_request_all(req, 0);
			break;
		default:
			/* No default because rq_data_dir(req) is 1 bit */
			break;
		}
	}
}

/* 
 * block_device_operations
 */
struct block_device_operations simp_blkdev_fops = 
{
        .owner = THIS_MODULE,
};

/* 
 * simp_blkdev_init
 */
static int __init simp_blkdev_init(void)
{
        int ret;
		struct elevator_queue *elv_old;

		//分配一个请求队列
        simp_blkdev_queue = blk_init_queue(simp_blkdev_do_request, NULL);
        if(!simp_blkdev_queue) 
		{
			ret = -ENOMEM;
            goto blk_init_queue;
        }
		
		elv_old = simp_blkdev_queue->elevator;
		simp_blkdev_queue->elevator = NULL;
		//更换IO调度器
		if (IS_ERR_VALUE(elevator_init(simp_blkdev_queue, "noop")))
			printk(KERN_WARNING "Switch elevator failed, using default\n");
		else
			elevator_exit(elv_old);
		//分配一个 gendisk 结构，有一个分区
        simp_blkdev_disk = alloc_disk(1);
        if(!simp_blkdev_disk) 
		{
            ret = -ENOMEM;
            goto err_alloc_disk;
        }
	
		//填充 gendisk 主要结构成员
        strcpy(simp_blkdev_disk->disk_name, SIMP_BLKDEV_DISKNAME);
        simp_blkdev_disk->major = SIMP_BLKDEV_DEVICEMAJOR;
        simp_blkdev_disk->first_minor = 0;
        simp_blkdev_disk->fops = &simp_blkdev_fops;
        simp_blkdev_disk->queue = simp_blkdev_queue;
        set_capacity(simp_blkdev_disk, SIMP_BLKDEV_BYTES >> 9);

		//向内核注册块设备驱动
        add_disk(simp_blkdev_disk);

        return 0;

err_alloc_disk:
        blk_cleanup_queue(simp_blkdev_queue);
blk_init_queue:
        return ret;
}

/* 
 * simp_blkdev_exit
 */
static void __exit simp_blkdev_exit(void)
{
        del_gendisk(simp_blkdev_disk);		/* 删除 gendisk 结构 */
        put_disk(simp_blkdev_disk);		/* 释放一个该对象的引用 */
        blk_cleanup_queue(simp_blkdev_queue);	/* 清理请求队列 */
}

module_init(simp_blkdev_init);
module_exit(simp_blkdev_exit);
