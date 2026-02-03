/*
	Copyright (C) 2004 - 2005 rt2x00 SourceForge Project
	<http://rt2x00.serialmonkey.com>

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the
	Free Software Foundation, Inc.,
	59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
	Module: rt2500usb
	Abstract: rt2500usb device specific routines.
	Supported chipsets: RT2570.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/delay.h>

#include "rt2x00.h"
#include "rt2500usb.h"

#ifdef DRV_NAME
#undef DRV_NAME
#define DRV_NAME			"rt2500usb"
#endif /* DRV_NAME */

/*
 * Register access.
 * All access to the registers will go through rt2x00_register_read and rt2x00_register_write.
 * BBP and RF register require indirect register access through the register BBPCSR and RFCSR.
 * The indirect register access work with busy bits, and a read or write function call can fail.
 */
#define REGISTER_BUSY_COUNT	10		/* Number of retries before failing. */
#define REGISTER_BUSY_DELAY	( 500 )		/* ms delay between each register access retry. */

static void
rt2x00_vendor_request(
	const struct _rt2x00_usb *rt2x00usb,
	const u8 request,
	const u8 type,
	const u16 offset,
	u16 value,
	u16 *buffer,
	const u16 buffer_length)
{
	unsigned int		pipe = 0x00000000;
	int			status = 0x00000000;
	u8			counter = 0x00;

	if(type == USB_VENDOR_REQUEST_IN)
		pipe = usb_rcvctrlpipe(rt2x00usb->usb_dev, 0);
	else
		pipe = usb_sndctrlpipe(rt2x00usb->usb_dev, 0);

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		status = usb_control_msg(rt2x00usb->usb_dev, pipe, request, type,
				value, offset, buffer, buffer_length, REGISTER_BUSY_DELAY);
		if(status >= 0)
			return;
	}

	ERROR("vendor request error. Request 0x%02x failed for offset 0x%04x with error %d.\n", request, offset, status);
}

static inline void
rt2x00_register_read(const struct _rt2x00_usb *rt2x00usb, u16 offset, u16 *value)
{
	rt2x00_vendor_request(rt2x00usb, USB_SINGLE_READ, USB_VENDOR_REQUEST_IN, offset, 0x00, value, 2);
}

static inline void
rt2x00_register_multiread(const struct _rt2x00_usb *rt2x00usb, u16 offset, u16 *value, const u16 length)
{
	rt2x00_vendor_request(rt2x00usb, USB_MULTI_READ, USB_VENDOR_REQUEST_IN, offset, 0x00, value, length);
}

static inline void
rt2x00_register_write(const struct _rt2x00_usb *rt2x00usb, u16 offset, u16 value)
{
	rt2x00_vendor_request(rt2x00usb, USB_SINGLE_WRITE, USB_VENDOR_REQUEST_OUT, offset, value, NULL, 0);
}

static inline void
rt2x00_register_multiwrite(const struct _rt2x00_usb *rt2x00usb, u16 offset, u16 *value, const u16 length)
{
	rt2x00_vendor_request(rt2x00usb, USB_MULTI_WRITE, USB_VENDOR_REQUEST_OUT, offset, 0x00, value, length);
}

static void 
rt2x00_bbp_regwrite(const struct _rt2x00_usb *rt2x00usb, const u8 reg_id, u8 value)
{
	u16		reg = 0x0000;
	u8		counter = 0x00;

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00usb, PHY_CSR8, &reg);
		if(!rt2x00_get_field16_nb(reg, PHY_CSR8_BBP_BUSY))
			goto bbp_write;
	}

	ERROR("BBPCSR register busy. Failed to write bbp 0x%02x.\n", reg_id);
	return;

bbp_write:
	reg = 0x0000;
	rt2x00_set_field16_nb(&reg, PHY_CSR7_BBP_DATA, value);
	rt2x00_set_field16_nb(&reg, PHY_CSR7_BBP_REG_ID, reg_id);
	rt2x00_set_field16_nb(&reg, PHY_CSR7_BBP_WRITE_CONTROL, 0);

	rt2x00_register_write(rt2x00usb, PHY_CSR7, reg);
}

static void
rt2x00_bbp_regread(const struct _rt2x00_usb *rt2x00usb, const u8 reg_id, u8 *value)
{
	u16		reg = 0x0000;
	u8		counter = 0x00;

	/*
	 * We first have to acquire the requested BBP register,
	 * so we write the register id into the BBP register first.
	 */
	rt2x00_set_field16_nb(&reg, PHY_CSR7_BBP_REG_ID, reg_id);
	rt2x00_set_field16_nb(&reg, PHY_CSR7_BBP_WRITE_CONTROL, 1);

	rt2x00_register_write(rt2x00usb, PHY_CSR7, reg);

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00usb, PHY_CSR8, &reg);
		if(!rt2x00_get_field16_nb(reg, PHY_CSR8_BBP_BUSY)){
			rt2x00_register_read(rt2x00usb, PHY_CSR7, &reg);
			*value = rt2x00_get_field16_nb(reg, PHY_CSR7_BBP_DATA);
			return;
		}
	}

	ERROR("BBPCSR register busy. Failed to write bbp 0x%02x.\n", reg_id);
	*value = 0xff;
}

static void
rt2x00_rf_regwrite(const struct _rt2x00_usb *rt2x00usb, u32 value)
{
	u16		reg = 0x0000;
	u8		counter = 0x00;

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00usb, PHY_CSR10, &reg);
		if(!rt2x00_get_field16_nb(reg, PHY_CSR10_RF_BUSY))
			goto rf_write;
	}

	ERROR("RFCSR register busy. Failed to write value 0x%08x.\n", value);
	return;

rf_write:
	reg = value & 0x0000ffff;
	rt2x00_register_write(rt2x00usb, PHY_CSR9, reg);

	reg = (value >> 16) & 0x0000ffff;
	rt2x00_set_field16_nb(&reg, PHY_CSR10_RF_NUMBER_OF_BITS, 20);
	rt2x00_set_field16_nb(&reg, PHY_CSR10_RF_IF_SELECT, 0);
	rt2x00_set_field16_nb(&reg, PHY_CSR10_RF_BUSY, 1);

	rt2x00_register_write(rt2x00usb, PHY_CSR10, reg);
}

static inline void
rt2x00_eeprom_read_word(const struct _rt2x00_usb *rt2x00usb, const u16 offset, u16 *value, const u16 length)
{
	rt2x00_vendor_request(rt2x00usb, USB_EEPROM_READ, USB_VENDOR_REQUEST_IN, offset, 0x00, value, length);
}

/*
 * Interrupt handlers.
 */
