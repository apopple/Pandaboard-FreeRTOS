FREERTOS_SOURCE_DIR = ./FreeRTOS
APPLICATION_SOURCE_DIR = ./Application
BUILD_DIR = ./Build
CROSS_COMPILE = arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
MKIMAGE=mkimage
IMAGE_LOADADDR=0x83000000

CFLAGS = -g -mcpu=cortex-m3 -mthumb -I$(APPLICATION_SOURCE_DIR) -I$(FREERTOS_SOURCE_DIR)/Source/include -I$(FREERTOS_SOURCE_DIR)/Source/portable/GCC/ARM_CM3 -D GCC_ARMCM -O2 -Wall
LDFLAGS = -Tcortex-m3.lds
LIBGCC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)
LIBC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-file-name=libc.a)

FREERTOS_SOURCE_DIRS = $(FREERTOS_SOURCE_DIR)/Source $(FREERTOS_SOURCE_DIR)/Source/portable/GCC/ARM_CM3 $(FREERTOS_SOURCE_DIR)/Source/portable/MemMang

VPATH = $(FREERTOS_SOURCE_DIRS):$(APPLICATION_SOURCE_DIR)
APPLICATION_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o

OBJS =	$(BUILD_DIR)/list.o \
	$(BUILD_DIR)/queue.o \
	$(BUILD_DIR)/tasks.o \
	$(BUILD_DIR)/timers.o \
	$(BUILD_DIR)/croutine.o \
	$(BUILD_DIR)/port.o \
	$(BUILD_DIR)/heap_1.o \
	$(APPLICATION_OBJS)

all: Demo.bin loader.img boot.scr

-include $(OBJS:.o=.d)

loader.img: loader.out
loader.out: loader.c cortex-a9.lds
	$(CC) -Tcortex-a9.lds -mcpu=cortex-a9 -o loader.out loader.c

Demo.bin: Demo.out

Demo.out: $(OBJS) $(LIBGCC) $(LIBC) cortex-m3.lds
	$(LD) $(LDFLAGS) $(OBJS) $(LIBGCC) $(LIBC) -o Demo.out

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) -c -MD $(CFLAGS) -o $@ -Wp,-MD,$(BUILD_DIR)/$*.d $<
	sed -i -e 's|.*:|$(BUILD_DIR)/$*.o:|' $(BUILD_DIR)/$*.d

%.scr: %.script
	$(MKIMAGE) -C none -O u-boot -T script -A arm -d $< $@

%.img: %.out
	$(OBJCOPY) $< -O binary $*.bin
	$(MKIMAGE) -A arm -C none -O linux -T kernel -a $(IMAGE_LOADADDR) -e `hexdump -s 24 -n 4 -e '"0x%x" "\n"' $<` -d $*.bin $@

%.bin: %.out
	$(OBJCOPY) $< -O binary $@

clean:
	rm -f $(BUILD_DIR)/*.d
	rm -f $(BUILD_DIR)/*.o
	rm -f Demo.out Demo.bin loader.out loader.bin boot.scr loader.img

.PHONY: clean
