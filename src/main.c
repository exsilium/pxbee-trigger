/***** XBEE APPLICATION PROJECT *****
 *
 * Auto-generated header with information about the
 * relation between the XBee module pins and the
 * project components.
 *
 ************ XBEE LAYOUT ***********
 *
 * This layout represents the XBee ZB (S2B) module
 * selected for the project with its pin distribution:
 *               _________________
 *              /     ________    \
 *             /     |   __   |    \
 *            /      | //  \\ |     \
 *   XPIN1  -|       | \\__// |      |- XPIN20
 *   XPIN2  -|       |________|      |- XPIN19
 *   XPIN3  -|                       |- XPIN18
 *   XPIN4  -| ===================== |- XPIN17
 *   XPIN5  -| #   # ####  #### #### |- XPIN16
 *   XPIN6  -|  # #  #   # #    #    |- XPIN15
 *   XPIN7  -|   #   ####  ###  ###  |- XPIN14
 *   XPIN8  -|  # #  #   # #    #    |- XPIN13
 *   XPIN9  -| #   # ####  #### #### |- XPIN12
 *   XPIN10 -| ===================== |- XPIN11
 *           |_______________________|
 *
 ************ PINS LEGEND ***********
 *
 * The following list displays all the XBee Module pins
 * with the project component which is using each one:
 *
 *   XPIN1 = VCC
 *   XPIN2 = uart0 [TX Pin]
 *   XPIN3 = uart0 [RX Pin]
 *   XPIN4 = RELAY_3 [GPIO Pin]
 *   XPIN5 = special0 [Reset Pin]
 *   XPIN6 = RELAY_2 [GPIO Pin] (Disabled: special0 [RSSI PWM Pin])
 *   XPIN7 = RELAY_1
 *   XPIN8 = special0 [BKGD Pin]
 *   XPIN9 = <<UNUSED>>
 *   XPIN10 = GND
 *   XPIN11 = RELAY_4
 *   XPIN12 = <<UNUSED>>
 *   XPIN13 = <<UNUSED>>
 *   XPIN14 = VCC REF
 *   XPIN15 = special0 [Association Pin]
 *   XPIN16 = <<UNUSED>>
 *   XPIN17 = <<UNUSED>>
 *   XPIN18 = Status pin 1 [IRQ Pin] (Pulled UP)
 *   XPIN19 = Status pin 2 [IRQ Pin] (Pulled UP)
 *   XPIN20 = <<UNUSED>>
 *
 ************************************/

#include <xbee_config.h>
#include <types.h>
#include <util.h>

// Custom profile and cluster implementation
#define CUSTOM_EP_BASIC_CLUSTER    0x0000
#define CUSTOM_EP_IDENTIFY_CLUSTER 0x0003 /* Not implemented */
#define CUSTOM_EP_GROUPS_CLUSTER   0x0004 /* Not implemented */
#define CUSTOM_EP_SCENES_CLUSTER   0x0005 /* Not implemented */
#define CUSTOM_EP_ONOFF_CLUSTER    0x0006
#define CUSTOM_EP_BIN_IN_CLUSTER   0x000f /* To be implemented? - custom_ep_rx_binary_in_cluster */

zcl_command_t zcl;

/* Global for the ZDO/ZCL state keeping */
wpan_ep_state_t zdo_ep_state;
wpan_ep_state_t custom_ha_ep_state;
wpan_ep_state_t custom_ha_ep2_state;
wpan_ep_state_t custom_ha_ep3_state;
wpan_ep_state_t custom_ha_ep4_state;

/* STATUS_* Pins */
#define CONTACT_OPEN   1
#define CONTACT_CLOSED 0
bool_t status_1_TimerSet = FALSE;
bool_t status_2_TimerSet = FALSE;
bool_t status_1 = CONTACT_OPEN;
bool_t status_2 = CONTACT_OPEN;

int trigger(void);
int custom_ep_rx_on_off_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);
int custom_ep_rx_notimpl_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);
int custom_ep_rx_binary_in_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);

