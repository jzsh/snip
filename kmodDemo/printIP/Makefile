obj-m := printip.o
KDIR := /usr/src/linux-source-2.6.32
PWD ?= $(shell pwd)

default:all

include $(PWD)/../common.mk

all:
	@echo $(obj-m)
	$(MAKE) -I$(KDIR)/include -C $(KDIR) SUBDIRS=$(PWD) modules

install:remove default
	insmod printip.ko
remove:
	-@rmmod printip.ko

