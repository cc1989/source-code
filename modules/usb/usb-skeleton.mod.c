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
	{ 0xf6df5a04, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x9fe02863, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xda8ed49d, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xabfc3307, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x50da2220, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x1ed85b62, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0xf38c45da, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xcb91acca, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x7106ab88, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x68dfc59f, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x3441837e, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x13e6ad28, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x935014de, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x396717f1, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0xe45f60d8, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x2f287f0d, __VMLINUX_SYMBOL_STR(copy_to_user) },
	{ 0x75bb675a, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x622fa02a, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x4292364c, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x2649c79d, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0x54320845, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x67f7403e, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xc604ec5, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0xd3d9129a, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0xc4554217, __VMLINUX_SYMBOL_STR(up) },
	{ 0x294850fe, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0xae0eca22, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x362ef408, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xf36bf65e, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x1a00fd8d, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x44f1606d, __VMLINUX_SYMBOL_STR(down_trylock) },
	{ 0x4792c572, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x8574eba, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x35731295, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7a3c4992, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0x8fcd7e4e, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0xf1faac3a, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xbb2846ac, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x22d449b7, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x8c4db1b5, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0xeec24d31, __VMLINUX_SYMBOL_STR(usb_wait_anchor_empty_timeout) },
	{ 0x6a6416e7, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x4af9da5f, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0483p5750d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "AC45C9F44E05658949A6E41");
