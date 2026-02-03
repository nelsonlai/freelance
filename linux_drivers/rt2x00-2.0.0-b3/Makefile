#	Copyright (C) 2004 - 2005 rt2x00 SourceForge Project
#	<http://rt2x00.serialmonkey.com>
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program; if not, write to the
#	Free Software Foundation, Inc.,
#	59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#	Module: Makefile 
#	Abstract: Makefile for rt2x00 kernel module 

obj-m += rt2x00core.o
obj-m += rt2400pci.o
obj-m += rt2500pci.o
obj-m += rt2500usb.o

ifdef KERNDIR
	KERNEL_SOURCES := $(KERNDIR)
else
	KERNEL_SOURCES := /lib/modules/$(shell uname -r)/build
endif

ifdef KERNOUT
	KERNEL_OUTPUT := KBUILD_OUTPUT=$(KERNOUT)
else
	KERNEL_OUTPUT :=
endif

ifdef KBUILD_EXTMOD
	IEEE80211_DIR := $(KBUILD_EXTMOD)/ieee80211
else
	IEEE80211_DIR := ieee80211
endif

MAKEFLAGS += --no-print-directory
CFLAGS := -I$(IEEE80211_DIR) -include $(IEEE80211_DIR)/net/ieee80211_compat.h $(CFLAGS)
CPPFLAGS := -I$(IEEE80211_DIR) -include $(IEEE80211_DIR)/net/ieee80211_compat.h $(CPPFLAGS)

all: debug
default: debug
nodebug: ieee80211-nodebug update-symbols rt2x00-nodebug
debug: ieee80211-debug update-symbols rt2x00-debug
install: ieee80211-install rt2x00-install
clean: ieee80211-clean rt2x00-clean

update-symbols:
	@mkdir -p .tmp_versions
	@cp $(IEEE80211_DIR)/.tmp_versions/*.mod .tmp_versions

ieee80211-nodebug:
	@$(MAKE) -C $(IEEE80211_DIR) nodebug

ieee80211-debug:
	@$(MAKE) -C $(IEEE80211_DIR) debug

ieee80211-install:
	@$(MAKE) -C $(IEEE80211_DIR) install

ieee80211-clean:
	@$(MAKE) -C $(IEEE80211_DIR) clean

rt2x00-nodebug:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) $(KERNEL_OUTPUT) modules

rt2x00-debug:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) EXTRA_CFLAGS="-DCONFIG_RT2X00_DEBUG" $(KERNEL_OUTPUT) modules

rt2x00-install:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) INSTALL_MOD_DIR=rt2x00 $(KERNEL_OUTPUT) modules_install
	/sbin/depmod -a

rt2x00-clean:
	@rm -f *.o *.ko .*.cmd .*.flags *.mod.c .*.o.d *~
	@rm -fr .tmp_versions