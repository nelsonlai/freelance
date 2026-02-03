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
	Abstract: rt2400pci device specific routines.
	Supported chipsets: RT2460.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/delay.h>

#include <asm/io.h>

#include "rt2x00.h"
#include "rt2400pci.h"

#ifdef DRV_NAME
#undef DRV_NAME
#define DRV_NAME			"rt2400pci"
#endif /* DRV_NAME */

/*
 * Interrupt routines.
 * rt2x00_interrupt_txdone processes all transmitted packetss results.
 * rt2x00_interrupt_rxdone processes all received rx packets.
 */
static void
rt2x00_interrupt_txdone(struct _data_ring *ring)
{
	struct _txd		*txd = NULL;
	u8			tx_result = 0x00;
	u8			retry_count = 0x00;

	do{
		txd = DESC_ADDR_DONE(ring);

		if(rt2x00_get_field32(txd->word0, TXD_W0_OWNER_NIC)
		|| !rt2x00_get_field32(txd->word0, TXD_W0_VALID))
			break;

		if(ring->ring_type == RING_TX){
			tx_result = rt2x00_get_field32(txd->word0, TXD_W0_RESULT);
			retry_count = rt2x00_get_field32(txd->word0, TXD_W0_RETRY_COUNT);

			rt2x00_update_stats(ring->device, STATS_TX_RESULT, tx_result);
			rt2x00_update_stats(ring->device, STATS_TX_RETRY_COUNT, retry_count);
		}

		rt2x00_set_field32(&txd->word0, TXD_W0_VALID, 0);

		rt2x00_ring_index_done_inc(ring);
	}while(!rt2x00_ring_empty(ring));
}

static void
rt2x00_interrupt_rxdone(struct _data_ring *ring)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(ring->device);
	struct _rxd		*rxd = NULL;
	void			*data = NULL;
	u16			size = 0x0000;
	u16			rssi = 0x0000;

	while(1){
		rxd = DESC_ADDR(ring);
		data = DATA_ADDR(ring);

		if(rt2x00_get_field32(rxd->word0, RXD_W0_OWNER_NIC))
			break;

		size = rt2x00_get_field32(rxd->word0, RXD_W0_DATABYTE_COUNT);
		rssi = rt2x00_get_field32(rxd->word2, RXD_W2_RSSI);

		if(rt2x00_get_field32(rxd->word0, RXD_W0_CRC))
			rt2x00_update_stats(ring->device, STATS_RX_CRC, 1);
		else if(rt2x00_get_field32(rxd->word0, RXD_W0_PHYSICAL_ERROR))
			rt2x00_update_stats(ring->device, STATS_RX_PHYSICAL, 1);
		else if(rt2x00pci->sensitivity > rssi)
			rt2x00_update_stats(ring->device, STATS_RX_QUALITY, 1);
		else
			rt2x00_ring_rx_packet(ring->device, size, data, rssi);

		rt2x00_set_field32(&rxd->word0, RXD_W0_OWNER_NIC, 1);

		rt2x00_ring_index_inc(&rt2x00pci->rx);
	}
}

/*
 * Some steps that we must take for processing interrupts.
 * 1. Get the interrupt sources & saved to local variable.
 * 2. Write register value back to clear pending interrupt.
 * 3. Handle interrupt, walk through all bits and run the tasks.
 */
static irqreturn_t
rt2x00_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	struct _rt2x00_device	*device = (struct _rt2x00_device*)dev_instance;
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	u32			reg = 0x00000000;
	u8			ring_type = 0x0000;

	rt2x00_register_read(rt2x00pci, CSR7, &reg);
	rt2x00_register_write(rt2x00pci, CSR7, reg);

	if(!reg)
		return IRQ_NONE;

	if(rt2x00_get_field32(reg, CSR7_TBCN_EXPIRE)){		/* Beacon timer expired interrupt. */
		rt2x00_tx(device, RING_BEACON);
	}
	if(rt2x00_get_field32(reg, CSR7_RXDONE)){		/* Rx ring done interrupt. */
		rt2x00_interrupt_rxdone(&rt2x00pci->rx);
	}
	if(rt2x00_get_field32(reg, CSR7_TXDONE_ATIMRING)){	/* Atim ring transmit done interrupt. */
		rt2x00_interrupt_txdone(&rt2x00pci->atim);
		ring_type |= RING_ATIM;
	}
	if(rt2x00_get_field32(reg, CSR7_TXDONE_PRIORING)){	/* Priority ring transmit done interrupt. */
		rt2x00_interrupt_txdone(&rt2x00pci->prio);
		ring_type |= RING_PRIO;
	}
	if(rt2x00_get_field32(reg, CSR7_TXDONE_TXRING)){	/* Tx ring transmit done interrupt. */
		rt2x00_interrupt_txdone(&rt2x00pci->tx);
		ring_type |= RING_TX;
	}

	if(ring_type)
		rt2x00_tx(device, ring_type);

	return IRQ_HANDLED;
}

/*
 * Initialization handlers.
 */

/*
 * rt2x00_init_eeprom.
 */
static void
rt2x00_init_eeprom(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32		reg = 0x00000000;
	u16		eeprom = 0x0000;
	u16		val_a = 0x0000;
	u16		val_b = 0x0000;

	/*
	 * 1 - Detect EEPROM width.
	 */
	rt2x00_register_read(rt2x00pci, CSR21, &reg);
	rt2x00pci->eeprom_width = rt2x00_get_field32(reg, CSR21_TYPE_93C46) ? EEPROM_WIDTH_93c46 : EEPROM_WIDTH_93c66;

	/*
	 * 2 - Identify rf chipset.
	 */
	eeprom = rt2x00_eeprom_read_word(rt2x00pci, EEPROM_ANTENNA);
	set_chip(&rt2x00pci->chip, RT2460, rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RF_TYPE));

	/*
	 * 3 - Identify default antenna configuration.
	 */
	val_a = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_TX_DEFAULT);
	val_b = rt2x00_get_field16(eeprom, EEPROM_ANTENNA_RX_DEFAULT);

	config->user.antenna_flags |= val_a;
	config->user.antenna_flags |= val_b << 8;

	if((config->user.antenna_flags & ANTENNA_TX) == 0)
		config->user.antenna_flags |= ANTENNA_TX_DIV;

	if((config->user.antenna_flags & ANTENNA_RX) == 0)
		config->user.antenna_flags |= ANTENNA_RX_DIV;

	/*
	 * 4 - Warn about absence of default geography configuration.
	 */
	DEBUG("RT2460 devices don't set default geography from EEPROM.\n");

	/*
	 * 5 - Read BBP data from EEPROM and store in private structure.
	 */
	memset(&rt2x00pci->eeprom, 0x00, sizeof(rt2x00pci->eeprom));
	for(eeprom = 0; eeprom < EEPROM_BBP_SIZE; eeprom++)
		rt2x00pci->eeprom[eeprom] = rt2x00_eeprom_read_word(rt2x00pci, EEPROM_BBP_START + eeprom);
}

