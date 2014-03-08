#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x324940a4, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5496aa47, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x12774ca5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xc324eea8, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x4ea203d2, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xab14bb97, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x7c82e601, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0xe43e5ec6, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0x7749e0d9, __VMLINUX_SYMBOL_STR(kunmap) },
	{ 0x2e60bace, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x10457196, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x7708298, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "89056A189D48C5872120B8F");