static void
rt2x00_interrupt_txdone(struct urb *urb, struct pt_regs *regs)
{
	struct _data_entry	*entry = (struct _data_entry*)urb->context;

	if(!test_bit(DEVICE_RADIO_ON, &entry->ring->device->flags))
		return;

	if(entry->ring_type == RING_TX)
		rt2x00_update_stats(entry->ring->device, STATS_TX_RESULT, (urb->status) ? TX_FAIL_OTHER : TX_SUCCESS);

	entry->status_flags = ENTRY_FREE;
	entry->packet_size = 0;
	rt2x00_ring_index_done_inc(entry->ring);

	rt2x00_tx(entry->ring->device, entry->ring_type);
}

static void
rt2x00_interrupt_rxdone(struct urb *urb, struct pt_regs *regs)
{
	struct _data_entry	*entry = (struct _data_entry*)urb->context;
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(entry->ring->device);
	struct _rxd		*rxd = NULL;
	void			*data = NULL;
	u16			size = 0x0000;
	u16			rssi = 0x0000;

	if(!test_bit(DEVICE_RADIO_ON, &entry->ring->device->flags))
		return;

	if(urb->status)
		return;

	rxd = RX_DESC_ADDR(urb);
	data = RX_DATA_ADDR(urb);

	/*
	 * Received USB packets have 4 bytes of extra data.
	 */
	size = rt2x00_get_field32(rxd->word0, RXD_W0_DATABYTE_COUNT) - 4;
	rssi = rt2x00_get_field32(rxd->word1, RXD_W1_RSSI);

	if(rt2x00_get_field32(rxd->word0, RXD_W0_CRC))
		rt2x00_update_stats(entry->ring->device, STATS_RX_CRC, 1);
	else if(rt2x00_get_field32(rxd->word0, RXD_W0_PHYSICAL_ERROR))
		rt2x00_update_stats(entry->ring->device, STATS_RX_PHYSICAL, 1);
	else if(rt2x00usb->sensitivity > rssi)
		rt2x00_update_stats(entry->ring->device, STATS_RX_QUALITY, 1);
	else
		rt2x00_ring_rx_packet(entry->ring->device, size, data, rssi);

	usb_submit_urb(urb, GFP_ATOMIC);

	rt2x00_ring_index_done_inc(entry->ring);
}

/*
 * Initialization handlers.
 */

/*
 * In word 22 the RF chip identification is located.
 */
static void
rt2x00_init_eeprom(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			reg = 0x0000;
	u8			tx_antenna = 0x00;
	u8			rx_antenna = 0x00;

	/*
	 * 1 - Identify RF chipset.
	 */
	rt2x00_eeprom_read_word(rt2x00usb, EEPROM_ANTENNA, &reg, 2);

	set_chip(&rt2x00usb->chip, RT2570, rt2x00_get_field16(reg, EEPROM_ANTENNA_RF_TYPE));

	/*
	 * 2 - Identify default antenna configuration.
	 */
	tx_antenna = rt2x00_get_field16(reg, EEPROM_ANTENNA_TX_DEFAULT);
	rx_antenna = rt2x00_get_field16(reg, EEPROM_ANTENNA_RX_DEFAULT);

	config->user.antenna_flags |= tx_antenna;
	config->user.antenna_flags |= rx_antenna << 8;

	if((config->user.antenna_flags & ANTENNA_TX) == 0)
		config->user.antenna_flags |= ANTENNA_TX_DIV;

	if((config->user.antenna_flags & ANTENNA_RX) == 0)
		config->user.antenna_flags |= ANTENNA_RX_DIV;

	/*
	 * 3 - Identify default geography configuration.
	 */
	rt2x00_eeprom_read_word(rt2x00usb, EEPROM_GEOGRAPHY, &reg, 2);
	config->user.geography = rt2x00_get_field16(reg, EEPROM_GEOGRAPHY_GEO);

	/*
	 * 4 - Read BBP data from EEPROM and store in private structure.
	 */
	memset(&rt2x00usb->eeprom, 0x00, sizeof(rt2x00usb->eeprom));
	rt2x00_eeprom_read_word(rt2x00usb, EEPROM_BBP_START, &rt2x00usb->eeprom[0], EEPROM_BBP_SIZE);
}

static void
rt2x00_init_read_mac(struct _rt2x00_usb *rt2x00usb, struct net_device *net_dev)
{
	u16			reg[3];

	memset(&reg, 0x00, sizeof(reg));

	rt2x00_eeprom_read_word(rt2x00usb, EEPROM_MAC_ADDR, &reg[0], 6);

	net_dev->dev_addr[0] = rt2x00_get_field16(reg[0], MAC_CSR2_BYTE0);
	net_dev->dev_addr[1] = rt2x00_get_field16(reg[0], MAC_CSR2_BYTE1);
	net_dev->dev_addr[2] = rt2x00_get_field16(reg[1], MAC_CSR3_BYTE2);
	net_dev->dev_addr[3] = rt2x00_get_field16(reg[1], MAC_CSR3_BYTE3);
	net_dev->dev_addr[4] = rt2x00_get_field16(reg[2], MAC_CSR4_BYTE4);
	net_dev->dev_addr[5] = rt2x00_get_field16(reg[2], MAC_CSR4_BYTE5);

	net_dev->addr_len = 6;

	rt2x00_register_multiwrite(rt2x00usb, MAC_CSR2, &reg[0], sizeof(reg));
}

static int
rt2x00_dev_probe(struct _rt2x00_device *device, struct _rt2x00_config *config, void *priv)
{
	struct usb_device		*usb_dev = (struct usb_device*)priv;
	struct _rt2x00_usb		*rt2x00usb = rt2x00_priv(device);

	memset(rt2x00usb, 0x00, sizeof(*rt2x00usb));

	if(unlikely(!usb_dev)){
		ERROR("invalid priv pointer.\n");
		return -ENODEV;
	}
	rt2x00usb->usb_dev = usb_dev;

	rt2x00usb->rx.data_addr = NULL;
	rt2x00usb->tx.data_addr = NULL;
	rt2x00usb->atim.data_addr = NULL;
	rt2x00usb->prio.data_addr = NULL;
	rt2x00usb->beacon.data_addr = NULL;

	rt2x00_init_eeprom(rt2x00usb, config);
	rt2x00_init_read_mac(rt2x00usb, device->net_dev);

	set_bit(DEVICE_CAP_802_11B, &device->flags);
	set_bit(DEVICE_CAP_802_11G, &device->flags);
	if(rt2x00_rf(&rt2x00usb->chip, RF5222))
		set_bit(DEVICE_CAP_802_11A, &device->flags);

	return 0;
}

