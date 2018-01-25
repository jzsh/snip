#Makefile 2.6

obj-m :=ipt_pktsize.o
KERNEL :=/usr/src/linux-source-2.6.32/
PWD :=$(shell pwd)
modules :
	$(MAKE) -C $(KERNEL) M=$(PWD) modules
.PHONEY:clean
clean :
	rm -rf *.o *.ko *.mod.c *.order *.symvers .*.cmd .tmp_versions *.so
install:remove
	insmod ./ipt_pktsize.ko
remove:
	-lsmod | grep ipt_pktsize && (iptables -F; rmmod ipt_pktsize)
show:
	dmesg

# Make libxt_ipaddr.so
lib%.so: lib%.o
	gcc -shared -o $@ $^;
lib%.o: lib%.c
	gcc -fPIC -D_INIT=lib$*_init -c -o $@ $<;

