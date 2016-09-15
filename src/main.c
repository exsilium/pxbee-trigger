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
 *   XPIN16 = <<UNUSED>>
 *   XPIN17 = <<UNUSED>>
 *   XPIN18 = <<UNUSED>>
 *   XPIN19 = <<UNUSED>>
 *   XPIN20 = special0 [Commissioning Pin]
 *
 ************************************/


#include <xbee_config.h>
#include <types.h>

#ifdef ENABLE_XBEE_HANDLE_RX
int xbee_transparent_rx(const wpan_envelope_t FAR *envelope, void FAR *context)
{
	char addrbuf[ADDR64_STRING_LENGTH];

	puts("Received Simple Frame");
	puts("---------------------");
	sys_watchdog_reset();
	printf("Source     : %s\n", addr64_format(addrbuf, &envelope->ieee_address));
	printf("Network    : %04x\n", be16toh(envelope->network_address));
	printf("Data length: %u\n", envelope->length);
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
}
#endif

void main(void)
{
	sys_hw_init();
	sys_xbee_init();
	sys_app_banner();

	for (;;) {
		/* Nothing to do... 
		 * Everything is done in the periodic task
		 */
		sys_watchdog_reset();
		sys_xbee_tick();
	}
}
