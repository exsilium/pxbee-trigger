/****************************************************************************
 * Copyright (C) 2011 - 2015 Digi International Inc, All Rights Reserved.
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


#include "xbee/atcmd.h"
#include "xbee/device.h"
#include "xbee/wpan.h"
#include "xbee/discovery.h"

#include <xbee_config.h>
#include <pan_init.h>
#include <stdlib.h>
#include <debug.h>
#include <system.h>

/* Custom frame handlers */
int xbee_disc_atnd_cmd_response_handler(xbee_dev_t *xbee, const void FAR *raw,
										uint16_t length, void FAR *context);
int xbee_node_identification_handler(xbee_dev_t *xbee, const void FAR *raw,
									 uint16_t length, void FAR *context);
int xbee_rx_simple_handler(xbee_dev_t *xbee, const void FAR *raw,
						   uint16_t length, void FAR *context);
int xbee_modem_status_handler(xbee_dev_t *xbee, const void FAR *payload,
                              uint16_t length, void FAR *context);
int xbee_transmit_status_handler(xbee_dev_t *xbee, const void FAR *payload,
								 uint16_t length, void FAR *context);

#if defined(ENABLE_XBEE_HANDLE_RX_EXPLICIT_FRAMES) || \
	defined(ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES)
/* Defined in endpoints.c */
extern const wpan_endpoint_table_entry_t endpoints_table[];
#define EP_TABLE		endpoints_table
#else
const wpan_endpoint_table_entry_t endpoints_table_empty[] = {
    { WPAN_ENDPOINT_END_OF_LIST }
};
#define EP_TABLE		endpoints_table_empty
#endif

/* Initialization of the frame handlers based on user selection */
const xbee_dispatch_table_entry_t xbee_frame_handlers[] = {
	XBEE_FRAME_HANDLE_LOCAL_AT,
#ifdef ENABLE_XBEE_HANDLE_MODEM_STATUS_FRAMES
	{XBEE_FRAME_MODEM_STATUS, 0, xbee_modem_status_handler, NULL},
#endif
#ifdef ENABLE_XBEE_HANDLE_REMOTE_AT
	XBEE_FRAME_HANDLE_REMOTE_AT,
#endif
#ifdef ENABLE_XBEE_HANDLE_RX_SIMPLE_FRAMES
	{XBEE_FRAME_RECEIVE, 0, xbee_rx_simple_handler, NULL},
#endif
#if defined(ENABLE_XBEE_HANDLE_RX_EXPLICIT_FRAMES) || \
	defined(ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES)
	XBEE_FRAME_HANDLE_RX_EXPLICIT,
#endif
#ifdef ENABLE_XBEE_HANDLE_TX_STATUS_FRAMES
	{XBEE_FRAME_TRANSMIT_STATUS, 0, xbee_transmit_status_handler, NULL},
#endif
#ifdef ENABLE_XBEE_HANDLE_ND_RESPONSE_FRAMES
	{XBEE_FRAME_LOCAL_AT_RESPONSE, 0, xbee_disc_atnd_response_handler, NULL},
#ifdef ENABLE_XBEE_HANDLE_RX_SIMPLE_FRAMES
	{XBEE_FRAME_NODE_ID, 0, xbee_node_identification_handler, NULL},
#endif
#endif
	XBEE_FRAME_TABLE_END
};

