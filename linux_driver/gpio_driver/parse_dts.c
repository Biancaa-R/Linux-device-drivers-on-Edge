#include <linux/module.h>
#include <linux/init.h>
#include <linux/mod_devicetable.h>
#include <linux/property.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Biancaa Ramesh");
MODULE_DESCRIPTION("Parsing the device tree to read values.");

//registering the probe and remove functions of dts
static int dt_probe(struct platform_device *pdev);
static int dt_remove(struct platform_device *pdev);

static struct of_device_id driver_ids[]={
    {.compatible = "brightlight,mydev",
    }, { }
};

MODULE_DEVICE_TABLE(of,driver_ids);
// xxx and name of the struct

static struct platform_driver dts_driver={
    .probe =dt_probe,
    .remove=dt_remove,
    .driver={
        .name = "dts_parse_driver",
        .of_match_table =driver_ids,
    },
};

static int dt_probe(struct platform_device *pdev){
    struct device *dev =&pdev->dev;
    const char *label;
    int my_val,ret;
    printk("THe execution of the probe function \n");
    if(!device_property_present(dev,"label")){
        printk("dt-probe - Error the device property label is not found\n");
        return -1;
    }
    if(!device_property_present(dev,"my_val")){
        printk("dt-probe - Error the device property label is not found\n");
        return -1;
    }
    //printing the device properties
    ret = device_property_read_string(dev,"label",&label);
    if(ret){
        printk("dt_probe - Error ! could not read the label \n");
        return -1;
    }
    printk("dt_probe- label: %s\n",label);
    ret =device_property_read_u32(dev,"my_value",&label);
    if(ret){
        printk("dt_probe - Error ! could not read the my_value\n");
        return -1;
    }  
    printk("dt-probe -my_value: %s\n",my_val);
    return 0;
}

static int dt_remove(struct platform_device *pdev){
    printk("dt_probe -Now I am in the remove function of the kernel\n");
    return 0;
}

static int __init kernel_init(void){
    printk("dt_probe - LOading the driver\n");
    if(platform_driver_register(&dts_driver)){
        //returning of non zero values
        printk("dt_probe -Error !could not load driver\n");
        return -1;
    }
    return 0;
}

static void __exit kernel_exit(void){
    printk("dt_probe- Unload dts driver \n");
    printk("Unloading of the driver module\n");
    platform_driver_unregister(&dts_driver);
}