static void
rt2x00_init_read_mac(struct _rt2x00_pci *rt2x00pci, struct net_device *net_dev)
{
	u32			reg[2];

	memset(&reg, 0x00, sizeof(reg));

	rt2x00_register_multiread(rt2x00pci, CSR3, &reg[0], sizeof(reg));

	net_dev->dev_addr[0] = rt2x00_get_field32(reg[0], CSR3_BYTE0);
	net_dev->dev_addr[1] = rt2x00_get_field32(reg[0], CSR3_BYTE1);
	net_dev->dev_addr[2] = rt2x00_get_field32(reg[0], CSR3_BYTE2);
	net_dev->dev_addr[3] = rt2x00_get_field32(reg[0], CSR3_BYTE3);
	net_dev->dev_addr[4] = rt2x00_get_field32(reg[1], CSR4_BYTE4);
	net_dev->dev_addr[5] = rt2x00_get_field32(reg[1], CSR4_BYTE5);

	net_dev->addr_len = 6;
}

static int
rt2x00_dev_probe(struct _rt2x00_device *device, struct _rt2x00_config *config, void *priv)
{
	struct pci_dev		*pci_dev = (struct pci_dev*)priv;
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	memset(rt2x00pci, 0x00, sizeof(*rt2x00pci));

	if(unlikely(!pci_dev)){
		ERROR("invalid priv pointer.\n");
		return -ENODEV;
	}
	rt2x00pci->pci_dev = pci_dev;

	rt2x00pci->rx.data_addr = NULL;
	rt2x00pci->tx.data_addr = NULL;
	rt2x00pci->atim.data_addr = NULL;
	rt2x00pci->prio.data_addr = NULL;
	rt2x00pci->beacon.data_addr = NULL;

	rt2x00pci->csr_addr = ioremap(pci_resource_start(pci_dev, 0), pci_resource_len(pci_dev, 0));
	if(!rt2x00pci->csr_addr){
		ERROR("ioremap failed.\n");
		return -ENOMEM;
	}

	rt2x00_init_eeprom(rt2x00pci, config);
	rt2x00_init_read_mac(rt2x00pci, device->net_dev);

	if(!rt2x00_rf(&rt2x00pci->chip, RF2420)
	&& !rt2x00_rf(&rt2x00pci->chip, RF2421)){
		iounmap(rt2x00pci->csr_addr);
		rt2x00pci->csr_addr = NULL;
		return -ENODEV;
	}

	set_bit(DEVICE_CAP_802_11B, &device->flags);

	return 0;
}

static int
rt2x00_dev_remove(struct _rt2x00_device *device)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	if(rt2x00pci->csr_addr){
		iounmap(rt2x00pci->csr_addr);
		rt2x00pci->csr_addr = NULL;
	}

	return 0;
}

/*
 * rt2x00_clear_ring
 * During the initialization some of the descriptor variables are filled in.
 * The default value of the owner variable is different between the types of the descriptor,
 * DMA ring entries that receive packets are owned by the device untill a packet is received.
 * DMA ring entries that are used to transmit a packet are owned by the module untill the device,
 * for these rings the valid bit is set to 0 to indicate it is ready for use.
 * should transmit the packet that particular DMA ring entry.
 * The BUFFER_ADDRESS variable is used to link a descriptor to a packet data block.
 */
static void
rt2x00_clear_ring(struct _rt2x00_pci *rt2x00pci, struct _data_ring *ring)
{
	struct _rxd		*rxd = NULL;
	struct _txd		*txd = NULL;
	dma_addr_t		data_dma = ring->data_dma + (ring->max_entries * ring->desc_size);
	u8			counter = 0x00;

	memset(ring->data_addr, 0x00, ring->mem_size);

	for(; counter < ring->max_entries; counter++){
		if(ring->ring_type == RING_RX){
			rxd = (struct _rxd*)__DESC_ADDR(ring, counter);

			rt2x00_set_field32(&rxd->word2, RXD_W2_BUFFER_LENGTH, ring->entry_size);
			rt2x00_set_field32(&rxd->word1, RXD_W1_BUFFER_ADDRESS, data_dma);
			rt2x00_set_field32(&rxd->word0, RXD_W0_OWNER_NIC, 1);
		}else{
			txd = (struct _txd*)__DESC_ADDR(ring, counter);
	
			rt2x00_set_field32(&txd->word2, TXD_W2_BUFFER_LENGTH, ring->entry_size);
			rt2x00_set_field32(&txd->word1, TXD_W1_BUFFER_ADDRESS, data_dma);
			rt2x00_set_field32(&txd->word0, TXD_W0_VALID, 0);
			rt2x00_set_field32(&txd->word0, TXD_W0_OWNER_NIC, 0);
		}

		data_dma += ring->entry_size;
	}

	rt2x00_ring_clear_index(ring);
}

/*
 * rt2x00_init_ring_register
 * The registers should be updated with the descriptor size and the
 * number of entries of each ring.
 * The address of the first entry of the descriptor ring is written to the register
 * corresponding to the ring.
 */
