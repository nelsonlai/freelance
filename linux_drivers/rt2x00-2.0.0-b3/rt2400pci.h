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
	Module: rt2400pci
	Abstract: Data structures and registers for the rt2400pci module.
	Supported chipsets: RT2460.
 */

#ifndef RT2400PCI_H
#define RT2400PCI_H

#include "rt2x00dev.h"

/*
 * RT chip defines
 */
#define RT2460				0x0101

/*
 * RF chip defines
 */
#define RF2420				0x0000
#define RF2421				0x0001

/*
 * Control/Status Registers(CSR).
 */
#define CSR0				0x0000		/* ASIC revision number. */
#define CSR1				0x0004		/* System control register. */
#define CSR2				0x0008		/* System admin status register (invalid). */
#define CSR3				0x000c		/* STA MAC address register 0. */
#define CSR4				0x0010		/* STA MAC address register 1. */
#define CSR5				0x0014		/* BSSID register 0. */
#define CSR6				0x0018		/* BSSID register 1. */
#define CSR7				0x001c		/* Interrupt source register. */
#define CSR8				0x0020		/* Interrupt mask register. */
#define CSR9				0x0024		/* Maximum frame length register. */
#define CSR11				0x002c		/* Back-off control register. */
#define CSR12				0x0030		/* Synchronization configuration register 0. */
#define CSR13				0x0034		/* Synchronization configuration register 1. */
#define CSR14				0x0038		/* Synchronization control register. */
#define CSR15				0x003c		/* Synchronization status register. */
#define CSR16				0x0040		/* TSF timer register 0. */
#define CSR17				0x0044		/* TSF timer register 1. */
#define CSR18				0x0048		/* IFS timer register 0. */
#define CSR19				0x004c		/* IFS timer register 1. */
#define CSR20				0x0050		/* WakeUp register. */
#define CSR21				0x0054		/* EEPROM control register. */
#define CSR22				0x0058		/* CFP Control Register. */

/*
 * Transmit related CSRs.
 */
#define TXCSR0				0x0060		/* TX control register. */
#define TXCSR1				0x0064		/* TX configuration register. */
#define TXCSR2				0x0068		/* TX descriptor configuratioon register. */
#define TXCSR3				0x006c		/* TX Ring Base address register. */
#define TXCSR4				0x0070		/* TX Atim Ring Base address register. */
#define TXCSR5				0x0074		/* TX Prio Ring Base address register. */
#define TXCSR6				0x0078		/* TX Beacon Ring Base address register. */
#define TXCSR7				0x007c		/* AutoResponder Control Register. */

/*
 * Receive related CSRs.
 */
#define RXCSR0				0x0080		/* RX control register. */
#define RXCSR1				0x0084		/* RX descriptor configuration register. */
#define RXCSR2				0x0088		/* RX Ring base address register. */
#define RXCSR3				0x0090		/* BBP ID register 0 */
#define RXCSR4				0x0094		/* BBP ID register 1. */
#define ARCSR0				0x0098		/* Auto responder PLCP config register 0. */
#define ARCSR1				0x009c		/* Auto Responder PLCP config register 1. */

/*
 * PCI control CSRs.
 */
#define PCICSR				0x008c		/* PCI control register. */

/*
 * Statistic Register.
 */
#define CNT0				0x00a0		/* FCS error count. */
#define TIMECSR2			0x00a8
#define CNT1				0x00ac		/* PLCP error count. */
#define CNT2				0x00b0		/* long error count. */
#define TIMECSR3			0x00b4
#define CNT3				0x00b8		/* CCA false alarm count. */
#define CNT4				0x00bc		/* Rx FIFO overflow count. */
#define CNT5				0x00c0		/* Tx FIFO underrun count. */

/*
 * Baseband Control Register.
 */
#define PWRCSR0				0x00c4		/* Power mode configuration. */
#define PSCSR0				0x00c8		/* Power state transition time. */
#define PSCSR1				0x00cc		/* Power state transition time. */
#define PSCSR2				0x00d0		/* Power state transition time. */
#define PSCSR3				0x00d4		/* Power state transition time. */
#define PWRCSR1				0x00d8		/* Manual power control / status. */
#define TIMECSR				0x00dc		/* Timer control. */
#define MACCSR0				0x00e0		/* MAC configuration. */
#define MACCSR1				0x00e4		/* MAC configuration. */
#define RALINKCSR			0x00e8		/* Ralink Auto-reset register. */
#define BCNCSR				0x00ec		/* Beacon interval control register. */

/*
 * BBP / RF / IF Control Register.
 */
#define BBPCSR				0x00f0		/* BBP serial control. */
#define RFCSR				0x00f4		/* RF serial control. */
#define LEDCSR				0x00f8		/* LED control register */

/*
 * ASIC pointer information.
 */
