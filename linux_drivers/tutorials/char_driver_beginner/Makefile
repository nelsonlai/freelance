# Out-of-tree kernel module build for ctut tutorial modules
#
# Usage:
#   make              # build ctut_char.ko and ctut_kfifo.ko against your running kernel
#   make clean
#   make user_test    # build userspace test program
#
# Notes:
# - This uses the running kernel’s build directory:
#     /lib/modules/$(uname -r)/build
# - You need kernel headers/build tools installed on your system.

obj-m += ctut_char.o
obj-m += ctut_kfifo.o

KDIR ?= /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: all clean user_test

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) user_test

user_test: user_test.c
	$(CC) -O2 -Wall -Wextra -o $@ $<

