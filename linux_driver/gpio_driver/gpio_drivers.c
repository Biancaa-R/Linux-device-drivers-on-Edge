#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio/consumer.h>
#include <linux/err.h>
#include <linux/device.h>

//okay so this is more like an LKM
static struct gpio_desc *inp,*op;
#define IO_LED 21
#define IO_BUTTON 22
#define IO_OFFSET 0
//as for now as I understand there is only one gpio offset (seeing the gpio bsp)

static int __init gpio_init(void){
    int led= gpio_to_desc(IO_LED+IO_OFFSET);
    if(!led){
        printk("gpioctrl- Error getting IO pin output\n");
        return -ENODEV;
        //printing error only if there is an issue in setting up of the gpio pin
    }
    int button=gpio_to_desc(IO_BUTTON+IO_OFFSET);
    if(!button){
        printk("gpioctrl -Error getting IO pin input\n");
        return -ENODEV;
    }

}

//configuring the direction of the pin
static int GPIO_config(bool direction, gpio_desc*ptr,uint8_t pins, ...){
    va_list valist;
    va_start(valist, pins);
    //ok I'll come back to this later
    if(direction==1){
        //configure as output
        int status=gpio_direction_output(ptr,0);
        if(!status){
        printk("gpioctrl -Error setting IO pin output\n");
        return -ENODEV;
    }
    }
    if(direction==0){
        //configure it as input
        int status=gpio_direction_input(ptr);
        if(!status){
        printk("gpioctrl -Error setting IO pin input\n");
        return -ENODEV;
    }
    }

}

static uint8_t GPIO_Pin_Set(gpio_desc*ptr, ...){
    gpiod_set_value(ptr,1);
}

static uint8_t GPIO_Pin_Clear(gpio_desc*ptr, ...){
    gpiod_set_value(ptr,0);
    //atomic functions so void return
}

static uint8_t GPIO_Pin_Toggle(gpio_desc*ptr){
    gpiod_toggle_value(ptr);
}

static uint32_t GPIO_Read_Data(gpio_desc*ptr)
{
    //log_debug("Data register : %x\n", (gpio_instance->GPIO_DATA));
    //return gpio_instance->GPIO_DATA;
    printk("gpioctrl-Data register: %d\n",gpiod_get_value(ptr));
    return gpiod_get_value(ptr);
}

MODULE_AUTHOR("Biancaa Ramesh");
MODULE_DESCRIPTION("Code for adding the GPIO drivers more like a top level LKM for secureIOT");
MODULE_LICENSE("GPL");