#define RXPTR				0x0100		/* Current RX ring address. */
#define TXPTR				0x0104		/* Current Tx ring address. */
#define PRIPTR				0x0108		/* Current Priority ring address. */
#define ATIMPTR				0x010c		/* Current ATIM ring address. */

/*
 * GPIO and others.
 */
#define GPIOCSR				0x0120		/* GPIO. */
#define BBPPCSR				0x0124		/* BBP Pin control register. */
#define BCNCSR1				0x0130		/* Tx BEACON offset time, unit: 1 usec. */
#define MACCSR2				0x0134		/* TX_PE to RX_PE delay time, unit: 1 PCI clock cycle. */
#define ARCSR2				0x013c		/* 1 Mbps ACK/CTS PLCP. */
#define ARCSR3				0x0140		/* 2 Mbps ACK/CTS PLCP. */
#define ARCSR4				0x0144		/* 5.5 Mbps ACK/CTS PLCP. */
#define ARCSR5				0x0148		/* 11 Mbps ACK/CTS PLCP. */

/*
 * EEPROM addresses
 */
#define EEPROM_ANTENNA			0x0b
#define EEPROM_BBP_START		0x0c

#define EEPROM_BBP_SIZE			7

/*
 * CSR Registers.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * CSR1: System control register.
 */
#define CSR1_SOFT_RESET			FIELD32(0, 0x00000001)		/* Software reset, 1: reset, 0: normal. */
#define CSR1_BBP_RESET			FIELD32(1, 0x00000002)		/* Hardware reset, 1: reset, 0, release. */
#define CSR1_HOST_READY			FIELD32(2, 0x00000004)		/* Host ready after initialization. */

/*
 * CSR3: STA MAC address register 0.
 */
#define CSR3_BYTE0			FIELD32(0, 0x000000ff)		/* MAC address byte 0. */
#define CSR3_BYTE1			FIELD32(8, 0x0000ff00)		/* MAC address byte 1. */
#define CSR3_BYTE2			FIELD32(16, 0x00ff0000)		/* MAC address byte 2. */
#define CSR3_BYTE3			FIELD32(24, 0xff000000)		/* MAC address byte 3. */

/*
 * CSR4: STA MAC address register 1.
 */
#define CSR4_BYTE4			FIELD32(0, 0x000000ff)		/* MAC address byte 4. */
#define CSR4_BYTE5			FIELD32(8, 0x0000ff00)		/* MAC address byte 5. */

/*
 * CSR5: BSSID register 0.
 */
#define CSR5_BYTE0			FIELD32(0, 0x000000ff)		/* BSSID address byte 0. */
#define CSR5_BYTE1			FIELD32(8, 0x0000ff00)		/* BSSID address byte 1. */
#define CSR5_BYTE2			FIELD32(16, 0x00ff0000)		/* BSSID address byte 2. */
#define CSR5_BYTE3			FIELD32(24, 0xff000000)		/* BSSID address byte 3. */

/*
 * CSR6: BSSID register 1.
 */
#define CSR6_BYTE4			FIELD32(0, 0x000000ff)		/* BSSID address byte 4. */
#define CSR6_BYTE5			FIELD32(8, 0x0000ff00)		/* BSSID address byte 5. */

/*
 * CSR7: Interrupt source register.
 * Write 1 to clear.
 */
#define CSR7_TBCN_EXPIRE		FIELD32(0, 0x00000001)		/* beacon timer expired interrupt. */
#define CSR7_TWAKE_EXPIRE		FIELD32(1, 0x00000002)		/* wakeup timer expired interrupt. */
#define CSR7_TATIMW_EXPIRE		FIELD32(2, 0x00000004)		/* timer of atim window expired interrupt. */
#define CSR7_TXDONE_TXRING		FIELD32(3, 0x00000008)		/* tx ring transmit done interrupt. */
#define CSR7_TXDONE_ATIMRING		FIELD32(4, 0x00000010)		/* atim ring transmit done interrupt. */
#define CSR7_TXDONE_PRIORING		FIELD32(5, 0x00000020)		/* priority ring transmit done interrupt. */
#define CSR7_RXDONE			FIELD32(6, 0x00000040)		/* receive done interrupt. */

/*
 * CSR8: Interrupt mask register.
 * Write 1 to mask interrupt.
 */
#define CSR8_TBCN_EXPIRE		FIELD32(0, 0x00000001)		/* beacon timer expired interrupt. */
#define CSR8_TWAKE_EXPIRE		FIELD32(1, 0x00000002)		/* wakeup timer expired interrupt. */
#define CSR8_TATIMW_EXPIRE		FIELD32(2, 0x00000004)		/* timer of atim window expired interrupt. */
#define CSR8_TXDONE_TXRING		FIELD32(3, 0x00000008)		/* tx ring transmit done interrupt. */
#define CSR8_TXDONE_ATIMRING		FIELD32(4, 0x00000010)		/* atim ring transmit done interrupt. */
#define CSR8_TXDONE_PRIORING		FIELD32(5, 0x00000020)		/* priority ring transmit done interrupt. */
#define CSR8_RXDONE			FIELD32(6, 0x00000040)		/* receive done interrupt. */

