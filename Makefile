###############################################################################
# Makefile for Programmable XBEE ##############################################
###############################################################################
# The BSD License (BSD)
#
# Copyright (c) 2015 Sten Feldman
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
###############################################################################

# Keep the APP_NAME short, as this is used throughout this Makefile for
# files and identifiers.
APP_NAME=trigger

# Toolchain and output. If you are using Docker to build, make sure the paths
# are relative and within this directory to ensure container access.
CC=./hc08c/bin/chc08
LINKER=./hc08c/bin/linker
BURNER=./hc08c/bin/burner
OUTPUT=obj

PXBEE_API_SRC=./pxbee
HC08C=./hc08c

###############################################################################
# FLOATING POINT ##############################################################
###############################################################################
# Be diligent when choosing the HC08C library to link and either enabling or ##
# disabling the Floating Point support. If you choose the wrong combination, ##
# you can be sure that things will start to fall apart sooner or laater. ######
# The incompatibility is not detected during compilation/linking/burning. #####
# In other words, BE EXTRA CAREFUL! ###########################################
###############################################################################

# Only enable one of the following
FLOATFLAGS=-D__NO_FLOAT__ # Floating Point support is disabled
#FLOATFLAGS=-TD2 -Fd # Floating Point support is enabled

# Enable only one of the following libraries to be linked. Beware extra space!
# S2B/S2C Module 32K, no floating point
HC08C_LIB=ansiis.lib
# S2B/S2C Module 32K, floating point
#HC08C_LIB=ansifs.lib
# S2B Module 128K, no floating point
#HC08C_LIB=ansibim.lib
# S2B Module 128K, floating point
#HC08C_LIB=ansibfm.lib

CFLAGS=-Ms $(FLOATFLAGS) -DCONFIG_XBEE_DEBUG_BUILD \
	-BfaTSRON -Qvtpnone -WmsgSd3303 -WmsgFob"%f%e:%l:%k:%d %m\n" -Cs08 \
	-I"./include" \
	-I"$(PXBEE_API_SRC)/headers" \
	-I"$(HC08C)/include"

###

all:	start cpu drivers misc pan link burn

start:	$(OUTPUT) \
	$(OUTPUT)/start08.o \
	$(OUTPUT)/util.o \
	$(OUTPUT)/main.o

$(OUTPUT)/start08.o: ./src/start08.c
	$(CC) $(CFLAGS) -ObjN="$@" -Lm="$@.d" -LmCfg=xilmou $<

$(OUTPUT)/util.o: ./src/util.c
	$(CC) $(CFLAGS) -ObjN="$@" -Lm="$@.d" -LmCfg=xilmou $<

$(OUTPUT)/main.o: ./src/main.c
	$(CC) $(CFLAGS) -ObjN="$@" -Lm="$@.d" -LmCfg=xilmou $<

###############################################################################
# PXBEE SDK Beyond this point #################################################
###############################################################################

cpu:	$(OUTPUT)/cpu \
	$(OUTPUT)/cpu/flash.o \
	$(OUTPUT)/cpu/hwinit.o \
	$(OUTPUT)/cpu/irq_vectors.o \
	$(OUTPUT)/cpu/lvd.o \
	$(OUTPUT)/cpu/mc9s08qe32.o \
	$(OUTPUT)/cpu/mc9s08qe128.o \
	$(OUTPUT)/cpu/pm.o \
	$(OUTPUT)/cpu/system.o

drivers: 1-wire adc eeprom gpio icapt i2c kbrds lcd ocomp pwm rtc serial spi timer tpm

1-wire:	$(OUTPUT)/drivers/1-wire \
	$(OUTPUT)/drivers/1-wire/ds18b20.o \
	$(OUTPUT)/drivers/1-wire/ds1904.o \
	$(OUTPUT)/drivers/1-wire/one_wire.o

adc:	$(OUTPUT)/drivers/adc \
	$(OUTPUT)/drivers/adc/adc.o

eeprom: $(OUTPUT)/drivers/eeprom \
	$(OUTPUT)/drivers/eeprom/24xxx.o \
	$(OUTPUT)/drivers/eeprom/25xxxx.o \
	$(OUTPUT)/drivers/eeprom/veeprom.o

