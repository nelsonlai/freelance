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
	Abstract: rt2x00 core routines.
	Supported chipsets: RT2460, RT2560 & RT2570.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>

#include "rt2x00.h"
#include "rt2x00core.h"

#ifdef DRV_NAME
#undef DRV_NAME
#define DRV_NAME			"rt2x00core"
#endif /* DRV_NAME */

static int rt2x00_radio_on(struct _rt2x00_device *device);
static int rt2x00_radio_off(struct _rt2x00_device *device);

struct _rt2x00_device*
rt2x00_device(struct net_device *net_dev)
{
	return ieee80211_priv(net_dev);
}
EXPORT_SYMBOL_GPL(rt2x00_device);

static void
rt2x00_wireless_event(struct _rt2x00_device *device, unsigned int event)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	union iwreq_data			wrqu;

	switch(event){
		case SIOCGIWSCAN:
			wrqu.data.length = 0;
			wrqu.data.flags = 0;
		break;
		case SIOCGIWAP:
			wrqu.ap_addr.sa_family = ARPHRD_ETHER;
			memcpy(&wrqu.ap_addr.sa_data, &core->config.active.bssid, ETH_ALEN);
		break;
	}

	wireless_send_event(device->net_dev, event, &wrqu, NULL);
}

static void
rt2x00_update_config(struct _rt2x00_device *device)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	u16					update_flags = 0x0000;

	if(!test_bit(DEVICE_ENABLED, &device->flags)
	&& !test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(test_and_set_bit(DEVICE_CONFIG_UPDATE, &device->flags))
		return;

	down_write(&device->rt2x00_sem);

	update_flags = core->config.update_flags;
	core->config.update_flags = 0;

	downgrade_write(&device->rt2x00_sem);

	if(likely(update_flags))
		device->handler->dev_update_config(device, &core->config, update_flags);

	up_read(&device->rt2x00_sem);

	clear_bit(DEVICE_CONFIG_UPDATE, &device->flags);
}

/*
 * Management frames handlers
 */
static struct sk_buff*
rt2x00_create_mgmt_frame(struct _rt2x00_device *device, unsigned int length, u16 type, u8 *addr)
{
	struct sk_buff				*skb = NULL;
	struct ieee80211_hdr_3addr		*ieee80211hdr = NULL;

	skb = dev_alloc_skb(MGMT_FRAME_SIZE);
	if(!skb){
		ERROR("couldn't create mgmt frame.\n");
		return NULL;
	}

	skb_reserve(skb, NET_IP_ALIGN);

	if(unlikely((skb->tail + length) > skb->end)){
		dev_kfree_skb_any(skb);
		ERROR("padding of mgmt frame failed.\n");
		return NULL;
	}
	ieee80211hdr = (struct ieee80211_hdr_3addr*)skb_put(skb, length);

	ieee80211hdr->frame_ctl = cpu_to_le16(IEEE80211_FTYPE_MGMT | type);
	ieee80211hdr->duration_id = cpu_to_le16(0);
	memcpy(&ieee80211hdr->addr1, addr, ETH_ALEN);
	memcpy(&ieee80211hdr->addr2, &device->net_dev->dev_addr, ETH_ALEN);
	memcpy(&ieee80211hdr->addr3, addr, ETH_ALEN);
	ieee80211hdr->seq_ctl = cpu_to_le16(rt2x00_get_sequence(device));

	return skb;
}

static int
rt2x00_encrypt_mgmt_frame(struct _rt2x00_device *device, struct sk_buff *skb)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct ieee80211_crypt_data		*crypt = NULL;

	spin_lock(&core->ieee80211->lock);

	crypt = core->ieee80211->crypt[core->ieee80211->tx_keyidx];
	atomic_inc(&crypt->refcnt);

	if(pskb_expand_head(skb,
	crypt->ops->extra_msdu_prefix_len + crypt->ops->extra_mpdu_prefix_len,
	crypt->ops->extra_msdu_postfix_len + crypt->ops->extra_mpdu_postfix_len,
	GFP_KERNEL)){
		INFO("Failed to expand buffer for encryption.\n");
		goto exit_fail;
	}

	if(crypt->ops->encrypt_msdu
	&& crypt->ops->encrypt_msdu(skb, IEEE80211_3ADDR_LEN, crypt->priv) < 0){
		INFO("Encryption (msdu) of mgmt frame failed.\n");
		goto exit_fail;
	}

	if(crypt->ops->encrypt_mpdu
	&& crypt->ops->encrypt_mpdu(skb, IEEE80211_3ADDR_LEN, crypt->priv) < 0){
		INFO("Encryption (mpdu) of mgmt frame failed.\n");
		goto exit_fail;
	}

	if(unlikely((skb->tail + 4) > skb->end)){
		ERROR("padding of mgmt frame failed.\n");
		goto exit_fail;
	}
	skb_put(skb, 4);

	atomic_dec(&crypt->refcnt);
	spin_unlock(&core->ieee80211->lock);

	return 0;

exit_fail:
	atomic_dec(&crypt->refcnt);
	core->ieee80211->ieee_stats.tx_discards++;
	spin_unlock(&core->ieee80211->lock);
	return -EFAULT;
}

static int
rt2x00_put_mgmt_buffer(struct sk_buff *skb, struct ieee80211_info_element *element, void *data)
{
	u8					*buffer = NULL;

	if(unlikely((skb->tail + sizeof(*element) + element->len) > skb->end)){
		dev_kfree_skb_any(skb);
		ERROR("padding of mgmt buffer failed.\n");
		return -ENOMEM;
	}
	buffer = skb_put(skb, sizeof(*element) + element->len);

	memcpy(buffer, element, sizeof(*element));
	buffer += sizeof(*element);
	memcpy(buffer, data, element->len);

	return 0;
}

static int
rt2x00_create_mgmt_buffer(struct _rt2x00_device *device, struct sk_buff *skb, u8 flags)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct ieee80211_info_element		element;
	u8					index = 0x00;

	if(flags & MGMT_BUFFER_ESSID){
		element.id = MFIE_TYPE_SSID;
		element.len = strlen(&core->config.active.essid[0]);
		if(rt2x00_put_mgmt_buffer(skb, &element, &core->config.active.essid))
			return -ENOMEM;
	}

	if(flags & MGMT_BUFFER_RATES){
		element.id = MFIE_TYPE_RATES;
		if(core->config.active.network == IEEE_B){
			element.len = 4;
			index = 0;
		}else if(core->config.active.network & IEEE_B){
			element.len = 12;
			index = 0;
		}else{
			element.len = 8;
			index = 4;
		}
		if(rt2x00_put_mgmt_buffer(skb, &element, &capabilities.bitrate[index]))
			return -ENOMEM;
	}

	if(flags & MGMT_BUFFER_CHANNEL){
		element.id = MFIE_TYPE_DS_SET;
		element.len = sizeof(core->config.active.channel);
		if(rt2x00_put_mgmt_buffer(skb, &element, &core->config.active.channel))
			return -ENOMEM;
	}

	if(core->ieee80211->sec.level >= SEC_LEVEL_2
	|| !(flags & MGMT_BUFFER_CHALLENGE) || !core->ieee80211->wpa_ie)
		return 0;

	memcpy(&element, core->ieee80211->wpa_ie, sizeof(element));
	if(((core->config.active.wpa_version ==  IW_AUTH_WPA_VERSION_WPA) && (element.id == MFIE_TYPE_GENERIC))
	|| ((core->config.active.wpa_version ==  IW_AUTH_WPA_VERSION_WPA2) && (element.id == MFIE_TYPE_RSN)))
		return rt2x00_put_mgmt_buffer(skb, &element, core->ieee80211->wpa_ie);

	WARNING("Required WPA IE not found.\n");

	return 0;
}

static u16
rt2x00_create_mgmt_capability(struct _rt2x00_device *device)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	u16					capability = 0x0000;

	if(core->config.active.iw_mode == IW_MODE_INFRA)
		capability |= WLAN_CAPABILITY_ESS;
	if(core->config.active.iw_mode == IW_MODE_ADHOC)
		capability |= WLAN_CAPABILITY_IBSS;
	if(core->ieee80211->sec.encrypt)
		capability |= WLAN_CAPABILITY_PRIVACY;
	if(core->config.active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		capability |= WLAN_CAPABILITY_SHORT_PREAMBLE;
	if(core->config.slot_time == 9)
		capability |= WLAN_CAPABILITY_SHORT_SLOT_TIME;

	return capability;
}

static void
rt2x00_mgmt_snd_beacon(struct _rt2x00_device *device)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_beacon		*beacon = NULL;
	u8					addr[ETH_ALEN];

	memset(&addr, 0xff, sizeof(addr));

	skb = rt2x00_create_mgmt_frame(device, sizeof(*beacon), IEEE80211_STYPE_BEACON, &addr[0]);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	beacon = (struct ieee80211_beacon*)skb->data;

	beacon->time_stamp[0] = jiffies;
	beacon->beacon_interval = cpu_to_le16(core->config.beacon);
	beacon->capability = cpu_to_le16(rt2x00_create_mgmt_capability(device));
	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_ALL)){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		return;
	}

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	spin_lock(&core->beacon.lock);
	skb_queue_purge(&core->beacon.queue);
	spin_unlock(&core->beacon.lock);

	rt2x00_queue_ring(&core->beacon, skb);
}

static void
rt2x00_mgmt_snd_probe_req(struct _rt2x00_device *device)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_info_element		element;
	u8					index = 0x00;

	memset(&element, 0x00, sizeof(element));

	skb = rt2x00_create_mgmt_frame(device, sizeof(struct ieee80211_probe_request), IEEE80211_STYPE_PROBE_REQ, &core->scan_req->bssid.sa_data[0]);
	if(!skb)
		return;

	element.id = MFIE_TYPE_SSID;
	element.len = core->scan_req->essid_len;
	if(rt2x00_put_mgmt_buffer(skb, &element, &core->scan_req->essid)){
		ERROR("could not create mgmt buffer.\n");
		return;
	}

	element.id = MFIE_TYPE_RATES;
	down_read(&device->rt2x00_sem);
	if(core->config.active.network == IEEE_B){
		element.len = 4;
		index = 0;
	}else if(core->config.active.network & IEEE_B){
		element.len = 12;
		index = 0;
	}else{
		element.len = 8;
		index = 4;
	}
	up_read(&device->rt2x00_sem);

	if(rt2x00_put_mgmt_buffer(skb, &element, &capabilities.bitrate[index])){
		ERROR("could not create mgmt buffer.\n");
		return;
	}

	rt2x00_queue_ring(&core->prio, skb);
}

static void
rt2x00_mgmt_snd_probe_resp(struct _rt2x00_device *device, u8 *addr)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_probe_response		*probe = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*probe), IEEE80211_STYPE_PROBE_RESP, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	probe = (struct ieee80211_probe_response*)skb->data;

	probe->time_stamp[0] = jiffies;
	probe->beacon_interval = cpu_to_le16(core->config.beacon);
	probe->capability = cpu_to_le16(rt2x00_create_mgmt_capability(device));
	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_ALL)){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		return;
	}

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	rt2x00_queue_ring(&core->prio, skb);

	INFO("Probe response sent to " MAC_FMT ".\n", MAC_ARG(probe->header.addr1));
}

static void
rt2x00_mgmt_snd_assoc(struct _rt2x00_device *device, u8 *addr)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_assoc_request		*assoc = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*assoc), IEEE80211_STYPE_ASSOC_REQ, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	assoc = (struct ieee80211_assoc_request*)skb->data;

	assoc->capability = cpu_to_le16(rt2x00_create_mgmt_capability(device));
	assoc->listen_interval = cpu_to_le16(3);
	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_ESSID | MGMT_BUFFER_RATES)){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		return;
	}

	rt2x00_set_connect(core, CONNECTION_ASSOCIATE);
	core->ieee80211->state = IEEE80211_ASSOCIATING;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Association request sent to " MAC_FMT ".\n", MAC_ARG(assoc->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);
}

static void
rt2x00_mgmt_snd_assoc_resp(struct _rt2x00_device *device, u16 request, u8 *addr, u16 reason)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_assoc_response	*assoc = NULL;

	if(request == IEEE80211_STYPE_ASSOC_REQ)
		skb = rt2x00_create_mgmt_frame(device, sizeof(*assoc), IEEE80211_STYPE_ASSOC_RESP, addr);
	else
		skb = rt2x00_create_mgmt_frame(device, sizeof(*assoc), IEEE80211_STYPE_REASSOC_RESP, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	assoc = (struct ieee80211_assoc_response*)skb->data;

	assoc->capability = cpu_to_le16(rt2x00_create_mgmt_capability(device));
	assoc->status = cpu_to_le16(reason);
	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_ESSID | MGMT_BUFFER_RATES)){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		return;
	}

	rt2x00_set_connect(core, CONNECTION_ASSOCIATE);
	core->ieee80211->state = IEEE80211_ASSOCIATING;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Association response sent to " MAC_FMT ".\n", MAC_ARG(assoc->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);
}

static void
rt2x00_mgmt_snd_disassoc(struct _rt2x00_device *device, u8 *addr, u16 reason)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_disassoc		*disassoc = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*disassoc), IEEE80211_STYPE_DISASSOC, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	disassoc = (struct ieee80211_disassoc*)skb->data;

	disassoc->reason = cpu_to_le16(reason);

	rt2x00_set_disconnect(core);
	core->ieee80211->state = IEEE80211_AUTHENTICATED;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Disassociation request sent to " MAC_FMT ".\n", MAC_ARG(disassoc->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);
}

static void
rt2x00_mgmt_snd_auth(struct _rt2x00_device *device, u16 direction, u8 *addr, u16 reason)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_auth			*auth = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*auth), IEEE80211_STYPE_AUTH, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	auth = (struct ieee80211_auth*)skb->data;

	auth->algorithm = cpu_to_le16(core->ieee80211->sec.auth_mode);
	auth->transaction = cpu_to_le16((direction == CONNECTION_TO_NODE) ? 1 : 2);
	auth->status = cpu_to_le16(reason);

	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_CHALLENGE)){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		return;
	}

	rt2x00_init_connect(core, CONNECTION_AUTHENTICATE, direction);
	core->ieee80211->state = IEEE80211_AUTHENTICATING;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Authentication request sent to " MAC_FMT ".\n", MAC_ARG(auth->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);
}

static void
rt2x00_mgmt_snd_auth_shake(struct _rt2x00_device *device, u8 *addr, u16 reason)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_auth			*auth = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*auth), IEEE80211_STYPE_AUTH, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	auth = (struct ieee80211_auth*)skb->data;

	auth->algorithm = cpu_to_le16(core->ieee80211->sec.auth_mode);
	auth->transaction = cpu_to_le16((CONNECT_DIR(core) == CONNECTION_TO_NODE) ? 3 : 4);
	auth->status = cpu_to_le16(reason);

	if(rt2x00_create_mgmt_buffer(device, skb, MGMT_BUFFER_CHALLENGE))
		goto exit_fail;

	if(rt2x00_encrypt_mgmt_frame(device, skb))
		goto exit_fail;

	rt2x00_set_connect(core, CONNECTION_HANDSHAKE);

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Authentication handshake request sent to " MAC_FMT ".\n", MAC_ARG(auth->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);

	return;