/*
 * CSR9: Maximum frame length register.
 */
#define CSR9_MAX_FRAME_UNIT		FIELD32(7, 0x00000f80)		/* maximum frame length in 128b unit, default: 12. */

/*
 * CSR11: Back-off control register.
 */
#define CSR11_CWMIN			FIELD32(0, 0x0000000f)		/* CWmin. Default cwmin is 31 (2^5 - 1). */
#define CSR11_CWMAX			FIELD32(4, 0x000000f0)		/* CWmax. Default cwmax is 1023 (2^10 - 1). */
#define CSR11_SLOT_TIME			FIELD32(8, 0x00001f00)		/* slot time, default is 20us for 802.11b */
#define CSR11_LONG_RETRY		FIELD32(16, 0x00ff0000)		/* long retry count. */
#define CSR11_SHORT_RETRY		FIELD32(24, 0xff000000)		/* short retry count. */

/*
 * CSR12: Synchronization configuration register 0.
 * All units in 1/16 TU.
 */
#define CSR12_BEACON_INTERVAL		FIELD32(0, 0x0000ffff)		/* beacon interval, default is 100 TU. */
#define CSR12_CFPMAX_DURATION		FIELD32(16, 0xffff0000)		/* cfp maximum duration, default is 100 TU. */

/*
 * CSR13: Synchronization configuration register 1.
 * All units in 1/16 TU.
 */
#define CSR13_ATIMW_DURATION		FIELD32(0, 0x0000ffff)		/* atim window duration. */
#define CSR13_CFP_PERIOD		FIELD32(16, 0x00ff0000)		/* cfp period, default is 0 TU. */

/*
 * CSR14: Synchronization control register.
 */
#define CSR14_TSF_COUNT			FIELD32(0, 0x00000001)		/* enable tsf auto counting. */
#define CSR14_TSF_SYNC			FIELD32(1, 0x00000006)		/* tsf sync, 0: disable, 1: infra, 2: ad-hoc mode. */
#define CSR14_TBCN			FIELD32(3, 0x00000008)		/* enable tbcn with reload value. */
#define CSR14_TCFP			FIELD32(4, 0x00000010)		/* enable tcfp & cfp / cp switching. */
#define CSR14_TATIMW			FIELD32(5, 0x00000020)		/* enable tatimw & atim window switching. */
#define CSR14_BEACON_GEN		FIELD32(6, 0x00000040)		/* enable beacon generator. */
#define CSR14_CFP_COUNT_PRELOAD		FIELD32(8, 0x0000ff00)		/* cfp count preload value. */
#define CSR14_TBCM_PRELOAD		FIELD32(16, 0xffff0000)		/* tbcn preload value in units of 64us. */

/*
 * CSR15: Synchronization status register.
 */
#define CSR15_CFP			FIELD32(0, 0x00000001)		/* ASIC is in contention-free period. */
#define CSR15_ATIMW			FIELD32(1, 0x00000002)		/* ASIC is in ATIM window. */
#define CSR15_BEACON_SENT		FIELD32(2, 0x00000004)		/* Beacon is send. */

/*
 * CSR16: TSF timer register 0.
 */
#define CSR16_LOW_TSFTIMER		FIELD32(0, 0xffffffff)

/*
 * CSR17: TSF timer register 1.
 */
#define CSR17_HIGH_TSFTIMER		FIELD32(0, 0xffffffff)

/*
 * CSR18: IFS timer register 0.
 */
#define CSR18_SIFS			FIELD32(0, 0x0000ffff)		/* sifs, default is 10 us. */
#define CSR18_PIFS			FIELD32(16, 0xffff0000)		/* pifs, default is 30 us. */

/*
 * CSR19: IFS timer register 1.
 */
#define CSR19_DIFS			FIELD32(0, 0x0000ffff)		/* difs, default is 50 us. */
#define CSR19_EIFS			FIELD32(16, 0xffff0000)		/* eifs, default is 364 us. */

/*
 * CSR20: Wakeup timer register.
 */
#define CSR20_DELAY_AFTER_TBCN		FIELD32(0, 0x0000ffff)		/* delay after tbcn expired in units of 1/16 TU. */
#define CSR20_TBCN_BEFORE_WAKEUP	FIELD32(16, 0x00ff0000)		/* number of beacon before wakeup. */
#define CSR20_AUTOWAKE			FIELD32(24, 0x01000000)		/* enable auto wakeup / sleep mechanism. */

/*
 * CSR21: EEPROM control register.
 */
