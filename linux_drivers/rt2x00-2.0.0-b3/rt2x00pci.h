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
	Module: rt2x00pci
	Abstract: Data structures and registers for the rt2x00 pci modules.
	Supported chipsets: RT2460 & RT2560.
 */

#ifndef RT2X00PCI_H
#define RT2X00PCI_H

/*
 * PCI data structure.
 */

/*
 * Ring handlers.
 */
static inline int
rt2x00_pci_alloc_ring(
	struct _rt2x00_device *device,
	struct _data_ring *ring,
	const u8 ring_type,
	const u16 max_entries,
	const u16 entry_size,
	const u16 desc_size)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	rt2x00_init_ring(device, ring, ring_type, max_entries, entry_size, desc_size);

	ring->data_addr = dma_alloc_coherent(&rt2x00pci->pci_dev->dev, ring->mem_size, &ring->data_dma, GFP_KERNEL);
	if(!ring->data_addr)
		return -ENOMEM;

	memset(ring->data_addr, 0x00, ring->mem_size);

	return 0;
}

static int
rt2x00_pci_alloc_rings(struct _rt2x00_device *device)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	if(rt2x00_pci_alloc_ring(device, &rt2x00pci->rx, RING_RX, RX_ENTRIES, DATA_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_pci_alloc_ring(device, &rt2x00pci->tx, RING_TX, TX_ENTRIES, DATA_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_pci_alloc_ring(device, &rt2x00pci->atim, RING_ATIM, ATIM_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_pci_alloc_ring(device, &rt2x00pci->prio, RING_PRIO, PRIO_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)
	|| rt2x00_pci_alloc_ring(device, &rt2x00pci->beacon, RING_BEACON, BEACON_ENTRIES, MGMT_FRAME_SIZE, SIZE_DESCRIPTOR)){
		ERROR("DMA allocation failed.\n");
		return -ENOMEM;
	}

	return 0;
}

static inline void
rt2x00_pci_free_ring(struct _data_ring *ring)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(ring->device);

	if(ring->data_addr)
		dma_free_coherent(&rt2x00pci->pci_dev->dev, ring->mem_size, ring->data_addr, ring->data_dma);
	ring->data_addr = NULL;

	rt2x00_deinit_ring(ring);
}

static void
rt2x00_pci_free_rings(struct _rt2x00_device *device)
{
	struct _rt2x00_pci	*rt2x00pci = rt2x00_priv(device);

	rt2x00_pci_free_ring(&rt2x00pci->rx);
	rt2x00_pci_free_ring(&rt2x00pci->tx);
	rt2x00_pci_free_ring(&rt2x00pci->atim);
	rt2x00_pci_free_ring(&rt2x00pci->prio);
	rt2x00_pci_free_ring(&rt2x00pci->beacon);
}

/*
 * Macro's for calculating exact position in data ring.
 */
#define DESC_BASE(__ring)		( (void*)((__ring)->data_addr) )
#define DATA_BASE(__ring)		( (void*)(DESC_BASE(__ring) + ((__ring)->max_entries * (__ring)->desc_size)) )

#define __DESC_ADDR(__ring, __index)	( (void*)(DESC_BASE(__ring) + ((__index) * (__ring)->desc_size)) )
#define __DATA_ADDR(__ring, __index)	( (void*)(DATA_BASE(__ring) + ((__index) * (__ring)->entry_size)) )

#define DESC_ADDR(__ring)		( __DESC_ADDR(__ring, (__ring)->index) )
#define DESC_ADDR_DONE(__ring)		( __DESC_ADDR(__ring, (__ring)->index_done) )

#define DATA_ADDR(__ring)		( __DATA_ADDR(__ring, (__ring)->index) )
#define DATA_ADDR_DONE(__ring)		( __DATA_ADDR(__ring, (__ring)->index_done) )

/*
 * Register access.
 * All access to the registers will go through rt2x00_register_read and rt2x00_register_write.
 * BBP and RF register require indirect register access through the register BBPCSR and RFCSR.
 * The indirect register access work with busy bits, and a read or write function call can fail.
 * Specific fields within a register can be accessed using the set and get field routines,
 * these function will handle the requirement of little_endian and big_endian conversions.
 */
#define REGISTER_BUSY_COUNT	10	/* Number of retries before failing access BBP & RF indirect register */
#define REGISTER_BUSY_DELAY	100	/* Delay between each register access retry. (us) */

static void
rt2x00_register_read(const struct _rt2x00_pci *rt2x00pci, const unsigned long offset, u32 *value)
{
	*value = readl((void*)(rt2x00pci->csr_addr + offset));
}

static void
rt2x00_register_multiread(const struct _rt2x00_pci *rt2x00pci, const unsigned long offset, u32 *value, const u16 length)
{
	memcpy_fromio((void*)value, (void*)(rt2x00pci->csr_addr + offset), length);
}

static void
rt2x00_register_write(const struct _rt2x00_pci *rt2x00pci, const unsigned long offset, const u32 value)
{
	writel(value, (void*)(rt2x00pci->csr_addr + offset));
}

static void
rt2x00_register_multiwrite(const struct _rt2x00_pci *rt2x00pci, const unsigned long offset, u32 *value, const u16 length)
{
	memcpy_toio((void*)(rt2x00pci->csr_addr + offset), (void*)value, length);
}

static void 
rt2x00_bbp_regwrite(const struct _rt2x00_pci *rt2x00pci, const u8 reg_id, const u8 value)
{
	u32		reg = 0x00000000;
	u8		counter = 0x00;

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00pci, BBPCSR, &reg);
		if(!rt2x00_get_field32(reg, BBPCSR_BUSY))
			goto bbp_write;
		udelay(REGISTER_BUSY_DELAY);
	}

	ERROR("BBPCSR register busy. Write failed\n");
	return;

