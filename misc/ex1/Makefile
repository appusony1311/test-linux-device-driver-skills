CONFIG_MODULE_SIG=n
obj-m := sample_module_01.o

KERNEL_PATH=/lib/modules/$(shell uname -r)/build
PWD=$(shell pwd)

all:
	make -C $(KERNEL_PATH) M=$(PWD) modules
clean:	
	make -C $(KERNEL_PATH) M=$(PWD) clean