#define CSR21_RELOAD			FIELD32(0, 0x00000001)		/* Write 1 to reload eeprom content. */
#define CSR21_EEPROM_DATA_CLOCK		FIELD32(1, 0x00000002)
#define CSR21_EEPROM_CHIP_SELECT	FIELD32(2, 0x00000004)
#define CSR21_EEPROM_DATA_IN		FIELD32(3, 0x00000008)
#define CSR21_EEPROM_DATA_OUT		FIELD32(4, 0x00000010)
#define CSR21_TYPE_93C46		FIELD32(5, 0x00000020)		/* 1: 93c46, 0:93c66. */

/*
 * CSR22: CFP control register.
 */
#define CSR22_CFP_DURATION_REMAIN	FIELD32(0, 0x0000ffff)		/* cfp duration remain, in units of TU. */
#define CSR22_RELOAD_CFP_DURATION	FIELD32(16, 0x00010000)		/* Write 1 to reload cfp duration remain. */

/*
 * TX / RX Registers.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * TXCSR0: TX Control Register.
 */
#define TXCSR0_KICK_TX			FIELD32(0, 0x00000001)		/* kick tx ring. */
#define TXCSR0_KICK_ATIM		FIELD32(1, 0x00000002)		/* kick atim ring. */
#define TXCSR0_KICK_PRIO		FIELD32(2, 0x00000004)		/* kick priority ring. */
#define TXCSR0_ABORT			FIELD32(3, 0x00000008)		/* abort all transmit related ring operation. */

/*
 * TXCSR1: TX Configuration Register.
 */
#define TXCSR1_ACK_TIMEOUT		FIELD32(0, 0x000001ff)		/* ack timeout, default = sifs + 2*slottime + acktime @ 1mbps. */
#define TXCSR1_ACK_CONSUME_TIME		FIELD32(9, 0x0003fe00)		/* ack consume time, default = sifs + acktime @ 1mbps. */
#define TXCSR1_TSF_OFFSET		FIELD32(18, 0x00fc0000)		/* insert tsf offset. */
#define TXCSR1_AUTORESPONDER		FIELD32(24, 0x01000000)		/* enable auto responder which include ack & cts. */

/*
 * TXCSR2: Tx descriptor configuration register.
 */
#define TXCSR2_TXD_SIZE			FIELD32(0, 0x000000ff)		/* tx descriptor size, default is 48. */
#define TXCSR2_NUM_TXD			FIELD32(8, 0x0000ff00)		/* number of txd in ring. */
#define TXCSR2_NUM_ATIM			FIELD32(16, 0x00ff0000)		/* number of atim in ring. */
#define TXCSR2_NUM_PRIO			FIELD32(24, 0xff000000)		/* number of priority in ring. */

/*
 * TXCSR3: TX Ring Base address register.
 */
#define TXCSR3_TX_RING_REGISTER		FIELD32(0, 0xffffffff)

/*
 * TXCSR4: TX Atim Ring Base address register.
 */
#define TXCSR4_ATIM_RING_REGISTER	FIELD32(0, 0xffffffff)

/*
 * TXCSR5: TX Prio Ring Base address register.
 */
#define TXCSR5_PRIO_RING_REGISTER	FIELD32(0, 0xffffffff)

/*
 * TXCSR6: Beacon Base address register.
 */
#define TXCSR6_BEACON_REGISTER		FIELD32(0, 0xffffffff)

/*
 * TXCSR7: Auto responder control register.
 */
#define TXCSR7_AR_POWERMANAGEMENT	FIELD32(0, 0x00000001)		/* auto responder power management bit. */

/*
 * RXCSR0: RX Control Register.
 */
#define RXCSR0_DISABLE_RX		FIELD32(0, 0x00000001)		/* disable rx engine. */
#define RXCSR0_DROP_CRC			FIELD32(1, 0x00000002)		/* drop crc error. */
#define RXCSR0_DROP_PHYSICAL		FIELD32(2, 0x00000004)		/* drop physical error. */
#define RXCSR0_DROP_CONTROL		FIELD32(3, 0x00000008)		/* drop control frame. */
#define RXCSR0_DROP_NOT_TO_ME		FIELD32(4, 0x00000010)		/* drop not to me unicast frame. */
#define RXCSR0_DROP_TODS		FIELD32(5, 0x00000020)		/* drop frame tods bit is true. */
#define RXCSR0_DROP_VERSION_ERROR	FIELD32(6, 0x00000040)		/* drop version error frame. */
#define RXCSR0_PASS_CRC			FIELD32(7, 0x00000080)		/* pass all packets with crc attached. */

/*
 * RXCSR1: RX descriptor configuration register.
 */
#define RXCSR1_RXD_SIZE			FIELD32(0, 0x000000ff)		/* rx descriptor size, default is 32b. */
#define RXCSR1_NUM_RXD			FIELD32(8, 0x0000ff00)		/* number of rxd in ring. */

