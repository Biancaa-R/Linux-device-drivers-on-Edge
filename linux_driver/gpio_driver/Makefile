obj-m += dt_probe.o
all:
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean: 
		make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
		rm -rf parser.dtbo

dt: parser.dts
		dtc -@ -I dts -O dtb -o parser.dtbo parser.dts