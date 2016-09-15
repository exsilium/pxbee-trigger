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
#include <endpoints.h>
/* Used to track ZDO transactions in order to match responses to requests
   (#ZDO_MATCH_DESC_RESP). */
/* wpan_ep_state_t zdo_ep_state = { 0 }; */
/* ZDO_ENDPOINT(zdo_ep_state), */

int xbee_transparent_rx( const wpan_envelope_t FAR *, void FAR *);
int xbee_discovery_cluster_handler(const wpan_envelope_t FAR *envelope,
								   void FAR *context);
void start_ota_fw_update(addr64 *host_address, app_rst_casuses_t reason);
const char *xbee_update_firmware_ota(const wpan_envelope_t FAR *envelope,
									  void FAR *context);
int xbee_my_cluster_rx(const wpan_envelope_t FAR *, void FAR *);

#ifdef	EP_INCLUDE_DECLARATIONS
EP_INCLUDE_DECLARATIONS
#endif

const wpan_cluster_table_entry_t digi_data_clusters[] = {
    /* Other clusters should go here, sorted by cluster ID... */
		DIGI_CLUSTER_SERIAL,
		DIGI_CLUSTER_NODEID,
		DIGI_CLUSTER_PXBEE_OTAUPD,
		DIGI_ADDITIONAL_CLUSTERS,
		WPAN_CLUST_ENTRY_LIST_END
};

const wpan_endpoint_table_entry_t endpoints_table[] = {
		DIGI_DATA_ENDPOINT,
		ADDITIONAL_ENDPOINTS,
	{ WPAN_ENDPOINT_END_OF_LIST }
};