static void
rt2x00_init_ring_register(struct _rt2x00_pci *rt2x00pci)
{
	u32			reg = 0x00000000;

	rt2x00_set_field32(&reg, TXCSR2_TXD_SIZE, rt2x00pci->tx.desc_size);
	rt2x00_set_field32(&reg, TXCSR2_NUM_TXD, rt2x00pci->tx.max_entries);
	rt2x00_set_field32(&reg, TXCSR2_NUM_ATIM, rt2x00pci->atim.max_entries);
	rt2x00_set_field32(&reg, TXCSR2_NUM_PRIO, rt2x00pci->prio.max_entries);
	rt2x00_register_write(rt2x00pci, TXCSR2, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, TXCSR3_TX_RING_REGISTER, rt2x00pci->tx.data_dma);
	rt2x00_register_write(rt2x00pci, TXCSR3, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, TXCSR5_PRIO_RING_REGISTER, rt2x00pci->prio.data_dma);
	rt2x00_register_write(rt2x00pci, TXCSR5, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, TXCSR4_ATIM_RING_REGISTER, rt2x00pci->atim.data_dma);
	rt2x00_register_write(rt2x00pci, TXCSR4, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, TXCSR6_BEACON_REGISTER, rt2x00pci->beacon.data_dma);
	rt2x00_register_write(rt2x00pci, TXCSR6, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, RXCSR1_RXD_SIZE, rt2x00pci->rx.desc_size);
	rt2x00_set_field32(&reg, RXCSR1_NUM_RXD, rt2x00pci->rx.max_entries);
	rt2x00_register_write(rt2x00pci, RXCSR1, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, RXCSR2_RX_RING_REGISTER, rt2x00pci->rx.data_dma);
	rt2x00_register_write(rt2x00pci, RXCSR2, reg);
}

static int
rt2x00_init_registers(struct _rt2x00_pci *rt2x00pci)
{
	u32		reg = 0x00000000;

	rt2x00_register_write(rt2x00pci, PWRCSR0, cpu_to_le32(0x3f3b3100));

	rt2x00_register_write(rt2x00pci, PSCSR0, cpu_to_le32(0x00020002));
	rt2x00_register_write(rt2x00pci, PSCSR1, cpu_to_le32(0x00000002));
	rt2x00_register_write(rt2x00pci, PSCSR2, cpu_to_le32(0x00020002));
	rt2x00_register_write(rt2x00pci, PSCSR3, cpu_to_le32(0x00000002));

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, TIMECSR_US_COUNT, 33);
	rt2x00_set_field32(&reg, TIMECSR_US_64_COUNT, 63);
	rt2x00_set_field32(&reg, TIMECSR_BEACON_EXPECT, 0);
	rt2x00_register_write(rt2x00pci, TIMECSR, reg);

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, CSR9_MAX_FRAME_UNIT, (rt2x00pci->tx.entry_size / 128));
	rt2x00_register_write(rt2x00pci, CSR9, reg);

	rt2x00_register_write(rt2x00pci, CNT3, cpu_to_le32(0x3f080000));

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, RXCSR0_DISABLE_RX, 0);
	rt2x00_register_write(rt2x00pci, RXCSR0, reg);

	rt2x00_register_write(rt2x00pci, MACCSR0, cpu_to_le32(0x00213223));

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, MACCSR1_AUTO_TXBBP, 1);
	rt2x00_set_field32(&reg, MACCSR1_AUTO_RXBBP, 1);
	rt2x00_register_write(rt2x00pci, MACCSR1, reg);

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, MACCSR2_DELAY, 64);
	rt2x00_register_write(rt2x00pci, MACCSR2, reg);

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0, 3);		/* Tx power. */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID0_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1, 32);		/* Signal. */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID1_VALID, 1);
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2, 36);		/* Rssi. */
	rt2x00_set_field32(&reg, RXCSR3_BBP_ID2_VALID, 1);
	rt2x00_register_write(rt2x00pci, RXCSR3, reg);

	rt2x00_register_read(rt2x00pci, TIMECSR, &reg);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA0, 17);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID0, 154);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_DATA1, 0);
	rt2x00_set_field32(&reg, RALINKCSR_AR_BBP_ID1, 154);
	rt2x00_register_write(rt2x00pci, RALINKCSR, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, LEDCSR_ON_PERIOD, 30);
	rt2x00_set_field32(&reg, LEDCSR_OFF_PERIOD, 70);
	rt2x00_set_field32(&reg, LEDCSR_LINK, 0);
	rt2x00_set_field32(&reg, LEDCSR_ACTIVITY, 0);
	rt2x00_register_write(rt2x00pci, LEDCSR, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, CSR1_SOFT_RESET, 1);
	rt2x00_register_write(rt2x00pci, CSR1, reg);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, CSR1_HOST_READY, 1);
	rt2x00_register_write(rt2x00pci, CSR1, reg);

	/*
	 * We must clear the FCS and FIFI error count.
	 * These registers are cleared on read, so we may pass a useless variable to store the value.
	 */
	rt2x00_register_read(rt2x00pci, CNT0, &reg);
	rt2x00_register_read(rt2x00pci, CNT4, &reg);

	return 0;
}

static void
rt2x00_init_write_mac(struct _rt2x00_pci *rt2x00pci, struct net_device *net_dev)
{
	u32			reg[2];

	memset(&reg, 0x00, sizeof(reg));

	rt2x00_set_field32(&reg[0], CSR3_BYTE0, net_dev->dev_addr[0]);
	rt2x00_set_field32(&reg[0], CSR3_BYTE1, net_dev->dev_addr[1]);
	rt2x00_set_field32(&reg[0], CSR3_BYTE2, net_dev->dev_addr[2]);
	rt2x00_set_field32(&reg[0], CSR3_BYTE3, net_dev->dev_addr[3]);
	rt2x00_set_field32(&reg[1], CSR4_BYTE4, net_dev->dev_addr[4]);
	rt2x00_set_field32(&reg[1], CSR4_BYTE5, net_dev->dev_addr[5]);

	rt2x00_register_multiwrite(rt2x00pci, CSR3, &reg[0], sizeof(reg));
}

