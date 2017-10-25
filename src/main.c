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
 *   XPIN4 = <<UNUSED>>
 *   XPIN5 = special0 [Reset Pin]
 *   XPIN6 = special0 [RSSI PWM Pin]
 *   XPIN7 = LED [GPIO Pin]
 *   XPIN8 = special0 [BKGD Pin]
 *   XPIN9 = <<UNUSED>>
 *   XPIN10 = GND
 *   XPIN11 = <<UNUSED>>
 *   XPIN12 = <<UNUSED>>
 *   XPIN13 = <<UNUSED>>
 *   XPIN14 = VCC REF
 *   XPIN15 = special0 [Association Pin]
 *   XPIN16 = RELAY_2 [GPIO Pin]
 *   XPIN17 = RELAY [GPIO Pin]
 *   XPIN18 = <<UNUSED>>
 *   XPIN19 = LED_GROVE
 *   XPIN20 = special0 [Commissioning Pin]
 *
 ************************************/


#include <xbee_config.h>
#include <types.h>

// Custom profile and cluster implementation
#define CUSTOM_EP_NULL_CLUSTER    0x0000
#define CUSTOM_EP_CUSTOM_CLUSTER  0x0006

zcl_command_t zcl;

int trigger(void);
int custom_ep_rx_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);

const wpan_cluster_table_entry_t custom_ep_clusters[] = {
    {CUSTOM_EP_NULL_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_CUSTOM_CLUSTER, custom_ep_rx_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    WPAN_CLUST_ENTRY_LIST_END
};


int custom_ep_default_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  uint8_t *payload_pointer = envelope->payload;
  int i = 0;

  payload_pointer[envelope->length] = '\0'; /* Add Null-terminator for printing */
  printf("\nCUSTOM ENDPOINT'S DEFAULT CLUSTER HANDLER\n");
  printf("Received  : %s\n", payload_pointer);
  if(envelope->length > 0) {
    printf("Payload in Hex: ");
    for(i = 0; i < envelope->length; i++) {
      printf("%02X ", payload_pointer[i]);
    }
    printf("\n");
  }
  printf("Payload length: %02X\n", envelope->length);
  printf("Cluster ID:     %02X\n", envelope->cluster_id);
  printf("Profile ID:     %02X\n", envelope->profile_id);
  printf("Destin. EP:     %02X\n", envelope->dest_endpoint);
  printf("Source  EP:     %02X\n", envelope->source_endpoint);

  /* Let's try to debug the ZCL command */
  zcl_envelope_payload_dump(envelope);

  /* Let's try to respond */
  printf("\n\nBuilding ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    printf("OK!\n");
    printf("----------------------\n");
    printf("Frame Control: %02X\n", zcl.frame_control);
    printf("Command: %02X\n", zcl.command);
    printf("ZCL Payload length: %02X\n", zcl.length);
    hex_dump(zcl.zcl_payload, zcl.length, HEX_DUMP_FLAG_TAB);

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
          printf("Handling response for Application version request\n");
          *end_response++ = 0x01;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x20;
          *end_response++ = 0x00;

          printf("Response length: %02X\n", end_response - start_response);
          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            printf("Response sent successfully");
          }
        }
        else if(zclPayload[0] == 0x04 && zclPayload[1] == 0x00) {
          /* Device manufacturer request */
          printf("Handling response for Device manufacturer request\n");
          *end_response++ = 0x04;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x42;
          *end_response++ = 0x05; // Length of data
          *end_response++ = 'P';
          *end_response++ = 'X';
          *end_response++ = 'B';
          *end_response++ = 'e';
          *end_response++ = 'e';

          printf("Response length: %02X\n", end_response - start_response);
          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            printf("Response sent successfully");
          }
        }
        else if(zclPayload[0] == 0x05 && zclPayload[1] == 0x00) {
          /* Device developer request */
          printf("Handling response for Device developer request\n");
          *end_response++ = 0x05;
          *end_response++ = 0x00;
          *end_response++ = ZCL_STATUS_SUCCESS;
          *end_response++ = 0x42;
          *end_response++ = 0x07; // Length of data
          *end_response++ = 'T';
          *end_response++ = 'r';
          *end_response++ = 'i';
          *end_response++ = 'g';
          *end_response++ = 'g';
          *end_response++ = 'e';
          *end_response++ = 'r';

          printf("Response length: %02X\n", end_response - start_response);
          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            printf("Response sent successfully\n");
          }
        }
      }
    }
  }
  else {
    printf("Error!\n");
  }

  printf("=====================================================================\n");

  return 0;
}