static int
rt2x00_init_registers(struct _rt2x00_usb *rt2x00usb)
{
	u16			reg = 0x0000;

	rt2x00_vendor_request(rt2x00usb, USB_DEVICE_MODE, USB_VENDOR_REQUEST_OUT, USB_MODE_TEST, 0x00, NULL, 0);
	rt2x00_vendor_request(rt2x00usb, USB_SINGLE_WRITE, USB_VENDOR_REQUEST_OUT, 0x0308, 0x00f0, NULL, 0);

	rt2x00_register_write(rt2x00usb, TXRX_CSR2, 0x0001);
	rt2x00_register_write(rt2x00usb, MAC_CSR13, 0x1111);
	rt2x00_register_write(rt2x00usb, MAC_CSR14, 0x1e11);
	rt2x00_register_write(rt2x00usb, MAC_CSR1, 0x0003);
	rt2x00_register_write(rt2x00usb, MAC_CSR1, 0x0000);
	rt2x00_register_write(rt2x00usb, TXRX_CSR5, 0x8c8d);
	rt2x00_register_write(rt2x00usb, TXRX_CSR6, 0x8b8a);
	rt2x00_register_write(rt2x00usb, TXRX_CSR7, 0x8687);
	rt2x00_register_write(rt2x00usb, TXRX_CSR8, 0x0085);
	rt2x00_register_write(rt2x00usb, TXRX_CSR21, 0xe78f);
	rt2x00_register_write(rt2x00usb, MAC_CSR9, 0xff1d);
	rt2x00_register_write(rt2x00usb, MAC_CSR1, 0x0004);
	rt2x00_register_write(rt2x00usb, MAC_CSR20, 0x0000);

	reg = 0x0000;
	rt2x00_register_read(rt2x00usb, MAC_CSR0, &reg);
	if(reg >= 0x0003){
		rt2x00_register_read(rt2x00usb, PHY_CSR2, &reg);
		reg = reg & 0xfffd;
	}else{
		reg = 0x3002;
	}
	rt2x00_register_write(rt2x00usb, PHY_CSR2, reg);

	rt2x00_register_write(rt2x00usb, MAC_CSR11, 0x0002);
	rt2x00_register_write(rt2x00usb, MAC_CSR22, 0x0053);
	rt2x00_register_write(rt2x00usb, MAC_CSR15, 0x01ee);
	rt2x00_register_write(rt2x00usb, MAC_CSR16, 0x0000);

	rt2x00_register_read(rt2x00usb, TXRX_CSR0, &reg);
	rt2x00_set_field16_nb(&reg, TXRX_CSR0_IV_OFFSET, IEEE80211_HEADER);
	rt2x00_set_field16_nb(&reg, TXRX_CSR0_KEY_ID, 0xff);
	rt2x00_register_write(rt2x00usb, TXRX_CSR0, reg);

	rt2x00_register_read(rt2x00usb, MAC_CSR8, &reg);
	rt2x00_set_field16_nb(&reg, MAC_CSR8_MAX_FRAME_UNIT, rt2x00usb->rx.entry_size);
	rt2x00_register_write(rt2x00usb, MAC_CSR8, reg);

	rt2x00_register_read(rt2x00usb, MAC_CSR18, &reg);
	rt2x00_set_field16_nb(&reg, MAC_CSR18_DELAY_AFTER_BEACON, 0x5a);
	rt2x00_register_write(rt2x00usb, MAC_CSR18, reg);

	rt2x00_register_read(rt2x00usb, TXRX_CSR1, &reg);
	rt2x00_set_field16_nb(&reg, TXRX_CSR1_AUTO_SEQUENCE, 0x00);
	rt2x00_register_write(rt2x00usb, TXRX_CSR1, reg);

	rt2x00_register_read(rt2x00usb, PHY_CSR4, &reg);
	rt2x00_register_write(rt2x00usb, PHY_CSR4, reg | 0x0001);

	return 0;
}

static void
rt2x00_init_write_mac(struct _rt2x00_usb *rt2x00usb, struct net_device *net_dev)
{
	u16			reg = 0x0000;

	rt2x00_set_field16_nb(&reg, MAC_CSR2_BYTE0, net_dev->dev_addr[0]);
	rt2x00_set_field16_nb(&reg, MAC_CSR2_BYTE1, net_dev->dev_addr[1]);
	rt2x00_register_write(rt2x00usb, MAC_CSR2, reg);

	reg = 0x0000;
	rt2x00_set_field16_nb(&reg, MAC_CSR3_BYTE2, net_dev->dev_addr[2]);
	rt2x00_set_field16_nb(&reg, MAC_CSR3_BYTE3, net_dev->dev_addr[3]);
	rt2x00_register_write(rt2x00usb, MAC_CSR3, reg);

	reg = 0x0000;
	rt2x00_set_field16_nb(&reg, MAC_CSR4_BYTE4, net_dev->dev_addr[4]);
	rt2x00_set_field16_nb(&reg, MAC_CSR4_BYTE5, net_dev->dev_addr[5]);
	rt2x00_register_write(rt2x00usb, MAC_CSR4, reg);
}

