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
	{ 0xd4bcc18f, __VMLINUX_SYMBOL_STR(elevator_exit) },
	{ 0xb6ea1f4c, __VMLINUX_SYMBOL_STR(elevator_init) },
	{ 0xa28ba572, __VMLINUX_SYMBOL_STR(blk_init_queue) },
	{ 0xa5b5786e, __VMLINUX_SYMBOL_STR(__blk_end_request_all) },
	{ 0x7749e0d9, __VMLINUX_SYMBOL_STR(kunmap) },
	{ 0x2e60bace, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x10457196, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x90fb01b2, __VMLINUX_SYMBOL_STR(blk_end_request_all) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe5e52ee2, __VMLINUX_SYMBOL_STR(blk_fetch_request) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "0DD9E349607D3CCD52F4E9C");
