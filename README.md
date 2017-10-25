# pxbee-trigger

Programmable XBee Trigger that is ZigBee Home Automation profile compliant. The testing of this feature branch is carried out using [SmartThings](https://www.smartthings.com) Hub and a default ZigBee device handler.

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