static int
rt2x00_init_bbp(struct _rt2x00_usb *rt2x00usb)
{
	u8			value = 0x00;
	u8			reg_id = 0x00;
	u8			counter = 0x00;

	for(counter = 0; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_bbp_regread(rt2x00usb, 0x00, &value);
		if((value != 0xff) && (value != 0x00))
			goto continue_csr_init;
	}

	ERROR("hardware problem, BBP register access failed, aborting.\n");
	return -EACCES;

continue_csr_init:
	rt2x00_bbp_regwrite(rt2x00usb, 3, 0x02);
	rt2x00_bbp_regwrite(rt2x00usb, 4, 0x19);
	rt2x00_bbp_regwrite(rt2x00usb, 14, 0x1c);
	rt2x00_bbp_regwrite(rt2x00usb, 15, 0x30);
	rt2x00_bbp_regwrite(rt2x00usb, 16, 0xac);
	rt2x00_bbp_regwrite(rt2x00usb, 17, 0x48);
	rt2x00_bbp_regwrite(rt2x00usb, 18, 0x18);
	rt2x00_bbp_regwrite(rt2x00usb, 19, 0xff);
	rt2x00_bbp_regwrite(rt2x00usb, 20, 0x1e);
	rt2x00_bbp_regwrite(rt2x00usb, 21, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 22, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 23, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 24, 0x80);
	rt2x00_bbp_regwrite(rt2x00usb, 25, 0x50);
	rt2x00_bbp_regwrite(rt2x00usb, 26, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 27, 0x23);
	rt2x00_bbp_regwrite(rt2x00usb, 30, 0x10);
	rt2x00_bbp_regwrite(rt2x00usb, 31, 0x2b);
	rt2x00_bbp_regwrite(rt2x00usb, 32, 0xb9);
	rt2x00_bbp_regwrite(rt2x00usb, 34, 0x12);
	rt2x00_bbp_regwrite(rt2x00usb, 35, 0x50);
	rt2x00_bbp_regwrite(rt2x00usb, 39, 0xc4);
	rt2x00_bbp_regwrite(rt2x00usb, 40, 0x02);
	rt2x00_bbp_regwrite(rt2x00usb, 41, 0x60);
	rt2x00_bbp_regwrite(rt2x00usb, 53, 0x10);
	rt2x00_bbp_regwrite(rt2x00usb, 54, 0x18);
	rt2x00_bbp_regwrite(rt2x00usb, 56, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 57, 0x10);
	rt2x00_bbp_regwrite(rt2x00usb, 58, 0x08);
	rt2x00_bbp_regwrite(rt2x00usb, 61, 0x60);
	rt2x00_bbp_regwrite(rt2x00usb, 62, 0x10);
	rt2x00_bbp_regwrite(rt2x00usb, 75, 0xff);

	DEBUG("Start reading EEPROM contents...\n");
	for(counter = 0; counter < EEPROM_BBP_SIZE; counter++){
		if(rt2x00usb->eeprom[counter] != 0xffff && rt2x00usb->eeprom[counter] != 0x0000){
			reg_id = rt2x00_get_field16(rt2x00usb->eeprom[counter], EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(rt2x00usb->eeprom[counter], EEPROM_BBP_VALUE);
			DEBUG("BBP reg_id: 0x%02x, value: 0x%02x.\n", reg_id, value);
			rt2x00_bbp_regwrite(rt2x00usb, reg_id, value);
		}
	}
	DEBUG("...End of EEPROM contents.\n");

	return 0;
}

static void
rt2x00_init_ring_rx(struct _rt2x00_device *device, struct _data_ring *ring)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	struct _data_entry	*entry = NULL;
	u8			counter = 0x00;

	entry = (struct _data_entry*)ring->priv;
	for(; counter < ring->max_entries; counter++){
		entry->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		entry->urb->transfer_dma = entry->data_dma;
		usb_fill_bulk_urb(
			entry->urb,
			rt2x00usb->usb_dev,
			usb_rcvbulkpipe(rt2x00usb->usb_dev, 1),
			entry->data_addr,
			ring->entry_size,
			rt2x00_interrupt_rxdone,
			entry);
		usb_submit_urb(entry->urb, GFP_ATOMIC);
		entry++;
	}
}

/*
 * memory ring allocation.
 * rt2x00_usb_allocate_ring will set the size variables.
 * Afterwards it will allocate the required amount of memory.
 * rt2x00_usb_free_ring will check if the pointers are valid,
 * if the pointers are valid the memory will be deallocated.
 */
static int
rt2x00_usb_alloc_ring(
	struct _rt2x00_device *device,
	struct _data_ring *ring,
	const u8 ring_type,
	const u16 max_entries,
	const u16 entry_size,
	const u16 desc_size)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	struct _data_entry	*entry = NULL;
	int			status = 0x00000000;
	u8			counter = 0x00;

	rt2x00_init_ring(device, ring, ring_type, max_entries, entry_size, desc_size);

	ring->data_addr = usb_buffer_alloc(rt2x00usb->usb_dev, ring->mem_size, GFP_KERNEL, &ring->data_dma);
	if(!ring->data_addr)
		return -ENOMEM;

	memset(ring->data_addr, 0x00, ring->mem_size);

	ring->priv = kmalloc(PRIV_SIZE(ring), GFP_KERNEL);
	if(!ring->priv)
		return -ENOMEM;

	memset(ring->priv, 0x00, PRIV_SIZE(ring));

	entry = (struct _data_entry*)ring->priv;
	for(; counter < ring->max_entries; counter++){
		entry->ring = ring;
		entry->ring_type = ring->ring_type;
		entry->status_flags = ENTRY_FREE;
		entry->urb = NULL;
		entry->data_addr = ring->data_addr + (counter * ENTRY_SIZE(ring));
		entry->data_dma = ring->data_dma + (counter * ENTRY_SIZE(ring));
		if(!status)
			entry->urb = usb_alloc_urb(0, GFP_KERNEL);
		if(!entry->urb)
			status = -ENOMEM;
		entry++;
	}

	return status;
}

static int
rt2x00_usb_alloc_rings(struct _rt2x00_device *device)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);

	if(rt2x00_usb_alloc_ring(device, &rt2x00usb->rx, RING_RX, RX_ENTRIES, DATA_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_usb_alloc_ring(device, &rt2x00usb->tx, RING_TX, TX_ENTRIES, DATA_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_usb_alloc_ring(device, &rt2x00usb->atim, RING_ATIM, ATIM_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_usb_alloc_ring(device, &rt2x00usb->prio, RING_PRIO, PRIO_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_usb_alloc_ring(device, &rt2x00usb->beacon, RING_BEACON, BEACON_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)){
		ERROR("ring memory allocation failed.\n");
		return -ENOMEM;
	}

	return 0;
}

static void
rt2x00_usb_free_ring(struct _rt2x00_device *device, struct _data_ring *ring)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	struct _data_entry	*entry = NULL;
	u8			counter = 0x00;

	if(!ring->priv)
		goto exit;

	entry = (struct _data_entry*)ring->priv;
	for(; counter < ring->max_entries; counter++){
		if(!entry->urb)
			break;
		usb_kill_urb(entry->urb);
		usb_free_urb(entry->urb);
		entry++;
	}

	kfree(ring->priv);
	ring->priv = NULL;

exit:
	if(ring->data_addr)
		usb_buffer_free(rt2x00usb->usb_dev, ring->mem_size, ring->data_addr, ring->data_dma);
	ring->data_addr = NULL;

	rt2x00_deinit_ring(ring);
}

static void
rt2x00_usb_free_rings(struct _rt2x00_device *device)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);

	rt2x00_usb_free_ring(device, &rt2x00usb->rx);
	rt2x00_usb_free_ring(device, &rt2x00usb->tx);
	rt2x00_usb_free_ring(device, &rt2x00usb->atim);
	rt2x00_usb_free_ring(device, &rt2x00usb->prio);
	rt2x00_usb_free_ring(device, &rt2x00usb->beacon);
}

/*
 * Radio control.
 */
