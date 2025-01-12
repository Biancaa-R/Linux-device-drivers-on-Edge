
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
 // For character device structure (cdev)
#define DRIVER_NAME "my_driver"
static dev_t my_device_nr;
static struct cdev my_device;
static struct class *my_class;

static int driver_open(struct inode *inode, struct file *file) {
    pr_info("Device opened\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
};

static int __init ModuleInit(void) {
//This function is called when the module is loaded (insmod). It's responsible for setting up the device and registering it with the kernel.
    if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
        pr_err("Device number allocation failed\n");
        return -1;
    }

    cdev_init(&my_device, &fops);
    if (cdev_add(&my_device, my_device_nr, 1) < 0) {
        pr_err("Device registration failed\n");
        unregister_chrdev_region(my_device_nr, 1);
        return -1;
	//    Register the cdev structure (my_device) with the kernel.
   	// If registration fails, free the device number using unregister_chrdev_region.
    }

    my_class = class_create(THIS_MODULE, "my_class");
    if (IS_ERR(my_class)) {
        pr_err("Failed to create class\n");
        cdev_del(&my_device);
        unregister_chrdev_region(my_device_nr, 1);
        return PTR_ERR(my_class);
    }

    if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
        pr_err("Failed to create device\n");
        class_destroy(my_class);
        cdev_del(&my_device);
        unregister_chrdev_region(my_device_nr, 1);
        return -1;
    }

    pr_info("Driver initialized successfully\n");
    return 0;
}

static void __exit ModuleExit(void) {
    device_destroy(my_class, my_device_nr);
    class_destroy(my_class);
    cdev_del(&my_device);
    unregister_chrdev_region(my_device_nr, 1);
    pr_info("Driver removed\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
//module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Biancaa Ramesh");
MODULE_DESCRIPTION("A simple Linux device driver example");