gpio:	$(OUTPUT)/drivers/gpio \
	$(OUTPUT)/drivers/gpio/gpios.o

icapt:	$(OUTPUT)/drivers/icapture \
	$(OUTPUT)/drivers/icapture/icapture.o

i2c:	$(OUTPUT)/drivers/i2c \
	$(OUTPUT)/drivers/i2c/i2c.o

kbrds:	$(OUTPUT)/drivers/keyboards \
	$(OUTPUT)/drivers/keyboards/mpr121.o

lcd:	$(OUTPUT)/drivers/lcd \
	$(OUTPUT)/drivers/lcd/char_lcd.o \
	$(OUTPUT)/drivers/lcd/graphic_display.o

ocomp:	$(OUTPUT)/drivers/ocompare \
	$(OUTPUT)/drivers/ocompare/ocompare.o

pwm:	$(OUTPUT)/drivers/pwm \
	$(OUTPUT)/drivers/pwm/pwm.o

rtc:	$(OUTPUT)/drivers/rtc \
	$(OUTPUT)/drivers/rtc/rtc.o

serial:	$(OUTPUT)/drivers/serial \
	$(OUTPUT)/drivers/serial/uart.o

spi:	$(OUTPUT)/drivers/spi \
	$(OUTPUT)/drivers/spi/spi.o

timer:	$(OUTPUT)/drivers/timer \
	$(OUTPUT)/drivers/timer/timer.o

tpm:	$(OUTPUT)/drivers/tpm \
	$(OUTPUT)/drivers/tpm/tpm.o

misc:	$(OUTPUT)/misc \
	$(OUTPUT)/misc/cbuffer.o \
	$(OUTPUT)/misc/debug.o \
	$(OUTPUT)/misc/utils.o

pan:	$(OUTPUT)/pan \
	$(OUTPUT)/pan/endpoints.o \
	$(OUTPUT)/pan/ota_fw_update.o \
	$(OUTPUT)/pan/pan_init.o \
	hal util wpan xbee zigbee

hal:	$(OUTPUT)/pan/hal \
	$(OUTPUT)/pan/hal/xbee_platform_hcs08.o \
	$(OUTPUT)/pan/hal/xbee_serial_hcs08.o

util:	$(OUTPUT)/pan/util \
	$(OUTPUT)/pan/util/hexdump.o \
	$(OUTPUT)/pan/util/hexstrtobyte.o \
	$(OUTPUT)/pan/util/jslong.o \
	$(OUTPUT)/pan/util/memcheck.o \
	$(OUTPUT)/pan/util/swapbytes.o \
	$(OUTPUT)/pan/util/swapcpy.o \
	$(OUTPUT)/pan/util/xmodem_crc16.o

wpan:	$(OUTPUT)/pan/wpan \
	$(OUTPUT)/pan/wpan/wpan_aps.o \
	$(OUTPUT)/pan/wpan/wpan_types.o

xbee:	$(OUTPUT)/pan/xbee \
	$(OUTPUT)/pan/xbee/xbee_atcmd.o \
	$(OUTPUT)/pan/xbee/xbee_atmode.o \
	$(OUTPUT)/pan/xbee/xbee_cbuf.o \
	$(OUTPUT)/pan/xbee/xbee_commissioning.o \
	$(OUTPUT)/pan/xbee/xbee_device.o \
	$(OUTPUT)/pan/xbee/xbee_discovery.o \
	$(OUTPUT)/pan/xbee/xbee_firmware.o \
	$(OUTPUT)/pan/xbee/xbee_ota_client.o \
	$(OUTPUT)/pan/xbee/xbee_ota_server.o \
	$(OUTPUT)/pan/xbee/xbee_route.o \
	$(OUTPUT)/pan/xbee/xbee_time.o \
	$(OUTPUT)/pan/xbee/xbee_transparent_serial.o \
	$(OUTPUT)/pan/xbee/xbee_wpan.o \
	$(OUTPUT)/pan/xbee/xbee_xmodem.o