exit_fail:
	dev_kfree_skb_any(skb);
	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);
}

static void
rt2x00_mgmt_snd_deauth(struct _rt2x00_device *device, u8 *addr, u16 reason)
{
	struct _rt2x00_core			*core = rt2x00_core(device);
	struct sk_buff				*skb = NULL;
	struct ieee80211_deauth		*auth = NULL;

	skb = rt2x00_create_mgmt_frame(device, sizeof(*auth), IEEE80211_STYPE_DEAUTH, addr);
	if(!skb)
		return;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	auth = (struct ieee80211_deauth*)skb->data;

	auth->reason = cpu_to_le16(reason);

	rt2x00_set_disconnect(core);
	core->ieee80211->state = IEEE80211_INITIALIZED;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Deauthentication request sent to " MAC_FMT ".\n", MAC_ARG(auth->header.addr1));

	rt2x00_queue_ring(&core->prio, skb);
}

static int
rt2x00_handle_auth(struct net_device *net_dev, struct ieee80211_auth *auth)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);
	u16					status = le16_to_cpu(auth->status);

	down_read(&device->rt2x00_sem);

	if(!core->network
	|| (core->config.active.flags & CONFIG_FIX_BSSID
	&& compare_ether_addr(&auth->header.addr2[0], &core->config.active.bssid[0]))){
		up_read(&device->rt2x00_sem);
		return 0;
	}

	if(!AUTHENTICATING(core)){
		up_read(&device->rt2x00_sem);
		INFO("Authentication request received from " MAC_FMT ".\n", MAC_ARG(auth->header.addr2));
		rt2x00_mgmt_snd_auth(device, CONNECTION_FROM_NODE, &auth->header.addr2[0], WLAN_STATUS_SUCCESS);
		return 0;
	}

	if(status != WLAN_STATUS_SUCCESS){
		up_read(&device->rt2x00_sem);
		INFO("Authentication request failed for " MAC_FMT ", status: %d.\n", MAC_ARG(auth->header.addr2), status);
		return 0;
	}

	spin_lock(&core->ieee80211->lock);

	if(!core->ieee80211->ieee802_1x
	&& core->ieee80211->sec.encrypt
	&& core->ieee80211->sec.level >= SEC_LEVEL_2){
		spin_unlock(&core->ieee80211->lock);
		up_read(&device->rt2x00_sem);
		rt2x00_mgmt_snd_auth_shake(device, &auth->header.addr2[0], WLAN_STATUS_SUCCESS);
		return 0;
	}

	core->ieee80211->state = IEEE80211_AUTHENTICATED;

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Authentication request succeeded for " MAC_FMT ".\n", MAC_ARG(auth->header.addr2));

	rt2x00_mgmt_snd_assoc(device, &auth->header.addr2[0]);

	return 0;
}

static int
rt2x00_handle_deauth(struct net_device *net_dev, struct ieee80211_auth *auth)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);

	rt2x00_mgmt_snd_deauth(device, &auth->header.addr2[0], auth->transaction);

	return 0;
}

static int
rt2x00_handle_probe_request(struct net_device *net_dev, struct ieee80211_probe_request *req, struct ieee80211_rx_stats *rx_stats)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	if(core->config.active.iw_mode == IW_MODE_MONITOR
	|| core->config.active.iw_mode == IW_MODE_INFRA){
		up_read(&device->rt2x00_sem);
		return 0;
	}

	up_read(&device->rt2x00_sem);

	rt2x00_mgmt_snd_probe_resp(device, &req->header.addr2[0]);

	return 0;
}

static void
rt2x00_start_connection(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	u8				mode = 0x00;

	down_write(&device->rt2x00_sem);

	/*
	 * Start net interface tx /rx.
	 */
	netif_carrier_on(device->net_dev);
	netif_start_queue(device->net_dev);

	mode = core->config.active.iw_mode;

	core->config.led_status = 1;

	core->config.update_flags |= UPDATE_LED_STATUS;

	up_write(&device->rt2x00_sem);

	if(mode != IW_MODE_MONITOR){
		rt2x00_mgmt_snd_beacon(device);
		rt2x00_wireless_event(device, SIOCGIWAP);
	}

	rt2x00_update_config(device);
}

static void
rt2x00_handle_assoc(struct _rt2x00_device *device, struct ieee80211_hdr_4addr *ieee80211hdr)
{
	struct _rt2x00_core			*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	if(!core->network
	|| (core->config.active.flags & CONFIG_FIX_BSSID
	&& compare_ether_addr(&ieee80211hdr->addr2[0], &core->config.active.bssid[0]))){
		up_read(&device->rt2x00_sem);
		return;
	}

	spin_lock(&core->ieee80211->lock);
	rt2x00_set_connect(core, CONNECTION_ESTABLISHED);
	core->ieee80211->state = IEEE80211_ASSOCIATED;
	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Association request received from " MAC_FMT ".\n", MAC_ARG(ieee80211hdr->addr2));

	if(WLAN_FC_GET_STYPE(le16_to_cpu(ieee80211hdr->frame_ctl)) == IEEE80211_STYPE_ASSOC_REQ)
		rt2x00_mgmt_snd_assoc_resp(device, IEEE80211_STYPE_ASSOC_REQ, &ieee80211hdr->addr2[0], WLAN_STATUS_SUCCESS);
	else
		rt2x00_mgmt_snd_assoc_resp(device, IEEE80211_STYPE_REASSOC_REQ, &ieee80211hdr->addr2[0], WLAN_STATUS_SUCCESS);

	rt2x00_start_connection(device);

	return;
}

static int
rt2x00_handle_assoc_resp(struct net_device *net_dev, struct ieee80211_assoc_response *assoc, struct ieee80211_network *network)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);
	u16					status = le16_to_cpu(assoc->status);

	down_read(&device->rt2x00_sem);

	if(!ASSOCIATING(core)
	|| !core->network || compare_ether_addr(&assoc->header.addr2[0], &core->network->bssid[0])){
		up_read(&device->rt2x00_sem);
		return 0;
	}

	if(status != WLAN_STATUS_SUCCESS){
		up_read(&device->rt2x00_sem);
		INFO("Association request failed for " MAC_FMT ", reason: %d.\n", MAC_ARG(assoc->header.addr2), status);
		return 0;
	}

	core->network->last_associate = jiffies;
	core->network->last_scanned = jiffies;

	spin_lock(&core->ieee80211->lock);
	rt2x00_set_connect(core, CONNECTION_ESTABLISHED);
	core->ieee80211->state = IEEE80211_ASSOCIATED;
	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	INFO("Association request succeeded for " MAC_FMT ".\n", MAC_ARG(assoc->header.addr2));

	rt2x00_start_connection(device);

	return 0;
}

static int
rt2x00_handle_disassoc(struct net_device *net_dev, struct ieee80211_disassoc *disassoc)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);

	if(!core->network || compare_ether_addr(&disassoc->header.addr2[0], &core->network->bssid[0]))
		return 0;

	INFO("Disassociation request received from " MAC_FMT ".\n", MAC_ARG(disassoc->header.addr2));

	rt2x00_mgmt_snd_disassoc(device, &disassoc->header.addr2[0], disassoc->reason);

	return 0;
}


static int
rt2x00_handle_beacon(struct net_device *net_dev, struct ieee80211_beacon *beacon, struct ieee80211_network *network)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	network->last_scanned = jiffies;
	if(core->network && !compare_ether_addr(&network->bssid[0], &core->network->bssid[0]))
		memcpy(core->network, network, sizeof(*network));

	up_read(&device->rt2x00_sem);
	return 0;
}

static int
rt2x00_handle_probe_resp(struct net_device *net_dev, struct ieee80211_probe_response *resp, struct ieee80211_network *network)
{
	struct _rt2x00_device			*device = ieee80211_priv(net_dev);
	struct _rt2x00_core			*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	network->last_scanned = jiffies;
	if(core->network && !compare_ether_addr(&network->bssid[0], &core->network->bssid[0]))
		memcpy(core->network, network, sizeof(*network));

	up_read(&device->rt2x00_sem);
	return 0;
}

/*
 * Scanning routines.
 */
#define SCAN_TIME			( HZ / 5 )
#define BEACON_EXPIRE			( HZ * 2 )

static void
rt2x00_start_scan(struct _rt2x00_device *device, struct iw_scan_req *scan_req, const u16 flags)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	const struct ieee80211_geo	*geo = ieee80211_get_geo(core->ieee80211);
	u8				counter = 0x00;

	if(test_and_set_bit(DEVICE_SCANNING, &device->flags)){
		NOTICE("Device already busy scanning.\n");
		return;
	}

	down(&core->scan_sem);

	core->scan_flags = flags;
	core->scan_req = kmalloc(sizeof(*core->scan_req), GFP_KERNEL);
	if(!core->scan_req){
		up(&core->scan_sem);
		WARNING("not enough memory to allocate scan request.\n");
		return;
	}

	if(scan_req)
		memcpy(core->scan_req, scan_req, sizeof(*core->scan_req));
	else
		memset(core->scan_req, 0x00, sizeof(*core->scan_req));

	if(core->scan_flags == IW_SCAN_DEFAULT)
		memset(&core->scan_req->bssid.sa_data, 0xff, sizeof(core->scan_req->bssid.sa_data));

	if(!(core->scan_flags & IW_SCAN_THIS_ESSID)){
		memset(&core->scan_req->essid, '\0', sizeof(core->scan_req->essid));
		core->scan_req->essid_len = 0;
	}

	if(core->scan_flags & IW_SCAN_THIS_FREQ){
		down_read(&device->rt2x00_sem);
		core->scan_req->channel_list[0].m = core->config.active.channel;
		core->scan_req->num_channels = 1;
		up_read(&device->rt2x00_sem);
	}else if(!core->scan_req->num_channels){
		spin_lock(&core->ieee80211->lock);

		if(core->ieee80211->freq_band & IEEE80211_24GHZ_BAND){
			for(counter = 0; counter < geo->bg_channels; counter++)
				core->scan_req->channel_list[counter].m = geo->bg[counter].channel;
			core->scan_req->num_channels += geo->bg_channels;
		}
		if(core->ieee80211->freq_band & IEEE80211_52GHZ_BAND){
			for(counter = 0; counter < geo->a_channels; counter++)
				core->scan_req->channel_list[core->scan_req->num_channels + counter].m = geo->a[counter].channel;
			core->scan_req->num_channels += geo->a_channels;
		}

		spin_unlock(&core->ieee80211->lock);
	}else{
		for(counter = 0; counter < core->scan_req->num_channels; counter++){
			if(core->scan_req->channel_list[counter].m > 1000)
				core->scan_req->channel_list[counter].m =
					rt2x00_freq_to_channel(core->scan_req->channel_list[counter].m / 100000);
		}
	}

	if(core->scan_flags & IW_SCAN_THIS_FREQ){
		INFO("Start scanning current channel...\n");
	}else{
		INFO("Start scanning all channels...\n");
		down_write(&device->rt2x00_sem);
		core->config.active.channel = core->scan_req->channel_list[0].m;
		core->config.update_flags |= UPDATE_CHANNEL;
		up_write(&device->rt2x00_sem);
	}

	rt2x00_update_config(device);

	if(core->scan_req->scan_type == IW_SCAN_TYPE_ACTIVE)
		rt2x00_mgmt_snd_probe_req(device);

	queue_delayed_work(core->workqueue, &core->scan_tuner, SCAN_TIME);
}

static void
rt2x00_stop_scan(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);

	cancel_delayed_work(&core->scan_tuner);

	if(!test_and_clear_bit(DEVICE_SCANNING, &device->flags))
		return;

	if(!(core->scan_flags & IW_SCAN_THIS_FREQ)){
		down_write(&device->rt2x00_sem);
		core->config.active.channel = core->config.user.channel;
		core->config.update_flags |= UPDATE_CHANNEL;
		up_write(&device->rt2x00_sem);
		rt2x00_update_config(device);
	}

	if(core->scan_req)
		kfree(core->scan_req);
	core->scan_req = NULL;

	if(!test_bit(DEVICE_ENABLED, &device->flags)
	&& test_bit(DEVICE_RADIO_ON, &device->flags))
		rt2x00_radio_off(device);

	rt2x00_wireless_event(device, SIOCGIWSCAN);

	up(&core->scan_sem);

	INFO("...Scan ended.\n");
}

static void
rt2x00_scan_periodic(void *data)
{
	struct _rt2x00_device		*device = data;
	struct _rt2x00_core		*core = rt2x00_core(device);
	u8				counter = 0x00;
	u8				channel = 0x00;
	u8				new_channel = 0x00;

	down_read(&device->rt2x00_sem);
	channel = core->config.active.channel;
	up_read(&device->rt2x00_sem);

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(!test_bit(DEVICE_SCANNING, &device->flags)){
		WARNING("Scan update failed, not busy scanning.\n");
		return;
	}

	if(core->scan_flags & IW_SCAN_THIS_FREQ || core->scan_req->num_channels == 1){
		rt2x00_stop_scan(device);
		return;
	}

	for(counter = 0; counter < (core->scan_req->num_channels - 1); counter++){
		if(channel == core->scan_req->channel_list[counter].m)
			new_channel = core->scan_req->channel_list[counter + 1].m;
	}

	if(!new_channel){
		rt2x00_stop_scan(device);
		return;
	}

	down_write(&device->rt2x00_sem);
	core->config.active.channel = new_channel;
	core->config.update_flags |= UPDATE_CHANNEL;
	up_write(&device->rt2x00_sem);

	rt2x00_update_config(device);

	if(core->scan_req->scan_type == IW_SCAN_TYPE_ACTIVE)
		rt2x00_mgmt_snd_probe_req(device);

	queue_delayed_work(core->workqueue, &core->scan_tuner, SCAN_TIME);
}

/*
 * rt2x00_validate_scan_entry should be called with rt2x00_sem and ieee80211->lock held!.
 */
static int
rt2x00_validate_scan_entry(struct ieee80211_device *ieee80211, struct _rt2x00_config *config, struct ieee80211_network *entry)
{
	if(time_after(jiffies, (entry->last_scanned + BEACON_EXPIRE)))
		return -EINVAL;

	if(config->active.iw_mode != IW_MODE_AUTO){
		if(!(entry->capability & (WLAN_CAPABILITY_ESS | WLAN_CAPABILITY_IBSS)))
			return -EINVAL;
		if((config->active.iw_mode == IW_MODE_INFRA)
		&& !(entry->capability & WLAN_CAPABILITY_ESS))
			return -EINVAL;
		if(config->active.iw_mode == IW_MODE_ADHOC
		&& (entry->capability & WLAN_CAPABILITY_ESS))
			return -EINVAL;
	}

	if(config->active.flags & CONFIG_FIX_BSSID
	&& compare_ether_addr(&config->active.bssid[0], &entry->bssid[0]))
		return -EINVAL;

	if(config->active.flags & CONFIG_FIX_ESSID
	&& !ieee80211_is_empty_essid(&entry->ssid[0], entry->ssid_len)){
		if(entry->ssid_len != strlen(&config->active.essid[0])
		|| memcmp(&config->active.essid, &entry->ssid, entry->ssid_len))
			return -EINVAL;
	}

	if(config->active.flags & CONFIG_FIX_CHANNEL
	&& !(entry->channel == config->active.channel))
		return -EINVAL;

	if(!(entry->flags & NETWORK_HAS_CCK && ieee80211->modulation & IEEE80211_CCK_MODULATION)
	&& !(entry->flags & NETWORK_HAS_OFDM && ieee80211->modulation & IEEE80211_OFDM_MODULATION))
		return -EINVAL;

	if((entry->capability & WLAN_CAPABILITY_PRIVACY) ^ ieee80211->sec.enabled){
		if((ieee80211->sec.level != SEC_LEVEL_1)
		|| (!(entry->capability & WLAN_CAPABILITY_PRIVACY)
		&& (ieee80211->sec.auth_mode != WLAN_AUTH_OPEN)))
			return -EINVAL;
	}

	return 0;
}

