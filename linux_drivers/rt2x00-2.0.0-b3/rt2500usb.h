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
	Abstract: Data structures and registers for the rt2500usb module.
	Supported chipsets: RT2570.
 */

#ifndef RT2X00USB_H
#define RT2X00USB_H

#include "rt2x00dev.h"

/*
 * RT chip defines
 */
#define RT2570				0x1201

/*
 * RF chip defines
 */
#define RF2522				0x0000
#define RF2523				0x0001
#define RF2524				0x0002
#define RF2525				0x0003
#define RF2525E				0x0005
#define RF5222				0x0010

/*
 * Registers
 */

/*
 * Control/Status Registers(CSR).
 */
#define MAC_CSR0			0x0400		/* ASIC	version. */
#define MAC_CSR1			0x0402		/* system control. */
#define MAC_CSR2			0x0404		/* MAC addr0. */
#define MAC_CSR3			0x0406		/* MAC addr1. */
#define MAC_CSR4			0X0408		/* MAC addr2. */
#define MAC_CSR5			0x040a		/* BSSID0. */
#define MAC_CSR6			0x040c		/* BSSID1. */
#define MAC_CSR7			0x040e		/* BSSID2. */
#define MAC_CSR8			0x0410		/* Max frame length. */
#define MAC_CSR9			0x0412		/* Timer control. */
#define MAC_CSR10			0x0414		/* Slot time. */
#define MAC_CSR11			0x0416		/* IFS. */
#define MAC_CSR12			0x0418		/* EIFS. */
#define MAC_CSR13			0x041a		/* Power mode0. */
#define MAC_CSR14			0x041c		/* Power mode1. */
#define MAC_CSR15			0x041e		/* Power saving transition0. */
#define MAC_CSR16			0x0420		/* Power saving transition1. */
#define MAC_CSR17			0x0422		/* Power state control. */
#define MAC_CSR18			0x0424		/* Auto wake-up control. */
#define MAC_CSR19			0x0426		/* GPIO control. */
#define MAC_CSR20			0x0428		/* LED control0. */
#define MAC_CSR21			0x042a		/* LED control1. */
#define MAC_CSR22			0x042c		/* LED control1. */

/*
 * Transmit related CSRs.
 */
#define TXRX_CSR0			0x0440		/* Security control. */
#define TXRX_CSR1			0x0442		/* TX configuration. */
#define TXRX_CSR2			0x0444		/* RX control. */
#define TXRX_CSR3			0x0446		/* CCK RX BBP ID. */
#define TXRX_CSR4			0x0448		/* OFDM RX BBP ID. */
#define TXRX_CSR5			0x044a		/* CCK TX BBP ID0. */
#define TXRX_CSR6			0x044c		/* CCK TX BBP ID1. */
#define TXRX_CSR7			0x044e		/* OFDM TX BBP ID0. */
#define TXRX_CSR8			0x0450		/* OFDM TX BBP ID1. */
#define TXRX_CSR9			0x0452		/* TX ACK time-out. */
#define TXRX_CSR10			0x0454		/* Auto responder control. */
#define TXRX_CSR11			0x0456		/* Auto responder basic rate. */
#define TXRX_CSR12			0x0458		/* ACK/CTS time0. */
#define TXRX_CSR13			0x045a		/* ACK/CTS time1. */
#define TXRX_CSR14			0x045c		/* ACK/CTS time2. */
#define TXRX_CSR15			0x045e		/* ACK/CTS time3. */
#define TXRX_CSR16			0x0460		/* ACK/CTS time4. */
#define TXRX_CSR17			0x0462		/* ACK/CTS time5. */
#define TXRX_CSR18			0x0464		/* Beacon interval. */
#define TXRX_CSR19			0x0466		/* Beacon/sync control. */
#define TXRX_CSR20			0x0468		/* Beacon alignment. */
#define TXRX_CSR21			0x046a		/* Blue. */