static int
rt2x00_init_bbp(struct _rt2x00_pci *rt2x00pci)
{
	u8		reg_id = 0x00;
	u8		value = 0x00;
	u8		counter = 0x00;

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_bbp_regread(rt2x00pci, 0x00, &value);
		if((value != 0xff) && (value != 0x00))
			goto continue_csr_init;
		NOTICE("Waiting for BBP register.\n");
	}

	ERROR("hardware problem, BBP register access failed, aborting.\n");
	return -EACCES;

continue_csr_init:
	rt2x00_bbp_regwrite(rt2x00pci, 1, 0x00);
	rt2x00_bbp_regwrite(rt2x00pci, 3, 0x27);
	rt2x00_bbp_regwrite(rt2x00pci, 4, 0x08);
	rt2x00_bbp_regwrite(rt2x00pci, 10, 0x0f);
	rt2x00_bbp_regwrite(rt2x00pci, 13, 0x08);
	rt2x00_bbp_regwrite(rt2x00pci, 15, 0x72);
	rt2x00_bbp_regwrite(rt2x00pci, 16, 0x74);
	rt2x00_bbp_regwrite(rt2x00pci, 17, 0x20);
	rt2x00_bbp_regwrite(rt2x00pci, 18, 0x72);
	rt2x00_bbp_regwrite(rt2x00pci, 19, 0x0b);
	rt2x00_bbp_regwrite(rt2x00pci, 20, 0x00);
	rt2x00_bbp_regwrite(rt2x00pci, 28, 0x11);
	rt2x00_bbp_regwrite(rt2x00pci, 29, 0x04);
	rt2x00_bbp_regwrite(rt2x00pci, 30, 0x21);
	rt2x00_bbp_regwrite(rt2x00pci, 31, 0x00);

	DEBUG("Start reading EEPROM contents...\n");
	for(counter = 0; counter < EEPROM_BBP_SIZE; counter++){
		if(rt2x00pci->eeprom[counter] != 0xffff && rt2x00pci->eeprom[counter] != 0x0000){
			reg_id = rt2x00_get_field16(rt2x00pci->eeprom[counter], EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(rt2x00pci->eeprom[counter], EEPROM_BBP_VALUE);
			DEBUG("BBP reg_id: 0x%02x, value: 0x%02x.\n", reg_id, value);
			rt2x00_bbp_regwrite(rt2x00pci, reg_id, value);
		}
	}
	DEBUG("...End of EEPROM contents.\n");

	return 0;
}

/*
 * Device radio routines.
 * When the radio is switched on or off, the TX and RX
 * should always be reset using the TXCSR0 and RXCSR0 registers.
 * The radio itself is switched on and off using the PWRCSR0 register.
 */
static int
rt2x00_dev_radio_on(struct _rt2x00_device *device)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	u32			reg = 0x00000000;

	if(rt2x00_pci_alloc_rings(device))
		goto exit_fail;

	rt2x00_clear_ring(rt2x00pci, &rt2x00pci->rx);
	rt2x00_clear_ring(rt2x00pci, &rt2x00pci->tx);
	rt2x00_clear_ring(rt2x00pci, &rt2x00pci->atim);
	rt2x00_clear_ring(rt2x00pci, &rt2x00pci->prio);
	rt2x00_clear_ring(rt2x00pci, &rt2x00pci->beacon);

	rt2x00_init_ring_register(rt2x00pci);

	if(rt2x00_init_registers(rt2x00pci))
		goto exit_fail;

	rt2x00_init_write_mac(rt2x00pci, device->net_dev);

	if(rt2x00_init_bbp(rt2x00pci))
		goto exit_fail;

	/*
	 * Clear interrupts.
	 */
	rt2x00_register_read(rt2x00pci, CSR7, &reg);
	rt2x00_register_write(rt2x00pci, CSR7, reg);

	/*
	 * Register interrupt handler.
	 */
	if(request_irq(rt2x00pci->pci_dev->irq, rt2x00_interrupt, SA_SHIRQ, device->net_dev->name, device)){
		ERROR("IRQ %d allocation failed.\n", rt2x00pci->pci_dev->irq);
		goto exit_fail;
	}

	/*
	 * Enable interrupts.
	 */
	rt2x00_register_read(rt2x00pci, CSR8, &reg);
	rt2x00_set_field32(&reg, CSR8_TBCN_EXPIRE, 0);
	rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, 0);
	rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, 0);
	rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, 0);
	rt2x00_set_field32(&reg, CSR8_RXDONE, 0);
	rt2x00_register_write(rt2x00pci, CSR8, reg);

	return 0;

exit_fail:
	rt2x00_pci_free_rings(device);

	return -ENOMEM;
}

static int
rt2x00_dev_radio_off(struct _rt2x00_device *device)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	u32			reg = 0x00000000;

	rt2x00_register_write(rt2x00pci, PWRCSR0, cpu_to_le32(0x00000000));

	rt2x00_register_read(rt2x00pci, TXCSR0, &reg);
	rt2x00_set_field32(&reg, TXCSR0_ABORT, 1);
	rt2x00_register_write(rt2x00pci, TXCSR0, reg);

	rt2x00_register_read(rt2x00pci, RXCSR0, &reg);
	rt2x00_set_field32(&reg, RXCSR0_DISABLE_RX, 1);
	rt2x00_register_write(rt2x00pci, RXCSR0, reg);

	rt2x00_register_read(rt2x00pci, LEDCSR, &reg);
	rt2x00_set_field32(&reg, LEDCSR_LINK, 0);
	rt2x00_register_write(rt2x00pci, LEDCSR, reg);

	rt2x00_register_read(rt2x00pci, CSR8, &reg);
	rt2x00_set_field32(&reg, CSR8_TBCN_EXPIRE, 1);
	rt2x00_set_field32(&reg, CSR8_TXDONE_TXRING, 1);
	rt2x00_set_field32(&reg, CSR8_TXDONE_ATIMRING, 1);
	rt2x00_set_field32(&reg, CSR8_TXDONE_PRIORING, 1);
	rt2x00_set_field32(&reg, CSR8_RXDONE, 1);
	rt2x00_register_write(rt2x00pci, CSR8, reg);

	rt2x00_pci_free_rings(device);

	free_irq(rt2x00pci->pci_dev->irq, device);

	return 0;
}

