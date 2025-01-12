#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
// for the handling of file systems
#define MYMAJOR  90
#define DRIVER_NAME "my_gpio_driver"
#define DRIVER_CLASS "MyModuleClass"
//when device file is opened

//buffer for data:
static char buffer[255];
//buffer for both reading and writing
static int buffer_pointer=0;
//for signifying position

static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;
//the created device

static ssize_t driver_read(struct file *File, char *user_buffer,size_t count,loff_t *offs)
{
	int to_copy,not_copied, delta;
	char tmp[3] ="\n";
	to_copy = min(count, sizeof(tmp));
	printk("Value of button %d\n",gpio_get_value(17));
	not_copied =copy_to_user(user_buffer,&tmp,to_copy);
	tmp[0]= gpio_get_value(17)+'0';
	not_copied =copy_to_user(user_buffer,&tmp,to_copy);
	delta = to_copy-not_copied;
	return delta;
}

static ssize_t driver_write(struct file *File, const char *user_buffer,size_t count,loff_t *offs)
{
        int to_copy,not_copied, delta;
	char value;
        to_copy = min(count, sizeof(value));
        not_copied =copy_from_user(&value,user_buffer,to_copy);
	//buffer_pointer=to_copy;
	switch (value)
	{	case '0':
			gpio_set_value(4,0);
			break;
		case '1':
			gpio_set_value(4,1);
			break;
		default:
			printk("Invalid Input");
			break;
	}
        delta = to_copy-not_copied;
        return delta;
}
//that const in user buffer is so important
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
	.release =driver_close,
	.read=driver_read,
	.write=driver_write
};

int __init ModuleInit(void)
{	int retval;
        printk("read_write -hello kerell\n");
	//registering of the device number
	//trying to assign a dynamic device number.
	if( alloc_chrdev_region(&my_device_nr ,0,1, DRIVER_NAME) < 0)
	{	printk("Device Nr. could not be allocated\n");
		return -1;
	}
	//creating of the device class
	printk("read_write - Device Nr. major %d, minor %d was registered\n",my_device_nr >> 20, my_device_nr && 0xfffff);
	if((my_class= class_create(THIS_MODULE,DRIVER_CLASS))==NULL){
		printk("Device class cannot be created");
		goto ClassError;
	}
	//creation of device file
	if (device_create(my_class,NULL,my_device_nr,NULL,DRIVER_NAME) == NULL)
	{	printk("Cannot create device file \n");
		goto FileError;
	}
	//initialize the device file:
	cdev_init(&my_device, &fops);
	if (cdev_add(&my_device,my_device_nr,1) == -1){
		printk("Registering of device to kernel failed\n");
		goto AddError;
	}
	//GPIO 4 as op init
	if (gpio_request(4, "rpi-gpio-4"))
	{	printk("Cannot allocate GPIO 4 \n");
		goto AddError;
	}
	//setting of GPIO direction
	if (gpio_direction_output(4,0)){
		printk("Cannot set GPIO 4 as output\n");
		goto Gpio4Error;
	}
        //GPIO 17 as op init
        if (gpio_request(17, "rpi-gpio-17"))
        {       printk("Cannot allocate GPIO 17 \n");
                goto AddError;
        }
        //setting of GPIO direction
        if (gpio_direction_input(17)){
                printk("Cannot set GPIO 17 as output\n");
                goto Gpio17Error;
        }

	return 0;
	
	Gpio17Error:	
		gpio_free(17);
	Gpio4Error:
		gpio_free(4);
	AddError:
		device_destroy(my_class,my_device_nr);

	FileError:
		class_destroy(my_class);
	ClassError:
		unregister_chrdev(my_device_nr,DRIVER_NAME);
		return -1;
}
static void __exit ModuleExit(void)
{
	//cdev_del(&my_device_file);
	//for the deleting of the device file in the kernel
	//device_destroy(my_class,my_device_nr);
	//class_destroy(my_class);
	//unregister_chrdev(my_device_nr,DRIVER_NAME);
	////unregister_chrdev(MYMAJOR ,"my_dev_nr");// for the number
        //printk("dev_nr -good bye kernel\n");

	//setting of the output port to 0
	gpio_set_value(4,0);
	gpio_free(17);
	gpio_free(4);
	cdev_del(&my_device);
	device_destroy(my_class,my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr,1);
	printk("Goodbye Kernel \n");
        // return 0;
}


module_init(ModuleInit);
module_exit(ModuleExit);

/*meta info*/
//specify the lIcense using macro lisense
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Biancaa");
MODULE_DESCRIPTION("A basic GPIO device driver");