int custom_ep_rx_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  uint8_t                 *start_response;
  uint8_t									*end_response;
  PACKED_STRUCT {
    zcl_header_response_t	header;
    uint8_t								buffer[20];
  } response;

  printf("\nCUSTOM ENDPOINT HANDLER\n");
  printf("=======================\n");
  printf("\n\nBuilding ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    printf("OK!\n");
    printf("----------------------\n");
    printf("Frame Control: %02X\n", zcl.frame_control);
    printf("Command: %02X\n", zcl.command);
    printf("ZCL Payload length: %02X\n", zcl.length);
    hex_dump(zcl.zcl_payload, zcl.length, HEX_DUMP_FLAG_TAB);
    printf("----------------------\n");
    zcl_envelope_payload_dump(envelope);
    // Handle all the commands

    if(ZCL_CMD_MATCH(&zcl.frame_control, GENERAL, CLIENT_TO_SERVER, PROFILE)) {
      if(zcl.command == ZCL_CMD_READ_ATTRIB) {
        // Profile command received (Read attribute) for switch state
        printf("Handling response for switch state read\n");

        response.header.command = ZCL_CMD_READ_ATTRIB_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl);
        end_response = response.buffer;

        *end_response++ = 0x00;
        *end_response++ = 0x00;
        *end_response++ = ZCL_STATUS_SUCCESS;
        *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
        *end_response++ = 0x00; // Always return off state

        printf("Response length: %02X\n", end_response - start_response);
        if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
          printf("Response sent successfully\n");
        }
      }
      else if(zcl.command == ZCL_CMD_CONFIGURE_REPORT) {
        // Profile command received (Configure report) for switch state
        printf("Handling response for configure report command\n");

        response.header.command = ZCL_CMD_CONFIGURE_REPORT_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl);
        end_response = response.buffer;

        *end_response++ = ZCL_STATUS_SUCCESS;
        *end_response++ = ZCL_DIRECTION_SEND;
        *end_response++ = 0x00;
        *end_response++ = 0x00;

        printf("Response length: %02X\n", end_response - start_response);
        if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
          printf("Response sent successfully\n");
        }
      }
      else {
        printf("Unhandled Profile command received\n");
      }
    }
    else if(ZCL_CMD_MATCH(&zcl.frame_control, GENERAL, CLIENT_TO_SERVER, CLUSTER)) {
      // Cluster command received
      printf("Handling switch change command\n");
      switch(zcl.command) {
        case 0x00:
          printf("Turn off command received\n");
          break;

        case 0x01:
          printf("Turn on command received, ");

          #ifdef PXBEE_TRIGGER_IGNORE_BROADCAST
            if(envelope->options & WPAN_ENVELOPE_BROADCAST_ADDR) {
              printf("ignoring due to command sent as broadcast!\n");
            }
            else {
              printf("executing!\n");
              trigger();
            }
          #else
            printf("executing!\n");
            trigger();
          #endif

          /* We NEED to report back the On state before going back to Off state.
           * if we don't, the SmartThings GUI will stay in "TurningOn" state
           */
          response.header.command = ZCL_CMD_REPORT_ATTRIB;
          response.header.sequence++;
          response.header.u.std.frame_control = ZCL_FRAME_TYPE_PROFILE | ZCL_FRAME_SERVER_TO_CLIENT;

          start_response = (uint8_t *)&response + 2;
          end_response = response.buffer;

          *end_response++ = 0x00;
          *end_response++ = 0x00;
          *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
          *end_response++ = 0x01; // Report On state

          printf("Response length: %02X\n", end_response - start_response);
          if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
            printf("On response sent successfully\n");
          }
          break;

        case 0x02:
          printf("Toggle command received\n");
          break;

        default:
          printf("Unknown command received\n");
          break;
      }

      delay_ticks(HZ); // wait for 1 second prior to reporting Off state

      response.header.command = ZCL_CMD_REPORT_ATTRIB;
      response.header.sequence++;
      response.header.u.std.frame_control = ZCL_FRAME_TYPE_PROFILE | ZCL_FRAME_SERVER_TO_CLIENT;

      start_response = (uint8_t *)&response + 2;
      end_response = response.buffer;

      *end_response++ = 0x00;
      *end_response++ = 0x00;
      *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;
      *end_response++ = 0x00; // Report Off state

      printf("Response length: %02X\n", end_response - start_response);
      if(zcl_send_response(&zcl, start_response, end_response - start_response) == 0) {
        printf("Off response sent successfully\n");
      }

    }
  }
  else {
    printf("Error!\n");
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
		printf( "= 0x%0*" PRIX32 " (%" PRIu32 ")\n", length * 2, response->value,
			response->value);
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

  puts("Received Frame");
  puts("---------------------");
  sys_watchdog_reset();
  printf("Cluster ID          : %u\n", envelope->cluster_id);
  printf("Profile ID          : %u\n", envelope->profile_id);
  printf("Source Endpoint     : %u\n", envelope->source_endpoint);
  printf("Destination Endpoint: %u\n", envelope->dest_endpoint);
  printf("Source              : %s\n", addr64_format(addrbuf, &envelope->ieee_address));
  printf("Network             : %04x\n", be16toh(envelope->network_address));
  printf("Options             : %u\n", envelope->options);
  printf("Data length         : %u\n", envelope->length);
  puts("---------------------");
  puts(" P  A  Y  L  O  A  D ");
  puts("---------------------");
  sys_watchdog_reset();
  dump(envelope->payload, envelope->length);
  puts("\n");

  return 0;
}
#endif