/*
 * RXCSR2: RX Ring base address register.
 */
#define RXCSR2_RX_RING_REGISTER		FIELD32(0, 0xffffffff)

/*
 * RXCSR3: BBP ID register for Rx operation.
 */
#define RXCSR3_BBP_ID0			FIELD32(0, 0x0000007f)		/* bbp register 0 id. */
#define RXCSR3_BBP_ID0_VALID		FIELD32(7, 0x00000080)		/* bbp register 0 id is valid or not. */
#define RXCSR3_BBP_ID1			FIELD32(8, 0x00007f00)		/* bbp register 1 id. */
#define RXCSR3_BBP_ID1_VALID		FIELD32(15, 0x00008000)		/* bbp register 1 id is valid or not. */
#define RXCSR3_BBP_ID2			FIELD32(16, 0x007f0000)		/* bbp register 2 id. */
#define RXCSR3_BBP_ID2_VALID		FIELD32(23, 0x00800000)		/* bbp register 2 id is valid or not. */
#define RXCSR3_BBP_ID3			FIELD32(24, 0x7f000000)		/* bbp register 3 id. */
#define RXCSR3_BBP_ID3_VALID		FIELD32(31, 0x80000000)		/* bbp register 3 id is valid or not. */

/*
 * RXCSR4: BBP ID register for Rx operation.
 */
#define RXCSR4_BBP_ID4			FIELD32(0, 0x0000007f)		/* bbp register 4 id. */
#define RXCSR4_BBP_ID4_VALID		FIELD32(7, 0x00000080)		/* bbp register 4 id is valid or not. */
#define RXCSR4_BBP_ID5			FIELD32(8, 0x00007f00)		/* bbp register 5 id. */
#define RXCSR4_BBP_ID5_VALID		FIELD32(15, 0x00008000)		/* bbp register 5 id is valid or not. */

/*
 * ARCSR0: Auto Responder PLCP config register 0.
 */
#define ARCSR0_AR_BBP_DATA0		FIELD32(0, 0x000000ff)		/* Auto responder BBP register 0 data. */
#define ARCSR0_AR_BBP_ID0		FIELD32(8, 0x0000ff00)		/* Auto responder BBP register 0 Id. */
#define ARCSR0_AR_BBP_DATA1		FIELD32(16, 0x00ff0000)		/* Auto responder BBP register 1 data. */
#define ARCSR0_AR_BBP_ID1		FIELD32(24, 0xff000000)		/* Auto responder BBP register 1 Id. */

/*
 * ARCSR1: Auto Responder PLCP config register 1.
 */
#define ARCSR1_AR_BBP_DATA2		FIELD32(0, 0x000000ff)		/* Auto responder BBP register 2 data. */
#define ARCSR1_AR_BBP_ID2		FIELD32(8, 0x0000ff00)		/* Auto responder BBP register 2 Id. */
#define ARCSR1_AR_BBP_DATA3		FIELD32(16, 0x00ff0000)		/* Auto responder BBP register 3 data. */
#define ARCSR1_AR_BBP_ID3		FIELD32(24, 0xff000000)		/* Auto responder BBP register 3 Id. */

/*
 * Miscellaneous Registers.
 * Some values are set in TU, whereas 1 TU == 1024 us.
 */

/*
 * PCISR: PCI control register.
 */
#define PCICSR_BIG_ENDIAN		FIELD32(0, 0x00000001)		/* 1: big endian, 0: little endian. */
#define PCICSR_RX_TRESHOLD		FIELD32(1, 0x00000006)		/* rx threshold in dw to start pci access */
									/* 0: 16dw (default), 1: 8dw, 2: 4dw, 3: 32dw. */
#define PCICSR_TX_TRESHOLD		FIELD32(3, 0x00000018)		/* tx threshold in dw to start pci access */
									/* 0: 0dw (default), 1: 1dw, 2: 4dw, 3: forward. */
#define PCICSR_BURST_LENTH		FIELD32(5, 0x00000060)		/* pci burst length */
									/* 0: 4dw (default, 1: 8dw, 2: 16dw, 3:32dw. */
#define PCICSR_ENABLE_CLK		FIELD32(7, 0x00000080)		/* enable clk_run, */
									/* pci clock can't going down to non-operational. */

/*
 * PWRCSR1: Manual power control / status register.
 * state: 0 deep_sleep, 1: sleep, 2: standby, 3: awake.
 */
#define PWRCSR1_SET_STATE		FIELD32(0, 0x00000001)		/* set state. Write 1 to trigger, self cleared. */
#define PWRCSR1_BBP_DESIRE_STATE	FIELD32(1, 0x00000006)		/* BBP desired state. */
#define PWRCSR1_RF_DESIRE_STATE		FIELD32(3, 0x00000018)		/* RF desired state. */
#define PWRCSR1_BBP_CURR_STATE		FIELD32(5, 0x00000060)		/* BBP current state. */
#define PWRCSR1_RF_CURR_STATE		FIELD32(7, 0x00000180)		/* RF current state. */
#define PWRCSR1_PUT_TO_SLEEP		FIELD32(9, 0x00000200)		/* put to sleep. Write 1 to trigger, self cleared. */