/*
 * Configuration handlers.
 */
static void
rt2x00_dev_update_bssid(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg[2];

	memset(&reg, 0x00, sizeof(reg));

	rt2x00_set_field32(&reg[0], CSR5_BYTE0, config->active.bssid[0]);
	rt2x00_set_field32(&reg[0], CSR5_BYTE1, config->active.bssid[1]);
	rt2x00_set_field32(&reg[0], CSR5_BYTE2, config->active.bssid[2]);
	rt2x00_set_field32(&reg[0], CSR5_BYTE3, config->active.bssid[3]);
	rt2x00_set_field32(&reg[1], CSR6_BYTE4, config->active.bssid[4]);
	rt2x00_set_field32(&reg[1], CSR6_BYTE5, config->active.bssid[5]);

	rt2x00_register_multiwrite(rt2x00pci, CSR5, &reg[0], sizeof(reg));
}

static void
rt2x00_dev_update_packet_filter(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg = 0x00000000;

	rt2x00_register_read(rt2x00pci, RXCSR0, &reg);

	if(config->active.iw_mode == IW_MODE_ADHOC
	|| config->active.iw_mode == IW_MODE_INFRA
	|| config->active.iw_mode == IW_MODE_AUTO)
		rt2x00_set_field32(&reg, RXCSR0_DROP_TODS, 1);
	else
		rt2x00_set_field32(&reg, RXCSR0_DROP_TODS, 0);

	if(config->active.flags & CONFIG_ACCEPT_PROMISC)
		rt2x00_set_field32(&reg, RXCSR0_DROP_NOT_TO_ME, 0);
	else
		rt2x00_set_field32(&reg, RXCSR0_DROP_NOT_TO_ME, 1);

	rt2x00_set_field32(&reg, RXCSR0_DROP_CRC, 1);
	if(config->active.iw_mode == IW_MODE_MONITOR){
		rt2x00_set_field32(&reg, RXCSR0_DROP_PHYSICAL, 0);
		rt2x00_set_field32(&reg, RXCSR0_DROP_CONTROL, 0);
		rt2x00_set_field32(&reg, RXCSR0_DROP_VERSION_ERROR, 0);
	}else{
		rt2x00_set_field32(&reg, RXCSR0_DROP_PHYSICAL, 1);
		rt2x00_set_field32(&reg, RXCSR0_DROP_CONTROL, 1);
		rt2x00_set_field32(&reg, RXCSR0_DROP_VERSION_ERROR, 1);
	}

	rt2x00_register_write(rt2x00pci, RXCSR0, reg);
}

static void
rt2x00_dev_update_channel(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg = 0x00000000;

	if(rt2x00_get_rf_value(&rt2x00pci->chip, config->active.channel, &rt2x00pci->channel)){
		ERROR("RF values for chip %04x and channel %d not found.\n", rt2x00_get_rf(&rt2x00pci->chip), config->active.channel);
		return;
	}

	INFO("Switching to channel %d. RF1: 0x%08x, RF2: 0x%08x, RF3: 0x%08x.\n", config->active.channel,
		rt2x00pci->channel.rf1, rt2x00pci->channel.rf2, rt2x00pci->channel.rf3);

	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf1);
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf2);
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf3);

	/*
	 * RF2420 chipset don't need any additional actions.
	 */
	if(rt2x00_rf(&rt2x00pci->chip, RF2420))
		return;

	/*
	 * For the RT2421 chipsets we need to write an invalid
	 * reference clock rate to activate auto_tune.
	 * After that we set the value back to the correct channel.
	 */
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf1);
	rt2x00_rf_regwrite(rt2x00pci, cpu_to_le32(0x000c2a32));
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf3);

	msleep(1);

	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf1);
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf2);
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf3);

	msleep(1);

	/*
	 * Switch off tuning bits.
	 */
	rt2x00_set_field32(&rt2x00pci->channel.rf1, RF1_TUNER, 0);
	rt2x00_set_field32(&rt2x00pci->channel.rf3, RF3_TUNER, 0);

	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf1);
	rt2x00_rf_regwrite(rt2x00pci, rt2x00pci->channel.rf3);

	/*
	 * Clear false CRC during channel switch.
	 */
	rt2x00_register_read(rt2x00pci, CNT0, &reg);
}

static void
rt2x00_dev_update_rate(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			value = 0x00000000;
	u32			reg = 0x00000000;
	u8			counter = 0x00;

	rt2x00_register_read(rt2x00pci, TXCSR1, &reg);
	value = config->sifs + (2 * config->slot_time) + config->plcp
		+ get_preamble(config)
		+ get_duration(ACK_SIZE, capabilities.bitrate[0]);
	rt2x00_set_field32(&reg, TXCSR1_ACK_TIMEOUT, value);

	value = config->sifs + config->plcp
		+ get_preamble(config)
		+ get_duration(ACK_SIZE, capabilities.bitrate[0]);
	rt2x00_set_field32(&reg, TXCSR1_ACK_CONSUME_TIME, value);

	rt2x00_set_field32(&reg, TXCSR1_TSF_OFFSET, 0x18);
	rt2x00_set_field32(&reg, TXCSR1_AUTORESPONDER, 1);

	rt2x00_register_write(rt2x00pci, TXCSR1, reg);

	reg = 0x00000000;
	for(counter = 0; counter < 12; counter++){
		reg |= cpu_to_le32(0x00000001 << counter);
		if(capabilities.bitrate[counter] == config->active.bitrate)
			break;
	}

	rt2x00_register_write(rt2x00pci, ARCSR1, reg);
}

static void
rt2x00_dev_update_txpower(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	rt2x00_bbp_regwrite(rt2x00pci, 3, rt2x00_get_txpower(&rt2x00pci->chip, config->active.txpower));
}