const wpan_cluster_table_entry_t custom_ep_clusters[] = {
    {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_IDENTIFY_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_GROUPS_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_SCENES_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_BIN_IN_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    WPAN_CLUST_ENTRY_LIST_END
};

const wpan_cluster_table_entry_t custom_ep2_clusters[] = {
  {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
  {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
  WPAN_CLUST_ENTRY_LIST_END
};

const wpan_cluster_table_entry_t custom_ep3_clusters[] = {
  {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
  {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
  WPAN_CLUST_ENTRY_LIST_END
};

const wpan_cluster_table_entry_t custom_ep4_clusters[] = {
  {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
  {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
  WPAN_CLUST_ENTRY_LIST_END
};

int custom_ep_basic_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  puts("\n=== CUSTOM ENDPOINT'S DEFAULT CLUSTER HANDLER ===");
  puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    wpan_envelope_dump(envelope);

    if(ZCL_CMD_MATCH( &zcl.frame_control, GENERAL, CLIENT_TO_SERVER, PROFILE)) {
      if(zcl.command == ZCL_CMD_READ_ATTRIB && zcl.length == 2) {
        const char FAR *zclPayload = zcl.zcl_payload;
        uint8_t                 *start_response;
        uint8_t									*end_response;
        PACKED_STRUCT {
          zcl_header_response_t	header;
          uint8_t								buffer[20];
        } response;

        response.header.command = ZCL_CMD_READ_ATTRIB_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl);
        end_response = response.buffer;

        if(zclPayload[0] == 0x01 && zclPayload[1] == 0x00) {
          /* Application version request */
          puts("Handling response for Application version request");
          *end_response++ = 0x01;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x20;
          *end_response++ = 0x00;

          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            puts("Response sent successfully");
          }
        }
        else if(zclPayload[0] == 0x04 && zclPayload[1] == 0x00) {
          /* Device manufacturer request */
          puts("Handling response for Device manufacturer request");
          *end_response++ = 0x04;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x42;
          end_response = appendStringChar(end_response, ZCL_MANUFACTURER);

          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            puts("Response sent successfully");
          }
        }
        else if(zclPayload[0] == 0x05 && zclPayload[1] == 0x00) {
          /* Device developer request */
          puts("Handling response for Device developer request");
          *end_response++ = 0x05;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x42;
          end_response = appendStringChar(end_response, ZCL_MODEL);

          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            puts("Response sent successfully");
          }
        }
      }
    }
  }
  else {
    puts("Error!\n");
  }

  puts("=====================================================================\n");

  return 0;
}

int custom_ep_rx_on_off_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  uint8_t                 *start_response;
  uint8_t									*end_response;
  PACKED_STRUCT {
    zcl_header_response_t	header;
    uint8_t								buffer[20];
  } response;

  puts("\n=== CUSTOM ENDPOINT HANDLER - ON OFF CLUSTER ===");
  puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    wpan_envelope_dump(envelope);
    puts("----------------------");
    // Handle all the commands

    if(ZCL_CMD_MATCH(&zcl.frame_control, GENERAL, CLIENT_TO_SERVER, PROFILE)) {
      if(zcl.command == ZCL_CMD_READ_ATTRIB) {
        // Profile command received (Read attribute) for switch state
        puts("Handling response for switch state read");

        response.header.command = ZCL_CMD_READ_ATTRIB_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl);
        end_response = response.buffer;

        *end_response++ = 0x00;
        *end_response++ = 0x00;
        *end_response++ = ZCL_STATUS_SUCCESS;
        *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
        *end_response++ = 0x00; // Always return off state

        if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
          puts("Response sent successfully\n");
        }
      }
      else if(zcl.command == ZCL_CMD_CONFIGURE_REPORT) {
        // Profile command received (Configure report) for switch state
        puts("Handling response for configure report command");

        response.header.command = ZCL_CMD_CONFIGURE_REPORT_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl);
        end_response = response.buffer;

        *end_response++ = ZCL_STATUS_SUCCESS;
        *end_response++ = ZCL_DIRECTION_SEND;
        *end_response++ = 0x00;
        *end_response++ = 0x00;

        if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
          puts("Response sent successfully\n");
        }
      }
      else {
        puts("Unhandled Profile command received");
      }
    }
    else if(ZCL_CMD_MATCH(&zcl.frame_control, GENERAL, CLIENT_TO_SERVER, CLUSTER)) {
      // Cluster command received
      puts("Handling switch change command");
      switch(zcl.command) {
        case 0x00:
          puts("Turn off command received");
          break;

        case 0x01:
          puts("Turn on command received, ");

          #ifdef PXBEE_TRIGGER_IGNORE_BROADCAST
            if(envelope->options & WPAN_ENVELOPE_BROADCAST_ADDR) {
              puts("ignoring due to command sent as broadcast!");
            }
            else {
              puts("executing!");
              trigger();
            }
          #else
            puts("executing!");
            trigger();
          #endif

          /* We NEED to report back the On state before going back to Off state.
           * if we don't, the SmartThings GUI will stay in "TurningOn" state
           */
          response.header.command = ZCL_CMD_REPORT_ATTRIB;
          response.header.sequence++;
          response.header.u.std.frame_control = ZCL_FRAME_TYPE_PROFILE | ZCL_FRAME_SERVER_TO_CLIENT | ZCL_FRAME_MFG_SPECIFIC;

          start_response = (uint8_t *)&response + 2;
          end_response = response.buffer;

          *end_response++ = 0x00;
          *end_response++ = 0x00;
          *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
          *end_response++ = 0x01; // Report On state

          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            puts("On response sent successfully");
          }
          break;

        case 0x02:
          puts("Toggle command received");
          break;

        default:
          puts("Unknown command received");
          break;
      }

      delay_ticks(HZ); // wait for 1 second prior to reporting Off state

      response.header.command = ZCL_CMD_REPORT_ATTRIB;
      response.header.sequence++;
      response.header.u.std.frame_control = ZCL_FRAME_TYPE_PROFILE | ZCL_FRAME_SERVER_TO_CLIENT | ZCL_FRAME_MFG_SPECIFIC;

      start_response = (uint8_t *)&response + 2;
      end_response = response.buffer;

      *end_response++ = 0x00;
      *end_response++ = 0x00;
      *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
      *end_response++ = 0x00; // Report Off state

      if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
        puts("Off response sent successfully\n");
      }

    }
  }
  else {
    puts("Error!");
  }

  return 0;
}