/*
 * Encryption related CSRs.
 */
#define SEC_CSR0			0x0480		/* Shared key 0, word 0. */
#define SEC_CSR1			0x0482		/* Shared key 0, word 1. */
#define SEC_CSR2			0x0484		/* Shared key 0, word 2. */
#define SEC_CSR3			0x0486		/* Shared key 0, word 3. */
#define SEC_CSR4			0x0488		/* Shared key 0, word 4. */
#define SEC_CSR5			0x048a		/* Shared key 0, word 5. */
#define SEC_CSR6			0x048c		/* Shared key 0, word 6. */
#define SEC_CSR7			0x048e		/* Shared key 0, word 7. */
#define SEC_CSR8			0x0490		/* Shared key 1, word 0. */
#define SEC_CSR9			0x0492		/* Shared key 1, word 1. */
#define SEC_CSR10			0x0494		/* Shared key 1, word 2. */
#define SEC_CSR11			0x0496		/* Shared key 1, word 3. */
#define SEC_CSR12			0x0498		/* Shared key 1, word 4. */
#define SEC_CSR13			0x049a		/* Shared key 1, word 5. */
#define SEC_CSR14			0x049c		/* Shared key 1, word 6. */
#define SEC_CSR15			0x049e		/* Shared key 1, word 7. */
#define SEC_CSR16			0x04a0		/* Shared key 2, word 0. */
#define SEC_CSR17			0x04a2		/* Shared key 2, word 1. */
#define SEC_CSR18			0X04A4		/* Shared key 2, word 2. */
#define SEC_CSR19			0x04a6		/* Shared key 2, word 3. */
#define SEC_CSR20			0x04a8		/* Shared key 2, word 4. */
#define SEC_CSR21			0x04aa		/* Shared key 2, word 5. */
#define SEC_CSR22			0x04ac		/* Shared key 2, word 6. */
#define SEC_CSR23			0x04ae		/* Shared key 2, word 7. */
#define SEC_CSR24			0x04b0		/* Shared key 3, word 0. */
#define SEC_CSR25			0x04b2		/* Shared key 3, word 1. */
#define SEC_CSR26			0x04b4		/* Shared key 3, word 2. */
#define SEC_CSR27			0x04b6		/* Shared key 3, word 3. */
#define SEC_CSR28			0x04b8		/* Shared key 3, word 4. */
#define SEC_CSR29			0x04ba		/* Shared key 3, word 5. */
#define SEC_CSR30			0x04bc		/* Shared key 3, word 6. */
#define SEC_CSR31			0x04be		/* Shared key 3, word 7. */

/*
 * PHY control registers.
 */
#define PHY_CSR0			0x04c0		/* RF switching timing control. */
#define PHY_CSR1			0x04c2		/* TX PA configuration. */
#define PHY_CSR2			0x04c4		/* TX MAC configuration. */
#define PHY_CSR3			0x04c6		/* RX MAC configuration. */
#define PHY_CSR4			0x04c8		/* Interface configuration. */
#define PHY_CSR5			0x04ca		/* BBP pre-TX CCK. */
#define PHY_CSR6			0x04cc		/* BBP pre-TX OFDM. */
#define PHY_CSR7			0x04ce		/* BBP serial control. */
#define PHY_CSR8			0x04d0		/* BBP serial status. */
#define PHY_CSR9			0x04d2		/* RF serial control0. */
#define PHY_CSR10			0x04d4		/* RF serial control1. */

/*
 * Statistic Register.
 */
#define STA_CSR0			0x04e0		/* FCS error. */
#define STA_CSR1			0x04e2		/* PLCP error. */
#define STA_CSR2			0x04e4		/* LONG error. */
#define STA_CSR3			0x04e6		/* CCA false alarm. */
#define STA_CSR4			0x04e8		/* RX FIFO overflow. */
#define STA_CSR5			0x04ea		/* Beacon sent counter. */
#define STA_CSR6			0x04ec
#define STA_CSR7			0x04ee
#define STA_CSR8			0x04f0
#define STA_CSR9			0x04f2
#define STA_CSR10			0x04f4

