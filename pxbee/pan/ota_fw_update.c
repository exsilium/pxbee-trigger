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

#include <system.h>
#include <xbee/ota_server.h>

#ifndef TRIGGER_FW_UPDATE
#define TRIGGER_FW_UPDATE	"\0" /* default single null byte password */
#endif

void start_ota_fw_update(addr64 *host_address, app_rst_casuses_t reason)
{
	/* Declared at system.c as "volatile uint8_t haddr_64[8]  @0x20E;" */
	extern uint8_t haddr_64[8];
	/* Commenting following line will prevent previously configured parameters 
	 * (ID, NI ...) from being saved into radio flash. Its done because it helps
	 * to recover remotely this device in case it loses power during the update.
	 */
	xbee_cmd_simple(&xdev, "WR", 1); 
	/* Copy source address to shared memory */
	memcpy(&haddr_64, host_address, sizeof(addr64));
	/* Exit to the bootloader */
	sys_reset(reason);		
}

const char *xbee_update_firmware_ota( const wpan_envelope_t FAR *envelope,
	void FAR *context)
{
	app_rst_casuses_t reason;
	char addrbuf[ADDR64_STRING_LENGTH];
	
	if (envelope->length != sizeof(TRIGGER_FW_UPDATE) - 1 || 
		memcmp(TRIGGER_FW_UPDATE, envelope->payload,
				sizeof(TRIGGER_FW_UPDATE) - 1)) {
#ifndef SILENT_OTA_UPDATE
		printf("bad password\n");
#endif
		return "bad password";
	}
#ifndef SILENT_OTA_UPDATE
	printf("\nPassword correct. Starting OTA update with XMODEM");
	printf("\nHost address: %s", addr64_format(addrbuf,
								 &envelope->ieee_address));
	printf("\nHost may start transfer when receiving 'C's");
#endif
	reason = (envelope->options & WPAN_ENVELOPE_RX_APS_ENCRYPT) ? 
			  APP_CAUSE_FIRMWARE_UPDATE_APS : APP_CAUSE_FIRMWARE_UPDATE;
	start_ota_fw_update(&envelope->ieee_address, reason);
			
	return NULL;
}