static void
rt2x00_dev_update_antenna(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u8			reg = 0x00;

	rt2x00_bbp_regread(rt2x00pci, 1, &reg);

	reg &= ~0x03;

	if(config->active.antenna_flags & ANTENNA_TX_DIV)
		reg = (reg & 0xfc) | 0x01;
	else if(config->active.antenna_flags & ANTENNA_TX_A)
		reg = (reg & 0xfc) | 0x00;
	else if(config->active.antenna_flags & ANTENNA_TX_B)
		reg = (reg & 0xfc) | 0x02;

	rt2x00_bbp_regwrite(rt2x00pci, 1, reg);

	rt2x00_bbp_regread(rt2x00pci, 4, &reg);

	reg &= ~0x06;

	if(config->active.antenna_flags & ANTENNA_RX_DIV)
		reg = (reg & 0xf9) | 0x02;
	else if(config->active.antenna_flags & ANTENNA_RX_A)
		reg = (reg & 0xf9) | 0x00;
	else if(config->active.antenna_flags & ANTENNA_RX_B)
		reg = (reg & 0xf9) | 0x04;

	rt2x00_bbp_regwrite(rt2x00pci, 4, reg);
}

static void
rt2x00_dev_update_duration(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg = 0x00000000;

	rt2x00_register_read(rt2x00pci, CSR11, &reg);
	rt2x00_set_field32(&reg, CSR11_CWMIN, 5);		/* 2^5 = 32. */
	rt2x00_set_field32(&reg, CSR11_CWMAX, 10);		/* 2^10 = 1024. */
	rt2x00_set_field32(&reg, CSR11_SLOT_TIME, config->slot_time);
	rt2x00_set_field32(&reg, CSR11_LONG_RETRY, config->active.long_retry);
	rt2x00_set_field32(&reg, CSR11_SHORT_RETRY, config->active.short_retry);
	rt2x00_register_write(rt2x00pci, CSR11, reg);

	rt2x00_register_read(rt2x00pci, CSR18, &reg);
	rt2x00_set_field32(&reg, CSR18_SIFS, config->sifs);
	rt2x00_set_field32(&reg, CSR18_PIFS, config->sifs + config->slot_time);
	rt2x00_register_write(rt2x00pci, CSR18, reg);

	rt2x00_register_read(rt2x00pci, CSR19, &reg);
	rt2x00_set_field32(&reg, CSR19_DIFS, config->sifs + (2 * config->slot_time));
	rt2x00_set_field32(&reg, CSR19_EIFS, config->sifs + get_duration((IEEE80211_HEADER + ACK_SIZE), capabilities.bitrate[0]));
	rt2x00_register_write(rt2x00pci, CSR19, reg);
}

static void
rt2x00_dev_update_preamble(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg[4];
	u32			preamble = 0x00000000;

	memset(&reg, 0x00, sizeof(reg));

	if(config->active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		preamble = 0x00000008;

	reg[0] = cpu_to_le32(0x00700400 | preamble);	/* ARCSR2 */
	reg[1] = cpu_to_le32(0x00380401 | preamble);	/* ARCSR3 */
	reg[2] = cpu_to_le32(0x00150402 | preamble);	/* ARCSR4 */
	reg[3] = cpu_to_le32(0x000b8403 | preamble);	/* ARCSR5 */

	rt2x00_register_multiwrite(rt2x00pci, ARCSR2, &reg[0], sizeof(reg));
}

static void
rt2x00_dev_update_sensitivity(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	rt2x00pci->sensitivity = config->active.sensitivity;
}

static void
rt2x00_dev_update_led(struct _rt2x00_pci *rt2x00pci, struct _rt2x00_config *config)
{
	u32			reg = 0x00000000;

	rt2x00_register_read(rt2x00pci, LEDCSR, &reg);
	rt2x00_set_field32(&reg, LEDCSR_LINK, config->led_status ? 1 : 0);
	rt2x00_register_write(rt2x00pci, LEDCSR, reg);
}

static int
rt2x00_dev_update_config(struct _rt2x00_device *device, struct _rt2x00_config *config, u16 update_flags)
{
	struct _rt2x00_pci 	*rt2x00pci = rt2x00_priv(device);

	if(update_flags & UPDATE_BSSID)
		rt2x00_dev_update_bssid(rt2x00pci, config);

	if(update_flags & UPDATE_PACKET_FILTER)
		rt2x00_dev_update_packet_filter(rt2x00pci, config);

	if(update_flags & UPDATE_CHANNEL)
		rt2x00_dev_update_channel(rt2x00pci, config);

	if(update_flags & UPDATE_BITRATE)
		rt2x00_dev_update_rate(rt2x00pci, config);

	if(update_flags & UPDATE_TXPOWER)
		rt2x00_dev_update_txpower(rt2x00pci, config);

	if(update_flags & UPDATE_ANTENNA)
		rt2x00_dev_update_antenna(rt2x00pci, config);

	if(update_flags & UPDATE_DURATION || update_flags & UPDATE_RETRY)
		rt2x00_dev_update_duration(rt2x00pci, config);

	if(update_flags & UPDATE_PREAMBLE)
		rt2x00_dev_update_preamble(rt2x00pci, config);

	if(update_flags & UPDATE_SENSITIVITY)
		rt2x00_dev_update_sensitivity(rt2x00pci, config);

	if(update_flags & UPDATE_LED_STATUS)
		rt2x00_dev_update_led(rt2x00pci, config);

	return 0;
}

static int
rt2x00_dev_update_stats(struct _rt2x00_device *device, struct _rt2x00_stats *stats)
{
	struct _rt2x00_pci 	*rt2x00pci = rt2x00_priv(device);

	rt2x00_bbp_regread(rt2x00pci, 32, &stats->signal);

	return 0;
}

/*
 * Transmission routines.
 * rt2x00_dev_test_tx returns 0 if the requested amount of DMA ring entries are free.
 * rt2x00_write_tx_desc will write the txd descriptor.
 * rt2x00_dev_xmit_packet will copy the packets to the appropriate DMA ring.
 */
static int
rt2x00_dev_test_tx(struct _rt2x00_device *device, u8 fragments)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	return fragments > rt2x00_ring_free_entries(&rt2x00pci->tx);
}

