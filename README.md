# pxbee-trigger

Programmable XBee Trigger that is ZigBee Home Automation profile compliant. The testing of this feature is carried out using [SmartThings](https://www.smartthings.com) Hub and a default ZigBee device handler.

## Bill of Materials

|  Component    | Manufacturer  | Quantity | SKU / Part nr. | Mandatory / Optional |
| ------------- | ------------- | -------- | -------------- | -------------------- |
| [Programmable XBee](https://www.digi.com/products/xbee-rf-solutions/rf-modules/xbee-zigbee#partnumbers) | [Digi](https://www.digi.com) | 1 | XBP24CZ7PITB003 | M |
| [Grove - XBee Carrier](https://www.seeedstudio.com/Grove-XBee-Carrier-p-905.html) | [Seeed Development](https://www.seeedstudio.com/) | 1 | 113020004 | O |
| [Grove - Relay](https://www.seeedstudio.com/Grove-Relay-p-769.html) | [Seeed Development](https://www.seeedstudio.com/) | 1 | 103020005 | O |
| [Grove 5cm Cable](https://www.seeedstudio.com/Grove-Universal-4-Pin-Buckled-5cm-Cable-(5-PCs-Pack)-p-925.html) | [Seeed Development](https://www.seeedstudio.com/) | 1 | 110990036 | O |

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
- Upload the file via local XMODEM or use Over-the-air upgrade if the current firmware supports it
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