int custom_ep_rx_notimpl_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  uint8_t                 *start_response;
  uint8_t									*end_response;
  PACKED_STRUCT {
    zcl_header_response_t	header;
    uint8_t								buffer[20];
  } response;

  puts("\n=== NOTIMPL CLUSTER HANDLER ===");
  puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    wpan_envelope_dump(envelope);
    puts("----------------------");
  }
  return 0;
}
// END: Custom profile and cluster implementation

/* Callback function for XBee commands */
int xbee_cmd_callback( const xbee_cmd_response_t FAR *response)
{
	bool_t printable;
	uint_fast8_t length, i;
	uint8_t status;
	const uint8_t FAR *p;

	printf( "AT%.*" PRIsFAR " ", 2, response->command.str);

	if (response->flags & XBEE_CMD_RESP_FLAG_TIMEOUT)
	{
		puts( "(timed out)");
		return XBEE_ATCMD_DONE;
	}

	status = response->flags & XBEE_CMD_RESP_MASK_STATUS;
	if (status != XBEE_AT_RESP_SUCCESS)
	{
		printf( "(error: %s)\n",
			(status == XBEE_AT_RESP_ERROR) ? "general" :
			(status == XBEE_AT_RESP_BAD_COMMAND) ? "bad command" :
			(status == XBEE_AT_RESP_BAD_PARAMETER) ? "bad parameter" :
			(status == XBEE_AT_RESP_TX_FAIL) ? "Tx failure" :
			"unknown error");
		return XBEE_ATCMD_DONE;
	}

	length = response->value_length;
	if (! length)		// command sent successfully, no value to report
	{
		puts( "(success)");
		return XBEE_ATCMD_DONE;
	}

	// check to see if we can print the value out as a string
	printable = 1;
	p = response->value_bytes;
	for (i = length; i; ++p, --i)
	{
		if (! isprint( *p))
		{
			printable = 0;
			break;
		}
	}

	if (printable)
	{
		printf( "= \"%.*" PRIsFAR "\" ", length, response->value_bytes);
	}
	if (length <= 4)
	{
		// format hex string with (2 * number of bytes in value) leading zeros
		printf( "= 0x%0*" PRIX32 " (%" PRIu32 ")\n", length * 2, response->value, response->value);
	}
	else
	{
		printf( "= %d bytes:\n", length);
		hex_dump( response->value_bytes, length, HEX_DUMP_FLAG_TAB);
	}

	return XBEE_ATCMD_DONE;
}
// END: Callback functions for XBee commands

