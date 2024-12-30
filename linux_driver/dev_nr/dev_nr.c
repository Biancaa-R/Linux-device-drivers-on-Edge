#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
// for the handling of file systems
#define MYMAJOR  90
//when device file is opened
static int driver_open(struct inode *device_file,struct file *instance)
{
	printk("dev_nr -open was called\n");
	return 0;
}

static int driver_close(struct inode *device_file,struct file *instance)
{
        printk("dev_nr -close was called\n");
        return 0;
}

static struct file_operations fops= {
	.owner=THIS_MODULE,
	.open=driver_open,
	.release =driver_close
};

int __init ModuleInit(void)
{	int retval;
        printk("dev_nr -hello kerell\n");
	//registering of the device number
	retval =register_chrdev(MYMAJOR,"my_dev_nr",&fops);
	if (retval==0)
	{
		printk("dev_nr - registered Device number Major :%d, Minor: %d\n",MYMAJOR,0);
	}
	else if (retval>0)
	{
		printk("dev_nr - registered Device number Major : %d, Minor %d\n",retval>>20,retval&0xfffff);
	}
	else {
		printk("dev_nr - could not register device number\n");
		return -1;
		}
        return 0;
}
static void __exit ModuleExit(void)
{
	unregister_chrdev(MYMAJOR ,"my_dev_nr");
        printk("dev_nr -good bye kernel\n");
        // return 0;
}


module_init(ModuleInit);
module_exit(ModuleExit);

/*meta info*/
//specify the lIcense using macro lisense
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Biancaa");
MODULE_DESCRIPTION("registers a device number");