static void xbee_params_init(void)
{
#ifdef XBEE_ATCMD_PARAM_ID
	char *p = XBEE_ATCMD_PARAM_ID;
	uint8_t cmdparam[8];
	uint8_t length;
	int val;

	for (length = 0; *p && length < 8; ++length, p += 2) {
		val = hexstrtobyte(p);
		if (val < 0) {
			break;
		}
		cmdparam[length] = (uint8_t)val;
	}
	(void)xbee_cmd_execute(&xdev, "ID", cmdparam, length);
	sys_watchdog_reset();
#endif
#ifdef XBEE_ATCMD_PARAM_NI
	(void)xbee_cmd_execute(&xdev, "NI", XBEE_ATCMD_PARAM_NI,			\
				   	   	   (sizeof(XBEE_ATCMD_PARAM_NI)-1) / sizeof(char));
	sys_watchdog_reset();
#endif
#ifdef XBEE_ATCMD_PARAM_NT
	(void)xbee_cmd_simple(&xdev, "NT", XBEE_ATCMD_PARAM_NT);
#endif
#ifdef XBEE_ATCMD_PARAM_SC
	(void)xbee_cmd_simple(&xdev, "SC", XBEE_ATCMD_PARAM_SC);
#endif
#ifdef XBEE_ATCMD_PARAM_SD
	(void)xbee_cmd_simple(&xdev, "SD", XBEE_ATCMD_PARAM_SD);
#endif
#ifdef XBEE_ATCMD_PARAM_SM
	(void)xbee_cmd_simple(&xdev, "SM", XBEE_ATCMD_PARAM_SM);
#endif
#ifdef XBEE_ATCMD_PARAM_SN
	(void)xbee_cmd_simple(&xdev, "SN", XBEE_ATCMD_PARAM_SN);
#endif
#ifdef XBEE_ATCMD_PARAM_SP
	(void)xbee_cmd_simple(&xdev, "SP", XBEE_ATCMD_PARAM_SP);
#endif
#ifdef XBEE_ATCMD_PARAM_ST
	(void)xbee_cmd_simple(&xdev, "ST", XBEE_ATCMD_PARAM_ST);
#endif
#ifdef XBEE_ATCMD_PARAM_SO
#if defined(ENABLE_XBEE_HANDLE_MODEM_STATUS_FRAMES) && \
	(XBEE_ATCMD_PARAM_SM == 7 || XBEE_ATCMD_PARAM_SM == 8)
	/* Add SO bit 2 = Enable API sleep status messages */
	(void)xbee_cmd_simple(&xdev, "SO", XBEE_ATCMD_PARAM_SO | 0x04);
#else
	(void)xbee_cmd_simple(&xdev, "SO", XBEE_ATCMD_PARAM_SO);
#endif
#endif
#ifdef XBEE_ATCMD_PARAM_WH
	(void)xbee_cmd_simple(&xdev, "WH", XBEE_ATCMD_PARAM_WH);
#endif
#ifdef XBEE_ATCMD_PARAM_PO
	(void)xbee_cmd_simple(&xdev, "PO", XBEE_ATCMD_PARAM_PO);
#endif
#ifdef XBEE_ATCMD_PARAM_DD
	(void)xbee_cmd_simple(&xdev, "DD", XBEE_ATCMD_PARAM_DD);
#endif
#ifdef ENABLE_XBEE_HANDLE_RX_SIMPLE_FRAMES
	xbee_cmd_simple(&xdev, "AO", 0);
#elif defined(ENABLE_XBEE_HANDLE_RX_EXPLICIT_FRAMES)
	xbee_cmd_simple(&xdev, "AO", 1);
#elif defined(ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES)
	xbee_cmd_simple(&xdev, "AO", 3);
#else
	xbee_cmd_simple(&xdev, "AO", 0);
#endif
	sys_watchdog_reset();
}

/**
 *	@ingroup cpu_system
 *	@{
 *	@brief		Calls wpan_tick or xbee_dev_tick depending on the configuration
 *				of the ZigBee network.
 *				The callee will poll the underlaying hardware for new frames 
 *				that will be processed by the respective frame handlers.
 *				wpan_tick also time outs expired conversations.
 *				Needs to be called often enough to keep up with inbound bytes.
 *	@param[in]	xbee  XBee device to check for, and then dispatch, new frames.
 *	@retval		Variable	The value returned by xbee_dev_tick or wpan_tick, 
 *				The depending on the function called. Check that functions 
 *				for additional information.
 */
int sys_xbee_tick(void)
{
	xbee_cmd_tick();

#if defined(ENABLE_XBEE_HANDLE_RX_EXPLICIT_FRAMES) || \
	defined(ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES)
	return wpan_tick(&xdev.wpan_dev);
#else
	return xbee_dev_tick(&xdev);
#endif
}

/**
 *	@brief		Initializes the ZigBee network. Will initailize or not,
 *				depending on the configuration the APS-layer (endpoint/cluster).
 *	@param[in]	xbee  XBee device to configure.
 *	@retval		0 on success, error code otherwise.
 */
int sys_xbee_init(void)
{
	int status;

	xbee_params_init();
	
	/*
	 * Initialize the WPAN layer of the XBee device driver.  This layer enables
	 * endpoints and clusters, and is required for all ZigBee layers.
	 * The wpan is initialized even if endpoints and clusters are not used,
	 * because the wpan is used to transmit basic frames. In this case, we pass
	 * a null pointer as endpoint table.
	 */
	status = xbee_wpan_init(&xdev, EP_TABLE);
	if (status) {
		DBG(DBG_ERROR, ("Error %d initializing wpan.\n", status));
		return status;
	}

	/* Initialize the AT Command layer for this XBee device and have the
	 * driver query it for basic information (hardware version, firmware version,
	 * serial number, IEEE address, etc.)
	 */
	xbee_cmd_init_device(&xdev);
	DBG(DBG_INFO, ("Waiting for driver to query the XBee device...\n"));
	do {
		xbee_dev_tick(&xdev);
		sys_watchdog_reset();
		status = xbee_cmd_query_status(&xdev);
	} while (status == -EBUSY);
	
	if (status)
		DBG(DBG_ERROR, ("Error %d waiting for query to complete.\n", status));

#ifdef ENABLE_XBEE_HANDLE_ND_RESPONSE_FRAMES
	xbee_disc_add_node_id_handler(&xdev, &node_discovery_callback);
#endif
	return status;
}