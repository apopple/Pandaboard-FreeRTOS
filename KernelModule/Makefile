default: rproc

ARCH ?= arm
CROSS_COMPILE ?= arm-none-eabi-
KERNELDIR ?= /path/to/linux/kernel/source
PWD = `pwd`

ifeq ($(KERNELRELEASE),)

.PHONY: clean.
clean:
	rm -rf *.o *.~ *.ko *.mod.c

rproc:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

else
	obj-m:= rproc.o
endif
