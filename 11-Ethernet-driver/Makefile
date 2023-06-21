# Makefile for fake network device drivers.

EXTRA_CFLAGS = -Wall
obj-m = m_ethernet.o

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
	make -C $(KDIR) M=`pwd` clean