zigbee:	$(OUTPUT)/pan/zigbee \
	$(OUTPUT)/pan/zigbee/zcl_basic.o \
	$(OUTPUT)/pan/zigbee/zcl_client.o \
	$(OUTPUT)/pan/zigbee/zcl_commissioning.o \
	$(OUTPUT)/pan/zigbee/zcl_identify.o \
	$(OUTPUT)/pan/zigbee/zcl_onoff.o \
	$(OUTPUT)/pan/zigbee/zcl_time.o \
	$(OUTPUT)/pan/zigbee/zcl_types.o \
	$(OUTPUT)/pan/zigbee/zigbee_zcl.o \
	$(OUTPUT)/pan/zigbee/zigbee_zdo.o

$(OUTPUT)/%.o: $(PXBEE_API_SRC)/%.c
	$(CC) $(CFLAGS) -ObjN="$@" -Lm="$@.d" -LmCfg=xilmou $<

$(OUTPUT)/$(APP_NAME).abs \
link:
	@echo "Starting to link the world together..."
	$(LINKER) include/project.prm -M -WmsgFob"%f%e:%l:%k:%d %m\n" -WmsgSd1100 -WmsgSd1912 \
	-Add\("$(OUTPUT)/cpu/flash.o" \
	"$(OUTPUT)/cpu/hwinit.o" \
	"$(OUTPUT)/cpu/irq_vectors.o" \
	"$(OUTPUT)/cpu/lvd.o" \
	"$(OUTPUT)/cpu/mc9s08qe32.o" \
	"$(OUTPUT)/cpu/mc9s08qe128.o" \
	"$(OUTPUT)/cpu/pm.o" \
	"$(OUTPUT)/cpu/system.o" \
	"$(OUTPUT)/drivers/1-wire/ds18b20.o" \
	"$(OUTPUT)/drivers/1-wire/ds1904.o" \
	"$(OUTPUT)/drivers/1-wire/one_wire.o" \
	"$(OUTPUT)/drivers/adc/adc.o" \
	"$(OUTPUT)/drivers/eeprom/24xxx.o" \
	"$(OUTPUT)/drivers/eeprom/25xxxx.o" \
	"$(OUTPUT)/drivers/eeprom/veeprom.o" \
	"$(OUTPUT)/drivers/gpio/gpios.o" \
	"$(OUTPUT)/drivers/icapture/icapture.o" \
	"$(OUTPUT)/drivers/i2c/i2c.o" \
	"$(OUTPUT)/drivers/keyboards/mpr121.o" \
	"$(OUTPUT)/drivers/lcd/char_lcd.o" \
	"$(OUTPUT)/drivers/lcd/graphic_display.o" \
	"$(OUTPUT)/drivers/ocompare/ocompare.o" \
	"$(OUTPUT)/drivers/pwm/pwm.o" \
	"$(OUTPUT)/drivers/rtc/rtc.o" \
	"$(OUTPUT)/drivers/serial/uart.o" \
	"$(OUTPUT)/drivers/spi/spi.o" \
	"$(OUTPUT)/drivers/timer/timer.o" \
	"$(OUTPUT)/drivers/tpm/tpm.o" \
	"$(OUTPUT)/misc/cbuffer.o" \
	"$(OUTPUT)/misc/debug.o" \
	"$(OUTPUT)/misc/utils.o" \
	"$(OUTPUT)/pan/endpoints.o" \
	"$(OUTPUT)/pan/ota_fw_update.o" \
	"$(OUTPUT)/pan/pan_init.o" \
	"$(OUTPUT)/pan/hal/xbee_platform_hcs08.o" \
	"$(OUTPUT)/pan/hal/xbee_serial_hcs08.o" \
	"$(OUTPUT)/pan/util/hexdump.o" \
	"$(OUTPUT)/pan/util/hexstrtobyte.o" \
	"$(OUTPUT)/pan/util/jslong.o" \
	"$(OUTPUT)/pan/util/memcheck.o" \
	"$(OUTPUT)/pan/util/swapbytes.o" \
	"$(OUTPUT)/pan/util/swapcpy.o" \
	"$(OUTPUT)/pan/util/xmodem_crc16.o" \
	"$(OUTPUT)/pan/wpan/wpan_aps.o" \
	"$(OUTPUT)/pan/wpan/wpan_types.o" \
	"$(OUTPUT)/pan/xbee/xbee_atcmd.o" \
	"$(OUTPUT)/pan/xbee/xbee_atmode.o" \
	"$(OUTPUT)/pan/xbee/xbee_cbuf.o" \
	"$(OUTPUT)/pan/xbee/xbee_commissioning.o" \
	"$(OUTPUT)/pan/xbee/xbee_device.o" \
	"$(OUTPUT)/pan/xbee/xbee_discovery.o" \
	"$(OUTPUT)/pan/xbee/xbee_firmware.o" \
	"$(OUTPUT)/pan/xbee/xbee_ota_client.o" \
	"$(OUTPUT)/pan/xbee/xbee_ota_server.o" \
	"$(OUTPUT)/pan/xbee/xbee_route.o" \
	"$(OUTPUT)/pan/xbee/xbee_time.o" \
	"$(OUTPUT)/pan/xbee/xbee_transparent_serial.o" \
	"$(OUTPUT)/pan/xbee/xbee_wpan.o" \
	"$(OUTPUT)/pan/xbee/xbee_xmodem.o" \
	"$(OUTPUT)/pan/zigbee/zcl_basic.o" \
	"$(OUTPUT)/pan/zigbee/zcl_client.o" \
	"$(OUTPUT)/pan/zigbee/zcl_commissioning.o" \
	"$(OUTPUT)/pan/zigbee/zcl_identify.o" \
	"$(OUTPUT)/pan/zigbee/zcl_onoff.o" \
	"$(OUTPUT)/pan/zigbee/zcl_time.o" \
	"$(OUTPUT)/pan/zigbee/zcl_types.o" \
	"$(OUTPUT)/pan/zigbee/zigbee_zcl.o" \
	"$(OUTPUT)/pan/zigbee/zigbee_zdo.o" \
	"$(OUTPUT)/start08.o" \
	"$(OUTPUT)/util.o" \
	"$(OUTPUT)/main.o" \
	"$(HC08C)/lib/$(HC08C_LIB)"\) \
	-O"$(OUTPUT)/$(APP_NAME).abs"
	mv $(APP_NAME).map $(OUTPUT)/

