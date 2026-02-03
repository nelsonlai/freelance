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
	Module: rt2x00core
	Abstract: Data structures for the rt2x00 core module.
	Supported chipsets: RT2460, RT2560 & RT2570.
 */ 

#ifndef RT2X00CORE_H
#define RT2X00CORE_H

#include <net/ieee80211.h>

/*
 * NOTE: Lock ordering.
 * Locks should be acquired in the following order:
 *	device->rt2x00_sem
 *	ieee80211->lock
 *	ring->lock
 * Locks should be released in reversed order.
 */

/* 
 * Private IOCTL commands
 */
#define SIOCSIWPRIVNETWORK		SIOCIWFIRSTPRIV + 0x0000
#define SIOCGIWPRIVNETWORK		SIOCIWFIRSTPRIV + 0x0001
#define SIOCSIWPRIVPREAMBLE		SIOCIWFIRSTPRIV + 0x0002
#define SIOCGIWPRIVPREAMBLE		SIOCIWFIRSTPRIV + 0x0003
#define SIOCSIWPRIVANTENNA		SIOCIWFIRSTPRIV + 0x0004
#define SIOCGIWPRIVANTENNA		SIOCIWFIRSTPRIV + 0x0005
#define SIOCSIWPRIVGEOGRAPHY		SIOCIWFIRSTPRIV + 0x0006
#define SIOCGIWPRIVGEOGRAPHY		SIOCIWFIRSTPRIV + 0x0007
#define SIOCSIWPRIVADHOCOFDM		SIOCIWFIRSTPRIV + 0x0008
#define SIOCGIWPRIVADHOCOFDM		SIOCIWFIRSTPRIV + 0x0009

/*
 * Private IOCTL flags.
 */
#define IOCTL_PREAMBLE_LONG		0x01	/* SIOCSIWPRIVPREAMBLE */
#define IOCTL_PREAMBLE_SHORT		0x02	/* SIOCSIWPRIVPREAMBLE */
#define IOCTL_ANTENNA_TX_MASK		0x0f	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_TX_DIV		0x01	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_TX_A		0x02	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_TX_B		0x04	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_RX_MASK		0xf0	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_RX_DIV		0x10	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_RX_A		0x20	/* SIOCSIWPRIVANTENNA */
#define IOCTL_ANTENNA_RX_B		0x40	/* SIOCSIWPRIVANTENNA */
#define IOCTL_GEOGRAPHY_USA		0x00	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_CANADA		0x01	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_EUROPE		0x02	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_SPAIN		0x03	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_FRANCE		0x04	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_JAPAN		0x05	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_JAPAN1		0x06	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_ISRAEL		0x07	/* SIOCSIWPRIVGEOGRAPHY */
#define IOCTL_GEOGRAPHY_INVAL		0x08	/* SIOCSIWPRIVGEOGRAPHY */

/*
 * Buffer flags for MGMT frames.
 */
#define MGMT_BUFFER_ALL			0xff
#define MGMT_BUFFER_ESSID		0x01
#define MGMT_BUFFER_RATES		0x02
#define MGMT_BUFFER_CHANNEL		0x04
#define MGMT_BUFFER_CHALLENGE		0x08

/*
 * Core data structures.
 */

struct _packet_ring{
	spinlock_t			lock;
	struct _rt2x00_core		*core;
	struct work_struct		work;
	struct sk_buff_head		queue;
	u8				ready;
	u8				type;
	u16				__pad;		/* For alignment only. */
} __attribute__ ((packed));

struct _rt2x00_core{
	struct _rt2x00_device		*device;

	/*
	 * Ieee80211 stack structure.
	 */
	struct ieee80211_device	*ieee80211;

	/*
	 * Device configuration.
	 */
	struct _rt2x00_config		config;

	/*
	 * Queue for pending Scan and link tuning work.
	 */
	struct workqueue_struct	*workqueue;

	/*
	 * Work structure for periodic channel switching during scan period.
	 */
	struct semaphore		scan_sem;
	struct work_struct		scan_tuner;
	struct iw_scan_req		*scan_req;
	u16				scan_flags;

	/*
	 * Connection information.
	 */
	u8				connection_attempt;
	u8				connection_status;
#define CONNECTION_INITIALIZED		0x00		/* Not busy connecting. */
#define CONNECTION_STATUS		0x0f		/* Busy connecting. */
#define CONNECTION_AUTHENTICATE		0x01		/* Authenticating. */
#define CONNECTION_HANDSHAKE		0x02		/* Handshaking. */
#define CONNECTION_ASSOCIATE		0x04		/* Associating. */
#define CONNECTION_ESTABLISHED		0x08		/* Connected. */
#define CONNECTION_DIRECTION		0xf0		/* Connection direction. */
#define CONNECTION_TO_NODE		0x10		/* Device connects to node. */
#define CONNECTION_FROM_NODE		0x20		/* Node connects to device. */

	/*
	 * Network we are connected to.
	 */
	struct ieee80211_network	*network;

	/*
	 * Work structure for periodic link handling.
	 */
	struct work_struct		link_tuner;

	/*
	 * Ring name: RX.
	 * Description: Packet ring used for receiving packets.
	 */
	struct _packet_ring		rx;

	/*
	 * Ring name: TX.
	 * Description: Packet ring used for transmitting normal packets.
	 */
	struct _packet_ring		tx;

	/*
	 * Ring name: ATIM.
	 * Description: Packet ring used for transmitting power management packets.
	 */
	struct _packet_ring		atim;