/*
 * EEPROM addresses
 */
#define EEPROM_MAC_ADDR			0x0004
#define EEPROM_ANTENNA			0x0016
#define EEPROM_GEOGRAPHY		0x001a
#define EEPROM_BBP_START		0x001c

#define EEPROM_BBP_SIZE			16

/*
 * Control/Status Registers(CSR).
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * MAC_CSR2: STA MAC register 0.
 */
#define MAC_CSR2_BYTE0			FIELD16(0, 0x00ff)		/* MAC address byte 0. */
#define MAC_CSR2_BYTE1			FIELD16(8, 0xff00)		/* MAC address byte 1. */

/*
 * MAC_CSR3: STA MAC register 1.
 */
#define MAC_CSR3_BYTE2			FIELD16(0, 0x00ff)		/* MAC address byte 2. */
#define MAC_CSR3_BYTE3			FIELD16(8, 0xff00)		/* MAC address byte 3. */

/*
 * MAC_CSR4: STA MAC register 2.
 */
#define MAC_CSR4_BYTE4			FIELD16(0, 0x00ff)		/* MAC address byte 4. */
#define MAC_CSR4_BYTE5			FIELD16(8, 0xff00)		/* MAC address byte 5. */

/*
 * MAC_CSR5: BSSID register 0.
 */
#define MAC_CSR5_BYTE0			FIELD16(0, 0x00ff)		/* BSSID address byte 0. */
#define MAC_CSR5_BYTE1			FIELD16(8, 0xff00)		/* BSSID address byte 1. */

/*
 * MAC_CSR6: BSSID register 1.
 */
#define MAC_CSR6_BYTE2			FIELD16(0, 0x00ff)		/* BSSID address byte 2. */
#define MAC_CSR6_BYTE3			FIELD16(8, 0xff00)		/* BSSID address byte 3. */

/*
 * MAC_CSR7: BSSID register 2.
 */
#define MAC_CSR7_BYTE4			FIELD16(0, 0x00ff)		/* BSSID address byte 4. */
#define MAC_CSR7_BYTE5			FIELD16(8, 0xff00)		/* BSSID address byte 5. */

/*
 * MAC_CSR8: Max frame length.
 */
#define MAC_CSR8_MAX_FRAME_UNIT		FIELD16(0, 0x0fff)		/* Max frame length. */

/*
 * MAC_CSR17: Manual power control / status register.
 */
#define MAC_CSR17_SET_STATE		FIELD16(0, 0x0001)
#define MAC_CSR17_BBP_DESIRE_STATE	FIELD16(1, 0x0006)
#define MAC_CSR17_RF_DESIRE_STATE	FIELD16(3, 0x0018)
#define MAC_CSR17_BBP_CURRENT_STATE	FIELD16(5, 0x0060)
#define MAC_CSR17_RF_CURRENT_STATE	FIELD16(7, 0x0180)
#define MAC_CSR17_PUT_TO_SLEEP		FIELD16(9, 0x0200)

/*
 * MAC_CSR18: Wakeup timer register.
 */
#define MAC_CSR18_DELAY_AFTER_BEACON	FIELD16(0, 0x00ff)		/* Delay after Tbcn expired in units of 1/16 TU. */
#define MAC_CSR18_BEACONS_BEFORE_WAKEUP	FIELD16(8, 0x7f00)		/* Number of beacon before wakeup. */
#define MAC_CSR18_AUTO_WAKE		FIELD16(15, 0x8000)		/* Enable auto wakeup / sleep mechanism. */

/*
 * Transmit related CSRs.
 */

/*
 * TXRX_CSR0: Security control register.
 */
#define TXRX_CSR0_ALGORITHM		FIELD16(0, 0x0007)
#define TXRX_CSR0_IV_OFFSET		FIELD16(3, 0x01f8)
#define TXRX_CSR0_KEY_ID		FIELD16(9, 0x1e00)