/*
 * rt2x00_search_scan should be called with rt2x00_sem and ieee80211->lock held!.
 */
static struct ieee80211_network*
rt2x00_search_scan(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	struct ieee80211_network	*result = NULL;
	struct ieee80211_network	*entry = NULL;

	if(test_bit(DEVICE_SCANNING, &device->flags))
		return NULL;

	list_for_each_entry(entry, &core->ieee80211->network_list, list){
		if(!rt2x00_validate_scan_entry(core->ieee80211, &core->config, entry))
			if(!result || entry->stats.rssi > result->stats.rssi)
				result = entry;
	}

	return result;
}

/*
 * Configuration validation routines.
 * The validation functions must be called with the rt2x00_sem held.
 */
static int
rt2x00_validate_config_mode(struct _rt2x00_device *device, struct _rt2x00_config_request *config, u8 iw_mode)
{
	if(!config->adhoc_ofdm && iw_mode == IW_MODE_ADHOC && ieee80211_is_ofdm_rate(config->bitrate)){
		NOTICE("OFDM rates are not allowed on an adhoc network.\n");
		return -EINVAL;
	}

	return 0;
}

static int
rt2x00_validate_config_channel(struct _rt2x00_device *device, struct _rt2x00_config_request *config, u8 channel)
{
	if((!(config->network & IEEE_A) && rt2x00_is_52ghz_channel(channel))
	|| (config->network == IEEE_A && rt2x00_is_24ghz_channel(channel))){
		NOTICE("Channel not supported for current network type.\n");
		return -EINVAL;
	}

	if(rt2x00_is_52ghz_channel(channel) && ieee80211_is_cck_rate(config->bitrate)){
		NOTICE("CCK rates are not allowed on a 5.2GHz channel.\n");
		return -EINVAL;
	}

	if(channel == 14 && ieee80211_is_ofdm_rate(config->bitrate)){
		NOTICE("OFDM rates are not allowed on channel 14.\n");
		return -EINVAL;
	}

	return 0;
}

static int
rt2x00_validate_config_bitrate(struct _rt2x00_device *device, struct _rt2x00_config_request *config, u8 bitrate)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	u8				cck_rate = ieee80211_is_cck_rate(bitrate);
	u8				ofdm_rate = ieee80211_is_ofdm_rate(bitrate);
	u8				counter = 0x00;

	if(!(cck_rate ^ ofdm_rate)){
		NOTICE("Rate %d is not CCK and not OFDM.\n", bitrate);
		return -EINVAL;
	}

	if((!(config->network & IEEE_B) && cck_rate)
	|| (config->network == IEEE_B && ofdm_rate)){
		NOTICE("Rate not supported for current network type.\n");
		return -EINVAL;
	}

	if(rt2x00_is_52ghz_channel(config->channel) && cck_rate){
		NOTICE("CCK rates are not allowed on a 5.2GHz channel.\n");
		return -EINVAL;
	}

	if(config->channel == 14 && ofdm_rate){
		NOTICE("OFDM rates are not allowed on channel 14.\n");
		return -EINVAL;
	}


	if(!config->adhoc_ofdm && config->iw_mode == IW_MODE_ADHOC && ofdm_rate){
		NOTICE("OFDM rates are not allowed on an adhoc network.\n");
		return -EINVAL;
	}

	if(!core->network)
		return 0;

	for(counter = 0; counter < MAX_RATES_EX_LENGTH; counter++){
		if(counter < core->network->rates_len){
			if(bitrate == (core->network->rates[counter]^IEEE80211_BASIC_RATE_MASK))
				return 0;
		}
		if(counter < core->network->rates_ex_len){
			if(bitrate == (core->network->rates_ex[counter]^IEEE80211_BASIC_RATE_MASK))
				return 0;
		}
	}

	return -EINVAL;
}

static int
rt2x00_activate_config_network(struct _rt2x00_device *device, u8 network)
{
	struct _rt2x00_core		*core = rt2x00_core(device);

	spin_lock(&core->ieee80211->lock);

	core->ieee80211->mode = network;
	core->ieee80211->abg_true = network;

	if(network == IEEE_A){		/* 802.11a */
		core->ieee80211->freq_band &= ~IEEE80211_24GHZ_BAND;
		core->ieee80211->freq_band |= IEEE80211_52GHZ_BAND;
		core->ieee80211->modulation &= ~IEEE80211_CCK_MODULATION;
		core->ieee80211->modulation |= IEEE80211_OFDM_MODULATION;
	}else if(network & IEEE_A){	/* 802.11abg */
		core->ieee80211->freq_band |= IEEE80211_24GHZ_BAND;
		core->ieee80211->freq_band |= IEEE80211_52GHZ_BAND;
		core->ieee80211->modulation |= IEEE80211_CCK_MODULATION;
		core->ieee80211->modulation |= IEEE80211_OFDM_MODULATION;
	}else if(network & IEEE_G){	/* 802.11bg */
		core->ieee80211->freq_band |= IEEE80211_24GHZ_BAND;
		core->ieee80211->freq_band &= ~IEEE80211_52GHZ_BAND;
		core->ieee80211->modulation |= IEEE80211_CCK_MODULATION;
		core->ieee80211->modulation |= IEEE80211_OFDM_MODULATION;
	}else{				/* 802.11b */
		core->ieee80211->freq_band |= IEEE80211_24GHZ_BAND;
		core->ieee80211->freq_band &= ~IEEE80211_52GHZ_BAND;
		core->ieee80211->modulation |= IEEE80211_CCK_MODULATION;
		core->ieee80211->modulation &= ~IEEE80211_OFDM_MODULATION;
	}

	core->config.active.network = network;

	spin_unlock(&core->ieee80211->lock);

	return 0;
}

static int
rt2x00_activate_config_geography(struct _rt2x00_device *device, u8 geography)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	struct ieee80211_geo		*geo = NULL;
	u8				counter = 0x00;
	u8				channel = 0x00;
	u8				channel_max = 0x00;
	u8				a_mask = 0x00;
	u16				frequency = 0x0000;

	geo = kmalloc(sizeof(*geo), GFP_KERNEL);
	if(!geo)
		return -ENOMEM;

	memset(geo, 0x00, sizeof(geo));

	if(geography == IOCTL_GEOGRAPHY_USA){
		strcpy(geo->name, "US");
		channel = 1;
		channel_max = 11;
		a_mask = CHANNEL_UNII_LOW | CHANNEL_UNII_HIGH;
	}else if(geography == IOCTL_GEOGRAPHY_CANADA){
		strcpy(geo->name, "CA");
		channel = 1;
		channel_max = 11;
		a_mask = CHANNEL_UNII_LOW | CHANNEL_UNII_HIGH;
	}else if(geography == IOCTL_GEOGRAPHY_EUROPE){
		strcpy(geo->name, "EU");
		channel = 1;
		channel_max = 13;
		a_mask = CHANNEL_HIPERLAN2;
	}else if(geography == IOCTL_GEOGRAPHY_SPAIN){
		strcpy(geo->name, "ES");
		channel = 10;
		channel_max = 11;
		a_mask = CHANNEL_HIPERLAN2;
	}else if(geography == IOCTL_GEOGRAPHY_FRANCE){
		strcpy(geo->name, "FR");
		channel = 10;
		channel_max = 13;
		a_mask = CHANNEL_HIPERLAN2;
	}else if(geography == IOCTL_GEOGRAPHY_JAPAN){
		strcpy(geo->name, "JP");
		channel = 10;
		channel_max = 11;
	}else if(geography == IOCTL_GEOGRAPHY_JAPAN1){
		strcpy(geo->name, "JP1");
		channel = 1;
		channel_max = 13;
	}else if(geography == IOCTL_GEOGRAPHY_ISRAEL){
		strcpy(geo->name, "IL");
		channel = 3;
		channel_max = 9;
	}else if(geography == IOCTL_GEOGRAPHY_INVAL){
		strcpy(geo->name, "??");
		channel = 1;
		channel_max = 11;
	}

	frequency = 2412;
	for(counter = 0; channel <= channel_max; channel++){
		geo->bg[counter].channel = channel;
		geo->bg[counter].freq = frequency;
		frequency += 5;
		counter++;
	}

	if(geography == IOCTL_GEOGRAPHY_JAPAN){
		geo->bg_channels += 1;
		geo->bg[counter].channel = 14;
		geo->bg[counter].freq = 2484;
		counter++;
	}

	geo->bg_channels = counter;
	counter = 0;

	if(a_mask & CHANNEL_UNII_LOW){
		frequency = 5180;
		for(channel = CHANNEL_UNII_LOW_MIN; channel <= CHANNEL_UNII_LOW_MAX; channel += 4){
			geo->a[counter].channel = channel;
			geo->a[counter].freq = frequency;
			frequency += 20;
			counter++;
		}
		geo->a_channels = counter;
	}

	if(a_mask & CHANNEL_HIPERLAN2){
		frequency = 5500;
		for(channel = CHANNEL_HIPERLAN2_MIN; channel <= CHANNEL_HIPERLAN2_MAX; channel += 4){
			geo->a[counter].channel = channel;
			geo->a[counter].freq = frequency;
			frequency += 20;
			counter++;
		}
	}

	if(a_mask & CHANNEL_UNII_HIGH){
		frequency = 5745;
		for(channel = CHANNEL_UNII_HIGH_MIN; channel <= CHANNEL_UNII_HIGH_MAX; channel += 4){
			geo->a[counter].channel = channel;
			geo->a[counter].freq = frequency;
			frequency += 20;
			counter++;
		}
	}

	geo->a_channels = counter;

	spin_lock(&core->ieee80211->lock);
	ieee80211_set_geo(core->ieee80211, geo);
	spin_unlock(&core->ieee80211->lock);

	kfree(geo);

	return 0;
}

static void
rt2x00_activate_config(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	const struct ieee80211_geo	*geo = ieee80211_get_geo(core->ieee80211);
	u32				commit = 0x00000000;

	INFO("Activating configuration...\n");

	down_write(&device->rt2x00_sem);

	commit = core->config.user_commit;
	core->config.user_commit = 0;

	if(commit & COMMIT_NETWORK){
		if(!core->config.user.network){
			if(test_bit(DEVICE_CAP_802_11A, &device->flags))
				core->config.user.network |= IEEE_A;
			if(test_bit(DEVICE_CAP_802_11B, &device->flags))
				core->config.user.network |= IEEE_B;
			if(test_bit(DEVICE_CAP_802_11G, &device->flags))
				core->config.user.network |= IEEE_G;
		}
		if(rt2x00_activate_config_network(device, core->config.user.network)){
			core->config.user_commit |= COMMIT_NETWORK;
		}else{
			core->config.active.network = core->config.user.network;
			core->config.user_commit |= COMMIT_BITRATE | COMMIT_CHANNEL;
		}
	}

	if(commit & COMMIT_GEOGRAPHY){
		if(core->config.user.geography >= IOCTL_GEOGRAPHY_INVAL)
			core->config.user.geography = IOCTL_GEOGRAPHY_INVAL;
		if(rt2x00_activate_config_geography(device, core->config.user.geography)){
			core->config.user_commit |= COMMIT_GEOGRAPHY;
		}else{
			core->config.active.geography = core->config.user.geography;
			core->config.user_commit |= COMMIT_CHANNEL;
		}
	}

	if(commit & COMMIT_ADHOC_OFDM){
		core->config.active.adhoc_ofdm = core->config.user.adhoc_ofdm;
	}

	if(commit & COMMIT_MODE){
		if(rt2x00_validate_config_mode(device, &core->config.active, core->config.user.iw_mode)) {
			core->config.user.bitrate = IEEE80211_CCK_RATE_11MB;
			core->config.user_commit |= COMMIT_BITRATE;    
		}
		core->config.active.iw_mode = core->config.user.iw_mode;
	}

	if(commit & COMMIT_CHANNEL){
		if(!core->config.user.channel){
			if(core->config.active.network & IEEE_B)
				core->config.user.channel = geo->bg[0].channel;
			else
				core->config.user.channel = geo->a[0].channel;
		}

		if(!rt2x00_validate_config_channel(device, &core->config.active, core->config.user.channel)
		|| ieee80211_is_valid_channel(core->ieee80211, core->config.user.channel))
			core->config.active.channel = core->config.user.channel;
		else if(core->config.active.network & IEEE_B)
			core->config.active.channel = geo->bg[0].channel;
		else
			core->config.active.channel = geo->a[0].channel;
		if(rt2x00_is_52ghz_channel(core->config.active.channel))
			core->config.slot_time = 9;
		else
			core->config.slot_time = 20;
		core->config.update_flags |= UPDATE_CHANNEL | UPDATE_DURATION;
	}

	if(commit & COMMIT_BITRATE){
		if(!core->config.user.bitrate){
			if(core->config.active.network & IEEE_G)
				core->config.user.bitrate = IEEE80211_OFDM_RATE_54MB;
			else
				core->config.user.bitrate = IEEE80211_CCK_RATE_11MB;
		}

		if(!rt2x00_validate_config_bitrate(device, &core->config.active, core->config.user.bitrate))
			core->config.active.bitrate = core->config.user.bitrate;
		else if(core->config.active.network & IEEE_B)
			core->config.active.bitrate = IEEE80211_CCK_RATE_11MB;
		else
			core->config.active.bitrate = IEEE80211_OFDM_RATE_54MB;
		core->config.update_flags |= UPDATE_BITRATE;
	}

	if(commit & COMMIT_ESSID){
		if(core->config.user.flags & CONFIG_FIX_ESSID)
			memcpy(&core->config.active.essid, &core->config.user.essid, sizeof(core->config.active.essid));
	}

	if(commit & COMMIT_BSSID){
		if(core->config.user.flags & CONFIG_FIX_BSSID)
			memcpy(&core->config.active.bssid, &core->config.user.bssid, sizeof(core->config.active.bssid));
		core->config.update_flags |= UPDATE_BSSID;
	}

	if(commit & COMMIT_RETRY){
		core->config.active.long_retry = core->config.user.long_retry;
		core->config.active.short_retry = core->config.user.short_retry;
		core->config.update_flags |= UPDATE_RETRY;
	}

	if(commit & COMMIT_TXPOWER){
		core->config.active.txpower = core->config.user.txpower;
		core->config.update_flags |= UPDATE_TXPOWER;
	}

	if(commit & COMMIT_PREAMBLE){
		core->config.update_flags |= UPDATE_PREAMBLE;
	}

	if(commit & COMMIT_ANTENNA){
		core->config.active.antenna_flags = core->config.user.antenna_flags;
		core->config.update_flags |= UPDATE_ANTENNA;
	}

	if(commit & COMMIT_SENSITIVITY){
		core->config.active.sensitivity = core->config.user.sensitivity;
		core->config.update_flags |= UPDATE_SENSITIVITY;
	}

	if(commit & COMMIT_RTS_THRESHOLD){
		core->config.active.rts_threshold = core->config.user.rts_threshold;
		spin_lock(&core->ieee80211->lock);
		core->ieee80211->rts = core->config.active.rts_threshold;
		spin_unlock(&core->ieee80211->lock);
	}

	if(commit & COMMIT_FRAGMENTATION){
		core->config.active.fragmentation = core->config.user.fragmentation;
		spin_lock(&core->ieee80211->lock);
		core->ieee80211->fts = core->config.active.fragmentation;
		spin_unlock(&core->ieee80211->lock);
	}

	if(commit & COMMIT_PACKET_FILTER){
		core->config.update_flags |= UPDATE_PACKET_FILTER;
	}

	if(commit & COMMIT_AUTHENTICATION){
		core->config.active.wpa_version |= core->config.user.wpa_version;
	}

	core->config.active.flags = core->config.user.flags;

	up_write(&device->rt2x00_sem);
}

