/*
 * This is an auto-generated file based on the
 * configuration of the XBee Programmable project.
 *
 * Edit this file to change project parameters.
 */

#ifndef __XBEE_CONFIG_H_
#define __XBEE_CONFIG_H_

/* Project definitions */
#define APP_VERSION_STRING              "Trigger v0.1.0"
#define CONFIG_XBEE_ZB
#define CONFIG_XBEE_THT
#define CONFIG_XBEE_S2CTH
#define CONFIG_XBEE_FLASH_LEN           32

/* system0 component */
#define SYS_CFG_CLK_48_MHz
#define SYS_CFG_BUSCLK_SYSCLK_DIV2
#define ENABLE_WD
#define WD_CFG_LONG_TOUT

/* special0 component */
//#define ENABLE_ASSOCIATION_LED_XPIN_15
//#define ENABLE_COMMISSIONING_XPIN_20
#define ENABLE_RESET_PIN_XPIN_5
//#define ENABLE_BKGD_PIN_XPIN_8
//#define ENABLE_RSSI_PWM_XPIN_6

/* rtc0 component */
#define ENABLE_RTC
#define RTC_ENABLE_PERIODIC_TASK
#define RTC_CFG_PERIODIC_TASK_PERIOD    1000

/* LED component */
#define ENABLE_GPIO_XPIN_7
#define LED                             XPIN_7
#define GPIO_CFG_DIR_7                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_7           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_7         GPIO_CFG_SLEW_RATE_EN
#define GPIO_CFG_DRV_STR_7              GPIO_CFG_DRV_STR_LOW

/* network0 component */
#define ENABLE_XBEE_HANDLE_RX
#define ENABLE_OTA_UPDATE
//#define TRIGGER_FW_UPDATE               "12345"

/* uart0 component */
#define ENABLE_UART
#define UART_CFG_MODE_2W                1
#define UART_CFG_BAUDRATE               115200
#define UART_CFG_PAR_EN                 UART_CFG_PARITY_DIS
#define UART_CFG_PAR_VAL                UART_CFG_PARITY_ODD
#define UART_CFG_BITS                   UART_CFG_BITS_8
#define UART_CFG_RX_WATERMARK           1
#define UART_CFG_RX_BUF_LEN             32
#define ENABLE_STDIO_PRINTF_SCANF       1

/* xbee_config0 component */
//#define XBEE_ATCMD_PARAM_ID             "0123456789ABCDEF"
#define XBEE_ATCMD_PARAM_SC             0x7FFF
#define XBEE_ATCMD_PARAM_NI             "PROGRAMMABLE TEST 1"

/* GROVE LED component on the XBee Carrier (I2C socket) */
#define ENABLE_GPIO_XPIN_19
#define LED_GROVE                       XPIN_19
#define GPIO_CFG_DIR_19                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_19          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_19        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_19             GPIO_CFG_DRV_STR_HIGH

/* RELAY component */
#define ENABLE_GPIO_XPIN_17
#define RELAY                           XPIN_17
#define GPIO_CFG_DIR_17                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_17          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_17        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_17             GPIO_CFG_DRV_STR_HIGH

#define ENABLE_GPIO_XPIN_16
#define RELAY_2                         XPIN_16
#define GPIO_CFG_DIR_16                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_16          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_16        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_16             GPIO_CFG_DRV_STR_HIGH

/* GROVE XBee Carrier Board Power Control for GROVE sockets */
#define ENABLE_GPIO_XPIN_12
#define PWR_CNTRL_RELAY                 XPIN_12
#define GPIO_CFG_DIR_12                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_12          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_12        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_12             GPIO_CFG_DRV_STR_LOW

#define ENABLE_GPIO_XPIN_11
#define PWR_CNTRL_LED                   XPIN_11
#define GPIO_CFG_DIR_11                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_11          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_11        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_11             GPIO_CFG_DRV_STR_LOW

/* Disable other outputs by pulling low */
#define ENABLE_GPIO_XPIN_18
#define GPIO_CFG_DIR_18                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_18          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_18        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_18             GPIO_CFG_DRV_STR_LOW

#define ENABLE_GPIO_XPIN_4
#define GPIO_CFG_DIR_4                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_4           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_4         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_4              GPIO_CFG_DRV_STR_LOW

/* Disable special pins */
#define ENABLE_GPIO_XPIN_20
#define GPIO_CFG_DIR_20                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_20          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_20        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_20             GPIO_CFG_DRV_STR_LOW

#define ENABLE_GPIO_XPIN_15
#define GPIO_CFG_DIR_15                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_15          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_15        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_15             GPIO_CFG_DRV_STR_LOW

#define ENABLE_GPIO_XPIN_8
#define GPIO_CFG_DIR_8                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_8           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_8         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_8              GPIO_CFG_DRV_STR_LOW

#define ENABLE_GPIO_XPIN_6
#define GPIO_CFG_DIR_6                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_6           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_6         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_6              GPIO_CFG_DRV_STR_LOW

/* relayTimer component */
#define ENABLE_TIMER
#define relayTimer                      TPM1
#define TPM1_OVERFLOW_INTERRUPT
#define relayTimer_irq                  tpm1ov_irq
#define ENABLE_TPM1

/* Used pins macros */
#define XPIN_20_USED
#define XPIN_19_USED
#define XPIN_15_USED
#define XPIN_5_USED
#define XPIN_8_USED
#define XPIN_6_USED
#define XPIN_7_USED
#define XPIN_3_USED
#define XPIN_2_USED
#define XPIN_17_USED
#define XPIN_16_USED

/* Components includes */
#include <custom.h>
#include <system.h>
#include <rtc.h>
#include <gpios.h>
#include <pan_init.h>
#include <endpoints.h>
#include <xbee/discovery.h>
#include <xbee/wpan.h>
#include <xbee/atcmd.h>
#include <uart.h>
#include <timer.h>

#endif /* __XBEE_CONFIG_H_ */
