#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbc87a494, "module_layout" },
	{ 0x3c91424a, "cdev_del" },
	{ 0xdfb68b8e, "cdev_init" },
	{ 0x2e5810c6, "__aeabi_unwind_cpp_pr1" },
	{ 0xc68d626b, "device_destroy" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x7c32d0f0, "printk" },
	{ 0xe97c4103, "ioremap" },
	{ 0x935b6dd2, "device_create" },
	{ 0xd389127b, "cdev_add" },
	{ 0xedc03953, "iounmap" },
	{ 0x9756de3b, "class_destroy" },
	{ 0x1ed0cdf7, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "CA4CF297B6A756B38C1462E");