#if defined(RTC_ENABLE_PERIODIC_TASK)
void rtc_periodic_task(void)
{
  gpio_set(LED, !gpio_get(LED));
  //gpio_set(RELAY, !gpio_get(LED));
  //gpio_set(RELAY_2, gpio_get(RELAY));
}
#endif

#ifdef relayTimer_irq
void relayTimer_irq(void)
{
  puts("EVENT TRIGGERED: relayTimer_irq");
  gpio_set(RELAY,   0);
  gpio_set(RELAY_2, 0);
}
#endif

/* Global for the ZDO/ZCL state keeping */
wpan_ep_state_t zdo_ep_state;
wpan_ep_state_t custom_ha_ep_state;

void main(void)
{
  uint8_t option;

  sys_hw_init();
  sys_xbee_init();
  sys_app_banner();

  gpio_set(XPIN_19, 0);
  gpio_set(XPIN_18, 0);
  gpio_set(XPIN_16, 0);
  gpio_set(XPIN_11, 0);
  gpio_set(XPIN_7,  0);
  gpio_set(XPIN_4,  0);

  // Drive special pins low
  gpio_set(XPIN_15, 0);
  gpio_set(XPIN_20, 0);
  gpio_set(XPIN_8,  0);
  gpio_set(XPIN_6,  0);

  gpio_set(RELAY,           0);
  gpio_set(LED_GROVE,       0);
  gpio_set(PWR_CNTRL_RELAY, 0);
  gpio_set(PWR_CNTRL_LED,   0);

  printf("> ");

  for (;;) {

    /* Interactive menu for action control */
    if(uart_bytes_in_rx_buffer() > 0) {
      uart_read(&option, 1);
      printf("Got char: %u\n", option);
      if(option == 49) { /* 1 */
        int16_t request;
        
        printf("\nRequesting Operating PAN ID (OP)\n");
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
        printf("\n Setting additional radio settings: ZS ");
        xbee_cmd_simple(&xdev, "ZS", XBEE_PARAM_ZS);
        printf("NJ ");
        xbee_cmd_simple(&xdev, "NJ", XBEE_PARAM_NJ);
        printf("NH ");
        xbee_cmd_simple(&xdev, "NH", XBEE_PARAM_NH);
        printf("NO ");
        xbee_cmd_simple(&xdev, "NO", XBEE_PARAM_NO);
        printf("EE ");
        xbee_cmd_simple(&xdev, "EE", XBEE_PARAM_EE);
        printf("EO ");
        xbee_cmd_simple(&xdev, "EO", XBEE_PARAM_EO);
        printf("AP ");
        xbee_cmd_simple(&xdev, "AP", XBEE_PARAM_AP);
        printf("KY ");
        xbee_cmd_execute(&xdev, "KY", XBEE_PARAM_KY, (sizeof(XBEE_PARAM_KY) - 1) / sizeof(char));
        printf("WR ");
        xbee_cmd_execute(&xdev, "WR", NULL, 0);
        printf("Done!\n\n");
      }
      else if(option == 48) { /* 0 */
        printf("\n Resetting Network\n");
        xbee_cmd_simple(&xdev, "NR", 0);
      }
      else if(option == 98 || option == 66) { /* b || B */
        sys_app_banner();
      }
      else if(option == 104 || option == 72) { /* h || H */

      }
      else {
        puts("-------------------------------------");
        puts("|              H E L P              |");
        puts("-------------------------------------");
        puts("[1] - Print Operating PAN ID");
        puts("[2] - Init additional radio settings");
        puts("[0] - Local network reset");
        puts("");
      }
      printf("> ");
    }
    /* End of interactive menu */

    sys_watchdog_reset();
    sys_xbee_tick();
  }
}

int trigger(void) {
  printf("Trigger!\n");
  gpio_set(RELAY,   0);
  gpio_set(RELAY_2, 0);

  if(timer_config(relayTimer, TRUE, ONE_SHOT, 125000) == 0) {
    gpio_set(RELAY,   1);
    gpio_set(RELAY_2, 1);
    return 0;
  }
  else {
    return -EINVAL;
  }
}