/*
 * PLCP_SIGNAL, PLCP_SERVICE, PLCP_LENGTH_LOW and PLCP_LENGTH_HIGH are BBP registers.
 * Besides the value we want to write we also set the busy bit (0x8000) and the register number (0x0f00).
 * The value we want to write is stored in 0x00ff.
 * For PLCP_SIGNAL we can optionally enable SHORT_PREAMBLE.
 * For PLCP_SERVICE we can set the length extension bit according to
 * 802.11b standard 18.2.3.5.
 */
static void
rt2x00_write_tx_desc(struct _rt2x00_pci *rt2x00pci, struct _txd *txd, u32 packet_size, u16 rate, u8 priority, u16 xmit_flags)
{
	u32		residual = 0x00000000;
	u16		signal = 0x0000;
	u16		service = 0x0000;
	u16		length_low = 0x0000;
	u16		length_high = 0x0000;

	rt2x00_set_field32(&txd->word0, TXD_W0_VALID, 1);
	rt2x00_set_field32(&txd->word2, TXD_W2_DATABYTE_COUNT, packet_size);
	rt2x00_set_field32(&txd->word0, TXD_W0_ACK, (xmit_flags & XMIT_ACK) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_RETRY_MODE, (xmit_flags & XMIT_LONG_RETRY) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_TIMESTAMP, (xmit_flags & XMIT_TIMESTAMP) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_ACK, (xmit_flags & XMIT_ACK) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_MORE_FRAG, (xmit_flags & XMIT_MORE_FRAGS) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_MORE_FRAG, (xmit_flags & XMIT_RTS) ? 1 : 0);
	rt2x00_set_field32(&txd->word0, TXD_W0_RTS, (xmit_flags & XMIT_RTS) ? 1 : 0);

	packet_size += 4;

	/*
	 * Convert length to microseconds.
	 */
	residual = get_duration_res(packet_size, rate);
	packet_size = get_duration(packet_size, rate);

	if(residual != 0)
		packet_size++;

	length_high = 0x8000 | 0x0700 | (packet_size >> 8);
	length_low = 0x8000 | 0x0800 | (packet_size & 0xff);

	signal |= 0x8500 | rt2x00_get_plcp(rate);
	if(xmit_flags & XMIT_SHORT_PREAMBLE)
		signal |= 0x0008;

	service |= 0x0600 | 0x0004;
	if(residual <= (8 % 11))
		service |= 0x0080;

	rt2x00_set_field32(&txd->word3, TXD_W3_PLCP_SIGNAL, signal);
	rt2x00_set_field32(&txd->word3, TXD_W3_PLCP_SERVICE, service);
	rt2x00_set_field32(&txd->word4, TXD_W4_PLCP_LENGTH_LOW, length_low);
	rt2x00_set_field32(&txd->word4, TXD_W4_PLCP_LENGTH_HIGH, length_high);

	if(xmit_flags & XMIT_IFS_BACKOFF)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 0);
	else if(xmit_flags & XMIT_IFS_SIFS)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 1);
	else if(xmit_flags & XMIT_IFS_NEW_BACKOFF)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 2);
	else if(xmit_flags & XMIT_IFS_NONE)
		rt2x00_set_field32(&txd->word0, TXD_W0_IFS, 3);

	/*
	 * Set this last, after this the device can start transmitting the packet.
	 */
	rt2x00_set_field32(&txd->word0, TXD_W0_OWNER_NIC, 1);
}

static int
rt2x00_dev_xmit_packet(struct _rt2x00_device *device, struct sk_buff *skb, u8 ring_type, u16 rate, u16 xmit_flags)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	struct _data_ring	*ring = NULL;
	struct _txd		*txd = NULL;
	void			*data = NULL;
	u32			reg = 0x00000000;

	rt2x00_register_read(rt2x00pci, TXCSR0, &reg);

	if(ring_type == RING_TX){
		ring = &rt2x00pci->tx;
		rt2x00_set_field32(&reg, TXCSR0_KICK_TX, 1);
	}else if(ring_type == RING_PRIO){
		ring = &rt2x00pci->prio;
		rt2x00_set_field32(&reg, TXCSR0_KICK_PRIO, 1);
	}else if(ring_type == RING_ATIM){
		ring = &rt2x00pci->atim;
		rt2x00_set_field32(&reg, TXCSR0_KICK_ATIM, 1);
	}else if(ring_type == RING_BEACON){
		ring = &rt2x00pci->beacon;
	}

	if(skb){
		txd = DESC_ADDR(ring);
		data = DATA_ADDR(ring);

		if(rt2x00_get_field32(txd->word0, TXD_W0_OWNER_NIC)
		|| rt2x00_get_field32(txd->word0, TXD_W0_VALID))
			return -ENOMEM;

		memcpy(data, skb->data, skb->len);
		rt2x00_write_tx_desc(rt2x00pci, txd, skb->len, rate, skb->priority, xmit_flags);
	
		rt2x00_ring_index_inc(ring);
	}

	if(xmit_flags & XMIT_START)
		rt2x00_register_write(rt2x00pci, TXCSR0, reg);

	return 0;
}

/*
 * PCI device handlers for usage by core module.
 */
static struct _rt2x00_dev_handler rt2x00_pci_handler = {
	.dev_module		= THIS_MODULE,
	.dev_probe		= rt2x00_dev_probe,
	.dev_remove		= rt2x00_dev_remove,
	.dev_radio_on		= rt2x00_dev_radio_on,
	.dev_radio_off		= rt2x00_dev_radio_off,
	.dev_update_config	= rt2x00_dev_update_config,
	.dev_update_stats	= rt2x00_dev_update_stats,
	.dev_test_tx		= rt2x00_dev_test_tx,
	.dev_xmit_packet	= rt2x00_dev_xmit_packet,
};

/*
 * PCI driver handlers.
 */