/*
 * Link up/down routines.
 */
#define LINK_TIME			( HZ )

static void
rt2x00_link_up_config(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	s8				counter = 0x00;
	u8				rate = 0x00;
	u8				bitrate_min = 0x00;
	u8				bitrate_max = 0x00;

	down_write(&device->rt2x00_sem);

	bitrate_min = (core->config.active.network & IEEE_B) ? 0 : 4;
	bitrate_max = (core->config.active.network == IEEE_B) ? 4 : 12;

	if(core->config.active.iw_mode == IW_MODE_MONITOR){
		memset(&core->config.active.essid, '\0', sizeof(core->config.active.essid));
		memset(&core->config.active.bssid, 0x00, sizeof(core->config.active.bssid));
		core->config.active.channel = core->config.user.channel;
		core->config.update_flags |= UPDATE_BSSID | UPDATE_CHANNEL;
		up_write(&device->rt2x00_sem);
		return;
	}

	if(!core->network){
		up_write(&device->rt2x00_sem);
		return;
	}

	if(!ieee80211_is_empty_essid(&core->network->ssid[0], core->network->ssid_len))
		memcpy(&core->config.active.essid, &core->network->ssid, core->network->ssid_len);
	else 
		memcpy(&core->config.active.essid, "<hidden>", sizeof("<hidden>"));

	memcpy(&core->config.active.bssid, &core->network->bssid, sizeof(core->config.active.bssid));

	core->config.active.channel = core->network->channel;

	if(rt2x00_is_52ghz_channel(core->config.active.channel))
		core->config.slot_time = 9;
	else
		core->config.slot_time = 20;

	for(counter = (bitrate_max - 1); counter >= bitrate_min; counter--){
		rate = capabilities.bitrate[counter];
		if(rate <= core->config.user.bitrate
		&& !rt2x00_validate_config_bitrate(device, &core->config.active, rate)){
			core->config.active.bitrate = rate;
			break;
		}
	}

	core->config.update_flags |= UPDATE_BSSID | UPDATE_CHANNEL | UPDATE_DURATION;

	up_write(&device->rt2x00_sem);
}

static void
rt2x00_link_down_config(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);

	down_write(&device->rt2x00_sem);

	if(!(core->config.active.flags & CONFIG_FIX_ESSID))
		memset(&core->config.active.essid, '\0', sizeof(core->config.active.essid));

	if(!(core->config.active.flags & CONFIG_FIX_BSSID))
		memset(&core->config.active.bssid, 0x00, sizeof(core->config.active.bssid));

	up_write(&device->rt2x00_sem);
}

static void
rt2x00_link_periodic_config(struct _rt2x00_device *device)
{
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			status = 0x00;

	down_write(&device->rt2x00_sem);

	if(device->net_dev->flags & IFF_PROMISC){
		if(!(core->config.user.flags & CONFIG_ACCEPT_PROMISC))
			core->config.user_commit |= COMMIT_PACKET_FILTER;
		core->config.user.flags |= CONFIG_ACCEPT_PROMISC;
	}else{
		if(core->config.user.flags & CONFIG_ACCEPT_PROMISC)
			core->config.user_commit |= COMMIT_PACKET_FILTER;
		core->config.user.flags &= ~CONFIG_ACCEPT_PROMISC;
	}

	status = core->config.user_commit != 0;

	device->handler->dev_update_stats(device, &core->rt2x00_stats);

	up_write(&device->rt2x00_sem);

	if(status)
		rt2x00_activate_config(device);
}

