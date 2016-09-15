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

#ifndef __PAN_INIT_H_
#define __PAN_INIT_H_

#include <xbee/device.h>	/* for XBEE_FRAME_HANDLE_TX_STATUS */
#include <xbee/atcmd.h>
#include <xbee/discovery.h>
#define CHECK_NODETYPE(req_nodetype) (!(xdev.firmware_version & XBEE_NODETYPE_MASK) || \
		((unsigned)(xdev.firmware_version & XBEE_NODETYPE_MASK) == req_nodetype))

#if defined(ENABLE_XBEE_HANDLE_RX) || defined(ENABLE_OTA_UPDATE) || \
	defined(ENABLE_XBEE_HANDLE_ND_RESPONSE_FRAMES)
#ifdef CONFIG_XBEE_ZB
#define ENABLE_XBEE_HANDLE_RX_ZCL_FRAMES
#else
#define	ENABLE_XBEE_HANDLE_RX_EXPLICIT_FRAMES
#endif /* CONFIG_XBEE_ZB */
#endif
int sys_xbee_init(void);
int sys_xbee_tick(void);
void node_discovery_callback(xbee_dev_t *xbee, const xbee_node_id_t *rec);

extern xbee_dev_t xdev;

#endif /* __PAN_INIT_H_ */