static int
rt2x00_dev_radio_on(struct _rt2x00_device *device)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	u16			reg = 0x0000;

	if(rt2x00_usb_alloc_rings(device))
		goto exit_fail;

	if(rt2x00_init_registers(rt2x00usb))
		goto exit_fail;

	rt2x00_init_write_mac(rt2x00usb, device->net_dev);

	if(rt2x00_init_bbp(rt2x00usb))
		goto exit_fail;

	rt2x00_init_ring_rx(device, &rt2x00usb->rx);

	rt2x00_register_read(rt2x00usb, TXRX_CSR2, &reg);
	rt2x00_set_field16_nb(&reg, TXRX_CSR2_DISABLE_RX, 0);
	rt2x00_register_write(rt2x00usb, TXRX_CSR2, reg);

	return 0;

exit_fail:
	rt2x00_usb_free_rings(device);

	return -ENOMEM;
}

static int
rt2x00_dev_radio_off(struct _rt2x00_device *device)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	u16			reg = 0x0000;

	rt2x00_register_read(rt2x00usb, TXRX_CSR2, &reg);
	rt2x00_set_field16_nb(&reg, TXRX_CSR2_DISABLE_RX, 1);
	rt2x00_register_write(rt2x00usb, TXRX_CSR2, reg);

	rt2x00_register_write(rt2x00usb, MAC_CSR20, 0);

	rt2x00_vendor_request(rt2x00usb, USB_RX_CONTROL, USB_VENDOR_REQUEST_OUT, 0x00, 0x00, NULL, 0);

	rt2x00_register_write(rt2x00usb, MAC_CSR13, 0x2121);
	rt2x00_register_write(rt2x00usb, MAC_CSR14, 0x2121);

	rt2x00_usb_free_rings(device);

	return 0;
}

/*
 * Configuration handlers.
 */
static void
rt2x00_dev_update_bssid(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			reg[3];

	memset(&reg, 0x00, sizeof(reg));

	rt2x00_set_field16_nb(&reg[0], MAC_CSR5_BYTE0, config->active.bssid[0]);
	rt2x00_set_field16_nb(&reg[0], MAC_CSR5_BYTE1, config->active.bssid[1]);
	rt2x00_set_field16_nb(&reg[1], MAC_CSR6_BYTE2, config->active.bssid[2]);
	rt2x00_set_field16_nb(&reg[1], MAC_CSR6_BYTE3, config->active.bssid[3]);
	rt2x00_set_field16_nb(&reg[2], MAC_CSR7_BYTE4, config->active.bssid[4]);
	rt2x00_set_field16_nb(&reg[2], MAC_CSR7_BYTE5, config->active.bssid[5]);

	rt2x00_register_multiwrite(rt2x00usb, MAC_CSR5, &reg[0], sizeof(reg));
}

static void
rt2x00_dev_update_packet_filter(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			reg = 0x0000;

	rt2x00_register_read(rt2x00usb, TXRX_CSR2, &reg);

	if(config->active.iw_mode == IW_MODE_ADHOC
	|| config->active.iw_mode == IW_MODE_INFRA
	|| config->active.iw_mode == IW_MODE_AUTO)
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_TODS, 1);
	else
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_TODS, 0);

	if(config->active.flags & CONFIG_ACCEPT_PROMISC)
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_NOT_TO_ME, 0);
	else
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_NOT_TO_ME, 1);

	rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_CRC, 1);
	if(config->active.iw_mode == IW_MODE_MONITOR){
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_PHYSICAL, 0);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_CONTROL, 0);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_VERSION_ERROR, 0);
	}else{
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_PHYSICAL, 1);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_CONTROL, 1);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_VERSION_ERROR, 1);
	}

	if(config->active.flags & CONFIG_ACCEPT_MULTICAST){
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_MCAST, 0);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_BCAST, 0);
	}else{
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_MCAST, 1);
		rt2x00_set_field16_nb(&reg, TXRX_CSR2_DROP_BCAST, 1);
	}

	rt2x00_register_write(rt2x00usb, TXRX_CSR2, reg);
}

static void
rt2x00_dev_update_channel(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u8			txpower = rt2x00_get_txpower(&rt2x00usb->chip, config->active.txpower);

	if(rt2x00_get_rf_value(&rt2x00usb->chip, config->active.channel, &rt2x00usb->channel)){
		ERROR("RF values for chip %04x and channel %d not found.\n", rt2x00_get_rf(&rt2x00usb->chip), config->active.channel);
		return;
	}

	INFO("Switching to channel %d. RF1: 0x%08x, RF2: 0x%08x, RF3: 0x%08x, RF4: 0x%08x.\n",
		config->active.channel, rt2x00usb->channel.rf1, rt2x00usb->channel.rf2,
		rt2x00usb->channel.rf3, rt2x00usb->channel.rf4);

	rt2x00_set_field32_nb(&rt2x00usb->channel.rf3, RF3_TXPOWER, txpower);

	/*
	 * For RT2525E we should first set the channel to half band higher.
	 */
	if(rt2x00_rf(&rt2x00usb->chip, RF2525E)){
		rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf2 + 0x00000010);
		if(rt2x00usb->channel.rf4)
			rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf4);
	}

	rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf1);
	rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf2);
	rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf3);
	if(rt2x00usb->channel.rf4)
		rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf4);
}

static void
rt2x00_dev_update_rate(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			reg = 0x0000;
	u16			value = 0x0000;
	u8			counter = 0x00;

	rt2x00_register_read(rt2x00usb, TXRX_CSR1, &reg);
	value = config->sifs + (2 * config->slot_time) + config->plcp
		+ get_preamble(config)
		+ get_duration(ACK_SIZE, capabilities.bitrate[0]);
	rt2x00_set_field16_nb(&reg, TXRX_CSR1_ACK_TIMEOUT, value);

	rt2x00_set_field16_nb(&reg, TXRX_CSR1_TSF_OFFSET, 0x18);

	rt2x00_register_write(rt2x00usb, TXRX_CSR1, reg);

	for(counter = 0; counter < 12; counter++){
		reg |= 0x0001 << counter;
		if(capabilities.bitrate[counter] == config->active.bitrate)
			break;
	}

	rt2x00_register_write(rt2x00usb, TXRX_CSR11, reg);
}

static void
rt2x00_dev_update_txpower(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u8			txpower = rt2x00_get_txpower(&rt2x00usb->chip, config->active.txpower);

	rt2x00_set_field32_nb(&rt2x00usb->channel.rf3, RF3_TXPOWER, txpower);
	rt2x00_rf_regwrite(rt2x00usb, rt2x00usb->channel.rf3);
}