/*
 * TXRX_CSR1: TX configuration.
 */
#define TXRX_CSR1_ACK_TIMEOUT		FIELD16(0, 0x00ff)		/* ACK Timeout in unit of 1-us. */
#define TXRX_CSR1_TSF_OFFSET		FIELD16(8, 0x7f00)		/* TSF offset in MAC header. */
#define TXRX_CSR1_AUTO_SEQUENCE		FIELD16(15, 0x8000)		/* Let ASIC control frame sequence number. */

/*
 * TXRX_CSR2: RX control.
 */
#define	TXRX_CSR2_DISABLE_RX		FIELD16(0, 0x0001)		/* disable rx engine. */
#define TXRX_CSR2_DROP_CRC		FIELD16(1, 0x0002)		/* drop crc error. */
#define TXRX_CSR2_DROP_PHYSICAL		FIELD16(2, 0x0004)		/* drop physical error. */
#define TXRX_CSR2_DROP_CONTROL		FIELD16(3, 0x0008)		/* drop control frame. */
#define TXRX_CSR2_DROP_NOT_TO_ME	FIELD16(4, 0x0010)		/* drop not to me unicast frame. */
#define TXRX_CSR2_DROP_TODS		FIELD16(5, 0x0020)		/* drop frame tods bit is true. */
#define TXRX_CSR2_DROP_VERSION_ERROR	FIELD16(6, 0x0040)		/* drop version error frame. */
#define TXRX_CSR2_DROP_MCAST		FIELD16(9, 0x0200)		/* Drop multicast frames. */
#define TXRX_CSR2_DROP_BCAST		FIELD16(10, 0x0400)		/* Drop broadcast frames. */

/*
 * TXRX_CSR18: Synchronization control register.
 */
#define TXRX_CSR18_OFFSET		FIELD16(0, 0x000f)
#define TXRX_CSR18_INTERVAL		FIELD16(4, 0xfff0)

/*
 * TXRX_CSR19: Synchronization control register.
 */
#define TXRX_CSR19_TSF_COUNT		FIELD16(0, 0x0001)		/* Enable TSF auto counting. */
#define TXRX_CSR19_TSF_SYNC		FIELD16(1, 0x0006)		/* TSF sync, 0: disable, 1: infra mode, 2: ad-hoc mode. */
#define TXRX_CSR19_TBCN			FIELD16(3, 0x0008)		/* Enable Tbcn with reload value. */
#define TXRX_CSR19_BEACON_GEN		FIELD16(4, 0x0010)		/* Enable beacon generator. */

/*
 * TXRX_CSR20: Tx BEACON offset time control register.
 */
#define TXRX_CSR20_OFFSET		FIELD16(0, 0x1fff)		/* In units of usec. */
#define TXRX_CSR20_BCN_EXPECT_WINDOW	FIELD16(13, 0xe000)		/* 2^CWmin. */

/*
 * PHY control registers.
 */

/*
 * PHY_CSR7: BBP access register 0.
 */
#define PHY_CSR7_BBP_DATA		FIELD16(0, 0x00ff)		/* BBP data. */
#define PHY_CSR7_BBP_REG_ID		FIELD16(8, 0x7f00)		/* BBP register ID. */
#define PHY_CSR7_BBP_WRITE_CONTROL	FIELD16(15, 0x8000)		/* 0: read, 1: write. */

/*
 * PHY_CSR8: BBP access register 1.
 */
#define PHY_CSR8_BBP_BUSY		FIELD16(0, 0x0001)		/* ASIC is busy execute BBP programming. */

/*
 * PHY_CSR9: RF access register.
 */
#define PHY_CSR9_RF_VALUE		FIELD16(0, 0xffff)		/* register value + id to program into rf/if. */

/*
 * PHY_CSR10: RF access register.
 */