#ifdef ENABLE_XBEE_HANDLE_RX
int xbee_transparent_rx(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  char addrbuf[ADDR64_STRING_LENGTH];

  puts("---Received Frame----");
  sys_watchdog_reset();
  printf("Cluster ID          : %u\n", envelope->cluster_id);
  printf("Profile ID          : %u\n", envelope->profile_id);
  printf("Source Endpoint     : %u\n", envelope->source_endpoint);
  printf("Destination Endpoint: %u\n", envelope->dest_endpoint);
  printf("Source              : %s\n", addr64_format(addrbuf, &envelope->ieee_address));
  printf("Network             : %04x\n", be16toh(envelope->network_address));
  printf("Options             : %u\n", envelope->options);
  printf("Data length         : %u\n", envelope->length);
  puts("-P  A  Y  L  O  A  D-");
  sys_watchdog_reset();
  dump(envelope->payload, envelope->length);
  puts("\n");

  return 0;
}
#endif

#if defined(RTC_ENABLE_PERIODIC_TASK)
void rtc_periodic_task(void)
{
  return;
}
#endif

#ifdef relayTimer_irq
void relayTimer_irq(void)
{
  puts("EVENT TRIGGERED: relayTimer_irq");
  gpio_set(RELAY_1,   0);
}
#endif

#ifdef status_1_CheckTimer_irq
void status_1_CheckTimer_irq(void) {
  if (gpio_get(STATUS_1)) {
    /* State has changed back, stop the check timer */
    status_1 = CONTACT_OPEN;
    status_1_TimerSet = FALSE;
    timer_enable(status_1_CheckTimer, FALSE);
    puts("EVENT TRIGGERED: status_1_CheckTimer_irq (CONTACT_OPEN)");
  }
}
#endif

#ifdef status_2_CheckTimer_irq
void status_2_CheckTimer_irq(void) {
  if (gpio_get(STATUS_2)) {
    /* State has changed back, stop the check timer */
    status_2 = CONTACT_OPEN;
    status_2_TimerSet = FALSE;
    timer_enable(status_2_CheckTimer, FALSE);
    puts("EVENT TRIGGERED: status_2_CheckTimer_irq (CONTACT_OPEN)");
  }
}
#endif

#ifdef status_1_irq
void status_1_irq(void)
{
  if(!status_1_TimerSet) { 
    if(timer_config(status_1_CheckTimer, TRUE, PERIODIC, 500000) == 0) {
      status_1_TimerSet = TRUE;
      status_1 = CONTACT_CLOSED;
    }
    puts("EVENT TRIGGERED: status_1_irq (CONTACT_CLOSED)");
  }
}
#endif

#ifdef status_2_irq
void status_2_irq(void)
{
  if(!status_2_TimerSet) { 
    if(timer_config(status_2_CheckTimer, TRUE, PERIODIC, 500000) == 0) {
      status_2_TimerSet = TRUE;
      status_2 = CONTACT_CLOSED;
    }
    puts("EVENT TRIGGERED: status_2_irq (CONTACT_CLOSED)");
  }
}
#endif