	/*
	 * Ring name: PRIO.
	 * Description: Packet ring used for transmitting management packets.
	 */
	struct _packet_ring		prio;

	/*
	 * Ring name: BEACON.
	 * Description: Packet ring used for transmitting beacon packets.
	 */
	struct _packet_ring		beacon;

	/*
	 * Connection statistics.
	 */
	struct _rt2x00_stats		rt2x00_stats;

	/*
	 * Network statistics.
	 */
	struct iw_statistics		wireless_stats;
	struct iw_public_data 		wireless_data;
} __attribute__ ((packed));

#define CONNECTION_TIME_LIMIT		( HZ / 2 )
#define CONNECTION_ATTEMPT_LIMIT	( 5 )
#define AUTHENTICATING(__core)		( (__core)->connection_status & (CONNECTION_AUTHENTICATE | CONNECTION_HANDSHAKE) )
#define HANDSHAKING(__core)		( (__core)->connection_status & CONNECTION_HANDSHAKE )
#define ASSOCIATING(__core)		( (__core)->connection_status & CONNECTION_ASSOCIATE )
#define CONNECTED(__core)		( (__core)->connection_status & CONNECTION_ESTABLISHED )
#define CONNECT_DIR(__core)		( (__core)->connection_status & CONNECTION_DIRECTION )

static inline void
rt2x00_init_connect(struct _rt2x00_core *core, u8 status, u8 direction)
{
	unsigned long		time_stamp = jiffies;

	memcpy(&core->network->time_stamp, &time_stamp, sizeof(time_stamp));
	core->connection_attempt = 0;
	core->connection_status = status | direction;
}

static inline void
rt2x00_set_connect(struct _rt2x00_core *core, u8 status)
{
	unsigned long		time_stamp = jiffies;

	memcpy(&core->network->time_stamp, &time_stamp, sizeof(time_stamp));
	core->connection_attempt = 0;
	core->connection_status &= ~CONNECTION_STATUS;
	core->connection_status |= status;
}

static inline void
rt2x00_set_disconnect(struct _rt2x00_core *core)
{
	core->connection_attempt = 0;
	core->connection_status = 0;
}

static inline int
rt2x00_connection_status(struct _rt2x00_core *core)
{
	if(core->connection_status & CONNECTION_ESTABLISHED)
		return 0;
	if(!core->network)
		return -ENOMEM;
	if(time_after(jiffies, ((unsigned long)core->network->time_stamp) + CONNECTION_TIME_LIMIT))
		core->connection_attempt++;
	if(core->connection_attempt > CONNECTION_ATTEMPT_LIMIT)
		return -ENOTCONN;
	if(core->connection_status & CONNECTION_TO_NODE)
		return -EAGAIN;
	return 0;
}

static inline void
rt2x00_init_ring(struct _rt2x00_device *device, struct _packet_ring *ring, u8 ring_type, void (*handler)(void*))
{
	spin_lock_init(&ring->lock);
	skb_queue_head_init(&ring->queue);
	INIT_WORK(&ring->work, handler, ring);
	ring->core = rt2x00_core(device);
	ring->type = ring_type;
	ring->ready = 0;
}

static inline void
rt2x00_enable_ring(struct _packet_ring *ring)
{
	spin_lock(&ring->lock);
	ring->ready = 1;
	spin_unlock(&ring->lock);
}

static inline void
rt2x00_disable_ring(struct _packet_ring *ring)
{
	spin_lock(&ring->lock);
	ring->ready = 0;
	cancel_delayed_work(&ring->work);
	skb_queue_purge(&ring->queue);
	spin_unlock(&ring->lock);
}

static inline void
rt2x00_kick_ring(struct _packet_ring *ring)
{
	spin_lock(&ring->lock);
	ring->ready = 1;
	if(!skb_queue_empty(&ring->queue))
		queue_work(ring->core->workqueue, &ring->work);
	spin_unlock(&ring->lock);
}

static inline void
rt2x00_queue_ring(struct _packet_ring *ring, struct sk_buff *skb)
{
	spin_lock(&ring->lock);
	skb_queue_tail(&ring->queue, skb);
	if(ring->ready)
		queue_work(ring->core->workqueue, &ring->work);
	spin_unlock(&ring->lock);
}

static inline int
rt2x00_is_24ghz_channel(const u8 channel)
{
	return (channel >= IEEE80211_24GHZ_MIN_CHANNEL && channel <= IEEE80211_24GHZ_MAX_CHANNEL);
}

static inline int
rt2x00_is_52ghz_channel(const u8 channel)
{
	return (channel >= IEEE80211_52GHZ_MIN_CHANNEL && channel <= IEEE80211_52GHZ_MAX_CHANNEL);
}

static inline u16
rt2x00_get_sequence(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	u16				sequence = 0x0000;

	spin_lock(&core->ieee80211->lock);

	sequence = core->config.sequence;
	core->config.sequence = (core->config.sequence + 0x0010) & IEEE80211_SCTL_SEQ;

	spin_unlock(&core->ieee80211->lock);

	return sequence;
}

static inline u16
rt2x00_channel_to_freq(const u8 channel)
{
	if(channel <= 14)
		return ((channel == 14) ? 2484 : (channel * 5) + 2407);
	else
		return ((channel + 1000) * 5);
}

static inline u8
rt2x00_freq_to_channel(const u16 freq)
{
	if(freq <= 2484)
		return ((freq == 2484) ? 14 : (freq - 2407) / 5);
	else
		return ((freq / 5) - 1000);

}

#endif /* RT2X00CORE_H */
