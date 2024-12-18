# NanoEls H5

Latest version of the electronic lead screw controller for metal lathes.

![image](https://github.com/user-attachments/assets/0a85636e-be05-4bb6-93ba-16217404e416)

## Parts list

- 89€ Nextion 5 inch display [NX8048P050 011C Y](https://www.aliexpress.com/item/1005002457232503.html)
- 23€ [PS2 mini keyboard](https://www.amazon.de/gp/product/B01MRJQVZP)
- 10€ [5V 2A non-USB power adapter](https://www.amazon.de/dp/B09KNFD38L)
- 5€ [ESP32-S3 N16R8 weld](https://www.aliexpress.com/item/1005005051294262.html)
- 3€ [SN74HCT245N](https://www.aliexpress.com/item/1005007118898020.html) - pack of 10, we only need 2
- 6€ 3 packs of [5 pairs 3.5mm terminals 4P straight](https://www.aliexpress.com/item/1005006895741900.html)
- 4€ [USB C male to female](https://www.aliexpress.com/item/1005007549815957.html)
- 5€ [custom PCB](pcb/Gerber_PCB_NanoElsH5-20241218.zip) ordered on jlcpcb.com
- [3D-printed case](case/h5case.step)
- 5x M3 bolts 5-8mm length
- Optional curved 4-pin header to connect display wires to the PCB

## PCB

![schematics](pcb/schematics.png)

![PCB rear](pcb/pcb1.PNG)

![PCB front](pcb/pcb2.PNG)

## Assembly instructions

NOTE: throughout the assembly make sure to avoid static electricity accumulation on your body by wearing suitable clothes and shoes, not using chairs known to cause ESD. Touch any grounded metal device housing to check.

![image](https://github.com/user-attachments/assets/8a630150-ad79-434e-bc0c-9a0f711de5bb)

Check that ESP32-S3 board is working by uploading [h5.ino](h5.ino) onto it using Arduino IDE.

Solder ESP32, 2x SN74HCT245N and optional curved header onto the PCB. Double check the side and orientation of each piece before soldering.

Insert USB extension into the COM port.

Separate all terminals into 2 pieces. Insert female terminals into the 3D-printed housing. Place the PCB on top and secure it with 4 M3 bolts. Secure the other end of the USB extension in the access hole with an M3 bolt.

Solder 15 terminals to the PCB while everything is positioned in the case.

Remove screen back cover. Attach the included 4-lead wire to the screen and to the PCB - each `RX` should be attached to `TX` on the other side.

Bolt the case and screen together using the bolts that used to hold the back cover.

Prepare MicroSD card with 1 file on it - [h5.tft](screen/h5.tft) - insert it into the screen. Connect 5V power supply to the POWER terminal, wait for screen to report that flashing has finished. Disconnect the power, remove the card.

Cut the keyboard cord to the suitable length, find which color corresponds to which line in your particular keyboard [using the port pinout](https://en.wikipedia.org/wiki/PS/2_port) and multimeter continuity tester.
