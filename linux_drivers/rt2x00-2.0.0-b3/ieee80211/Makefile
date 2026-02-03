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
#	Abstract: Makefile for ieee80211 kernel module 

ieee80211-objs := ieee80211_module.o ieee80211_tx.o ieee80211_rx.o ieee80211_wx.o ieee80211_geo.o

obj-m += ieee80211.o
obj-m += ieee80211_crypt.o
obj-m += ieee80211_crypt_wep.o
obj-m += ieee80211_crypt_ccmp.o
obj-m += ieee80211_crypt_tkip.o

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
	IEEE80211_DIR := $(KBUILD_EXTMOD)
else
	IEEE80211_DIR := .
endif

MAKEFLAGS += --no-print-directory
CFLAGS := -I$(IEEE80211_DIR) -include $(IEEE80211_DIR)/net/ieee80211_compat.h $(CFLAGS)
CPPFLAGS := -I$(IEEE80211_DIR) -include $(IEEE80211_DIR)/net/ieee80211_compat.h $(CPPFLAGS)

all: debug
default: debug

nodebug:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) $(KERNEL_OUTPUT) modules

debug:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) EXTRA_CFLAGS="-DCONFIG_IEEE80211_DEBUG" $(KERNEL_OUTPUT) modules

install:
	@$(MAKE) -C $(KERNEL_SOURCES) SUBDIRS=$(shell pwd) INSTALL_MOD_DIR=rt2x00 $(KERNEL_OUTPUT) modules_install
	/sbin/depmod -a

clean:
	@rm -f *.o *.ko .*.cmd .*.flags *.mod.c .*.o.d *~
	@rm -f net/*.o net/*.ko net/.*.cmd net/.*.flags net/*.mod.c net/.*.o.d net/*~
	@rm -fr .tmp_versions