#define PHY_CSR10_RF_VALUE		FIELD16(0, 0x00ff)		/* register value + id to program into rf/if. */
#define PHY_CSR10_RF_NUMBER_OF_BITS	FIELD16(8, 0x1f00)		/* number of bits used in value (i:20, rfmd:22). */
#define PHY_CSR10_RF_IF_SELECT		FIELD16(13, 0x2000)		/* chip to program: 0: rf, 1: if. */
#define PHY_CSR10_RF_PLL_LD		FIELD16(14, 0x4000)		/* rf pll_ld status. */
#define PHY_CSR10_RF_BUSY		FIELD16(15, 0x8000)		/** 1: asic is busy execute rf programming. */

/*
 * RF registers
 */
#define RF1_TUNER			FIELD32(17, 0x00020000)
#define RF3_TUNER			FIELD32(8, 0x00000100)
#define RF3_TXPOWER			FIELD32(9, 0x00003e00)

/*
 * EEPROM content format.
 */

/*
 * EEPROM antenna.
 */
#define EEPROM_ANTENNA_NUM		FIELD16(0, 0x0003)		/* Number of antenna's. */
#define EEPROM_ANTENNA_TX_DEFAULT	FIELD16(2, 0x000c)		/* Default antenna 0: diversity, 1: A, 2: B. */
#define EEPROM_ANTENNA_RX_DEFAULT	FIELD16(4, 0x0030)		/* Default antenna 0: diversity, 1: A, 2: B. */
#define EEPROM_ANTENNA_LED_MODE		FIELD16(6, 0x01c0)		/* 0: default, 1: TX/RX activity, */
									/* 2: Single LED (ignore link), 3: reserved. */
#define EEPROM_ANTENNA_DYN_TXAGC	FIELD16(9, 0x0200)		/* Dynamic TX AGC control. */
#define EEPROM_ANTENNA_HARDWARE_RADIO	FIELD16(10, 0x0400)		/* 1: Hardware controlled radio. Read GPIO0. */
#define EEPROM_ANTENNA_RF_TYPE		FIELD16(11, 0xf800)		/* rf_type of this adapter. */

/*
 * EEPROM NIC config.
 */
#define EEPROM_NIC_CARDBUS_ACCEL	FIELD16(0, 0x0001)		/* 0: enable, 1: disable. */
#define EEPROM_NIC_DYN_BBP_TUNE		FIELD16(1, 0x0002)		/* 0: enable, 1: disable. */
#define EEPROM_NIC_CCK_TX_POWER		FIELD16(2, 0x000c)		/* CCK TX power compensation. */

/*
 * EEPROM geography.
 */
#define EEPROM_GEOGRAPHY_GEO		FIELD16(8, 0x0f00)		/* Default geography setting for device. */

/*
 * EEPROM TX power.
 */
#define EEPROM_TX_POWER1		FIELD16(0, 0x00ff)
#define EEPROM_TX_POWER2		FIELD16(8, 0xff00)

/*
 * EEPROM BBP.
 */
#define EEPROM_BBP_VALUE		FIELD16(0, 0x00ff)
#define EEPROM_BBP_REG_ID		FIELD16(8, 0xff00)

/*
 * Ring defines and data structures.
 */

/*
 * Size of a single descriptor.
 * The descriptor size depends ont the ring type.
 * The size of 20 bytes is the size of the tx descriptor.
 * rx descriptors are 16 bytes
 * To prevent overhead on checking ring type while handling decriptors,
 * we are setting the size by default to 20 bytes.
 */
#define SIZE_DESCRIPTOR			20

/*
 * TX descriptor format for TX, PRIO, ATIM and Beacon Ring.
 */
