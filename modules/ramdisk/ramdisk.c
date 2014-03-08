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


#define SIMP_BLKDEV_DEVICEMAJOR		COMPAQ_SMART2_MAJOR 
#define SIMP_BLKDEV_DISKNAME        	"cc"
#define SIMP_BLKDEV_BYTES        	(16 * 1024 * 1024)

static struct request_queue *simp_blkdev_queue;
static struct gendisk *simp_blkdev_disk;
unsigned char simp_blkdev_data[SIMP_BLKDEV_BYTES];
/*
 * simp_blkdev_make_request
 */
static void simp_blkdev_make_request(struct request_queue *q, struct bio *bio)
{
    struct bio_vec *bvec;
    int i;
    void *dsk_mem;
	
	/* 判断 IO 请求是否超出实际 RanDisk 大小 */
    if((bio->bi_sector << 9) + bio->bi_size > SIMP_BLKDEV_BYTES) 
	{
        printk(KERN_ERR SIMP_BLKDEV_DISKNAME
            ": bad request: block=%llu, count=%u\n",
            (unsigned long long)bio->bi_sector, bio->bi_size);

/* 条件编译，对于 2.4 内核之后的变量多了一个，伤不起阿！ */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
                /* 返回这个对 bio 请求的处理结果，－EIO 表示出错 */
        bio_endio(bio, 0, -EIO);
#else
        bio_endio(bio, -EIO);
#endif

        return ;
	}

    dsk_mem = simp_blkdev_data + (bio->bi_sector << 9);
    /* 遍历 bio 中所有的 bvec */
    bio_for_each_segment(bvec, bio, i)
    {
        void *iovec_mem;

        switch(bio_rw(bio))
        {
            case READ:
            case READA:             /* 读和预读都进行同样的处理 */
                /* 用 kmalloc 将请求页映射到非线性映射区域进行
                    * 访问，这种方法主要是为了兼容高端内存，
                    * (bvec->bv_page 可能源于高端内存） */
                iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
                memcpy(iovec_mem, dsk_mem, bvec->bv_len);
                kunmap(bvec->bv_page);
                break;
			case WRITE:
					iovec_mem = kmap(bvec->bv_page) + bvec->bv_offset;
					memcpy(dsk_mem, iovec_mem, bvec->bv_len);
					kunmap(bvec->bv_page);
					break;

			default:
					printk(KERN_ERR SIMP_BLKDEV_DISKNAME
							":Unknown value of bio_rw: %lu\n",
							bio_rw(bio));
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
					bio_endio(bio, 0, -EIO);
#else
					bio_endio(bio, -EIO);
#endif
					return ;
			}
        dsk_mem += bvec->bv_len;
    }

/* 返回这个对 bio 请求的处理结果，0 表示正常 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
    bio_endio(bio, 0, 0);
#else
    bio_endio(bio, 0);
#endif

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

	/* 分配一个请求队列 */
        simp_blkdev_queue = blk_alloc_queue(GFP_KERNEL);
        if(!simp_blkdev_queue) 
	{
                ret = -ENOMEM;
                goto err_alloc_queue;
        }
	
	/* 为请求队列绑定 make_request_fn 方法 */
        blk_queue_make_request(simp_blkdev_queue, simp_blkdev_make_request);

	/* 分配一个 gendisk 结构 */
        simp_blkdev_disk = alloc_disk(1);
        if(!simp_blkdev_disk) 
	{
                ret = -ENOMEM;
                goto err_alloc_disk;
        }
	
	/* 填充 gendisk 主要结构成员 */
        strcpy(simp_blkdev_disk->disk_name, SIMP_BLKDEV_DISKNAME);
        simp_blkdev_disk->major = SIMP_BLKDEV_DEVICEMAJOR;
        simp_blkdev_disk->first_minor = 0;
        simp_blkdev_disk->fops = &simp_blkdev_fops;
        simp_blkdev_disk->queue = simp_blkdev_queue;
        set_capacity(simp_blkdev_disk, SIMP_BLKDEV_BYTES >> 9);

	/* 向内核注册块设备驱动 */
        add_disk(simp_blkdev_disk);

        return 0;

err_alloc_disk:
        blk_cleanup_queue(simp_blkdev_queue);
err_alloc_queue:
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
