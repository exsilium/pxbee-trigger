/****************************************************************************
 * Copyright (C) 2012 - 2015 Digi International Inc, All Rights Reserved.
 *
 * This software is provided as instructional material without charge 
 * by Digi International for use by its employees and customers
 * subject to the following terms.
 *
 * PERMISSION
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software, to deal with it without restriction, 
 * including without limitation the rights to use, copy,  modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of it, and to permit persons to 
 * whom it is furnished to do so, provided the above copyright notice 
 * and this permission notice are included in all derived works
 * and the use of this software is restricted to Digi products.
 *
 * WARRANTY
 * THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT.  
 *
 * LIABILITY
 * IN NO EVENT SHALL DIGI INTERNATIONAL BE LIABLE FOR ANY CLAIM, DAMAGES, 
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT, OR OTHERWISE, 
 * ARISING FROM, OUT OF, OR IN CONNECTION WITH THE SOFTWARE, OR THE USE 
 * OR OTHER DEALINGS WITH THE SOFTWARE.
 *
 ****************************************************************************/
#include <xbee_config.h>
#include <xbee/ota_server.h>

#ifndef __ENDPOINTS_H_
#define __ENDPOINTS_H_

/* Used to track ZDO transactions in order to match responses to requests */
/* (#ZDO_MATCH_DESC_RESP). */
/* wpan_ep_state_t zdo_ep_state = { 0 }; */
/* ZDO_ENDPOINT(zdo_ep_state), */

extern const wpan_cluster_table_entry_t digi_data_clusters[];

/* Define function to handle other clusters, i.e.: 
 * #define DEFAULT_DIGI_CLUSTER_HANDLER digi_default_cluster_callback
 */
#ifndef DEFAULT_DIGI_CLUSTER_HANDLER
#define DEFAULT_DIGI_CLUSTER_HANDLER		NULL
#else
int DEFAULT_DIGI_CLUSTER_HANDLER(const wpan_envelope_t FAR *envelope,
								 void FAR *context);
#endif

#define DIGI_DATA_ENDPOINT		{WPAN_ENDPOINT_DIGI_DATA, WPAN_PROFILE_DIGI, \
								 DEFAULT_DIGI_CLUSTER_HANDLER, \
								 NULL, 0x0000, 0x00, digi_data_clusters}
#ifdef ENABLE_XBEE_HANDLE_RX
#define DIGI_CLUSTER_SERIAL		{DIGI_CLUST_SERIAL, xbee_transparent_rx, NULL,	\
								WPAN_CLUST_FLAG_INOUT | WPAN_CLUST_FLAG_NOT_ZCL}\
								/* cluster 0x0011 */
#else
#define DIGI_CLUSTER_SERIAL		{0}
#endif /* ENABLE_XBEE_HANDLE_RX */

#ifdef ENABLE_XBEE_HANDLE_ND_RESPONSE_FRAMES
#define DIGI_CLUSTER_NODEID		{DIGI_CLUST_NODEID_MESSAGE, \
								 xbee_disc_nodeid_cluster_handler, NULL, \
								 WPAN_CLUST_FLAG_INPUT | WPAN_CLUST_FLAG_NOT_ZCL}\
								 /* cluster 0x0095 */
#else
#define DIGI_CLUSTER_NODEID		{0}
#endif /* ENABLE_XBEE_HANDLE_ND_RESPONSE_FRAMES */

#ifdef ENABLE_OTA_UPDATE
#define DIGI_CLUSTER_PXBEE_OTAUPD	XBEE_OTA_CMD_SERVER_CLUST_ENTRY(WPAN_CLUST_FLAG_NONE)
#else
#define DIGI_CLUSTER_PXBEE_OTAUPD	{0}
#endif /* ENABLE_OTA_UPDATE */



#ifndef DIGI_ADDITIONAL_CLUSTERS
#define DIGI_ADDITIONAL_CLUSTERS	{0}
#endif

#ifndef ADDITIONAL_ENDPOINTS
#define ADDITIONAL_ENDPOINTS		{0}
#endif

#endif /* __ENDPOINTS_H_ */
