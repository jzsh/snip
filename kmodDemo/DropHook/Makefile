
obj-m :=drop.o
KERNEL := /lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)

all:
	$(MAKE) -C $(KERNEL) M=$(PWD) modules

.PYONY:clean
clean:
	$(MAKE) -C $(KERNEL) M=$(PWD) clean