static void
rt2x00_dev_update_antenna(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			csr5_reg = 0x0000;
	u16			csr6_reg = 0x0000;
	u8			tx_reg = 0x0000;
	u8			rx_reg = 0x0000;

	rt2x00_bbp_regread(rt2x00usb, 2, &tx_reg);
	rt2x00_bbp_regread(rt2x00usb, 14, &rx_reg);
	rt2x00_register_read(rt2x00usb, PHY_CSR5, &csr5_reg);
	rt2x00_register_read(rt2x00usb, PHY_CSR6, &csr6_reg);

	csr5_reg &= ~0x0003;
	csr6_reg &= ~0x0003;
	tx_reg &= ~0x03;
	rx_reg &= ~0x03;

	if(config->active.antenna_flags & ANTENNA_TX_DIV){
		tx_reg |= 0x01;
		csr5_reg |= 0x0001;
		csr6_reg |= 0x0001;
	}else if(config->active.antenna_flags & ANTENNA_TX_A){
		tx_reg |= 0x00;
		csr5_reg |= 0x0000;
		csr6_reg |= 0x0000;
	}else if(config->active.antenna_flags & ANTENNA_TX_B){
		tx_reg |= 0x02;
		csr5_reg |= 0x0002;
		csr6_reg |= 0x0002;
	}

	if(config->active.antenna_flags & ANTENNA_RX_DIV)
		rx_reg |= 0x01;
	else if(config->active.antenna_flags & ANTENNA_RX_A)
		rx_reg |= 0x00;
	else if(config->active.antenna_flags & ANTENNA_RX_B)
		rx_reg |= 0x02;

	/*
	 * RT2525E needs to flip TX I/Q but not RX I/Q.
	 */
	if(rt2x00_rf(&rt2x00usb->chip, RF2525E)){
		tx_reg |= 0x04;
		rx_reg &= ~0x04;
		csr5_reg |= 0x0004;
		csr6_reg |= 0x0004;
	}
	/*
	 * RT5222 needs to flip TX I/Q.
	 */
	if(rt2x00_rf(&rt2x00usb->chip, RF5222)){
		tx_reg |= 0x04;
		csr5_reg |= 0x0004;
		csr6_reg |= 0x0004;
	}

	rt2x00_bbp_regwrite(rt2x00usb, 2, tx_reg);
	rt2x00_bbp_regwrite(rt2x00usb, 14, rx_reg);
	rt2x00_register_write(rt2x00usb, PHY_CSR5, csr5_reg);
	rt2x00_register_write(rt2x00usb, PHY_CSR6, csr6_reg);
}

static void
rt2x00_dev_update_duration(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	rt2x00usb->long_retry = config->active.long_retry;
	rt2x00usb->short_retry = config->active.short_retry;

	rt2x00_register_write(rt2x00usb, MAC_CSR10, config->slot_time);
}

static void
rt2x00_dev_update_preamble(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	u16			reg = 0x0000;

	rt2x00_register_read(rt2x00usb, TXRX_CSR10, &reg);

	if(config->active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		reg |= 0x0004;
	else
		reg &= ~0x0004;

	rt2x00_register_write(rt2x00usb, TXRX_CSR10, reg);
}

static void
rt2x00_dev_update_sensitivity(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	rt2x00usb->sensitivity = config->active.sensitivity;
}

static void
rt2x00_dev_update_led(struct _rt2x00_usb *rt2x00usb, struct _rt2x00_config *config)
{
	rt2x00_register_write(rt2x00usb, MAC_CSR20, config->led_status ? 3 : 0);
}

static int
rt2x00_dev_update_config(struct _rt2x00_device *device, struct _rt2x00_config *config, u16 update_flags)
{
	struct _rt2x00_usb 	*rt2x00usb = rt2x00_priv(device);

	if(update_flags & UPDATE_BSSID)
		rt2x00_dev_update_bssid(rt2x00usb, config);

	if(update_flags & UPDATE_PACKET_FILTER)
		rt2x00_dev_update_packet_filter(rt2x00usb, config);

	if(update_flags & UPDATE_CHANNEL)
		rt2x00_dev_update_channel(rt2x00usb, config);

	if(update_flags & UPDATE_BITRATE)
		rt2x00_dev_update_rate(rt2x00usb, config);

	if(update_flags & UPDATE_TXPOWER)
		rt2x00_dev_update_txpower(rt2x00usb, config);

	if(update_flags & UPDATE_ANTENNA)
		rt2x00_dev_update_antenna(rt2x00usb, config);

	if(update_flags & UPDATE_DURATION || update_flags & UPDATE_RETRY)
		rt2x00_dev_update_duration(rt2x00usb, config);

	if(update_flags & UPDATE_PREAMBLE)
		rt2x00_dev_update_preamble(rt2x00usb, config);

	if(update_flags & UPDATE_SENSITIVITY)
		rt2x00_dev_update_sensitivity(rt2x00usb, config);

	if(update_flags & UPDATE_LED_STATUS)
		rt2x00_dev_update_led(rt2x00usb, config);

	return 0;
}

static int
rt2x00_dev_update_stats(struct _rt2x00_device *device, struct _rt2x00_stats *stats)
{
	struct _rt2x00_usb 	*rt2x00usb = rt2x00_priv(device);

	rt2x00_bbp_regread(rt2x00usb, 17, &stats->noise);
	rt2x00_bbp_regread(rt2x00usb, 0, &stats->signal);

	return 0;
}

/*
 * xmit handlers.
 */
static int
rt2x00_dev_test_tx(struct _rt2x00_device *device, u8 fragments)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);

	return fragments > rt2x00_ring_free_entries(&rt2x00usb->tx);
}

static void
rt2x00_kick_tx(struct _rt2x00_usb *rt2x00usb, struct _data_ring *ring)
{
	struct _data_entry	*entry = NULL;
	u8			counter = 0x00;

	for(; counter < ring->max_entries; counter++){
		entry = (struct _data_entry*)__ENTRY_ADDR(ring, counter);
		if(entry->status_flags == ENTRY_QUEUED){
			entry->urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
			entry->urb->transfer_dma = entry->data_dma;
			usb_fill_bulk_urb(
				entry->urb,
				rt2x00usb->usb_dev,
				usb_sndbulkpipe(rt2x00usb->usb_dev, 1),
				entry->data_addr,
				entry->packet_size + sizeof(struct _txd),
				rt2x00_interrupt_txdone,
				entry);
			usb_submit_urb(entry->urb, GFP_ATOMIC);

			entry->status_flags = ENTRY_BUSY;
		}
	}
}