/*
 * TIMECSR: Timer control register.
 */
#define TIMECSR_US_COUNT		FIELD32(0, 0x000000ff)		/* 1 us timer count in units of clock cycles. */
#define TIMECSR_US_64_COUNT		FIELD32(8, 0x0000ff00)		/* 64 us timer count in units of 1 us timer. */
#define TIMECSR_BEACON_EXPECT		FIELD32(16, 0x00070000)		/* Beacon expect window. */

/*
 * MACCSR1: MAC configuration register 1.
 */
#define MACCSR1_KICK_RX			FIELD32(0, 0x00000001)		/* kick one-shot rx in one-shot rx mode. */
#define MACCSR1_ONESHOT_RXMODE		FIELD32(1, 0x00000002)		/* enable one-shot rx mode for debugging. */
#define MACCSR1_BBPRX_RESET_MODE	FIELD32(2, 0x00000004)		/* ralink bbp rx reset mode. */
#define MACCSR1_AUTO_TXBBP		FIELD32(3, 0x00000008)		/* auto tx logic access bbp control register. */
#define MACCSR1_AUTO_RXBBP		FIELD32(4, 0x00000010)		/* auto rx logic access bbp control register. */
#define MACCSR1_LOOPBACK		FIELD32(5, 0x00000060)		/* loopback mode. */
									/* 0: normal, 1: internal, 2: external, 3:rsvd. */
#define MACCSR1_INTERSIL_IF		FIELD32(7, 0x00000080)		/* intersil if calibration pin. */

/*
 * RALINKCSR: Ralink Rx auto-reset BBCR.
 */
#define RALINKCSR_AR_BBP_DATA0		FIELD32(0, 0x000000ff)		/* auto reset bbp register 0 data. */
#define RALINKCSR_AR_BBP_ID0		FIELD32(8, 0x0000ff00)		/* auto reset bbp register 0 id. */
#define RALINKCSR_AR_BBP_DATA1		FIELD32(16, 0x00ff0000)		/* auto reset bbp register 1 data. */
#define RALINKCSR_AR_BBP_ID1		FIELD32(24, 0xff000000)		/* auto reset bbp register 1 id. */

/*
 * BCNCSR: Beacon interval control register.
 */
#define BCNCSR_CHANGE			FIELD32(0, 0x00000001)		/* write one to change beacon interval. */
#define BCNCSR_DELTATIME		FIELD32(1, 0x0000001e)		/* the delta time value. */
#define BCNCSR_NUM_BEACON		FIELD32(5, 0x00001fe0)		/* number of beacon according to mode. */
#define BCNCSR_MODE			FIELD32(13, 0x00006000)		/* please refer to asic specs. */
#define BCNCSR_PLUS			FIELD32(15, 0x00008000)		/* plus or minus delta time value. */

/*
 * BBPCSR: BBP serial control register.
 */
#define BBPCSR_VALUE			FIELD32(0, 0x000000ff)		/* register value to program into bbp. */
#define BBPCSR_REGNUM			FIELD32(8, 0x00007f00)		/* selected bbp register. */
#define BBPCSR_BUSY			FIELD32(15, 0x00008000)		/* 1: asic is busy execute bbp programming. */
#define BBPCSR_WRITE_CONTROL		FIELD32(16, 0x00010000)		/* 1: write bbp, 0: read bbp. */

/*
 * RFCSR: RF serial control register.
 */
#define RFCSR_VALUE			FIELD32(0, 0x00ffffff)		/* register value + id to program into rf/if. */
#define RFCSR_NUMBER_OF_BITS		FIELD32(24, 0x1f000000)		/* number of bits used in value (i:20, rfmd:22). */
#define RFCSR_IF_SELECT			FIELD32(29, 0x20000000)		/* chip to program: 0: rf, 1: if. */
#define RFCSR_PLL_LD			FIELD32(30, 0x40000000)		/* rf pll_ld status. */
#define RFCSR_BUSY			FIELD32(31, 0x80000000)		/* 1: asic is busy execute rf programming. */

/*
 * LEDCSR: LED control register.
 */
#define LEDCSR_ON_PERIOD		FIELD32(0, 0x000000ff)		/* on period, default 70ms. */
#define LEDCSR_OFF_PERIOD		FIELD32(8, 0x0000ff00)		/* off period, default 30ms. */
#define LEDCSR_LINK			FIELD32(16, 0x00010000)		/* 0: linkoff, 1: linkup. */
#define LEDCSR_ACTIVITY			FIELD32(17, 0x00020000)		/* 0: idle, 1: active. */

