# pxbee-trigger

Programmable XBee Trigger that is ZigBee Home Automation profile compliant. The testing of this feature is carried out using [SmartThings](https://www.smartthings.com) Hub v3. A default ZigBee device handler can be used for limited functionality.

## Bill of Materials (BOM)

| Component                                                                                                            | Manufacturer                                      | Quantity | SKU / Part nr.                | Specification                                                                      | Option |
| -------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- | -------- | ----------------------------- | ---------------------------------------------------------------------------------- | ------ |
| [Programmable XBee](https://www.digi.com/products/xbee-rf-solutions/rf-modules/xbee-zigbee#partnumbers) (with RPSMA) | [Digi](https://www.digi.com)                      |        1 | XBP24CZ7SITB003               | [PDF](http://www.digi.com/resources/documentation/digidocs/pdfs/90002002.pdf)      |        |
| [Bridge Rectifier DF01M](https://www.mouser.ee/ProductDetail/512-DF01M)                                              | [ON Semiconductor](https://www.onsemi.com)        |        1 | Mouser No: 512-DF01M          | [PDF](https://www.mouser.ee/datasheet/2/308/DF10M-D-1803766.pdf)                   |        |
| [Electrolytic Capacitor - Radial 220uF 50V](https://www.mouser.ee/ProductDetail/EEU-FM1H221)                         | [Panasonic](https://industrial.panasonic.com).    |      1-2 | Mouser No: 667-EEU-FM1H221.   | [PDF](https://www.mouser.ee/datasheet/2/315/ABA0000C1018-947496.pdf).              |        |
| [DC/DC Isolated Converter Cosel MGFS1R5243R3](https://www.mouser.ee/ProductDetail/436-MGFS1R5243R3)                  | [Cosel](https://www.coseleurope.eu)               |        1 | Mouser No: 436-MGFS1R5243R3   | [PDF](https://www.mouser.ee/datasheet/2/622/SFE_MGFS-1115632.pdf)                  |        |
| [Bipolar Transistor BC548BTA](https://www.mouser.ee/ProductDetail/512-BC548BTA)                                      | [ON Semiconductor](https://www.onsemi.com)        |        4 | Mouser No: 512-BC548BTA       | [PDF](https://www.mouser.ee/datasheet/2/308/BC548-1118644.pdf)                     |        |
| [Diode 1N4004](https://www.mouser.ee/ProductDetail/863-1N4004RLG)                                                    | [ON Semiconductor](https://www.onsemi.com)        |        4 | Mouser No: 863-1N4004RLG      | [PDF](https://www.mouser.ee/datasheet/2/308/1N4001-D-110363.pdf)                   |        |
| [General Purpose Relay (APAN3103)](https://www.mouser.ee/ProductDetail/769-APAN3103)                                 | [Panasonic](https://industrial.panasonic.com)     |        4 | Mouser No: 769-APAN3103       | [PDF](https://www.mouser.ee/datasheet/2/315/mech_eng_pan-1299258.pdf)              |        |
| [Resistor RN55D1801FB14](https://www.mouser.ee/ProductDetail/71-RN55D1801FB14)                                       | [Vishay](https://www.vishay.com)                  |        4 | Mouser No: 71-RN55D1801FB14   | [PDF](https://www.mouser.ee/datasheet/2/427/cmfmil-109690.pdf)                     |        |
| [10 pin header for XBee](https://www.mouser.ee/ProductDetail/855-M22-7131042)                                        | [Harwin](https://www.harwin.com)                  |        2 | Mouser No: 855-M22-7131042    | [PDF](https://www.mouser.ee/datasheet/2/181/M22-713-1134021.pdf)                   |        |
| [2 pin Terminal Block (PCB)](https://www.mouser.ee/ProductDetail/538-39501-1002)                                     | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-39501-1002     | [PDF](https://www.mouser.ee/datasheet/2/276/0395011002_TERMINAL_BLOCKS-163759.pdf) | A      |
| [2 pin Terminal Plug](https://www.mouser.ee/ProductDetail/538-39500-0002)                                            | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-39500-0002     | [PDF](https://www.mouser.ee/datasheet/2/276/0395000002_TERMINAL_BLOCKS-136229.pdf) | A      |
| [9 pin Terminal Block (PCB)](https://www.mouser.ee/ProductDetail/538-39501-1009)                                     | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-39501-1009     | [PDF](https://www.mouser.ee/datasheet/2/276/0395011009_TERMINAL_BLOCKS-163629.pdf) | A      |
| [9 pin Terminal Plug](https://www.mouser.ee/ProductDetail/651-1908101)                                               | [Molex](https://www.molex.com)                    |        1 | Mouser No: 651-1908101        | [PDF](https://www.mouser.ee/datasheet/2/276/0395000009_TERMINAL_BLOCKS-163669.pdf) | A      |
| [2 pin Fixed Terminal Block (PCB)](https://www.mouser.ee/ProductDetail/538-39357-0002)                               | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-39357-0002     | [PDF](https://www.mouser.ee/datasheet/2/276/0393570002_TERMINAL_BLOCKS-227759.pdf) | B      |
| [9 pin Fixed Terminal Block (PCB)](https://www.mouser.ee/ProductDetail/538-39357-0009)                               | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-39357-0009     | [PDF](https://www.mouser.ee/datasheet/2/276/0393570009_TERMINAL_BLOCKS-136250.pdf) | B      |
| [Antenna with RP-SMA Connector](https://www.mouser.ee/ProductDetail/712-ANT-2.4-CW-RAH)                              | [Linx Technologies](https://linxtechnologies.com) |        1 | Mouser No: 712-ANT-2.4-CW-RAH | [PDF](https://www.mouser.ee/datasheet/2/238/ant-2.4-cw-rah-ccc-1659143.pdf)        |        |
| [6 pin Debug Header](https://www.mouser.ee/ProductDetail/538-22-28-8065)                                             | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-22-28-8065     | [PDF](https://www.mouser.ee/datasheet/2/276/0022288065_PCB_HEADERS-159204.pdf)     | O      |
| [2 pin Reset Header](https://www.mouser.ee/ProductDetail/Molex/22-28-5027)                                           | [Molex](https://www.molex.com)                    |        1 | Mouser No: 538-22-28-5027     | [PDF](https://www.mouser.ee/ProductDetail/Molex/22-28-5027)                        | O      |

Standard 3.5 width headers are used. Option **A**) uses pluggable termination; **B**) Fixed screw termination; **O**) Parts are optional and meant for development; Components can easily be switched with other termination blocks or use direct wire soldering.

## Compiling

- On 32bit Linux target, simply: `make`
- On 64bit Linux target:
    - Intall 32bit compatible libraries: `sudo apt-get install lib32stdc++6`
    - `make`
- On MacOS:
    - Install [Docker](https://www.docker.com)
    - `make builddocker`
    - `make dall`

## Firmware

- Output file: `obj/trigger.abs.bin`
- Upload the file via local XMODEM or use Over-the-air upgrade if the current firmware supports it (you can use [pxbee-fwup.js](https://github.com/exsilium/pxbee-fwup.js))
- See further [Programmable XBee documentation](http://xbee-sdk-doc.readthedocs.io)

## Trigger

Send a Unicast ZCL "On" command to trigger the connected relay for 125ms. The state of the switch remains in "Off" state. Broadcast command is ignored by default.

```
Endpoint: 0xEA,
clusterId: 0x0006,
profileId: 0x0104,
command: 0x01
```

## Settings

The following defines can be altered in `custom.h` prior to compilation to change the behavior how the Trigger works:

|  Name | Description | Default |
| ------| ----------- | ------- |
| `PXBEE_TRIGGER_IGNORE_BROADCAST` | When enabled, ignores broadcast commands and reacts only when unicast messages are sent to the specific address (ignores All On/All Off commands). | Enabled |
| `ZCL_MANUFACTURER` | The reported manufacturer string. For SmartThings local execution support without custom device handler, set this to "Leviton". | "PXBee" |
| `ZCL_MODEL` | The reported model string. For SmartThings local execution support without custom device handler, set this to "ZSS-10". | "Trigger" |

## License

This project is based on [exsilium/pxbee-blink-led](https://github.com/exsilium/pxbee-blink-led) boilerplate and includes the full [Digi](http://www.digi.com) XBee SDK version 1.6.0 sources.

Includes the necessary build binaries:
```
HI-CROSS+ ANSI-C Compiler for HC08 V-5.0.39, Dec 13 2011
HI-CROSS+ SmartLinker V-5.0.48, Dec 13 2011
HI-CROSS+ Burner V-5.0.16, Dec 13 2011
(c) Copyright Freescale 1987-2010
```

If not otherwise noted, the added code is [BSD licensed](LICENSE).