struct _txd{
	u32	word0;
#define TXD_W0_PACKET_ID		FIELD32(0, 0x0000000f)		/* Written by MAC about Frame translate status. */
#define TXD_W0_RETRY_LIMIT		FIELD32(4, 0x000000f0)
#define TXD_W0_MORE_FRAG		FIELD32(8, 0x00000100)		/* More fragments are following. */
#define TXD_W0_ACK			FIELD32(9, 0x00000200)
#define TXD_W0_TIMESTAMP		FIELD32(10, 0x00000400)		/* Insert TSF. */
#define TXD_W0_OFDM			FIELD32(11, 0x00000800)
#define TXD_W0_NEW_SEQ			FIELD32(12, 0x00001000)		/* New sequence. */
#define TXD_W0_IFS			FIELD32(13, 0x00006000)
#define TXD_W0_DATABYTE_COUNT		FIELD32(16, 0x0fff0000)		/* Databyte count. */
#define TXD_W0_CIPHER			FIELD32(29, 0x20000000)
#define TXD_W0_KEY_ID			FIELD32(30, 0xc0000000)

	u32	word1;
#define TXD_W1_IV_OFFSET		FIELD32(0, 0x0000003f)
#define TXD_W1_AIFS			FIELD32(6, 0x000000c0)
#define TXD_W1_CWMIN			FIELD32(8, 0x00000f00)
#define TXD_W1_CWMAX			FIELD32(12, 0x0000f000)

	u32	word2;
#define TXD_W2_PLCP_SIGNAL		FIELD32(0, 0x000000ff)		/* BBP R0. */
#define TXD_W2_PLCP_SERVICE		FIELD32(8, 0x0000ff00)		/* BBP R1. */
#define TXD_W2_PLCP_LENGTH_LOW		FIELD32(16, 0x00ff0000)		/* BBP R2. */
#define TXD_W2_PLCP_LENGTH_HIGH		FIELD32(24, 0xff000000)		/* BBP R3. */

	u32	word3;
#define TXD_W3_IV			FIELD32(0, 0xffffffff)

	u32	word4;
#define TXD_W4_EIV			FIELD32(0, 0xffffffff)
} __attribute__ ((packed));

/*
 * RX descriptor format for RX Ring.
 */
struct _rxd{
	u32	word0;
#define RXD_W0_UNICAST_TO_ME		FIELD32(1, 0x00000002)
#define RXD_W0_MULTICAST		FIELD32(2, 0x00000004)
#define RXD_W0_BROADCAST		FIELD32(3, 0x00000008)
#define RXD_W0_MY_BSS			FIELD32(4, 0x00000010)
#define RXD_W0_CRC			FIELD32(5, 0x00000020)
#define RXD_W0_OFDM			FIELD32(6, 0x00000040)
#define RXD_W0_PHYSICAL_ERROR		FIELD32(7, 0x00000080)
#define RXD_W0_CIPHER			FIELD32(8, 0x00000100)
#define RXD_W0_CI_ERROR			FIELD32(9, 0x00000200)
#define RXD_W0_DATABYTE_COUNT		FIELD32(16, 0x0fff0000)

	u32	word1;
#define RXD_W1_SIGNAL			FIELD32(0, 0x000000ff)		/* BBP R0. */
#define RXD_W1_RSSI			FIELD32(8, 0x0000ff00)		/* BBP R1. */

	u32	word2;
#define RXD_W2_IV			FIELD32(0, 0xffffffff)

	u32	word3;
#define RXD_W3_EIV			FIELD32(0, 0xffffffff)
} __attribute__ ((packed));

/*
 * USB data structures.
 */

/*
 * USB request types.
 */
#define USB_VENDOR_REQUEST_IN		(USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE )
#define USB_VENDOR_REQUEST_OUT		(USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE)

/*
 * USB vendor commands.
 */
#define USB_DEVICE_MODE			0x01
#define USB_SINGLE_WRITE		0x02
#define USB_SINGLE_READ			0x03
#define USB_MULTI_WRITE			0x06
#define USB_MULTI_READ			0x07
#define USB_EEPROM_WRITE		0x08
#define USB_EEPROM_READ			0x09
#define USB_RX_CONTROL			0x0c