void main(void)
{
  uint8_t option;

  sys_hw_init();
  sys_xbee_init();
  sys_app_banner();

  // Drive special pins low
  gpio_set(XPIN_15, 0);
  gpio_set(XPIN_8,  0);
  gpio_set(XPIN_6,  0);

  gpio_set(RELAY_1, 0);
  gpio_set(RELAY_2, 0);
  gpio_set(RELAY_3, 0);
  gpio_set(RELAY_4, 0);

  /* During startup, we should check the STATUS_* pins in case they have already been driven low (CONTACT_CLOSED) */
  if (!gpio_get(STATUS_1)) {
    status_1 = CONTACT_CLOSED;
    puts("STARTUP check STATUS_1 - CONTACT_CLOSED");
  }
  if (!gpio_get(STATUS_2)) {
    status_2 = CONTACT_CLOSED;
    puts("STARTUP check STATUS_2 - CONTACT_CLOSED");
  }

  fputs("> ", stdout);

  for (;;) {

    /* Interactive menu for action control */
    if(uart_bytes_in_rx_buffer() > 0) {
      uart_read(&option, 1);
      printf("Got char: %u\n", option);
      if(option == 49) { /* 1 */
        int16_t request;
        
        puts("\nRequesting Operating PAN ID (OP)");
        request = xbee_cmd_create(&xdev, "OP");
        if (request < 0) {
		      printf( "Error creating request: %d (%" PRIsFAR ") \n", request, strerror( -request));
	      }
	      else  {
	        xbee_cmd_set_callback(request, xbee_cmd_callback, NULL);
	        xbee_cmd_send(request);
	      }
      }
      else if(option == 50) { /* 2 */
        // Additionnal XBee settings
        fputs("\n Setting additional radio settings: ZS ", stdout);
        xbee_cmd_simple(&xdev, "ZS", XBEE_PARAM_ZS);
        fputs("NJ ", stdout);
        xbee_cmd_simple(&xdev, "NJ", XBEE_PARAM_NJ);
        fputs("NH ", stdout);
        xbee_cmd_simple(&xdev, "NH", XBEE_PARAM_NH);
        fputs("NO ", stdout);
        xbee_cmd_simple(&xdev, "NO", XBEE_PARAM_NO);
        fputs("EE ", stdout);
        xbee_cmd_simple(&xdev, "EE", XBEE_PARAM_EE);
        fputs("EO ", stdout);
        xbee_cmd_simple(&xdev, "EO", XBEE_PARAM_EO);
        fputs("AP ", stdout);
        xbee_cmd_simple(&xdev, "AP", XBEE_PARAM_AP);
        fputs("KY ", stdout);
        xbee_cmd_execute(&xdev, "KY", XBEE_PARAM_KY, (sizeof(XBEE_PARAM_KY) - 1) / sizeof(char));
        fputs("WR ", stdout);
        xbee_cmd_execute(&xdev, "WR", NULL, 0);
        puts("Done!\n");
      }
      else if(option == 48) { /* 0 */
        puts("\n Resetting Network");
        xbee_cmd_simple(&xdev, "NR", 0);
      }
      else if(option == 98 || option == 66) { /* b || B */
        sys_app_banner();
      }
      else if(option == 104 || option == 72) { /* h || H */

      }
      else {
        puts("---------------H E L P---------------\n[1] - Print Operating PAN ID\n[2] - Init additional radio settings\n[0] - Local network reset\n");
      }
      fputs("> ", stdout);
    }
    /* End of interactive menu */

    sys_watchdog_reset();
    sys_xbee_tick();
  }
}

int trigger(void) {
  puts("Trigger!");
  gpio_set(RELAY_1, 0);

  if(timer_config(relayTimer, TRUE, ONE_SHOT, 125000) == 0) {
    gpio_set(RELAY_1, 1);
    return 0;
  }
  else {
    return -EINVAL;
  }
}
