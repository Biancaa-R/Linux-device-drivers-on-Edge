#include <linux/module.h>
#include <linux/init.h>
int my_init(void)
{
	printk("hello -hello kernel\n");
	return 0;
}
static void my_exit(void)
{
        printk("hello -good bye kernel\n");
        // return 0;
}
module_init(my_init);
module_exit(my_exit);

//specify the lIcense using macro lisense
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Biancaa");
MODULE_DESCRIPTION("A simple kernal");