/*
 * Device modes offset
 */
#define USB_MODE_RESET			0x01
#define USB_MODE_UNPLUG			0x02
#define USB_MODE_FUNCTION		0x03
#define USB_MODE_TEST			0x04

/*
 * _data_entry
 * Private structure for _data_ring.
 */
struct _data_entry{
	/*
	 * Ring we belong to.
	 */
	struct _data_ring		*ring;

	/*
	 * Information for communication with device.
	 */
	struct urb			*urb;
	void				*data_addr;
	dma_addr_t			data_dma;

	/*
	 * Additional packet information.
	 */
	u16				packet_size;
	u8				ring_type;
	u8				status_flags;
#define ENTRY_FREE			0x00
#define ENTRY_BUSY			0x01
#define ENTRY_QUEUED			0x02
} __attribute__ ((packed));

/*
 * _rt2x00_usb
 * This is the main structure which contains all variables required to communicate with the USB device.
 */
struct _rt2x00_usb{
	/*
	 * USB device structure.
	 */
	struct usb_device		*usb_dev;

	/*
	 * Chipset identification.
	 */
	struct _rt2x00_chip		chip;

	/*
	 * RF register values for current channel.
	 */
	struct _rf_channel		channel;

	/*
	 * Configuration variables.
	 */
	u8				long_retry;
	u8				short_retry;

	/*
	 * Minimum RSSI value to accept a received packet.
	 */
	u16				sensitivity;

	/*
	 * EEPROM BBP data.
	 */
	u16				eeprom[EEPROM_BBP_SIZE];

	/*
	 * DMA packet ring.
	 */
	struct _data_ring		rx;
	struct _data_ring		tx;
	struct _data_ring		atim;
	struct _data_ring		prio;
	struct _data_ring		beacon;
} __attribute__ ((packed));

/*
 * Macro's for calculating exact position in DMA ring.
 */
#define ENTRY_SIZE(__ring)		( (__ring)->desc_size + (__ring)->entry_size )
#define PRIV_SIZE(__ring)		( (__ring)->max_entries * sizeof(struct _data_entry) )

#define __ENTRY_ADDR(__ring, __index)	( (struct _data_entry*)((__ring)->priv + (__index * sizeof(struct _data_entry))) )
#define ENTRY_ADDR(__ring) 		( __ENTRY_ADDR(__ring, (__ring)->index) )

#define RX_DESC_ADDR(__urb) 		( RX_DATA_ADDR(__urb) + ((__urb)->actual_length - sizeof(struct _rxd)) )
#define RX_DATA_ADDR(__urb) 		( ((struct _data_entry*)((__urb)->context))->data_addr )

#define TX_DESC_ADDR(__ring)		( ENTRY_ADDR(__ring)->data_addr )
#define TX_DATA_ADDR(__ring)		( TX_DESC_ADDR(__ring) + sizeof(struct _txd) )