static int
rt2x00_connect(struct _rt2x00_device *device, struct ieee80211_network *network, u8 mode)
{
	struct _rt2x00_core		*core = rt2x00_core(device);

	if(network){
		core->network = kmalloc(sizeof(struct ieee80211_network), GFP_KERNEL);
		if(!core->network){
			ERROR("could not allocate ieee80211 struct.\n");
			return -ENOMEM;
		}
		memcpy(core->network, network, sizeof(*network));
	}

	down_write(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	core->ieee80211->iw_mode = mode;
	core->config.active.iw_mode = mode;

	if(core->network)
		memcpy(&core->ieee80211->bssid, &core->network->bssid, sizeof(core->network->bssid));
	else
		core->connection_status = CONNECTION_ESTABLISHED;

	spin_unlock(&core->ieee80211->lock);
	up_write(&device->rt2x00_sem);

	rt2x00_link_up_config(device);
	rt2x00_link_periodic_config(device);

	rt2x00_update_config(device);

	if(core->network)
		rt2x00_mgmt_snd_auth(device, CONNECTION_TO_NODE, &core->network->bssid[0], WLAN_STATUS_SUCCESS);

	if(mode == IW_MODE_MONITOR)
		rt2x00_start_connection(device);

	return 0;
}

static void
rt2x00_disconnect(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	enum ieee80211_state		state = IEEE80211_UNINITIALIZED;

	down_write(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	/*
	 * Stop net interface tx /rx.
	 */
	netif_stop_queue(device->net_dev);
	netif_carrier_off(device->net_dev);

	/*
	 * Reset working mode.
	 */
	core->ieee80211->iw_mode = 0;
	core->config.active.iw_mode = core->config.user.iw_mode;

	memset(&core->ieee80211->bssid, 0x00, sizeof(core->ieee80211->bssid));
	state = core->ieee80211->state;

	core->config.led_status = 0;

	core->config.update_flags |= UPDATE_LED_STATUS;

	spin_unlock(&core->ieee80211->lock);
	up_write(&device->rt2x00_sem);

	if(core->network){
		if(state == IEEE80211_ASSOCIATED)
			rt2x00_mgmt_snd_disassoc(device, &core->network->bssid[0], WLAN_REASON_DISASSOC_STA_HAS_LEFT);
		else if(state == IEEE80211_AUTHENTICATED)
			rt2x00_mgmt_snd_deauth(device, &core->network->bssid[0], WLAN_REASON_DEAUTH_LEAVING);
		kfree(core->network);
		core->network = NULL;
	}

	rt2x00_link_down_config(device);

	rt2x00_update_config(device);

	rt2x00_wireless_event(device, SIOCGIWAP);
}

static void
rt2x00_link_up(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);
	u8				mode = 0x00;
	u8				channel_scan = 0x00;

	NOTICE("Link up.\n");

	down_read(&device->rt2x00_sem);
	mode = core->config.active.iw_mode;
	channel_scan = (core->config.active.flags & CONFIG_FIX_CHANNEL) ? IW_SCAN_THIS_FREQ : IW_SCAN_DEFAULT;
	up_read(&device->rt2x00_sem);

	if(mode == IW_MODE_AUTO || mode == IW_MODE_ADHOC || mode == IW_MODE_INFRA){
		rt2x00_start_scan(device, NULL, channel_scan);
	}else if(mode == IW_MODE_MONITOR){
		NOTICE("Enabling monitor mode.\n");

		down_write(&device->rt2x00_sem);
		device->net_dev->type = ARPHRD_IEEE80211;
		dev_set_promiscuity(device->net_dev, 1);
		up_write(&device->rt2x00_sem);

		rt2x00_connect(device, NULL, IW_MODE_MONITOR);
	}

	queue_delayed_work(core->workqueue, &core->link_tuner, LINK_TIME);
}

static void
rt2x00_link_down(struct _rt2x00_device *device)
{
	struct _rt2x00_core		*core = rt2x00_core(device);

	cancel_delayed_work(&core->link_tuner);

	down_read(&device->rt2x00_sem);

	if(core->config.active.iw_mode == IW_MODE_MONITOR){
		device->net_dev->type = ARPHRD_ETHER;
		dev_set_promiscuity(device->net_dev, -1);
	}

	up_write(&device->rt2x00_sem);

	rt2x00_disconnect(device);

	NOTICE("Link down.\n");
}

static void
rt2x00_link_periodic(void *data)
{
	struct _rt2x00_device		*device = data;
	struct _rt2x00_core		*core = rt2x00_core(device);
	struct ieee80211_network	*network = NULL;
	int				status = 0x00000000;
	u8				channel_scan = 0x00;

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(test_bit(DEVICE_SCANNING, &device->flags))
		goto exit;

	down_read(&device->rt2x00_sem);

	if(core->config.active.iw_mode == IW_MODE_MONITOR){
		up_read(&device->rt2x00_sem);
		rt2x00_link_periodic_config(device);
		rt2x00_update_config(device);
		goto exit;
	}

	channel_scan = (core->config.active.flags & CONFIG_FIX_CHANNEL) ? IW_SCAN_THIS_FREQ : IW_SCAN_DEFAULT;

	if(CONNECTED(core)){
		up_read(&device->rt2x00_sem);
		rt2x00_link_periodic_config(device);
		rt2x00_update_config(device);
		goto exit;
	}else if(!core->network){
		spin_lock(&core->ieee80211->lock);
		network = rt2x00_search_scan(device);
		spin_unlock(&core->ieee80211->lock);

		up_read(&device->rt2x00_sem);

		if(!network
		&& (core->config.active.iw_mode == IW_MODE_AUTO
		|| core->config.active.iw_mode == IW_MODE_ADHOC))
			rt2x00_connect(device, NULL, IW_MODE_ADHOC);
		else if(!network && core->config.active.iw_mode == IW_MODE_INFRA)
			rt2x00_start_scan(device, NULL, channel_scan);
		else if(network && network->capability & WLAN_CAPABILITY_ESS)
			rt2x00_connect(device, network, IW_MODE_INFRA);
		else if(network && network->capability & WLAN_CAPABILITY_IBSS)
			rt2x00_connect(device, network, IW_MODE_ADHOC);
		goto exit;
	}else{
		spin_lock(&core->ieee80211->lock);
		status = rt2x00_validate_scan_entry(core->ieee80211, &core->config, core->network);
		spin_unlock(&core->ieee80211->lock);

		if(status){
			up_read(&device->rt2x00_sem);
			NOTICE("Beacon lost, rescanning.\n");
			rt2x00_disconnect(device);
			rt2x00_start_scan(device, NULL, channel_scan);
			goto exit;
		}

		status = rt2x00_connection_status(core);
		if(status == -EAGAIN && AUTHENTICATING(core)){
			up_read(&device->rt2x00_sem);
			if(HANDSHAKING(core))
				rt2x00_mgmt_snd_auth_shake(device, &core->network->bssid[0], WLAN_STATUS_SUCCESS);
			else
				rt2x00_mgmt_snd_auth(device, CONNECTION_TO_NODE, &core->network->bssid[0], WLAN_STATUS_SUCCESS);
		}else if(status == -EAGAIN && ASSOCIATING(core)){
			up_read(&device->rt2x00_sem);
			rt2x00_mgmt_snd_assoc(device, &core->network->bssid[0]);
		}else{
			up_read(&device->rt2x00_sem);
			NOTICE("Connection attempt failed, rescanning.\n");
			rt2x00_disconnect(device);
			rt2x00_start_scan(device, NULL, channel_scan);
		}
		goto exit;
	}

	up_read(&device->rt2x00_sem);

exit:
	queue_delayed_work(core->workqueue, &core->link_tuner, LINK_TIME);
}

/*
 * Radio control.
 */
static int
rt2x00_radio_on(struct _rt2x00_device *device)
{
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = 0x00000000;

	if(test_bit(DEVICE_RADIO_ON, &device->flags)){
		WARNING("Radio already on.\n");
		return -ENOTCONN;
	}

	if(!try_module_get(device->handler->dev_module)){
		ERROR("failure to acquire module.\n");
		return -ENODEV;
	}

	rt2x00_enable_ring(&core->rx);
	rt2x00_enable_ring(&core->tx);
	rt2x00_enable_ring(&core->atim);
	rt2x00_enable_ring(&core->prio);
	rt2x00_enable_ring(&core->beacon);

	status = device->handler->dev_radio_on(device);
	if(status){
		module_put(device->handler->dev_module);
		return status;
	}

	set_bit(DEVICE_RADIO_ON, &device->flags);

	return 0;
}

static int
rt2x00_radio_off(struct _rt2x00_device *device)
{
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(!test_and_clear_bit(DEVICE_RADIO_ON, &device->flags)){
		WARNING("Radio already off.\n");
		return -ENOTCONN;
	}

	/*
	 * Shut down all rings.
	 */
	rt2x00_disable_ring(&core->rx);
	rt2x00_disable_ring(&core->tx);
	rt2x00_disable_ring(&core->atim);
	rt2x00_disable_ring(&core->prio);
	rt2x00_disable_ring(&core->beacon);

	/*
	 * Halt all periodic handlers.
	 */
	rt2x00_stop_scan(device);
	rt2x00_link_down(device);

	/*
	 * Wait untill all running tasks have been halted.
	 */
	flush_workqueue(core->workqueue);

	/*
	 * Deactivate device.
	 */
	device->handler->dev_radio_off(device);

	module_put(device->handler->dev_module);

	return 0;
}

/*
 * IOCTL routines.
 */
static int
rt2x00_ioctl_commit(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = 0x00000000;
	u8			commit = 0x00;
	u8			mode = 0x00;

	down_read(&device->rt2x00_sem);
	commit = core->config.user_commit;
	mode = core->config.active.iw_mode;
	up_read(&device->rt2x00_sem);

	if(test_bit(DEVICE_RADIO_ON, &device->flags) && commit & COMMIT_RESET_REQUIRED && mode != IW_MODE_MONITOR){
		INFO("SIOCSIWCOMMIT: Connection will be reset.\n");
		rt2x00_radio_off(device);
		status = rt2x00_radio_on(device);
		if(status)
			return status;
		rt2x00_activate_config(device);
		rt2x00_link_up(device);
	}else{
		INFO("SIOCSIWCOMMIT: Pending configuration will be loaded.\n");
		rt2x00_activate_config(device);
		rt2x00_update_config(device);
	}

	return 0;
}

static int
rt2x00_ioctl_get_name(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	char 			*ieee80211_modes[] = {"?", "a", "b", "ab", "g", "ag", "bg", "abg"};

	down_read(&device->rt2x00_sem);

	snprintf(wrqu->name, sizeof(wrqu->name), "IEEE 802.11%s", ieee80211_modes[core->config.active.network]);

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_frequency(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u16			channel = 0x00;

	if((wrqu->freq.m >= 0) && (wrqu->freq.m <= 1000))
		channel = wrqu->freq.m;
	else
		channel = rt2x00_freq_to_channel(wrqu->freq.m / 100000);

	down_write(&device->rt2x00_sem);

	if(!channel || rt2x00_validate_config_channel(device, &core->config.user, channel)){
		up_write(&device->rt2x00_sem);
		return -EINVAL;
	}

	core->config.user.channel = channel;

	if(wrqu->freq.flags == IW_FREQ_FIXED)
		core->config.user.flags |= CONFIG_FIX_CHANNEL;
	else
		core->config.user.flags &= ~CONFIG_FIX_CHANNEL;

	core->config.user_commit |= COMMIT_CHANNEL;

	up_write(&device->rt2x00_sem);

	INFO("SIOCSIWFREQ: Channel = %d.\n", channel);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_frequency(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			channel = 0x00;

	down_read(&device->rt2x00_sem);

	if(test_bit(DEVICE_SCANNING, &device->flags))
		channel = core->config.user.channel;
	else
		channel = core->config.active.channel;

	up_read(&device->rt2x00_sem);

	wrqu->freq.m = rt2x00_channel_to_freq(channel) * 100000;
	wrqu->freq.e = 1;
	wrqu->freq.i = channel;
	wrqu->freq.flags = (core->config.active.flags == CONFIG_FIX_CHANNEL) ? IW_FREQ_FIXED : IW_FREQ_AUTO;

	return 0;
}

static int 
rt2x00_ioctl_set_mode(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(wrqu->mode == IW_MODE_REPEAT
	|| wrqu->mode == IW_MODE_MASTER
	|| wrqu->mode == IW_MODE_SECOND)
		return -ENOTSUPP;

	down_write(&device->rt2x00_sem);

	core->config.user.iw_mode = wrqu->mode;
	core->config.user_commit |= COMMIT_MODE;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_mode(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	if(core->config.active.iw_mode)
		wrqu->mode = core->config.active.iw_mode;
	else
		wrqu->mode = core->config.user.iw_mode;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_sens(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_write(&device->rt2x00_sem);

	if(wrqu->sens.value < 0)	/* dBm. */
		core->config.user.sensitivity = wrqu->sens.value + 120;
	else				/* RSSI. */
		core->config.user.sensitivity = wrqu->sens.value;

	core->config.user_commit |= COMMIT_SENSITIVITY;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_sens(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->sens.value = core->config.active.sensitivity;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_get_range(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device		*device = ieee80211_priv(net_dev);
	struct _rt2x00_core		*core = rt2x00_core(device);
	struct iw_range		*range = (struct iw_range *)extra;
	const struct ieee80211_geo	*geo = ieee80211_get_geo(core->ieee80211);
	u8				bitrate_min = 0x00;
	u8				bitrate_max = 0x00;
	u8				network = 0x00;
	u8				counter = 0x00;

	memset(range, 0x00, sizeof(*range));

	down_read(&device->rt2x00_sem);
	bitrate_min = (core->config.active.network & IEEE_B) ? 0 : 4;
	bitrate_max = (core->config.active.network == IEEE_B) ? 4 : 12;
	network = core->config.active.network;
	up_read(&device->rt2x00_sem);

	range->throughput = capabilities.bitrate[bitrate_max - 1] * 500000;

	IW_EVENT_CAPA_SET_KERNEL(range->event_capa);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWSCAN);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWAP);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWSPY);
	IW_EVENT_CAPA_SET(range->event_capa, SIOCGIWTHRSPY);

	range->num_bitrates = bitrate_max;
	for(counter = 0x00; counter < bitrate_max; counter++)
		range->bitrate[counter] = capabilities.bitrate[counter] * 500000;

	range->min_rts = 0;
	range->max_rts = MAX_FRAG_THRESHOLD;

	range->min_frag = MIN_FRAG_THRESHOLD;
	range->max_frag = MAX_FRAG_THRESHOLD;

	range->encoding_size[0] = 5;	/* 64bit WEP. */
	range->encoding_size[1] = 13;	/* 128bit WEP. */
	range->num_encoding_sizes = 2;
	range->max_encoding_tokens = 4;

	range->txpower_capa = IW_TXPOW_RELATIVE;
	range->num_txpower = ARRAY_SIZE(capabilities.txpower);
	for(counter = 0x00; counter < range->num_txpower; counter++)
		range->txpower[counter] = capabilities.txpower[counter];

	range->we_version_compiled = WIRELESS_EXT;
	range->we_version_source = 18;

	range->retry_capa = IW_RETRY_LIMIT;
	range->retry_flags = IW_RETRY_LIMIT | IW_RETRY_MIN | IW_RETRY_MAX;
	range->min_retry = 0;
	range->max_retry = 255;

	spin_lock(&core->ieee80211->lock);

	range->num_channels = 0;
	if((network & IEEE_B))
		range->num_channels += geo->bg_channels;
	if(network & IEEE_A)
		range->num_channels += geo->a_channels;

	if(range->num_channels > IW_MAX_FREQUENCIES)
		range->num_channels = IW_MAX_FREQUENCIES;

	range->num_frequency = range->num_channels;

	for(counter = 0x00; counter < range->num_frequency; counter++) {
		if((network & IEEE_B) && counter < geo->bg_channels){
			range->freq[counter].i = geo->bg[counter].channel;
			range->freq[counter].m = geo->bg[counter].freq * 100000;
			range->freq[counter].e = 1;
		}else if((network & IEEE_A) && (counter - geo->bg_channels) < geo->a_channels){
			range->freq[counter].i = geo->a[counter - geo->bg_channels].channel;
			range->freq[counter].m = geo->a[counter - geo->bg_channels].freq * 100000;
			range->freq[counter].e = 1;
		}
	}

	spin_unlock(&core->ieee80211->lock);

	range->enc_capa = IW_ENC_CAPA_WPA | IW_ENC_CAPA_WPA2 | IW_ENC_CAPA_CIPHER_TKIP | IW_ENC_CAPA_CIPHER_CCMP;

	wrqu->data.length = sizeof(struct iw_range);

	return 0;
}

static int
rt2x00_ioctl_set_wap(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(wrqu->ap_addr.sa_family != ARPHRD_ETHER)
		return -EINVAL;

	down_write(&device->rt2x00_sem);

	/*
	 * When the address is not valid, because it is, for example, a broadcast address,
	 * we must set the essid to 'any' instead.
	 */
	if(is_valid_ether_addr(&wrqu->ap_addr.sa_data[0])){
		memcpy(&core->config.user.bssid, &wrqu->ap_addr.sa_data, ETH_ALEN);

		core->config.user_commit |= COMMIT_BSSID;
		core->config.user.flags |= CONFIG_FIX_BSSID;
	} else {
		core->config.user_commit |= COMMIT_BSSID;
		core->config.user.flags &= ~CONFIG_FIX_BSSID;
	}

	INFO("SIOCSIWAP: Bssid = " MAC_FMT ".\n", MAC_ARG(core->config.user.bssid));

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_wap(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->ap_addr.sa_family = ARPHRD_ETHER;

	if(CONNECTED(core)
	&& (core->config.active.iw_mode == IW_MODE_ADHOC
	|| core->config.active.iw_mode == IW_MODE_INFRA))
		memcpy(&wrqu->ap_addr.sa_data, &core->config.active.bssid, sizeof(wrqu->ap_addr.sa_data));
	else
		memset(&wrqu->ap_addr.sa_data, 0x00, sizeof(wrqu->ap_addr.sa_data));

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_mlme(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct iw_mlme		*mlme = (struct iw_mlme*)wrqu->data.pointer;

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return -ENOTCONN;

	if(mlme->cmd == IW_MLME_DEAUTH)
		rt2x00_mgmt_snd_deauth(device, &mlme->addr.sa_data[0], mlme->reason_code);
	if(mlme->cmd == IW_MLME_DISASSOC)
		rt2x00_mgmt_snd_disassoc(device, &mlme->addr.sa_data[0], mlme->reason_code);

	return 0;
}

static int
rt2x00_ioctl_set_scan(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device		*device = rt2x00_device(net_dev);
	int				status = 0x00000000;

	if(test_bit(DEVICE_SCANNING, &device->flags)){
		NOTICE("Device already busy scanning, aborting current scan...\n");
		rt2x00_stop_scan(device);
	}

	if(!test_bit(DEVICE_RADIO_ON, &device->flags)){
		status = rt2x00_radio_on(device);
		if(status)
			return status;
		rt2x00_activate_config(device);
	}

	if(wrqu->param.flags)
		rt2x00_start_scan(device, (struct iw_scan_req*)extra, wrqu->param.flags);
	else
		rt2x00_start_scan(device, NULL, IW_SCAN_DEFAULT);

	return 0;
}

static int
rt2x00_ioctl_get_scan(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device		*device = rt2x00_device(net_dev);
	struct _rt2x00_core		*core = rt2x00_core(device);

	if(down_interruptible(&core->scan_sem))
		return -EINTR;
	up(&core->scan_sem);

	return ieee80211_wx_get_scan(core->ieee80211, info, wrqu, extra);
}

static int
rt2x00_ioctl_set_essid(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_write(&device->rt2x00_sem);

	if(wrqu->essid.flags){
		if(wrqu->essid.length > IW_ESSID_MAX_SIZE) {
			up_write(&device->rt2x00_sem);
			return -E2BIG;
		}

		if(wrqu->essid.length > 0){
			memcpy(&core->config.user.essid, extra, wrqu->essid.length);
			memset(&core->config.user.essid[wrqu->essid.length], '\0', IW_ESSID_MAX_SIZE - wrqu->essid.length);
		}

		core->config.user.flags |= CONFIG_FIX_ESSID;
	}else
		core->config.user.flags &= ~CONFIG_FIX_ESSID;

	core->config.user_commit |= COMMIT_ESSID;

	up_write(&device->rt2x00_sem);

	if (wrqu->essid.flags){
		INFO("SIOCSIWESSID: Essid = %s length = %d.\n", extra, wrqu->essid.length);}
	else{
		INFO("SIOCSIWESSID: Essid = ANY\n");}

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_essid(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->essid.length = strnlen(core->config.active.essid, IW_ESSID_MAX_SIZE);

	if(wrqu->essid.length){
		memcpy(extra, &core->config.active.essid, wrqu->essid.length);
		wrqu->essid.flags = 1;
	}else
		wrqu->essid.flags = 0;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_nickname(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if (wrqu->data.length > IW_ESSID_MAX_SIZE)
		return -E2BIG;

	down_write(&device->rt2x00_sem);

	memcpy(&core->config.nickn, extra, wrqu->data.length);
	memset(&core->config.nickn[wrqu->data.length], '\0', IW_ESSID_MAX_SIZE - wrqu->data.length);

	up_write(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_get_nickname(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->data.length = strnlen(core->config.nickn, IW_ESSID_MAX_SIZE);
	memcpy(extra, &core->config.nickn, wrqu->data.length);

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_bitrate(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			rate = wrqu->bitrate.value / 500000;

	down_write(&device->rt2x00_sem);

	if(wrqu->bitrate.value == -1)
		rate = 0;
	else{
		if(rt2x00_validate_config_bitrate(device, &core->config.user, rate)){
			up_write(&device->rt2x00_sem);
			return -EINVAL;
		}
	}

	core->config.user.bitrate = rate;

	if(wrqu->bitrate.fixed)
		core->config.user.flags |= CONFIG_FIX_BITRATE;
	else
		core->config.user.flags &= ~CONFIG_FIX_BITRATE;

	core->config.user_commit |= COMMIT_BITRATE;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_bitrate(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->bitrate.value = core->config.active.bitrate * 500000;
	wrqu->bitrate.fixed = core->config.active.flags & CONFIG_FIX_BITRATE;
	wrqu->bitrate.disabled = 0;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_rts_threshold(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(wrqu->rts.value != -1 && wrqu->rts.value > MAX_FRAG_THRESHOLD)
		return -EINVAL;

	down_write(&device->rt2x00_sem);

	if(wrqu->rts.disabled){
		core->config.user.flags &= ~CONFIG_ENABLED_RTS;
		core->config.user.rts_threshold = MAX_FRAG_THRESHOLD;
	}else{
		core->config.user.flags |= CONFIG_ENABLED_RTS;
		core->config.user.rts_threshold = wrqu->rts.value;
	}

	if(wrqu->rts.fixed)
		core->config.user.flags |= CONFIG_FIX_RTS;
	else
		core->config.user.flags &= ~CONFIG_FIX_RTS;

	core->config.user_commit |= COMMIT_RTS_THRESHOLD;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_rts_threshold(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->rts.value = core->config.active.rts_threshold;
	wrqu->rts.disabled = !(core->config.active.flags & CONFIG_ENABLED_RTS);
	wrqu->rts.fixed = core->config.active.flags & CONFIG_FIX_RTS;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_fragmentation(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(wrqu->frag.value != -1
	&& (MIN_FRAG_THRESHOLD > wrqu->frag.value || wrqu->frag.value > MAX_FRAG_THRESHOLD))
		return -EINVAL;

	down_write(&device->rt2x00_sem);

	if(wrqu->frag.disabled){
		core->config.user.flags &= ~CONFIG_ENABLED_FRAG;
		core->config.user.fragmentation = MAX_FRAG_THRESHOLD;
	}else{
		core->config.user.flags |= CONFIG_ENABLED_FRAG;
		core->config.user.fragmentation = wrqu->frag.value;
	}

	if(wrqu->frag.fixed)
		core->config.user.flags |= CONFIG_FIX_FRAG;
	else
		core->config.user.flags &= ~CONFIG_FIX_FRAG;

	core->config.user_commit |= COMMIT_FRAGMENTATION;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_fragmentation(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->frag.value = core->config.active.fragmentation;
	wrqu->frag.disabled = !(core->config.active.flags & CONFIG_ENABLED_FRAG);
	wrqu->frag.fixed = core->config.active.flags & CONFIG_FIX_FRAG;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_txpower(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = 0x00000000;
	u8			txpower = 0x00;
	u8			counter = 0x00;
	u8			max = 0x00;

	if(test_bit(DEVICE_ENABLED, &device->flags)
	&& test_bit(DEVICE_RADIO_ON, &device->flags)
	&& (wrqu->txpower.disabled || wrqu->txpower.value == 0)){
		INFO("SIOCSIWTXPOW: Radio off.\n");
		return rt2x00_radio_off(device);
	}

	if(wrqu->txpower.flags & IW_TXPOW_DBM
	|| wrqu->txpower.flags & IW_TXPOW_MWATT)
		return -ENOTSUPP;

	max = ARRAY_SIZE(capabilities.txpower);

	for(; counter < max; counter++){
		txpower = capabilities.txpower[counter];
		if(txpower >= wrqu->txpower.value)
			break;
	}

	down_write(&device->rt2x00_sem);

	core->config.user.txpower = txpower;

	if(wrqu->txpower.fixed)
		core->config.user.flags |= CONFIG_FIX_TXPOWER;
	else
		core->config.user.flags &= ~CONFIG_FIX_TXPOWER;

	core->config.user_commit |= COMMIT_TXPOWER;

	up_write(&device->rt2x00_sem);

	if(test_bit(DEVICE_ENABLED, &device->flags)
	&& !test_bit(DEVICE_RADIO_ON, &device->flags)){
		INFO("SIOCSIWTXPOW: Radio on.\n");
		status = rt2x00_radio_on(device);
		if(status)
			return status;
		rt2x00_activate_config(device);
		rt2x00_link_up(device);
		return 0;
	}

	INFO("SIOCSIWTXPOW: Tx power = %d%s.\n", txpower, "%");

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_txpower(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu, 
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	wrqu->txpower.value = core->config.active.txpower;
	wrqu->txpower.disabled = !test_bit(DEVICE_RADIO_ON, &device->flags);
	wrqu->txpower.fixed = core->config.active.flags & CONFIG_FIX_TXPOWER;
	wrqu->txpower.flags |= IW_TXPOW_RELATIVE;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_retry(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(!(wrqu->retry.flags & IW_RETRY_LIMIT))
		return -ENOTSUPP;

	down_write(&device->rt2x00_sem);

	if(wrqu->retry.flags & IW_RETRY_MAX){
		core->config.user.long_retry = wrqu->retry.value;
		core->config.user.flags |= CONFIG_ENABLED_LONG_RETRY;
	}else if(wrqu->retry.flags & IW_RETRY_MIN){
		core->config.user.short_retry = wrqu->retry.value;
		core->config.user.flags &= ~CONFIG_ENABLED_LONG_RETRY;
	}else{
		core->config.user.short_retry = wrqu->retry.value;
		core->config.user.long_retry = wrqu->retry.value;
		core->config.user.flags |= CONFIG_ENABLED_LONG_RETRY;
	}

	core->config.user_commit |= COMMIT_RETRY;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_retry(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(!(wrqu->retry.flags & IW_RETRY_LIMIT))
		return -ENOTSUPP;

	down_read(&device->rt2x00_sem);

	if(wrqu->retry.flags & IW_RETRY_MAX)
		wrqu->retry.value = core->config.active.long_retry;
	else if(wrqu->retry.flags & IW_RETRY_MIN)
		wrqu->retry.value = core->config.active.short_retry;
	else if(core->config.active.flags & CONFIG_ENABLED_LONG_RETRY){
		wrqu->retry.value = core->config.active.long_retry;
		wrqu->retry.flags |= IW_RETRY_MAX;
	}else{
		wrqu->retry.value = core->config.active.short_retry;
		wrqu->retry.flags |= IW_RETRY_MIN;
	}

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_encode(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	int			status = 0x00000000;

	status = ieee80211_wx_set_encode(netdev_priv(net_dev), info, wrqu, extra);
	if(status)
		return status;

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_encode(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	return ieee80211_wx_get_encode(netdev_priv(net_dev), info, wrqu, extra);
}

static int
rt2x00_ioctl_set_genie(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	void			*data = NULL;

	if(wrqu->data.length > MAX_WPA_IE_LEN)
		return -E2BIG;

	if(wrqu->data.length){
		data = kmalloc(wrqu->data.length, GFP_KERNEL);
		if(!data)
			return -ENOMEM;
		memcpy(data, wrqu->data.pointer, wrqu->data.length);
	}

	spin_lock(&core->ieee80211->lock);

	if(core->ieee80211->wpa_ie)
		kfree(core->ieee80211->wpa_ie);

	core->ieee80211->wpa_ie = data;
	core->ieee80211->wpa_ie_len = wrqu->data.length;

	spin_unlock(&core->ieee80211->lock);

	down_write(&device->rt2x00_sem);

	core->config.user_commit |= COMMIT_ENCRYPTION;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_genie(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	spin_lock(&core->ieee80211->lock);

	if(core->ieee80211->wpa_ie == NULL || core->ieee80211->wpa_ie_len == 0){
		spin_unlock(&core->ieee80211->lock);
		return -ENOTSUPP;
	}

	memcpy(wrqu->data.pointer, core->ieee80211->wpa_ie, core->ieee80211->wpa_ie_len);
	wrqu->data.length = core->ieee80211->wpa_ie_len;

	spin_unlock(&core->ieee80211->lock);

	return 0;
}

static int
rt2x00_ioctl_set_auth(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = -EIWCOMMIT;

	down_write(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	switch(wrqu->param.flags & IW_AUTH_INDEX){
		case IW_AUTH_WPA_VERSION:
			core->config.user.wpa_version = wrqu->param.value;
		break;
		case IW_AUTH_DROP_UNENCRYPTED:
			core->ieee80211->drop_unencrypted = wrqu->param.value;
		break;
		case IW_AUTH_80211_AUTH_ALG:
			if(wrqu->param.value & IW_AUTH_ALG_SHARED_KEY){
				core->ieee80211->sec.auth_mode = WLAN_AUTH_SHARED_KEY;
				core->ieee80211->open_wep = 0;
			}else if(wrqu->param.value & IW_AUTH_ALG_OPEN_SYSTEM){
				core->ieee80211->sec.auth_mode = WLAN_AUTH_OPEN;
				core->ieee80211->open_wep = 1;
			}else
				status = -ENOTSUPP;
		break;
		case IW_AUTH_WPA_ENABLED:
			core->ieee80211->wpa_enabled = wrqu->param.value;
		break;
		case IW_AUTH_PRIVACY_INVOKED:
			core->ieee80211->privacy_invoked = wrqu->param.value;
		break;
		case IW_AUTH_RX_UNENCRYPTED_EAPOL:
			core->ieee80211->ieee802_1x = wrqu->param.value;
		break;
		default:
			status = -ENOTSUPP;
		break;
	}

	spin_unlock(&core->ieee80211->lock);

	if(status == -EIWCOMMIT)
		core->config.user_commit |= COMMIT_AUTHENTICATION;
	else if(status == -ENOTSUPP)
		ERROR("SIOCSIWAUTH: unknown or unsupported flag flag %d.\n", wrqu->param.flags);

	up_write(&device->rt2x00_sem);

	return status;
}

static int
rt2x00_ioctl_get_auth(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = 0x00000000;

	down_read(&device->rt2x00_sem);
	spin_lock(&core->ieee80211->lock);

	switch(wrqu->param.flags & IW_AUTH_INDEX){
		case IW_AUTH_WPA_VERSION:
			wrqu->param.value = core->config.user.wpa_version;
		break;
		case IW_AUTH_DROP_UNENCRYPTED:
			wrqu->param.value = core->ieee80211->drop_unencrypted;
		break;
		case IW_AUTH_80211_AUTH_ALG:
			if(core->ieee80211->sec.auth_mode & WLAN_AUTH_SHARED_KEY)
				wrqu->param.value = IW_AUTH_ALG_SHARED_KEY;
			else
				wrqu->param.value = IW_AUTH_ALG_OPEN_SYSTEM;
		break;
		case IW_AUTH_WPA_ENABLED:
			wrqu->param.value = core->ieee80211->wpa_enabled;
		break;
		case IW_AUTH_PRIVACY_INVOKED:
			wrqu->param.value = core->ieee80211->privacy_invoked;
		break;
		case IW_AUTH_RX_UNENCRYPTED_EAPOL:
			wrqu->param.value = core->ieee80211->ieee802_1x;
		break;
		default:
			status = -ENOTSUPP;
		break;
	}

	spin_unlock(&core->ieee80211->lock);
	up_read(&device->rt2x00_sem);

	if(status == -ENOTSUPP)
		ERROR("SIOCGIWAUTH: unknown or unsupported flag flag %d.\n", wrqu->param.flags);

	return status;
}

static int
rt2x00_ioctl_set_encodeext(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	int			res = 0x00000000;

	res = ieee80211_wx_set_encodeext(netdev_priv(net_dev), info, wrqu, extra);
	if(res)
		return res;

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_encodeext(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	return ieee80211_wx_get_encodeext(netdev_priv(net_dev), info, wrqu, extra);
}

static int
rt2x00_ioctl_set_network(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			network = *extra;

	if((network & IEEE_A) && !test_bit(DEVICE_CAP_802_11A, &device->flags)){
		DEBUG("SIOCSIWPRIVNETWORK: Device does not support 802.11a.\n");
		return 0;
	}

	if((network & IEEE_G) && !test_bit(DEVICE_CAP_802_11G, &device->flags)){
		DEBUG("SIOCSIWPRIVNETWORK: Device does not support 802.11g.\n");
		return 0;
	}

	if(!(network & IEEE_MODE_MASK))
		network = 0;

	if(network & IEEE_G)
		network |= IEEE_B;

	if(network & IEEE_A && network & IEEE_B)
		network |= IEEE_G;

	down_write(&device->rt2x00_sem);

	core->config.user.network = network;
	core->config.user_commit |= COMMIT_NETWORK;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_network(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	*extra = core->config.active.network;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_preamble(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_write(&device->rt2x00_sem);

	if(*extra & IOCTL_PREAMBLE_SHORT)
		core->config.user.flags |= CONFIG_ENABLED_SHORT_PREAMBLE;
	else
		core->config.user.flags &= ~CONFIG_ENABLED_SHORT_PREAMBLE;

	core->config.user_commit |= COMMIT_PREAMBLE;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_preamble(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	if(core->config.active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		*extra = IOCTL_PREAMBLE_SHORT;
	else
		*extra = IOCTL_PREAMBLE_LONG;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_antenna(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			antenna = *extra;

	down_write(&device->rt2x00_sem);

	if(antenna & IOCTL_ANTENNA_RX_MASK){
		core->config.user.antenna_flags &= ~ANTENNA_RX;
		if(antenna & IOCTL_ANTENNA_RX_DIV)
			core->config.user.antenna_flags |= ANTENNA_RX_DIV;
		else if(antenna & IOCTL_ANTENNA_RX_A)
			core->config.user.antenna_flags |= ANTENNA_RX_A;
		else if(antenna & IOCTL_ANTENNA_RX_B)
			core->config.user.antenna_flags |= ANTENNA_RX_B;
	}

	if(antenna & IOCTL_ANTENNA_TX_MASK){
		core->config.user.antenna_flags &= ~ANTENNA_TX;
		if(antenna & IOCTL_ANTENNA_TX_DIV)
			core->config.user.antenna_flags |= ANTENNA_TX_DIV;
		else if(antenna & IOCTL_ANTENNA_TX_A)
			core->config.user.antenna_flags |= ANTENNA_TX_A;
		else if(antenna & IOCTL_ANTENNA_TX_B)
			core->config.user.antenna_flags |= ANTENNA_TX_B;
	}

	core->config.user_commit |= COMMIT_ANTENNA;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_antenna(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	if((core->config.active.antenna_flags & ANTENNA_RX) == ANTENNA_RX_DIV)
		*extra |= IOCTL_ANTENNA_RX_DIV;
	else if((core->config.active.antenna_flags & ANTENNA_RX) == ANTENNA_RX_A)
		*extra |= IOCTL_ANTENNA_RX_A;
	else if((core->config.active.antenna_flags & ANTENNA_RX) == ANTENNA_RX_B)
		*extra |= IOCTL_ANTENNA_RX_B;

	if((core->config.active.antenna_flags & ANTENNA_TX) == ANTENNA_TX_DIV)
		*extra |= IOCTL_ANTENNA_TX_DIV;
	else if((core->config.active.antenna_flags & ANTENNA_TX) == ANTENNA_TX_A)
		*extra |= IOCTL_ANTENNA_TX_A;
	else if((core->config.active.antenna_flags & ANTENNA_TX) == ANTENNA_TX_B)
		*extra |= IOCTL_ANTENNA_TX_B;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_geography(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			geography = *extra;

	if(geography >= IOCTL_GEOGRAPHY_INVAL)
		return -EINVAL;

	down_write(&device->rt2x00_sem);

	core->config.user.geography = geography;
	core->config.user_commit |= COMMIT_GEOGRAPHY;

	up_write(&device->rt2x00_sem);

	return -EIWCOMMIT;
}

static int
rt2x00_ioctl_get_geography(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	*extra = core->config.active.geography;

	up_read(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_set_adhoc_ofdm(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_write(&device->rt2x00_sem);

	core->config.user.adhoc_ofdm = *extra;
	core->config.user_commit |= COMMIT_ADHOC_OFDM;

	up_write(&device->rt2x00_sem);

	return 0;
}

static int
rt2x00_ioctl_get_adhoc_ofdm(
	struct net_device *net_dev,
	struct iw_request_info *info,
	union iwreq_data *wrqu,
	char *extra)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	down_read(&device->rt2x00_sem);

	*extra = core->config.active.adhoc_ofdm;

	up_read(&device->rt2x00_sem);

	return 0;
}

static struct iw_statistics*
rt2x00_get_wireless_stats(struct net_device *net_dev)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	return	&core->wireless_stats;
}

static const iw_handler rt2x00_ioctl_handler[] = {
	(iw_handler) rt2x00_ioctl_commit,		/* SIOCSIWCOMMIT */
	(iw_handler) rt2x00_ioctl_get_name,		/* SIOCGIWNAME */
	(iw_handler) NULL,				/* SIOCSIWNWID */
	(iw_handler) NULL,				/* SIOCGIWNWID */
	(iw_handler) rt2x00_ioctl_set_frequency,	/* SIOCSIWFREQ */
	(iw_handler) rt2x00_ioctl_get_frequency,	/* SIOCGIWFREQ */
	(iw_handler) rt2x00_ioctl_set_mode,		/* SIOCSIWMODE */
	(iw_handler) rt2x00_ioctl_get_mode,		/* SIOCGIWMODE */
	(iw_handler) rt2x00_ioctl_set_sens,		/* SIOCSIWSENS */
	(iw_handler) rt2x00_ioctl_get_sens,		/* SIOCGIWSENS */
	(iw_handler) NULL, /* Unused */		/* SIOCSIWRANGE */
	(iw_handler) rt2x00_ioctl_get_range,		/* SIOCGIWRANGE */
	(iw_handler) NULL, /* Unused */		/* SIOCSIWPRIV */
	(iw_handler) NULL, /* Provided by kernel */	/* SIOCGIWPRIV */
	(iw_handler) NULL, /* Unused */		/* SIOCSIWSTATS */
	(iw_handler) NULL, /* Provided by kernel */	/* SIOCGIWSTATS */
	(iw_handler) iw_handler_set_spy,		/* SIOCSIWSPY */
	(iw_handler) iw_handler_get_spy,		/* SIOCGIWSPY */
	(iw_handler) iw_handler_set_thrspy,		/* SIOCSIWTHRSPY */
	(iw_handler) iw_handler_get_thrspy,		/* SIOCGIWTHRSPY */
	(iw_handler) rt2x00_ioctl_set_wap,		/* SIOCSIWAP */
	(iw_handler) rt2x00_ioctl_get_wap,		/* SIOCGIWAP */
	(iw_handler) rt2x00_ioctl_set_mlme,		/* SIOCSIWMLME */
	(iw_handler) NULL, /* Deprecated */		/* SIOCGIWAPLIST */
	(iw_handler) rt2x00_ioctl_set_scan,		/* SIOCSIWSCAN */
	(iw_handler) rt2x00_ioctl_get_scan,		/* SIOCGIWSCAN */
	(iw_handler) rt2x00_ioctl_set_essid,		/* SIOCSIWESSID */
	(iw_handler) rt2x00_ioctl_get_essid,		/* SIOCGIWESSID */
	(iw_handler) rt2x00_ioctl_set_nickname,		/* SIOCSIWNICKN */
	(iw_handler) rt2x00_ioctl_get_nickname,		/* SIOCGIWNICKN */
	(iw_handler) NULL,				/* -- hole -- */
	(iw_handler) NULL,				/* -- hole -- */
	(iw_handler) rt2x00_ioctl_set_bitrate,		/* SIOCSIWRATE */
	(iw_handler) rt2x00_ioctl_get_bitrate,		/* SIOCGIWRATE */
	(iw_handler) rt2x00_ioctl_set_rts_threshold,	/* SIOCSIWRTS */
	(iw_handler) rt2x00_ioctl_get_rts_threshold,	/* SIOCGIWRTS */
	(iw_handler) rt2x00_ioctl_set_fragmentation,	/* SIOCSIWFRAG */
	(iw_handler) rt2x00_ioctl_get_fragmentation,	/* SIOCGIWFRAG */
	(iw_handler) rt2x00_ioctl_set_txpower,		/* SIOCSIWTXPOW */
	(iw_handler) rt2x00_ioctl_get_txpower,		/* SIOCGIWTXPOW */
	(iw_handler) rt2x00_ioctl_set_retry,		/* SIOCSIWRETRY */
	(iw_handler) rt2x00_ioctl_get_retry,		/* SIOCGIWRETRY */
	(iw_handler) rt2x00_ioctl_set_encode,		/* SIOCSIWENCODE */
	(iw_handler) rt2x00_ioctl_get_encode,		/* SIOCGIWENCODE */
	(iw_handler) NULL,				/* SIOCSIWPOWER */
	(iw_handler) NULL,				/* SIOCGIWPOWER */
	(iw_handler) NULL,				/* -- hole -- */
	(iw_handler) NULL,				/* -- hole -- */
	(iw_handler) rt2x00_ioctl_set_genie,		/* SIOCSIWGENIE */
	(iw_handler) rt2x00_ioctl_get_genie,		/* SIOCGIWGENIE */
	(iw_handler) rt2x00_ioctl_set_auth,		/* SIOCSIWAUTH */
	(iw_handler) rt2x00_ioctl_get_auth,		/* SIOCGIWAUTH */
	(iw_handler) rt2x00_ioctl_set_encodeext,	/* SIOCSIWENCODEEXT */
	(iw_handler) rt2x00_ioctl_get_encodeext,	/* SIOCGIWENCODEEXT */
	(iw_handler) NULL,				/* SIOCSIWPMKSA */
};

static const iw_handler rt2x00_ioctl_priv_handler[] = {
	(iw_handler) rt2x00_ioctl_set_network,		/* SIOCSIWPRIVNETWORK */
	(iw_handler) rt2x00_ioctl_get_network,		/* SIOCGIWPRIVNETWORK */
	(iw_handler) rt2x00_ioctl_set_preamble,		/* SIOCSIWPRIVPREAMBLE */
	(iw_handler) rt2x00_ioctl_get_preamble,		/* SIOCGIWPRIVPREAMBLE */
	(iw_handler) rt2x00_ioctl_set_antenna,		/* SIOCSIWPRIVANTENNA */
	(iw_handler) rt2x00_ioctl_get_antenna,		/* SIOCGIWPRIVANTENNA */
	(iw_handler) rt2x00_ioctl_set_geography,	/* SIOCSIWPRIVGEOGRAPHY */
	(iw_handler) rt2x00_ioctl_get_geography,	/* SIOCGIWPRIVGEOGRAPHY */
	(iw_handler) rt2x00_ioctl_set_adhoc_ofdm,	/* SIOCSIWPRIVADHOCOFDM */
	(iw_handler) rt2x00_ioctl_get_adhoc_ofdm,	/* SIOCGIWPRIVADHOCOFDM */
};

static const struct iw_priv_args rt2x00_ioctl_priv_args[] = {
	{ SIOCSIWPRIVNETWORK, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0, "set_network" },
	{ SIOCGIWPRIVNETWORK, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "get_network" },
	{ SIOCSIWPRIVPREAMBLE, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0, "set_preamble" },
	{ SIOCGIWPRIVPREAMBLE, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "get_preamble" },
	{ SIOCSIWPRIVANTENNA, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0, "set_antenna" },
	{ SIOCGIWPRIVANTENNA, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "get_antenna" },
	{ SIOCSIWPRIVGEOGRAPHY, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0, "set_geography" },
	{ SIOCGIWPRIVGEOGRAPHY, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "get_geography" },
	{ SIOCSIWPRIVADHOCOFDM, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, 0, "set_adhoc_ofdm" },
	{ SIOCGIWPRIVADHOCOFDM, 0, IW_PRIV_TYPE_BYTE | IW_PRIV_SIZE_FIXED | 1, "get_adhoc_ofdm" },
};

static const struct iw_handler_def rt2x00_ioctl_handler_def = {
	.num_standard		= ARRAY_SIZE(rt2x00_ioctl_handler),
	.num_private		= ARRAY_SIZE(rt2x00_ioctl_priv_handler),
	.num_private_args	= ARRAY_SIZE(rt2x00_ioctl_priv_args),
	.standard		= rt2x00_ioctl_handler,
	.private		= rt2x00_ioctl_priv_handler,
	.private_args		= rt2x00_ioctl_priv_args,
	.get_wireless_stats	= rt2x00_get_wireless_stats,
};

static void
rt2x00_set_security(struct net_device *net_dev, struct ieee80211_security *sec)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	u8			counter = 0x00;

	down_write(&device->rt2x00_sem);

	spin_lock(&core->ieee80211->lock);

	for(counter = 0; counter < WEP_KEYS; counter++){
		if(sec->flags & (1 << counter)) {
			core->ieee80211->sec.encode_alg[counter] = sec->encode_alg[counter];
			core->ieee80211->sec.key_sizes[counter] = sec->key_sizes[counter];
			if(sec->key_sizes[counter] != 0)
				memcpy(core->ieee80211->sec.keys[counter], sec->keys[counter], sec->key_sizes[counter]);
			core->ieee80211->sec.flags |= (1 << counter);
		}else if(sec->level != SEC_LEVEL_1)
			core->ieee80211->sec.flags &= ~(1 << counter);
	}

	if(sec->flags & SEC_ACTIVE_KEY){
		if(sec->active_key <= 3){
			core->ieee80211->sec.active_key = sec->active_key;
			core->ieee80211->sec.flags |= SEC_ACTIVE_KEY;
		}else
			core->ieee80211->sec.flags &= ~SEC_ACTIVE_KEY;
	}else
		core->ieee80211->sec.flags &= ~SEC_ACTIVE_KEY;

	if((sec->flags & SEC_AUTH_MODE) && (core->ieee80211->sec.auth_mode != sec->auth_mode)){
		core->ieee80211->sec.auth_mode = sec->auth_mode;
		core->ieee80211->sec.flags |= SEC_AUTH_MODE;
	}

	if(sec->flags & SEC_ENABLED && core->ieee80211->sec.enabled != sec->enabled){
		core->ieee80211->sec.flags |= SEC_ENABLED;
		core->ieee80211->sec.enabled = sec->enabled;
	}

	if(sec->flags & SEC_ENCRYPT)
		core->ieee80211->sec.encrypt = sec->encrypt;

	if(sec->flags & SEC_LEVEL && core->ieee80211->sec.level != sec->level){
		core->ieee80211->sec.level = sec->level;
		core->ieee80211->sec.flags |= SEC_LEVEL;
	}

	spin_unlock(&core->ieee80211->lock);

	core->config.user_commit |= COMMIT_ENCRYPTION;

	up_write(&device->rt2x00_sem);
}

/*
 * TX/RX related routines.
 */
static int
rt2x00_start_xmit(struct ieee80211_txb *txb, struct net_device *net_dev, int pri)
{
	struct _rt2x00_device		*device = rt2x00_device(net_dev);
	struct _rt2x00_core		*core = rt2x00_core(device);
	struct sk_buff			*skb = NULL;
	u16				frame = 0x0000;
	u8				counter = 0x00;

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return -ENOTCONN;

	frame = rt2x00_get_sequence(device);

	if(txb->nr_frags > 1)
		frame += 0x0001;

	spin_lock(&core->tx.lock);

	for(counter= 0x00; counter < txb->nr_frags; counter++){
		skb = txb->fragments[counter];
		txb->fragments[counter] = NULL;

		if(unlikely(!skb))
			break;

		skb->priority = pri;
		((struct ieee80211_hdr_3addr*)skb->data)->seq_ctl = cpu_to_le16(frame);
		((struct _skb_cb*)&skb->cb)->id = frame;
		((struct _skb_cb*)&skb->cb)->packets = txb->nr_frags;

		skb_queue_tail(&core->tx.queue, skb);

		frame += 0x0001;
	}

	if(core->tx.ready)
		queue_work(core->workqueue, &core->tx.work);

	spin_unlock(&core->tx.lock);

	ieee80211_txb_free(txb);

	return 0;
}

void
rt2x00_rx(struct _rt2x00_device *device, struct sk_buff *skb)
{
	rt2x00_queue_ring(&((struct _rt2x00_core*)rt2x00_core(device))->rx, skb);
}
EXPORT_SYMBOL_GPL(rt2x00_rx);

void
rt2x00_tx(struct _rt2x00_device *device, u8 ring_type)
{
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(ring_type & RING_TX)
		rt2x00_kick_ring(&core->tx);

	if(ring_type & RING_PRIO)
		rt2x00_kick_ring(&core->prio);

	if(ring_type & RING_ATIM)
		rt2x00_kick_ring(&core->atim);

	if(ring_type & RING_BEACON)
		rt2x00_kick_ring(&core->beacon);
}
EXPORT_SYMBOL_GPL(rt2x00_tx);

void
rt2x00_update_stats(struct _rt2x00_device *device, u8 flags, u8 value)
{
	struct _rt2x00_core	*core = rt2x00_core(device);

	if(flags & STATS_RX_CRC || flags & STATS_RX_PHYSICAL || flags & STATS_RX_QUALITY)
		core->ieee80211->stats.rx_crc_errors += value;

	if(flags & STATS_RX_DROP)
		core->ieee80211->stats.rx_dropped += value;

	if(flags & STATS_TX_RETRY_COUNT)
		core->ieee80211->stats.collisions += value;

	if(flags & STATS_TX_RESULT){
		switch(value){
			case TX_FAIL_RETRY:
				core->wireless_stats.discard.retries++;
				core->ieee80211->stats.tx_errors++;
			break;
			case TX_FAIL_INVALID:
			case TX_FAIL_OTHER:
				core->wireless_stats.discard.misc++;
				core->ieee80211->stats.tx_errors++;
			break;
		}
	}
}
EXPORT_SYMBOL_GPL(rt2x00_update_stats);

/*
 * Workqueue handlers.
 */
static void
rt2x00_delayed_rx(void *data)
{
	struct _packet_ring		*ring = data;
	struct _rt2x00_core		*core = ring->core;
	struct ieee80211_hdr_4addr	*ieee80211hdr = NULL;
	struct ieee80211_rx_stats	rx_stats;
	struct sk_buff			*skb = NULL;
	u16				frame = 0x00;

	if(!ring->ready
	|| !test_bit(DEVICE_RADIO_ON, &core->device->flags))
		return;

	memset(&rx_stats, 0x00, sizeof(rx_stats));

	down_read(&core->device->rt2x00_sem);

	rx_stats.rate = core->config.active.bitrate * 5000; /* in 100 kbps */
	rx_stats.received_channel = core->config.active.channel;
	if(rt2x00_is_24ghz_channel(core->config.active.channel))
		rx_stats.freq = IEEE80211_24GHZ_BAND;
	else
		rx_stats.freq = IEEE80211_52GHZ_BAND;

	up_read(&core->device->rt2x00_sem);

	spin_lock(&ring->lock);

	while(!skb_queue_empty(&ring->queue)){
		skb = skb_dequeue(&ring->queue);
		if(!skb){
			ERROR("failed to dequeue packet.\n");
			break;
		}

		spin_unlock(&ring->lock);

		rx_stats.mask = IEEE80211_STATMASK_RATE;

		rx_stats.rssi = ((struct _skb_cb*)&skb->cb)->rssi;
		if(rx_stats.rssi)
			rx_stats.mask |= IEEE80211_STATMASK_RSSI;

		rx_stats.noise = core->rt2x00_stats.noise;
		if(rx_stats.noise)
			rx_stats.mask |= IEEE80211_STATMASK_NOISE;

		rx_stats.signal = core->rt2x00_stats.signal;
		if(rx_stats.signal)
			rx_stats.mask |= IEEE80211_STATMASK_SIGNAL;

		rx_stats.len = skb->len;

		ieee80211hdr = (struct ieee80211_hdr_4addr*)skb->data;
		frame = le16_to_cpu(ieee80211hdr->frame_ctl);

		if(WLAN_FC_GET_TYPE(frame) == IEEE80211_FTYPE_MGMT
		&& core->config.active.iw_mode != IW_MODE_MONITOR){
			if(WLAN_FC_GET_STYPE(frame) == IEEE80211_STYPE_ASSOC_REQ
			|| WLAN_FC_GET_STYPE(frame) == IEEE80211_STYPE_REASSOC_REQ)
				rt2x00_handle_assoc(core->device, ieee80211hdr);
			else
				ieee80211_rx_mgt(core->ieee80211, ieee80211hdr, &rx_stats);
			dev_kfree_skb_any(skb);
		}else if(!ieee80211_rx(core->ieee80211, skb, &rx_stats))
			dev_kfree_skb_any(skb);

		spin_lock(&ring->lock);
	}

	spin_unlock(&ring->lock);

	core->device->net_dev->last_rx = jiffies;
}

static int
rt2x00_xmit_packet(struct _rt2x00_core *core, struct _packet_ring *ring, u8 rate, u16 xmit_flags)
{
	struct sk_buff			*skb = NULL;
	struct ieee80211_hdr_3addr	*ieee80211hdr = NULL;
	u16				duration = 0x0000;
	u8				frame_gap = 0x00;

	if(!ring->ready)
		return -EBUSY;

	skb = skb_dequeue(&ring->queue);
	if(!skb){
		ERROR("failed to dequeue packet.\n");
		return -ENODATA;
	}

	ieee80211hdr = (struct ieee80211_hdr_3addr*)skb->data;

	if(ring->type == RING_BEACON)
		ieee80211hdr->seq_ctl = cpu_to_le16(rt2x00_get_sequence(core->device));

	duration = core->config.sifs + get_preamble(&core->config) + get_duration(ACK_SIZE, IEEE80211_CCK_RATE_2MB);
	if(ring->type == RING_TX){
		duration *= 2;
		duration += core->config.sifs + get_preamble(&core->config) + get_duration(skb->len, rate);
	}
	ieee80211hdr->duration_id = cpu_to_le16(duration);

	if(WLAN_GET_SEQ_FRAG(ieee80211hdr->seq_ctl) <= 1){
		frame_gap = XMIT_IFS_BACKOFF;
		xmit_flags |= XMIT_NEW_SEQUENCE;
	}else
		frame_gap = XMIT_IFS_SIFS;

	if(WLAN_FC_GET_TYPE(ieee80211hdr->frame_ctl)==IEEE80211_STYPE_RTS){
		xmit_flags |= XMIT_RTS;
		frame_gap = XMIT_IFS_SIFS;
	}

	xmit_flags |= frame_gap;

	if(is_valid_ether_addr(&ieee80211hdr->addr1[0])
	&& WLAN_FC_GET_TYPE(ieee80211hdr->frame_ctl)==IEEE80211_STYPE_ACK)
		xmit_flags |= XMIT_ACK;

	if(WLAN_FC_GET_TYPE(ieee80211hdr->frame_ctl)==IEEE80211_STYPE_PROBE_RESP)
		xmit_flags |= XMIT_TIMESTAMP;

	if(ieee80211_is_ofdm_rate(rate))
		xmit_flags |= XMIT_OFDM;

	if(core->device->handler->dev_xmit_packet(core->device, skb, ring->type, rate, xmit_flags)){
		ring->ready = 0;
		skb_queue_head(&ring->queue, skb);
		return -ENOMEM;
	}

	if(ring->type != RING_BEACON)
		dev_kfree_skb_any(skb);
	else{
		ring->ready = 0;
		skb_queue_head(&ring->queue, skb);
	}

	return 0;
}

static void
rt2x00_delayed_tx(void *data)
{
	struct _packet_ring		*ring = data;
	struct _rt2x00_device		*device = ring->core->device;
	struct sk_buff			*skb = NULL;
	u16				packet_id = 0x0000;
	u16				xmit_flags = 0x0000;
	u8				rate = 0x00;

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(test_bit(DEVICE_SCANNING, &device->flags))
		return;

	down_read(&device->rt2x00_sem);

	rate = ring->core->config.active.bitrate;

	if(ring->core->config.active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		xmit_flags |= XMIT_SHORT_PREAMBLE;

	if(ring->core->config.active.flags & CONFIG_ENABLED_LONG_RETRY)
		xmit_flags |= XMIT_LONG_RETRY;

	up_read(&device->rt2x00_sem);

	spin_lock(&ring->lock);

	while(!skb_queue_empty(&ring->queue)){
		skb = skb_peek(&ring->queue);
		if(!skb)
			goto exit_kick_tx;

		packet_id = ((struct _skb_cb*)&skb->cb)->id;

		if(device->handler->dev_test_tx(device, ((struct _skb_cb*)&skb->cb)->packets)){
			NOTICE("TX ring full");
			goto exit_kick_tx;
		}

		do{
			if(rt2x00_xmit_packet(ring->core, ring, rate, xmit_flags)){
				NOTICE("TX ring full");
				goto exit_kick_tx;
			}

			skb = skb_peek(&ring->queue);
			if(!skb)
				goto exit_kick_tx;
		}while(((struct _skb_cb*)&skb->cb)->id == packet_id);
	}

exit_kick_tx:
	if(device->handler->dev_xmit_packet(device, NULL, ring->type, 0, XMIT_START))
		ERROR("failed to kick TX queue.\n");

	spin_unlock(&ring->lock);

	device->net_dev->trans_start = jiffies;
}

static void
rt2x00_delayed_mgmt(void *data)
{
	struct _packet_ring		*ring = data;
	struct _rt2x00_device		*device = ring->core->device;
	u16				xmit_flags = 0x0000;
	u8				rate = 0x00;

	if(!test_bit(DEVICE_RADIO_ON, &device->flags))
		return;

	if(ring->type != RING_PRIO && test_bit(DEVICE_SCANNING, &device->flags))
		return;

	down_read(&ring->core->device->rt2x00_sem);

	rate = ring->core->config.active.bitrate;

	if(ring->core->config.active.flags & CONFIG_ENABLED_SHORT_PREAMBLE)
		xmit_flags |= XMIT_SHORT_PREAMBLE;

	if(ring->core->config.active.flags & CONFIG_ENABLED_LONG_RETRY)
		xmit_flags |= XMIT_LONG_RETRY;

	if(ring->type != RING_BEACON)
		xmit_flags |= XMIT_START;

	up_read(&ring->core->device->rt2x00_sem);

	spin_lock(&ring->lock);

	while(!skb_queue_empty(&ring->queue)){
		if(rt2x00_xmit_packet(ring->core, ring, IEEE80211_CCK_RATE_2MB, xmit_flags)
		|| ring->type == RING_BEACON)
			break;
	}

	spin_unlock(&ring->lock);
}

/*
 * net_device handlers.
 */
static int
rt2x00_open(struct net_device *net_dev)
{
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);
	int			status = 0x00000000;

	if(test_and_set_bit(DEVICE_ENABLED, &device->flags)){
		ERROR("device already enabled.\n");
		return -EBUSY;
	}

	if(test_bit(DEVICE_SCANNING, &device->flags)){
		queue_delayed_work(core->workqueue, &core->link_tuner, LINK_TIME);
		return 0;
	}

	status = rt2x00_radio_on(device);
	if(status){
		clear_bit(DEVICE_ENABLED, &device->flags);
		return status;
	}

	rt2x00_activate_config(device);
	rt2x00_link_up(device);

	return 0;
}

static int
rt2x00_stop(struct net_device *net_dev)
{
	struct _rt2x00_device	*device = rt2x00_device(net_dev);

	if(!test_and_clear_bit(DEVICE_ENABLED, &device->flags)){
		ERROR("device already disabled.\n");
		return -EBUSY;
	}

	rt2x00_radio_off(device);

	return 0;
}

static int
rt2x00_change_mtu(struct net_device *net_dev, int new_mtu)
{
	if((new_mtu < 256) || (new_mtu > DATA_FRAME_SIZE) || (new_mtu > MAX_FRAG_THRESHOLD))
		return -EINVAL;

	net_dev->mtu = new_mtu;

	return 0;
}

static void
rt2x00_tx_timeout(struct net_device *net_dev)
{
	struct _rt2x00_device	*device = ieee80211_priv(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	WARNING("Tx timed out. Start kicking all packet rings.\n");

	device->handler->dev_xmit_packet(device, NULL, RING_TX, 0, XMIT_START);
	device->handler->dev_xmit_packet(device, NULL, RING_PRIO, 0, XMIT_START);
	device->handler->dev_xmit_packet(device, NULL, RING_ATIM, 0, XMIT_START);

	rt2x00_kick_ring(&core->tx);
	rt2x00_kick_ring(&core->prio);
	rt2x00_kick_ring(&core->atim);
}

static struct net_device_stats*
rt2x00_get_stats(struct net_device *net_dev)
{
	return &((struct ieee80211_device*)netdev_priv(net_dev))->stats;
}

/*
 * Initialization handlers.
 */
static void
rt2x00_init_config(struct _rt2x00_core *core)
{
	memset(&core->config.nickn, '\0', sizeof(core->config.nickn));
	memset(&core->config.user.essid, '\0', sizeof(core->config.user.essid));
	memset(&core->config.user.bssid, 0x00, sizeof(core->config.user.bssid));

	core->config.user.network = 0;
	core->config.user.iw_mode = IW_MODE_AUTO;
	core->config.user.geography = IOCTL_GEOGRAPHY_INVAL;
	core->config.user.channel = 0;
	core->config.user.bitrate = 0;
	core->config.user.flags |= CONFIG_ACCEPT_UNICAST | CONFIG_ACCEPT_MULTICAST;
	core->config.user.short_retry = 4;
	core->config.user.long_retry = 7;
	core->config.user.rts_threshold = MAX_FRAG_THRESHOLD;
	core->config.user.fragmentation = MAX_FRAG_THRESHOLD;
	core->config.user.txpower = 100;
	core->config.user.antenna_flags |= ANTENNA_TX_DIV | ANTENNA_RX_DIV;
	core->config.user.wpa_version = IW_AUTH_WPA_VERSION_DISABLED;
	core->config.user.adhoc_ofdm = 0;
	core->config.beacon = 100;
	core->config.plcp = 48;
	core->config.sifs = 10;
	core->config.sequence = 0;
	core->config.user.sensitivity = 10;
	core->config.user_commit = COMMIT_ALL_CONFIG;
}

/*
 * Module handlers.
 */
struct net_device*
rt2x00_core_probe(struct _rt2x00_dev_handler *handler, void *priv, u32 sizeof_dev, struct device *dev)
{
	struct net_device	*net_dev = NULL;
	struct _rt2x00_device	*device = NULL;
	struct _rt2x00_core	*core = NULL;

	if(unlikely(handler->dev_radio_on == NULL)
	|| unlikely(handler->dev_radio_off == NULL)
	|| unlikely(handler->dev_update_config == NULL)
	|| unlikely(handler->dev_update_stats == NULL)
	|| unlikely(handler->dev_test_tx == NULL)
	|| unlikely(handler->dev_xmit_packet == NULL)){
		ERROR("not enough handlers provided by device.\n");
		goto exit;
	}

	net_dev = alloc_ieee80211(sizeof_dev + sizeof(*device) + sizeof(*core));
	if(!net_dev){
		ERROR("not enough memory to allocate net_device.\n");
		goto exit;
	}

	device = ieee80211_priv(net_dev);
	memset(device, 0x00, sizeof(*device));

	core = (void*)device + sizeof(*device);
	core->ieee80211 = netdev_priv(net_dev);
	core->device = device;
	core->network = NULL;
	core->scan_req = NULL;
	core->scan_flags = 0;
	core->connection_attempt = 0;
	core->connection_status = CONNECTION_INITIALIZED;
	memset(&core->rt2x00_stats, 0x00, sizeof(core->rt2x00_stats));

	device->priv = (void*)core + sizeof(*core);
	device->owner = core;
	device->handler = handler;
	device->net_dev = net_dev;

	init_rwsem(&device->rt2x00_sem);
	init_MUTEX(&core->scan_sem);

	core->workqueue = create_singlethread_workqueue("rt2x00");
	if (!core->workqueue)
		goto exit_free_ieee80211;
	INIT_WORK(&core->scan_tuner, rt2x00_scan_periodic, device);
	INIT_WORK(&core->link_tuner, rt2x00_link_periodic, device);

	rt2x00_init_ring(device, &core->rx, RING_RX, rt2x00_delayed_rx);
	rt2x00_init_ring(device, &core->tx, RING_TX, rt2x00_delayed_tx);
	rt2x00_init_ring(device, &core->atim, RING_ATIM, rt2x00_delayed_mgmt);
	rt2x00_init_ring(device, &core->prio, RING_PRIO, rt2x00_delayed_mgmt);
	rt2x00_init_ring(device, &core->beacon, RING_BEACON, rt2x00_delayed_mgmt);

	rt2x00_init_config(core);

	if(device->handler->dev_probe
	&& device->handler->dev_probe(device, &core->config, priv)){
		ERROR("device probe failed.\n");
		goto exit_free_workqueue;
	}
	INFO("Device " MAC_FMT " detected.\n", MAC_ARG(device->net_dev->dev_addr));

	core->ieee80211->set_security = rt2x00_set_security;
	core->ieee80211->hard_start_xmit = rt2x00_start_xmit;
	core->ieee80211->handle_auth = rt2x00_handle_auth;
	core->ieee80211->handle_deauth = rt2x00_handle_deauth;
	core->ieee80211->handle_disassoc = rt2x00_handle_disassoc;
	core->ieee80211->handle_probe_request = rt2x00_handle_probe_request;
	core->ieee80211->handle_assoc_response = rt2x00_handle_assoc_resp;
	core->ieee80211->handle_beacon = rt2x00_handle_beacon;
	core->ieee80211->handle_probe_response = rt2x00_handle_probe_resp;

	core->ieee80211->config |= CFG_IEEE80211_RTS;
	core->ieee80211->state = IEEE80211_INITIALIZED;
	core->ieee80211->wpa_ie = NULL;
	core->ieee80211->sec.enabled = 0;
	core->ieee80211->sec.encrypt = 0;
	core->ieee80211->sec.auth_mode = WLAN_AUTH_OPEN;

	net_dev->open = rt2x00_open;
	net_dev->stop = rt2x00_stop;
	net_dev->change_mtu = rt2x00_change_mtu;
	net_dev->tx_timeout = rt2x00_tx_timeout;
	net_dev->watchdog_timeo = 2 * HZ;
	net_dev->wireless_handlers = &rt2x00_ioctl_handler_def;
	net_dev->wireless_data = &core->wireless_data;

	net_dev->get_stats = rt2x00_get_stats;

	SET_NETDEV_DEV(net_dev,dev);

	if(register_netdev(net_dev)){
		ERROR("net_device registration failed.\n");
		goto exit_dev_remove;
	}

	set_bit(DEVICE_AWAKE, &device->flags);

	/*
	 * Activate current configuration.
	 */
	rt2x00_activate_config(device);

	return net_dev;

exit_dev_remove:
	if(device->handler->dev_remove)
		device->handler->dev_remove(device);

exit_free_workqueue:
	destroy_workqueue(core->workqueue);

exit_free_ieee80211:
	free_ieee80211(net_dev);

exit:
	return NULL;
}
EXPORT_SYMBOL_GPL(rt2x00_core_probe);

void
rt2x00_core_remove(struct net_device *net_dev)
{
	struct _rt2x00_device	*device = rt2x00_device(net_dev);
	struct _rt2x00_core	*core = rt2x00_core(device);

	unregister_netdev(net_dev);

	destroy_workqueue(core->workqueue);

	down_write(&device->rt2x00_sem);

	if(device->handler->dev_remove)
		device->handler->dev_remove(device);

	if(core->ieee80211->wpa_ie)
		kfree(core->ieee80211->wpa_ie);
	core->ieee80211->wpa_ie = NULL;

	free_ieee80211(net_dev);

	up_write(&device->rt2x00_sem);
}
EXPORT_SYMBOL_GPL(rt2x00_core_remove);

int
rt2x00_suspend(struct _rt2x00_device *device)
{
	if(test_bit(DEVICE_ENABLED, &device->flags)){
		set_bit(DEVICE_RESTORE_LINK, &device->flags);
		if(dev_close(device->net_dev))
			return -EBUSY;
	}
	if(test_bit(DEVICE_RADIO_ON, &device->flags)){
		rt2x00_radio_off(device);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(rt2x00_suspend);

int
rt2x00_resume(struct _rt2x00_device *device)
{
	if(test_bit(DEVICE_RESTORE_LINK, &device->flags))
		return dev_open(device->net_dev);

	return 0;
}
EXPORT_SYMBOL_GPL(rt2x00_resume);

/*
 * RT2x00 core module information.
 */
static char version[] = DRV_NAME " - " DRV_VERSION " (" DRV_RELDATE ") by " DRV_PROJECT;

int rt2x00_debug_level = 0x00000000;
EXPORT_SYMBOL_GPL(rt2x00_debug_level);

MODULE_AUTHOR(DRV_PROJECT);
MODULE_VERSION(DRV_VERSION);
MODULE_DESCRIPTION("Ralink RT2400/RT2500 PCI, PCMCIA & USB Wireless LAN driver.");
MODULE_SUPPORTED_DEVICE("Ralink RT2460, RT2560 & RT2570 PCI, PCMCIA & USB chipset based cards");
MODULE_LICENSE("GPL");

static int __init rt2x00_core_init(void)
{
	printk(KERN_INFO "Loading module: %s\n", version);
	return 0;
}

static void __exit rt2x00_core_exit(void)
{
	printk(KERN_INFO "Unloading module: %s\n", version);
}

module_init(rt2x00_core_init);
module_exit(rt2x00_core_exit);