bbp_write:
	reg = 0x00000000;
	rt2x00_set_field32(&reg, BBPCSR_VALUE, value);
	rt2x00_set_field32(&reg, BBPCSR_REGNUM, reg_id);
	rt2x00_set_field32(&reg, BBPCSR_BUSY, 1);
	rt2x00_set_field32(&reg, BBPCSR_WRITE_CONTROL, 1);

	rt2x00_register_write(rt2x00pci, BBPCSR, reg);
}

static void
rt2x00_bbp_regread(const struct _rt2x00_pci *rt2x00pci, const u8 reg_id, u8 *value)
{
	u32		reg = 0x00000000;
	u8		counter = 0x00;

	/*
	 * We first have to acquire the requested BBP register,
	 * so we write the register id into the BBP register first.
	 */
	rt2x00_set_field32(&reg, BBPCSR_REGNUM, reg_id);
	rt2x00_set_field32(&reg, BBPCSR_BUSY, 1);
	rt2x00_set_field32(&reg, BBPCSR_WRITE_CONTROL, 0);

	rt2x00_register_write(rt2x00pci, BBPCSR, reg);

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00pci, BBPCSR, &reg);
		if(!rt2x00_get_field32(reg, BBPCSR_BUSY)){
			*value = rt2x00_get_field32(reg, BBPCSR_VALUE);
			return;
		}
		udelay(REGISTER_BUSY_DELAY);
	}

	ERROR("BBPCSR register busy. Read failed\n");
	*value = 0xff;
}

static void
rt2x00_rf_regwrite(const struct _rt2x00_pci *rt2x00pci, const u32 value)
{
	u32		reg = 0x00000000;
	u8		counter = 0x00;

	for(counter = 0x00; counter < REGISTER_BUSY_COUNT; counter++){
		rt2x00_register_read(rt2x00pci, RFCSR, &reg);
		if(!rt2x00_get_field32(reg, RFCSR_BUSY))
			goto rf_write;
		udelay(REGISTER_BUSY_DELAY);
	}

	ERROR("RFCSR register busy. Write failed\n");
	return;

rf_write:
	reg = value;
	rt2x00_set_field32(&reg, RFCSR_NUMBER_OF_BITS, 20);
	rt2x00_set_field32(&reg, RFCSR_IF_SELECT, 0);
	rt2x00_set_field32(&reg, RFCSR_BUSY, 1);

	rt2x00_register_write(rt2x00pci, RFCSR, reg);
}

/*
 * EEPROM access.
 * The EEPROM is being accessed by word index.
 * rt2x00_eeprom_read_word is the main access function that can be called by
 * the rest of the module. It will take the index number of the eeprom word
 * and the bus width.
 */