/*
 * PLCP_SIGNAL, PLCP_SERVICE, PLCP_LENGTH_LOW and PLCP_LENGTH_HIGH are BBP registers.
 * For PLCP_SIGNAL we can optionally enable SHORT_PREAMBLE.
 * For PLCP_SERVICE we can set the length extension bit according to
 * 802.11b standard 18.2.3.5.
 */
static void
rt2x00_write_tx_desc(struct _rt2x00_usb *rt2x00usb, struct _txd *txd, u32 packet_size, u16 rate, u8 priority, u16 xmit_flags)
{
	u32			residual = 0x00000000;
	u8			signal = 0x0000;
	u8			service = 0x0000;
	u8			length_low = 0x0000;
	u8			length_high = 0x0000;

	rt2x00_set_field32(&txd->word0, TXD_W0_ACK, (xmit_flags & XMIT_ACK) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_TIMESTAMP, (xmit_flags & XMIT_TIMESTAMP) ? 1 : 0);
	if(xmit_flags & XMIT_LONG_RETRY)
		rt2x00_set_field32(&txd->word0, TXD_W0_RETRY_LIMIT, rt2x00usb->long_retry);
	else
		rt2x00_set_field32(&txd->word0, TXD_W0_RETRY_LIMIT, rt2x00usb->short_retry);
	rt2x00_set_field32(&txd->word0, TXD_W0_MORE_FRAG, (xmit_flags & XMIT_MORE_FRAGS) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_OFDM, (xmit_flags & XMIT_OFDM) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_NEW_SEQ, (xmit_flags & XMIT_NEW_SEQUENCE) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_DATABYTE_COUNT, packet_size);

	/* For non encrypted frames add 4 length for plcp calculations */
	packet_size += 4;

	if(xmit_flags & XMIT_OFDM){
		/*
		 * Convert length to microseconds.
		 */
		length_high = (packet_size >> 6) & 0x3f;
		length_low = (packet_size & 0x3f);
	}else{
		residual = get_duration_res(packet_size, rate);
		packet_size = get_duration(packet_size, rate);

		if(residual != 0)
			packet_size++;

		length_high = (packet_size >> 8);
		length_low = (packet_size & 0xff);
	}

	signal = rt2x00_get_plcp(rate);
	if(xmit_flags & XMIT_SHORT_PREAMBLE)
		signal |= 0x08;

	service = 0x04;
	if(residual <= (8 % 11))
		service |= 0x80;

	rt2x00_set_field32(&txd->word2, TXD_W2_PLCP_SIGNAL, signal);
	rt2x00_set_field32(&txd->word2, TXD_W2_PLCP_SERVICE, service);
	rt2x00_set_field32(&txd->word2, TXD_W2_PLCP_LENGTH_LOW, length_low);
	rt2x00_set_field32(&txd->word2, TXD_W2_PLCP_LENGTH_HIGH, length_high);

	/*
	 * Set priority according to 802.11e/d4.4 June, 2003.
	 */
	if(priority <= 2){
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMIN, 3);
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMAX, 8);
		rt2x00_set_field32(&txd->word1, TXD_W1_AIFS, 2);
	}else if(priority == 3){
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMIN, 3);
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMAX, 8);
		rt2x00_set_field32(&txd->word1, TXD_W1_AIFS, 1);
	}else if(priority <= 5){
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMIN, 2);
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMAX, 3);
		rt2x00_set_field32(&txd->word1, TXD_W1_AIFS, 1);
	}else{
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMIN, 1);
		rt2x00_set_field32(&txd->word1, TXD_W1_CWMAX, 2);
		rt2x00_set_field32(&txd->word1, TXD_W1_AIFS, 1);
	}

	if(xmit_flags & XMIT_IFS_BACKOFF)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 0);
	else if(xmit_flags & XMIT_IFS_SIFS)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 1);
	else if(xmit_flags & XMIT_IFS_NEW_BACKOFF)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 2);
	else if(xmit_flags & XMIT_IFS_NONE)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 3);
}

static int
rt2x00_dev_xmit_packet(struct _rt2x00_device *device, struct sk_buff *skb, u8 ring_type, u16 rate, u16 xmit_flags)
{
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	struct _data_ring	*ring = NULL;
	struct _data_entry	*entry = NULL;

	if(ring_type == RING_TX)
		ring = &rt2x00usb->tx;
	if(ring_type == RING_PRIO)
		ring = &rt2x00usb->prio;
	if(ring_type == RING_ATIM)
		ring = &rt2x00usb->atim;
	if(ring_type == RING_BEACON)
		ring = &rt2x00usb->beacon;

	if(skb){
		entry = ENTRY_ADDR(ring);

		if(ENTRY_ADDR(ring)->status_flags != ENTRY_FREE)
			return -ENOMEM;

		memcpy(TX_DATA_ADDR(ring), skb->data, skb->len);
		rt2x00_write_tx_desc(rt2x00usb, TX_DESC_ADDR(ring), skb->len, rate, skb->priority, xmit_flags);
	
		entry->status_flags = ENTRY_QUEUED;
		entry->packet_size = skb->len;
	
		rt2x00_ring_index_inc(ring);
	}

	if(xmit_flags & XMIT_START)
		rt2x00_kick_tx(rt2x00usb, ring);

	return 0;
}

/*
 * USB device handlers for usage by core module.
 */
static struct _rt2x00_dev_handler rt2x00_usb_handler = {
	.dev_module		= THIS_MODULE,
	.dev_probe		= rt2x00_dev_probe,
	.dev_radio_on		= rt2x00_dev_radio_on,
	.dev_radio_off		= rt2x00_dev_radio_off,
	.dev_update_config	= rt2x00_dev_update_config,
	.dev_update_stats	= rt2x00_dev_update_stats,
	.dev_test_tx		= rt2x00_dev_test_tx,
	.dev_xmit_packet	= rt2x00_dev_xmit_packet,
};

static int
rt2x00_usb_probe(struct usb_interface *usb_intf, const struct usb_device_id *id)
{
	struct usb_device	*usb_dev = interface_to_usbdev(usb_intf);
	struct net_device	*net_dev = NULL;

	if(id->driver_info != RT2570){
		ERROR("Detected device not supported.\n");
		return -ENODEV;
	}

	usb_dev = usb_get_dev(usb_dev);

	net_dev = rt2x00_core_probe(&rt2x00_usb_handler, usb_dev, sizeof(struct _rt2x00_usb), &usb_dev->dev);
	if(!net_dev){
		ERROR("net_device allocation failed.\n");
		usb_put_dev(usb_dev);
		return -ENOMEM;
	}

	SET_NETDEV_DEV(net_dev, &usb_intf->dev);
	SET_MODULE_OWNER(net_dev);

	usb_set_intfdata(usb_intf, net_dev);

	return 0;
}