/*
 * GPIOCSR: GPIO control register.
 */
#define GPIOCSR_BIT0			FIELD32(0, 0x00000001)
#define GPIOCSR_BIT1			FIELD32(1, 0x00000002)
#define GPIOCSR_BIT2			FIELD32(2, 0x00000004)
#define GPIOCSR_BIT3			FIELD32(3, 0x00000008)
#define GPIOCSR_BIT4			FIELD32(4, 0x00000010)
#define GPIOCSR_BIT5			FIELD32(5, 0x00000020)
#define GPIOCSR_BIT6			FIELD32(6, 0x00000040)
#define GPIOCSR_BIT7			FIELD32(7, 0x00000080)

/*
 * BCNCSR1: Tx BEACON offset time control register.
 */
#define BCNCSR1_PRELOAD			FIELD32(0, 0x0000ffff)		/* beacon timer offset in units of usec. */

/*
 * MACCSR2: TX_PE to RX_PE turn-around time control register
 */
#define MACCSR2_DELAY			FIELD32(0, 0x000000ff)		/* RX_PE low width, in units of pci clock cycle. */

/*
 * RF registers
 */
#define RF1_TUNER			FIELD32(17, 0x00020000)
#define RF3_TUNER			FIELD32(8, 0x00000100)
#define RF3_TXPOWER			FIELD32(9, 0x00003e00)

/*
 * EEPROM content format.
 * The wordsize of the EEPROM is 16 bits.
 */

/*
 * EEPROM operation defines.
 */
#define EEPROM_WIDTH_93c46		6
#define EEPROM_WIDTH_93c66		8
#define EEPROM_WRITE_OPCODE		0x05
#define EEPROM_READ_OPCODE		0x06

/*
 * EEPROM antenna.
 */
#define EEPROM_ANTENNA_NUM		FIELD16(0, 0x0003)		/* Number of antenna's. */
#define EEPROM_ANTENNA_TX_DEFAULT	FIELD16(2, 0x000c)		/* Default antenna 0: diversity, 1: A, 2: B. */
#define EEPROM_ANTENNA_RX_DEFAULT	FIELD16(4, 0x0030)		/* Default antenna 0: diversity, 1: A, 2: B. */
#define EEPROM_ANTENNA_RF_TYPE		FIELD16(6, 0x0040)		/* rf_type of this adapter. */
#define EEPROM_ANTENNA_LED_MODE		FIELD16(7, 0x0180)		/* 0: default, 1: TX/RX activity, */
									/* 2: Single LED (ignore link), 3: reserved. */
#define EEPROM_ANTENNA_RX_AGCVGC	FIELD16(9, 0x0200)		/* 0: disable, 1:enable BBP R13 tuning. */
#define EEPROM_ANTENNA_HARDWARE_RADIO	FIELD16(10, 0x0400)		/* 1: Hardware controlled radio. Read GPIO0. */

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
 * DMA ring defines and data structures.
 */

/*
 * Size of a single descriptor.
 */
#define SIZE_DESCRIPTOR			32

/*
 * TX descriptor format for TX, PRIO, ATIM and Beacon Ring.
 */
struct _txd{
	u32	word0;
#define TXD_W0_OWNER_NIC		FIELD32(0, 0x00000001)
#define TXD_W0_VALID			FIELD32(1, 0x00000002)
#define TXD_W0_RESULT			FIELD32(2, 0x0000001c)		/* Set by device. */
#define TXD_W0_RETRY_COUNT		FIELD32(5, 0x000000e0)		/* Set by device. */
#define TXD_W0_MORE_FRAG		FIELD32(8, 0x00000100)		/* Set by device. */
#define TXD_W0_ACK			FIELD32(9, 0x00000200)
#define TXD_W0_TIMESTAMP		FIELD32(10, 0x00000400)
#define TXD_W0_RTS			FIELD32(11, 0x00000800)
#define TXD_W0_IFS			FIELD32(13, 0x00006000)
#define TXD_W0_RETRY_MODE		FIELD32(15, 0x00008000)
#define TXD_W0_AGC			FIELD32(16, 0x00ff0000)
#define TXD_W0_R2			FIELD32(24, 0xff000000)

	u32	word1;
#define TXD_W1_BUFFER_ADDRESS		FIELD32(0, 0xffffffff)

	u32	word2;
#define TXD_W2_BUFFER_LENGTH		FIELD32(0, 0x0000ffff)
#define TXD_W2_DATABYTE_COUNT		FIELD32(16, 0xffff0000)

	u32	word3;
#define TXD_W3_PLCP_SIGNAL		FIELD32(0, 0x0000ffff)
#define TXD_W3_PLCP_SERVICE		FIELD32(16, 0xffff0000)

