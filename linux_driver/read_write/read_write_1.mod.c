#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0x92997ed8, "_printk" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x7fb98451, "cdev_init" },
	{ 0x91128fc8, "cdev_add" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8d30dba0, "__class_create" },
	{ 0x43dd1c15, "cdev_del" },
	{ 0xbf3f457f, "device_create" },
	{ 0x7391ca5d, "class_destroy" },
	{ 0x54ae6ab6, "device_destroy" },
	{ 0x8f80e6e5, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "CEC6D8B066BD3F57402369D");