static void
rt2x00_usb_disconnect(struct usb_interface *usb_intf)
{
	struct usb_device	*usb_dev = interface_to_usbdev(usb_intf);
	struct net_device	*net_dev = usb_get_intfdata(usb_intf);

	rt2x00_core_remove(net_dev);

	usb_set_intfdata(usb_intf, NULL);

	usb_put_dev(usb_dev);
}

#ifdef CONFIG_PM
static int
rt2x00_usb_suspend(struct usb_interface *usb_intf, pm_message_t state)
{
	struct net_device	*net_dev = usb_get_intfdata(usb_intf);
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	u16			reg = 0x0000;

	if(!test_and_clear_bit(DEVICE_AWAKE, &device->flags)){
		NOTICE("Device already asleep.\n");
		return 0;
	}

	if(rt2x00_suspend(device))
		return -EBUSY;

	NOTICE("Going to sleep.\n");

	netif_device_detach(net_dev);

	rt2x00_set_field16_nb(&reg, MAC_CSR17_SET_STATE, 1);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_BBP_DESIRE_STATE, 1);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_RF_DESIRE_STATE, 1);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_PUT_TO_SLEEP, 1);

	rt2x00_register_write(rt2x00usb, MAC_CSR17, reg);

	return 0;
}

static int
rt2x00_usb_resume(struct usb_interface *usb_intf)
{
	struct net_device	*net_dev = usb_get_intfdata(usb_intf);
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_usb	*rt2x00usb = rt2x00_priv(device);
	u16			reg = 0x0000;

	if(test_and_set_bit(DEVICE_AWAKE, &device->flags)){
		NOTICE("Device already awake.\n");
		return 0;
	}

	NOTICE("Waking up.\n");

	rt2x00_set_field16_nb(&reg, MAC_CSR17_SET_STATE, 1);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_BBP_DESIRE_STATE, 3);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_RF_DESIRE_STATE, 3);
	rt2x00_set_field16_nb(&reg, MAC_CSR17_PUT_TO_SLEEP, 0);

	rt2x00_register_write(rt2x00usb, MAC_CSR17, reg);

	netif_device_attach(net_dev);

	return rt2x00_resume(device);
}
#endif /* CONFIG_PM */

/*
 * RT2x00 USB module information.
 */
static char version[] = DRV_NAME " - " DRV_VERSION " (" DRV_RELDATE ") by " DRV_PROJECT;

static struct usb_device_id rt2x00_device_usb_tbl[] = {
	{ USB_DEVICE(0x0b05, 0x1706), .driver_info = RT2570},	/* ASUS */
	{ USB_DEVICE(0x0b05, 0x1707), .driver_info = RT2570},	/* ASUS */
	{ USB_DEVICE(0x050d, 0x7050), .driver_info = RT2570},	/* Belkin */
	{ USB_DEVICE(0x050d, 0x705a), .driver_info = RT2570},	/* Belkin */
	{ USB_DEVICE(0x13b1, 0x000d), .driver_info = RT2570},	/* Cisco Systems */
	{ USB_DEVICE(0x13b1, 0x0011), .driver_info = RT2570},	/* Cisco Systems */
	{ USB_DEVICE(0x13b1, 0x001a), .driver_info = RT2570},	/* Cisco Systems */
	{ USB_DEVICE(0x14b2, 0x3c02), .driver_info = RT2570},	/* Conceptronic */
	{ USB_DEVICE(0x2001, 0x3c00), .driver_info = RT2570},	/* D-LINK */
	{ USB_DEVICE(0x1044, 0x8001), .driver_info = RT2570},	/* Gigabyte */
	{ USB_DEVICE(0x1044, 0x8007), .driver_info = RT2570},	/* Gigabyte */
	{ USB_DEVICE(0x06f8, 0xe000), .driver_info = RT2570},	/* Hercules */
	{ USB_DEVICE(0x0411, 0x0066), .driver_info = RT2570},	/* Melco */
	{ USB_DEVICE(0x0411, 0x0067), .driver_info = RT2570},	/* Melco */
	{ USB_DEVICE(0x0411, 0x008b), .driver_info = RT2570},	/* Melco */
	{ USB_DEVICE(0x0db0, 0x6861), .driver_info = RT2570},	/* MSI */
	{ USB_DEVICE(0x0db0, 0x6865), .driver_info = RT2570},	/* MSI */
	{ USB_DEVICE(0x0db0, 0x6869), .driver_info = RT2570},	/* MSI */
	{ USB_DEVICE(0x148f, 0x1706), .driver_info = RT2570},	/* Ralink */
	{ USB_DEVICE(0x148f, 0x2570), .driver_info = RT2570},	/* Ralink */
	{ USB_DEVICE(0x148f, 0x2573), .driver_info = RT2570},	/* Ralink */
	{ USB_DEVICE(0x148f, 0x9020), .driver_info = RT2570},	/* Ralink */
	{ USB_DEVICE(0x0707, 0xee13), .driver_info = RT2570},	/* SMC */
	{ USB_DEVICE(0x114b, 0x0110), .driver_info = RT2570},	/* Spairon */
	{0,}
};

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2500 USB Wireless LAN driver.");
MODULE_SUPPORTED_DEVICE("Ralink RT2570 USB chipset based cards");
MODULE_DEVICE_TABLE(usb, rt2x00_device_usb_tbl);
MODULE_LICENSE("GPL");

#ifdef CONFIG_RT2X00_DEBUG
module_param_named(debug, rt2x00_debug_level, bool, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(debug, "Set this parameter to 1 to enable debug output.");
#endif /* CONFIG_RT2X00_DEBUG */

static struct usb_driver rt2x00_usb_driver = {
	.owner		= THIS_MODULE,
	.name		= DRV_NAME,
	.id_table	= rt2x00_device_usb_tbl,
	.probe		= rt2x00_usb_probe,
	.disconnect	= rt2x00_usb_disconnect,
#ifdef CONFIG_PM
	.suspend	= rt2x00_usb_suspend,
	.resume		= rt2x00_usb_resume,
#endif /* CONFIG_PM */
};

static int __init rt2x00_usb_init(void)
{
	printk(KERN_INFO "Loading module: %s\n", version);
	return usb_register(&rt2x00_usb_driver);
}

static void __exit rt2x00_usb_exit(void)
{
	printk(KERN_INFO "Unloading module: %s\n", version);
	usb_deregister(&rt2x00_usb_driver);
}

module_init(rt2x00_usb_init);
module_exit(rt2x00_usb_exit);
