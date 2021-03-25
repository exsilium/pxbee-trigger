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
zcl_command_t zcl_onoff;
zcl_command_t zcl_binin;

/* Global for the ZDO/ZCL state keeping */
wpan_ep_state_t zdo_ep_state;
wpan_ep_state_t custom_ha_ep_state;
wpan_ep_state_t custom_ha_ep2_state;
wpan_ep_state_t custom_ha_ep3_state;
wpan_ep_state_t custom_ha_ep4_state;

/* STATUS_* Pins */
bool_t status_1_TimerSet = FALSE;
bool_t status_1_InterruptFree = TRUE;
bool_t status_1_SendStatus = TRUE;
bool_t status_2_TimerSet = FALSE;
bool_t status_2_InterruptFree = TRUE;
bool_t status_2_SendStatus = TRUE;

int trigger(uint8_t endpoint);
int custom_ep_rx_on_off_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);
int custom_ep_rx_notimpl_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);
int custom_ep_rx_binary_input_cluster(const wpan_envelope_t FAR *envelope, void FAR *context);

const wpan_cluster_table_entry_t custom_ep_clusters[] = {
    {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_IDENTIFY_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_GROUPS_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_SCENES_CLUSTER, custom_ep_rx_notimpl_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    {CUSTOM_EP_BIN_IN_CLUSTER, custom_ep_rx_binary_input_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
    WPAN_CLUST_ENTRY_LIST_END
};

const wpan_cluster_table_entry_t custom_ep2_clusters[] = {
  {CUSTOM_EP_BASIC_CLUSTER, NULL, NULL, WPAN_CLUST_FLAG_INPUT},
  {CUSTOM_EP_ONOFF_CLUSTER, custom_ep_rx_on_off_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
  {CUSTOM_EP_BIN_IN_CLUSTER, custom_ep_rx_binary_input_cluster, NULL, WPAN_CLUST_FLAG_INPUT},
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

typedef struct zcl_binary_input_attr_t {
  zcl_attribute_base_t		active_text;
  zcl_attribute_base_t		description;
  zcl_attribute_base_t		inactive_text;
  zcl_attribute_base_t		out_of_service;
  zcl_attribute_base_t		present_value;
  uint16_t						end_of_list;
} zcl_binary_input_attr_t;
// Variable data for ZCL_CLUST_BINARY_IN
typedef struct zcl_binary_input_t {
  bool_t		present_value;
  bool_t		out_of_service;
} zcl_binary_input_t;

#define ZCL_BININ_ATTR_ACTIVE_TEXT    0x0004	// CHAR STRING
#define ZCL_BININ_ATTR_DESCRIPTION    0x001C	// CHAR STRING
#define ZCL_BININ_ATTR_INACTIVE_TEXT  0x002E	// CHAR STRING
#define ZCL_BININ_ATTR_OUT_OF_SERVICE 0x0051	// BOOLEAN
#define ZCL_BININ_ATTR_PRESENT_VALUE  0x0055	// BOOLEAN

zcl_binary_input_t binaryInput = { ZCL_BOOL_FALSE, ZCL_BOOL_FALSE };
const zcl_binary_input_attr_t FAR zcl_binin_attributes = {
		{	ZCL_BININ_ATTR_ACTIVE_TEXT,	   ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn ON" },
		{	ZCL_BININ_ATTR_DESCRIPTION,	   ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn Description" },
		{	ZCL_BININ_ATTR_INACTIVE_TEXT,	 ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn OFF" },
		{	ZCL_BININ_ATTR_OUT_OF_SERVICE, ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_LOGICAL_BOOLEAN, &binaryInput.out_of_service },
		{	ZCL_BININ_ATTR_PRESENT_VALUE,	 ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_LOGICAL_BOOLEAN, &binaryInput.present_value	},
		ZCL_ATTRIBUTE_END_OF_LIST };
const zcl_attribute_tree_t FAR zcl_binin_attribute_tree[] =										\
		{ { ZCL_MFG_NONE, &zcl_binin_attributes.active_text, NULL } };

zcl_binary_input_t binaryInput2 = { ZCL_BOOL_FALSE, ZCL_BOOL_FALSE };
const zcl_binary_input_attr_t FAR zcl_binin_attributes2 = {
  {	ZCL_BININ_ATTR_ACTIVE_TEXT,	   ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn ON" },
  {	ZCL_BININ_ATTR_DESCRIPTION,	   ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn Description" },
  {	ZCL_BININ_ATTR_INACTIVE_TEXT,	 ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_STRING_CHAR,	"BinIn OFF" },
  {	ZCL_BININ_ATTR_OUT_OF_SERVICE, ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_LOGICAL_BOOLEAN, &binaryInput2.out_of_service },
  {	ZCL_BININ_ATTR_PRESENT_VALUE,	 ZCL_ATTRIB_FLAG_READONLY, ZCL_TYPE_LOGICAL_BOOLEAN, &binaryInput2.present_value	},
  ZCL_ATTRIBUTE_END_OF_LIST };
const zcl_attribute_tree_t FAR zcl_binin_attribute_tree2[] =										\
		{ { ZCL_MFG_NONE, &zcl_binin_attributes2.active_text, NULL } };

void send_status(const zcl_binary_input_attr_t *zcl_binin_attr, const wpan_endpoint_table_entry_t *source_endpoint);

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
  //wpan_envelope_dump(envelope);
  //puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    //zcl_command_dump(&zcl);
    //puts("----------------------");
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
              trigger(zcl.envelope->dest_endpoint);
            }
          #else
            puts("executing!");
            trigger(zcl.envelope->dest_endpoint);
          #endif

          /* We NEED to report back the On state before going back to Off state.
           * if we don't, the SmartThings GUI will stay in "TurningOn" state
           */
          response.header.command = ZCL_CMD_REPORT_ATTRIB;
          response.header.sequence++;

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

int custom_ep_rx_binary_input_cluster(const wpan_envelope_t FAR *envelope, void FAR *context)
{
  uint8_t                 *start_response;
  uint8_t									*end_response;
  PACKED_STRUCT {
    zcl_header_response_t	header;
    uint8_t								buffer[20];
  } response;

  puts("\n=== CUSTOM ENDPOINT HANDLER - BINARY INPUT CLUSTER ===");
  //wpan_envelope_dump(envelope);
  //puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl_binin, envelope, context) == 0) {
    //zcl_command_dump(&zcl_binin);
    //puts("----------------------");
    // Handle all the commands

    if (ZCL_CMD_MATCH(&zcl_binin.frame_control, GENERAL, CLIENT_TO_SERVER, PROFILE))
    {
      if (zcl_binin.command == ZCL_CMD_READ_ATTRIB)
      {
        // Profile command received (Read attribute) for switch state
        puts("Handling response for switch state read");

        response.header.command = ZCL_CMD_READ_ATTRIB_RESP;
        start_response = (uint8_t *)&response + zcl_build_header(&response.header, &zcl_binin);
        end_response = response.buffer;

        *end_response++ = 0x55;
        *end_response++ = 0x00;
        *end_response++ = ZCL_STATUS_SUCCESS;
        *end_response++ = ZCL_TYPE_LOGICAL_BOOLEAN;

        if(zcl_binin.envelope->dest_endpoint == CUSTOM_ENDPOINT) {
          *end_response++ = binaryInput.present_value;
        }
        else if(zcl_binin.envelope->dest_endpoint == CUSTOM_ENDPOINT2) {
          *end_response++ = binaryInput2.present_value;
        }
        else {
          *end_response++ = ZCL_BOOL_FALSE;
        }

        if (zcl_send_response(&zcl_binin, start_response, end_response - start_response) == 0) {
          puts("Response sent successfully\n");
        }
      }
      else
      {
        puts("Unhandled Profile command received");
      }
    }
  }
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
  wpan_envelope_dump(envelope);
  puts("Building ZCL Command based on received envelope: ");
  if(zcl_command_build(&zcl, envelope, context) == 0) {
    zcl_command_dump(&zcl);
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
  gpio_set(RELAY_2,   0);
  gpio_set(RELAY_3,   0);
  gpio_set(RELAY_4,   0);
}
#endif

#ifdef status_1_CheckTimer_irq
void status_1_CheckTimer_irq(void) {
  if (!((!gpio_get(STATUS_1)) ^ binaryInput.present_value) && status_1_SendStatus) {
    puts("EVENT TRIGGERED: status_1_irq (CONTACT CLOSED)");
    send_status(&zcl_binin_attributes, wpan_endpoint_match(&xdev.wpan_dev, CUSTOM_ENDPOINT, CUSTOM_EP_PROFILE));
    status_1_SendStatus = FALSE;
  }
  else if(gpio_get(STATUS_1) && !status_1_SendStatus) {
    puts("EVENT TRIGGERED: status_1_irq (CONTACT OPEN)");
    binaryInput.present_value = ZCL_BOOL_FALSE;
    send_status(&zcl_binin_attributes, wpan_endpoint_match(&xdev.wpan_dev, CUSTOM_ENDPOINT, CUSTOM_EP_PROFILE));
    status_1_SendStatus = TRUE;
    status_1_TimerSet = FALSE;
    timer_enable(status_1_CheckTimer, FALSE);
  }
}
#endif

#ifdef status_2_CheckTimer_irq
void status_2_CheckTimer_irq(void) {
  if (!((!gpio_get(STATUS_2)) ^ binaryInput2.present_value) && status_2_SendStatus) {
    puts("EVENT TRIGGERED: status_2_irq (CONTACT CLOSED)");
    send_status(&zcl_binin_attributes2, wpan_endpoint_match(&xdev.wpan_dev, CUSTOM_ENDPOINT2, CUSTOM_EP_PROFILE));
    status_2_SendStatus = FALSE;
  }
  else if(gpio_get(STATUS_2) && !status_2_SendStatus) {
    puts("EVENT TRIGGERED: status_2_irq (CONTACT OPEN)");
    binaryInput2.present_value = ZCL_BOOL_FALSE;
    send_status(&zcl_binin_attributes2, wpan_endpoint_match(&xdev.wpan_dev, CUSTOM_ENDPOINT2, CUSTOM_EP_PROFILE));
    status_2_SendStatus = TRUE;
    status_2_TimerSet = FALSE;
    timer_enable(status_2_CheckTimer, FALSE);
  }
}
#endif

#ifdef status_1_irq
void status_1_irq(void)
{
  if(status_1_InterruptFree) {
    status_1_InterruptFree = FALSE;
    if(!status_1_TimerSet) {
      binaryInput.present_value = !gpio_get(STATUS_1);
      if(timer_config(status_1_CheckTimer, TRUE, PERIODIC, DEBOUNCE_TIMER) == 0) {
        status_1_TimerSet = TRUE;
      }
    }
    status_1_InterruptFree = TRUE;
  }
}
#endif

#ifdef status_2_irq
void status_2_irq(void)
{
  if(status_2_InterruptFree) {
    status_2_InterruptFree = FALSE;
    if(!status_2_TimerSet) {
      binaryInput2.present_value = !gpio_get(STATUS_2);
      if(timer_config(status_2_CheckTimer, TRUE, PERIODIC, DEBOUNCE_TIMER) == 0) {
        status_2_TimerSet = TRUE;
      }
    }
    status_2_InterruptFree = TRUE;
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

  /* During startup, we should check the STATUS_* pins in case they have already been driven low (CONTACT CLOSED) */
  if (!gpio_get(STATUS_1)) {
    binaryInput.present_value = !gpio_get(STATUS_1);
    puts("STARTUP check STATUS_1 - CONTACT CLOSED");
  }
  if (!gpio_get(STATUS_2)) {
    binaryInput2.present_value = !gpio_get(STATUS_2);
    puts("STARTUP check STATUS_2 - CONTACT CLOSED");
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
      else if(option == 105 || option == 73) { /* i || I */
        trigger(CUSTOM_ENDPOINT);
      }
      else if(option == 106 || option == 74) { /* j || J */
        trigger(CUSTOM_ENDPOINT2);
      }
      else if(option == 107 || option == 75) { /* k || K */
        trigger(CUSTOM_ENDPOINT3);
      }
      else if(option == 108 || option == 76) { /* l || L */
        trigger(CUSTOM_ENDPOINT4);
      }
      else if(option == 104 || option == 72) { /* h || H */

      }
      else if(option == 115 || option == 83) { /* s || S */
        /* Power on UART1 & 2 (SCI) and turn off everything else */
        _SCGC1.Byte = SCGC1_SCI1_MASK | SCGC1_SCI2_MASK ;
        _SCGC2.Byte = 0;
        DoPassThroughMode();
        break;
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

int trigger(uint8_t endpoint) {
  puts("Trigger!");

  if(timer_config(relayTimer, TRUE, ONE_SHOT, RELAY_TIMER) == 0) {
    if(endpoint == CUSTOM_ENDPOINT) {
      gpio_set(RELAY_1, 1);
    }
    else if(endpoint == CUSTOM_ENDPOINT2) {
      gpio_set(RELAY_2, 1);
    }
    else if(endpoint == CUSTOM_ENDPOINT3) {
      gpio_set(RELAY_3, 1);
    }
    else if(endpoint == CUSTOM_ENDPOINT4) {
      gpio_set(RELAY_4, 1);
    }
    else {
      puts("Invalid endpoint received for triggering relay, no action taken.");
    }
    return 0;
  }
  else {
    return -EINVAL;
  }
}

void send_status(const zcl_binary_input_attr_t *zcl_binin_attr, const wpan_endpoint_table_entry_t *source_endpoint) {
  // This is meant for device side triggered notifications on state change
  PACKED_STRUCT request {
    zcl_header_nomfg_t	header;
    uint8_t					payload[80];
  } request;
  int bytecount;
  int retval = 0;
  wpan_envelope_t envelope;
  const zcl_attribute_base_t *attr_list = &zcl_binin_attr->present_value;

  wpan_envelope_create( &envelope, &xdev.wpan_dev, WPAN_IEEE_ADDR_COORDINATOR, WPAN_NET_ADDR_COORDINATOR);
  envelope.source_endpoint = source_endpoint->endpoint;
  envelope.dest_endpoint = 0x01;
  envelope.cluster_id = CUSTOM_EP_BIN_IN_CLUSTER;
  envelope.profile_id = CUSTOM_EP_PROFILE;
  envelope.payload = &request;
  request.header.frame_control = ZCL_FRAME_SERVER_TO_CLIENT
                                 | ZCL_FRAME_TYPE_PROFILE
                                 | ZCL_FRAME_DISABLE_DEF_RESP;
  request.header.command = ZCL_CMD_REPORT_ATTRIB;

  bytecount = zcl_create_attribute_records(&request.payload, sizeof(request.payload), &attr_list);
  request.header.sequence = wpan_endpoint_next_trans( source_endpoint );
  envelope.length = offsetof(struct request, payload) + bytecount;
  wpan_envelope_send(&envelope);
}