static inline void
rt2x00_eeprom_pulse_high(const struct _rt2x00_pci *rt2x00pci, u32 *flags)
{
	rt2x00_set_field32(flags, CSR21_EEPROM_DATA_CLOCK, 1);
	rt2x00_register_write(rt2x00pci, CSR21, *flags);
	udelay(1);
}

static inline void
rt2x00_eeprom_pulse_low(const struct _rt2x00_pci *rt2x00pci, u32 *flags)
{
	rt2x00_set_field32(flags, CSR21_EEPROM_DATA_CLOCK, 0);
	rt2x00_register_write(rt2x00pci, CSR21, *flags);
	udelay(1);
}

static void
rt2x00_eeprom_shift_out_bits(const struct _rt2x00_pci *rt2x00pci, const u16 data, const u16 count)
{
	u32	flags = 0x00000000;
	u32	mask =  0x0001 << (count - 1);

	rt2x00_register_read(rt2x00pci, CSR21, &flags);

	/*
	 * Clear data flags.
	 */
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_OUT, 0);

	/*
	 * Start writing all bits. 
	 */
	do{
		/*
		 * Only set the data_in flag when we are at the correct bit.
		 */
		rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, (data & mask) ? 1 : 0);

		rt2x00_register_write(rt2x00pci, CSR21, flags);

		rt2x00_eeprom_pulse_high(rt2x00pci, &flags);
		rt2x00_eeprom_pulse_low(rt2x00pci, &flags);

		/*
		 * Shift to next bit.
		 */
		mask >>= 1;
	} while(mask);

	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
	rt2x00_register_write(rt2x00pci, CSR21, flags);
}

static void
rt2x00_eeprom_shift_in_bits(const struct _rt2x00_pci *rt2x00pci, u16 *data)
{
	u32	flags = 0x00000000;
	u8	counter = 0x00;

	rt2x00_register_read(rt2x00pci, CSR21, &flags);

	/*
	 * Clear data flags.
	 */
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_OUT, 0);

	/*
	 * Start reading all 16 bits.
	 */
	for(counter = 0; counter < 16; counter++){
		/*
		 * Shift to the next bit.
		 */
		*data <<= 1;

		rt2x00_eeprom_pulse_high(rt2x00pci, &flags);

		rt2x00_register_read(rt2x00pci, CSR21, &flags);

		/*
		 * Clear data_in flag and set the data bit to 1 when the data_out flag is set.
		 */
		rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
		if(rt2x00_get_field32(flags, CSR21_EEPROM_DATA_OUT))
			*data |= 1;
	
		rt2x00_eeprom_pulse_low(rt2x00pci, &flags);
	}
}

static u16
rt2x00_eeprom_read_word(const struct _rt2x00_pci *rt2x00pci, const u8 word)
{
	u32	flags = 0x00000000;
	u16	data = 0x0000;

	/*
	 * Clear all flags, and enable chip select.
	 */
	rt2x00_register_read(rt2x00pci, CSR21, &flags);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_OUT, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_CLOCK, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_CHIP_SELECT, 1);
	rt2x00_register_write(rt2x00pci, CSR21, flags);

	/*
	 * kick a pulse.
	 */
	rt2x00_eeprom_pulse_high(rt2x00pci, &flags);
	rt2x00_eeprom_pulse_low(rt2x00pci, &flags);

	/*
	 * Select the read opcode and bus_width.
	 */
	rt2x00_eeprom_shift_out_bits(rt2x00pci, EEPROM_READ_OPCODE, 3);
	rt2x00_eeprom_shift_out_bits(rt2x00pci, word, rt2x00pci->eeprom_width);

	rt2x00_eeprom_shift_in_bits(rt2x00pci, &data);

	/*
	 * Clear chip_select and data_in flags.
	 */
	rt2x00_register_read(rt2x00pci, CSR21, &flags);
	rt2x00_set_field32(&flags, CSR21_EEPROM_DATA_IN, 0);
	rt2x00_set_field32(&flags, CSR21_EEPROM_CHIP_SELECT, 0);
	rt2x00_register_write(rt2x00pci, CSR21, flags);

	/*
	 * kick a pulse.
	 */
	rt2x00_eeprom_pulse_high(rt2x00pci, &flags);
	rt2x00_eeprom_pulse_low(rt2x00pci, &flags);

	return data;
}

#endif /* RT2X00PCI_H */
