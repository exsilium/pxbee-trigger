/*
 * This is an auto-generated file based on the
 * configuration of the XBee Programmable project.
 *
 * Edit this file to change project parameters.
 */

#ifndef __XBEE_CONFIG_H_
#define __XBEE_CONFIG_H_

/* Project definitions */
#define APP_VERSION_STRING              "Trigger v0.4.0-rc.0"
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

/* network0 component */
#define ENABLE_XBEE_HANDLE_RX
#define ENABLE_OTA_UPDATE
//#define TRIGGER_FW_UPDATE               "12345"

/* uart0 component */
#define ENABLE_UART
#define UART_CFG_MODE_2W                1
#define UART_CFG_BAUDRATE               9600
#define UART_CFG_PAR_EN                 UART_CFG_PARITY_DIS
#define UART_CFG_PAR_VAL                UART_CFG_PARITY_ODD
#define UART_CFG_BITS                   UART_CFG_BITS_8
#define UART_CFG_RX_WATERMARK           1
#define UART_CFG_RX_BUF_LEN             32
#define ENABLE_STDIO_PRINTF_SCANF       1

/* xbee_config0 component */
//#define XBEE_ATCMD_PARAM_ID             "0123456789ABCDEF"
#define XBEE_ATCMD_PARAM_SC             0x2000  // Only scan Channel 24 (0x18) Keep 0x7FFF for default scan
#define XBEE_ATCMD_PARAM_NI             "PROGRAMMABLE TEST 3W"

/* STATUS_1 pin */
#define ENABLE_GPIO_IRQ_XPIN_19
#define STATUS_1                        XPIN_19
#define status_1_irq                    gpio_irq_handler_xpin_19
#define GPIO_CFG_IRQ_MODE_19            GPIO_CFG_EDGE_IRQ
#define GPIO_IRQ_LEVEL_EDGE_19          GPIO_IRQ_EDGE_BOTH
#define GPIO_IRQ_CFG_PULL_19            GPIO_IRQ_CFG_PULL_HIGH
#define orPD19                          shift_xpin_19
#define andPD19                         ~0
#define orPR19                          shift_xpin_19
#define andPR19                         ~0

/* STATUS_2 pin */
#define ENABLE_GPIO_IRQ_XPIN_18
#define STATUS_2                        XPIN_18
#define status_2_irq                    gpio_irq_handler_xpin_18
#define GPIO_CFG_IRQ_MODE_18            GPIO_CFG_EDGE_IRQ
#define GPIO_IRQ_LEVEL_EDGE_18          GPIO_IRQ_EDGE_BOTH
#define GPIO_IRQ_CFG_PULL_18            GPIO_IRQ_CFG_PULL_HIGH
#define orPD18                          shift_xpin_18
#define andPD18                         ~0
#define orPR18                          shift_xpin_18
#define andPR18                         ~0

/* RELAY_1 pin */
#define ENABLE_GPIO_XPIN_7
#define RELAY_1                         XPIN_7
#define GPIO_CFG_DIR_7                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_7           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_7         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_7              GPIO_CFG_DRV_STR_HIGH

/* RELAY_2 pin */
#define ENABLE_GPIO_XPIN_6
#define RELAY_2                         XPIN_6
#define GPIO_CFG_DIR_6                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_6           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_6         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_6              GPIO_CFG_DRV_STR_HIGH

/* RELAY_3 pin */
#define ENABLE_GPIO_XPIN_4
#define RELAY_3                         XPIN_4
#define GPIO_CFG_DIR_4                  GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_4           GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_4         GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_4              GPIO_CFG_DRV_STR_HIGH

/* RELAY_4 pin */
#define ENABLE_GPIO_XPIN_11
#define RELAY_4                         XPIN_11
#define GPIO_CFG_DIR_11                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_11          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_11        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_11             GPIO_CFG_DRV_STR_HIGH

/* Disable other outputs by pulling low */
#define ENABLE_GPIO_XPIN_16
#define GPIO_CFG_DIR_16                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_16          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_16        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_16             GPIO_CFG_DRV_STR_HIGH

#define ENABLE_GPIO_XPIN_12
#define GPIO_CFG_DIR_12                 GPIO_CFG_OUTPUT
#define GPIO_CFG_PULL_UP_EN_12          GPIO_CFG_PULL_UP_DIS
#define GPIO_CFG_SLEW_RATE_EN_12        GPIO_CFG_SLEW_RATE_DIS
#define GPIO_CFG_DRV_STR_12             GPIO_CFG_DRV_STR_LOW

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

/* Enable timer/pulse-width modulator (TPM) module */
#define ENABLE_TIMER

/* relayTimer component */
#define relayTimer                      TPM1
#define TPM1_OVERFLOW_INTERRUPT
#define relayTimer_irq                  tpm1ov_irq
#define ENABLE_TPM1

/* status_1_CheckTimer component (XPIN19) */
#define status_1_CheckTimer             TPM2
#define TPM2_OVERFLOW_INTERRUPT
#define status_1_CheckTimer_irq         tpm2ov_irq
#define ENABLE_TPM2

/* status_2_CheckTimer component (XPIN18) */
#define status_2_CheckTimer             TPM3
#define TPM3_OVERFLOW_INTERRUPT
#define status_2_CheckTimer_irq         tpm3ov_irq
#define ENABLE_TPM3

/* Used pins macros */
#define XPIN_19_USED
#define XPIN_18_USED
#define XPIN_15_USED
#define XPIN_11_USED
#define XPIN_5_USED
#define XPIN_4_USED
#define XPIN_8_USED
#define XPIN_6_USED
#define XPIN_7_USED
#define XPIN_3_USED
#define XPIN_2_USED

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