static int
rt2x00_get_rf_value(const struct _rt2x00_chip *chip, const u8 channel, struct _rf_channel *rf_reg)
{
	int			index = 0x00;

	index = rt2x00_get_channel_index(channel);
	if(index < 0)
		return -EINVAL;

	memset(rf_reg, 0x00, sizeof(*rf_reg));

	if(rt2x00_rf(chip, RF2522)){
		rf_reg->rf1 = 0x00002050;
		rf_reg->rf3 = 0x00000101;
		goto update_rf2_1;
	}
	if(rt2x00_rf(chip, RF2523)){
		rf_reg->rf1 = 0x00022010;
		rf_reg->rf3 = 0x000e0111;
		rf_reg->rf4 = 0x00000a1b;
		goto update_rf2_2;
	}
	if(rt2x00_rf(chip, RF2524)){
		rf_reg->rf1 = 0x00032020;
		rf_reg->rf3 = 0x00000101;
		rf_reg->rf4 = 0x00000a1b;
		goto update_rf2_2;
	}
	if(rt2x00_rf(chip, RF2525)){
		rf_reg->rf1 = 0x00022020;
		rf_reg->rf2 = 0x00080000;
		rf_reg->rf3 = 0x00060111;
		rf_reg->rf4 = 0x00000a1b;
		goto update_rf2_2;
	}
	if(rt2x00_rf(chip, RF2525E)){
		rf_reg->rf1 = 0x00022010;
		rf_reg->rf3 = 0x00060111;
		goto update_rf2_3;
	}
	if(rt2x00_rf(chip, RF5222)){
		rf_reg->rf3 = 0x00000101;
		goto update_rf2_4;
	}

	return -EINVAL;

update_rf2_1: /* RF2522. */
	rf_reg->rf2 = 0x000c1fda + (index * 0x14);
	if(channel == 14)
		rf_reg->rf2 += 0x0000001c;
	goto exit;

update_rf2_2: /* RF2523, RF2524, RF2525. */
	rf_reg->rf2 |= 0x00000c9e + (index * 0x04);
	if(rf_reg->rf2 & 0x00000040)
		rf_reg->rf2 += 0x00000040;
	if(channel == 14){
		rf_reg->rf2 += 0x08;
		rf_reg->rf4 &= ~0x00000018;
	}
	goto exit;

update_rf2_3: /* RF2525E. */
	rf_reg->rf2 = 0x0000089a;
	if(index & 0x01){ /* Odd number. */
		index += 1;
		rf_reg->rf4 = 0x00000e07;
	}else{
		rf_reg->rf4 = 0x00000e1b;
	}
	rf_reg->rf2 += (index * 0x02);
	if(channel == 14)
		rf_reg->rf4 = 0x00000e23;
	goto exit;

update_rf2_4: /* RF5222. */
	if(OFDM_CHANNEL(channel)){
		rf_reg->rf1 = 0x00022020;
		rf_reg->rf2 |= 0x00001136 + (index * 0x04);
		if(rf_reg->rf2 & 0x00000040)
			rf_reg->rf2 += 0x00000040;
		if(channel == 14){
			rf_reg->rf2 += 0x04;
			rf_reg->rf4 = 0x00000a1b;
		}else{
			rf_reg->rf4 = 0x00000a0b;
		}
	}
	else if(UNII_LOW_CHANNEL(channel)){
		rf_reg->rf1 = 0x00022010;
		rf_reg->rf2 = 0x00018896 + (index * 0x04);
		rf_reg->rf4 = 0x00000a1f;
	}
	else if(HIPERLAN2_CHANNEL(channel)){
		rf_reg->rf1 = 0x00022010;
		rf_reg->rf2 = 0x00008802 + (index * 0x04);
		rf_reg->rf4 = 0x00000a0f;
	}
	else if(UNII_HIGH_CHANNEL(channel)){
		rf_reg->rf1 = 0x00022020;
		rf_reg->rf2 = 0x000090a6 + (index * 0x08);
		rf_reg->rf4 = 0x00000a07;
	}

exit:
	rf_reg->rf1 = rf_reg->rf1;
	rf_reg->rf2 = rf_reg->rf2;
	rf_reg->rf3 = rf_reg->rf3;
	rf_reg->rf4 = rf_reg->rf4;

	return 0;
}

/*
 * Get txpower value in mWatt mathing the requested percentage.
 */
static inline u8
rt2x00_get_txpower(const struct _rt2x00_chip *chip, const u8 tx_power)
{
	if(tx_power <= 3)
		return 19;
	else if(tx_power <= 12)
		return 22;
	else if(tx_power <= 25)
		return 25;
	else if(tx_power <= 50)
		return 28;
	else if(tx_power <= 75)
		return 30;
	else if(tx_power <= 100)
		return 31;

	ERROR("Invalid tx_power.\n");
	return 31;
}

#endif /* RT2X00USB_H */