static int 
rt2x00_pci_probe(struct pci_dev *pci_dev, const struct pci_device_id *id)
{
	struct net_device	*net_dev = NULL;
	int			status = 0x00000000;

	if(id->driver_data != RT2460){
		ERROR("detected device not supported.\n");
		status = -ENODEV;
		goto exit;
	}

	if(pci_enable_device(pci_dev)){
		ERROR("enable device failed.\n");
		status = -EIO;
		goto exit;
	}

	pci_set_master(pci_dev);

	if(pci_set_mwi(pci_dev))
		NOTICE("MWI not available\n");

	if(pci_set_dma_mask(pci_dev, DMA_64BIT_MASK)
	&& pci_set_dma_mask(pci_dev, DMA_32BIT_MASK)){
		ERROR("PCI DMA not supported\n");
		status = -EIO;
		goto exit_disable_device;
	}

	if(pci_request_regions(pci_dev, pci_name(pci_dev))){
		ERROR("PCI request regions failed.\n");
		status = -EBUSY;
		goto exit_disable_device;
	}

	net_dev = rt2x00_core_probe(&rt2x00_pci_handler, pci_dev, sizeof(struct _rt2x00_pci), &pci_dev->dev);
	if(!net_dev){
		ERROR("net_device allocation failed.\n");
		status = -ENOMEM;
		goto exit_release_regions;
	}

	net_dev->irq = pci_dev->irq;

	pci_set_drvdata(pci_dev, net_dev);

	return 0;

exit_release_regions:
	pci_release_regions(pci_dev);

exit_disable_device:
	if(status != -EBUSY)
		pci_disable_device(pci_dev);

exit:
	return status;
}

static void
rt2x00_pci_remove(struct pci_dev *pci_dev)
{
	struct net_device	*net_dev = pci_get_drvdata(pci_dev);

	rt2x00_core_remove(net_dev);

	pci_set_drvdata(pci_dev, NULL);

	pci_release_regions(pci_dev);

	pci_disable_device(pci_dev);
}

#ifdef CONFIG_PM
static int
rt2x00_pci_suspend(struct pci_dev *pci_dev, pm_message_t state)
{
	struct net_device	*net_dev = pci_get_drvdata(pci_dev);
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	u32			reg = 0x00000000;

	if(!test_and_clear_bit(DEVICE_AWAKE, &device->flags)){
		NOTICE("Device already asleep.\n");
		return 0;
	}

	if(rt2x00_suspend(device))
		return -EBUSY;

	NOTICE("Going to sleep.\n");

	netif_device_detach(net_dev);

	reg = 0x00000000;
	rt2x00_set_field32(&reg, PWRCSR1_SET_STATE, 1);
	rt2x00_set_field32(&reg, PWRCSR1_BBP_DESIRE_STATE, 1);
	rt2x00_set_field32(&reg, PWRCSR1_RF_DESIRE_STATE, 1);
	rt2x00_set_field32(&reg, PWRCSR1_PUT_TO_SLEEP, 1);

	rt2x00_register_write(rt2x00pci, PWRCSR1, reg);

	pci_save_state(pci_dev);
	pci_disable_device(pci_dev);
	pci_set_power_state(pci_dev, pci_choose_state(pci_dev, state));

	return 0;
}

static int
rt2x00_pci_resume(struct pci_dev *pci_dev)
{
	struct net_device	*net_dev = pci_get_drvdata(pci_dev);
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);
	u32			reg = 0x00000000;

	if(test_and_set_bit(DEVICE_AWAKE, &device->flags)){
		NOTICE("Device already awake.\n");
		return 0;
	}

	NOTICE("Waking up.\n");

	pci_set_power_state(pci_dev, PCI_D0);

	if(pci_enable_device(pci_dev)){
		ERROR("enable device failed.\n");
		return -EIO;
	}

	pci_restore_state(pci_dev);

	rt2x00_set_field32(&reg, PWRCSR1_SET_STATE, 1);
	rt2x00_set_field32(&reg, PWRCSR1_BBP_DESIRE_STATE, 3);
	rt2x00_set_field32(&reg, PWRCSR1_RF_DESIRE_STATE, 3);
	rt2x00_set_field32(&reg, PWRCSR1_PUT_TO_SLEEP, 0);

	rt2x00_register_write(rt2x00pci, PWRCSR1, reg);

	netif_device_attach(net_dev);

	return rt2x00_resume(device);
}
#endif /* CONFIG_PM */

/*
 * RT2x00 PCI module information.
 */
static char version[] = DRV_NAME " - " DRV_VERSION " (" DRV_RELDATE ") by " DRV_PROJECT;

static struct pci_device_id rt2x00_device_pci_tbl[] = {
	{ PCI_DEVICE(0x1814, 0x0101), .driver_data = RT2460},	/* Ralink 802.11b */
	{0,}
};

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2400 PCI & PCMCIA Wireless LAN driver.");
MODULE_SUPPORTED_DEVICE("Ralink RT2460 PCI & PCMCIA chipset based cards");
MODULE_DEVICE_TABLE(pci, rt2x00_device_pci_tbl);
MODULE_LICENSE("GPL");

#ifdef CONFIG_RT2X00_DEBUG
module_param_named(debug, rt2x00_debug_level, bool, S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(debug, "Set this parameter to 1 to enable debug output.");
#endif /* CONFIG_RT2X00_DEBUG */

static struct pci_driver rt2x00_pci_driver = {
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 15)
	.owner		= THIS_MODULE,
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 15) */
	.name		= DRV_NAME,
	.id_table	= rt2x00_device_pci_tbl,
	.probe		= rt2x00_pci_probe,
	.remove		= __devexit_p(rt2x00_pci_remove),
#ifdef CONFIG_PM
	.suspend	= rt2x00_pci_suspend,
	.resume		= rt2x00_pci_resume,
#endif /* CONFIG_PM */
};

static int __init rt2x00_pci_init(void)
{
	printk(KERN_INFO "Loading module: %s\n", version);
	return pci_register_driver(&rt2x00_pci_driver);
}

static void __exit rt2x00_pci_exit(void)
{
	printk(KERN_INFO "Unloading module: %s\n", version);
	pci_unregister_driver(&rt2x00_pci_driver);
}

module_init(rt2x00_pci_init);
module_exit(rt2x00_pci_exit);
