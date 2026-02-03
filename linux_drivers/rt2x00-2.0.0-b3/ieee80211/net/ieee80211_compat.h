/*
 * RT2X00 Compatability fixes for specific kernels.
 */
#ifndef IEEE_COMPAT_H
#define IEEE_COMPAT_H

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/etherdevice.h>

#if LINUX_VERSION_CODE == KERNEL_VERSION(2, 6, 13)
typedef unsigned __nocast gfp_t;

static inline int is_broadcast_ether_addr(const u8 *addr)
{
        return (addr[0] & addr[1] & addr[2] & addr[3] & addr[4] & addr[5]) == 0xff;
}
#endif /* LINUX_VERSION_CODE == KERNEL_VERSION(2, 6, 13) */

#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 14)
static inline unsigned compare_ether_addr(const u8 *_a, const u8 *_b)
{
	const u16 *a = (const u16 *) _a;
	const u16 *b = (const u16 *) _b;

	BUILD_BUG_ON(ETH_ALEN != 6);
	return ((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2])) != 0;
}
#endif /* LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 14) */
#endif /* IEEE_COMPAT_H */