burn:	include/burner.bbl $(OUTPUT)/$(APP_NAME).abs
	@echo "Let's burn the world..."
	$(BURNER) -WmsgFob"%f%e:%l:%k:%d:%m\n" -F="$<" -Env"ABS_FILE=$(OUTPUT)/$(APP_NAME).abs"

$(OUTPUT) \
$(OUTPUT)/cpu \
$(OUTPUT)/drivers/1-wire \
$(OUTPUT)/drivers/adc \
$(OUTPUT)/drivers/eeprom \
$(OUTPUT)/drivers/gpio \
$(OUTPUT)/drivers/i2c \
$(OUTPUT)/drivers/icapture \
$(OUTPUT)/drivers/keyboards \
$(OUTPUT)/drivers/lcd \
$(OUTPUT)/drivers/ocompare \
$(OUTPUT)/drivers/pwm \
$(OUTPUT)/drivers/rtc \
$(OUTPUT)/drivers/serial \
$(OUTPUT)/drivers/spi \
$(OUTPUT)/drivers/timer \
$(OUTPUT)/drivers/tpm \
$(OUTPUT)/misc \
$(OUTPUT)/pan \
$(OUTPUT)/pan/hal \
$(OUTPUT)/pan/util \
$(OUTPUT)/pan/wpan \
$(OUTPUT)/pan/xbee \
$(OUTPUT)/pan/zigbee:
	mkdir -p $@

###############################################################################
# Dockerized build support for building within Mac OS X using Linux Toolchain #
###############################################################################

builddocker:
	@echo "We will try to build a image according to the Dockerfile..."
	docker build --tag=$(APP_NAME):latest .

dall:
	docker run -v $(CURDIR):/$(APP_NAME) -w=/$(APP_NAME) --rm=true $(APP_NAME)

###############################################################################
# CLEAN #######################################################################
###############################################################################

clean:
	rm -rf ./obj
	rm -rf err.txt