	u32	word4;
#define TXD_W4_PLCP_LENGTH_LOW		FIELD32(0, 0x0000ffff)
#define TXD_W4_PLCP_LENGTH_HIGH		FIELD32(16, 0xffff0000)

	u32	word5;
#define TXD_W5_BBCR4			FIELD32(0, 0x0000ffff)
#define TXD_W5_AGC_REG			FIELD32(16, 0x007f0000)
#define TXD_W5_AGC_REG_VALID		FIELD32(23, 0x00800000)
#define TXD_W5_XXX_REG			FIELD32(24, 0x7f000000)
#define TXD_W5_XXX_REG_VALID		FIELD32(31, 0x80000000)

	u32	word6;
#define TXD_W6_SK_BUFF			FIELD32(0, 0xffffffff)

	u32	word7;
#define TXD_W7_RESERVED			FIELD32(0, 0xffffffff)
} __attribute__ ((packed));

/*
 * RX descriptor format for RX Ring.
 */
struct _rxd{
	u32 word0;
#define RXD_W0_OWNER_NIC		FIELD32(0, 0x00000001)
#define RXD_W0_UNICAST_TO_ME		FIELD32(1, 0x00000002)
#define RXD_W0_MULTICAST		FIELD32(2, 0x00000004)
#define RXD_W0_BROADCAST		FIELD32(3, 0x00000008)
#define RXD_W0_MY_BSS			FIELD32(4, 0x00000010)
#define RXD_W0_CRC			FIELD32(5, 0x00000020)
#define RXD_W0_PHYSICAL_ERROR		FIELD32(7, 0x00000080)
#define RXD_W0_DATABYTE_COUNT		FIELD32(16, 0xffff0000)

	u32 word1;
#define RXD_W1_BUFFER_ADDRESS		FIELD32(0, 0xffffffff)

	u32 word2;
#define RXD_W2_BUFFER_LENGTH		FIELD32(0, 0x0000ffff)
#define RXD_W2_BBR0			FIELD32(16, 0x00ff0000)
#define RXD_W2_RSSI			FIELD32(24, 0xff000000)

	u32 word3;
#define RXD_W3_BBR2			FIELD32(0, 0x000000ff)
#define RXD_W3_BBR3			FIELD32(8, 0x0000ff00)
#define RXD_W3_BBR4			FIELD32(16, 0x00ff0000)
#define RXD_W3_BBR5			FIELD32(24, 0xff000000)

	u32 word4;
#define RXD_W4_RX_END_TIME		FIELD32(0, 0xffffffff)

	u32 word5;
#define RXD_W5_RESERVED			FIELD32(0, 0xffffffff)

	u32 word6;
#define RXD_W6_RESERVED			FIELD32(0, 0xffffffff)

	u32 word7;
#define RXD_W7_RESERVED			FIELD32(0, 0xffffffff)
} __attribute__ ((packed));

/*
 * _rt2x00_pci
 * This is the main structure which contains all variables required to communicate with the PCI device.
 */
struct _rt2x00_pci{
	/*
	 * PCI device structure.
	 */
	struct pci_dev			*pci_dev;

	/*
	 * Chipset identification.
	 */
	struct _rt2x00_chip		chip;

	/*
	 * csr_addr
	 * Base address of device registers, all exact register addresses are calculated from this address.
	 */
	void __iomem			*csr_addr;

	/*
	 * RF register values for current channel.
	 */
	struct _rf_channel		channel;

	/*
	 * Minimum RSSI value to accept a received packet.
	 */
	u16				sensitivity;

	/*
	 * EEPROM bus width.
	 */
	u8				eeprom_width;

	u8				__pad;	/* For alignment only. */

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

static int
rt2x00_get_rf_value(const struct _rt2x00_chip *chip, const u8 channel, struct _rf_channel *rf_reg)
{
	rf_reg->rf1 = cpu_to_le32(0x00022058);

	if(channel < 14)
		rf_reg->rf2 = cpu_to_le32(0x000c1fda + ((channel - 1) * 0x14));
	else
		rf_reg->rf2 = cpu_to_le32(0x000c20fa);

	if(rt2x00_rf(chip, RF2420))
		rf_reg->rf3 = cpu_to_le32(0x00000111);
	else
		rf_reg->rf3 = cpu_to_le32(0x00000101);

	return 0;
}

/*
 * Get txpower value in dBm mathing the requested percentage.
 */
static inline u8
rt2x00_get_txpower(const struct _rt2x00_chip *chip, const u8 tx_power)
{
	if(tx_power <= 3)
		return 62;
	else if(tx_power <= 12)
		return 57;
	else if(tx_power <= 25)
		return 48;
	else if(tx_power <= 50)
		return 43;
	else if(tx_power <= 75)
		return 40;
	else if(tx_power <= 100)
		return 39;

	ERROR("Invalid tx_power.\n");
	return 39;
}

#include "rt2x00pci.h"

#endif /* RT2400PCI_H */
