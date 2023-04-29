# NanoEls H4

4-axis Electronic Lead Screw (ELS) based on ESP32-S3 for metal lathes ([datasheet PDF](https://raw.githubusercontent.com/kachurovskiy/nanoels/main/h4/h4-20230429.pdf)).

![h4-600px](https://user-images.githubusercontent.com/517919/235074149-307f8b7f-a9d5-4ade-b29a-13809ba81e75.JPG)

Controller itself is available for purchase on https://kachurovskiy.com/

## DIY

For now there's no DIY option for H4 since ordering from Gerber would be prohibitevely expensive - at least $400 for a minimum order due to the large number of small SMD components. Once the project gets traction, we'll likely have a compatible DIY version of the boards but it would still cost close to the commercial hardware since 2 sizeable PCBs, several critical chips, connectors and terminals are required and they all ship from different suppliers.

## Overview

Based on [ESP32-S3-WROOM-1U-N16R2](https://www.espressif.com/sites/default/files/documentation/esp32-s3-wroom-1_wroom-1u_datasheet_en.pdf) module, this controler is designed to be used for home and light industrial automation and control:

- automation of lathes processing metal or plastic parts
- automation of desktop CNC routers and milling machines
- similar applications to control actuators based on digital I/O and user input

In [h4.ino](https://github.com/kachurovskiy/nanoels/blob/main/h4/h4.ino) you can find the electronic lead screw software for this controller.

## Safety

If controller is used as a part of machinery, ensure that resulting machine complies with all applicable laws and regulations. Controller is not a safety device. Do not use the controller if it's damaged or is not working normally. Unplug all connections before disassembly, protect internal components from static electricity when disassembled.

Ensure that your emergency stop button stops all motion and it can't automatically restart when emergency stop is lifted.

## Case

Plastic case is 3D-printed from PLA. Two M5 mounting holes that are 50mm on center are located on the back side.

Two parts of the case are held together with four M3 DIN 7985 4.8 galvanized steel bolts.

## Display

Blue backlight LCD display HD44780 20x04 offers good visibility, acceptable refresh speed and viewing angles. Backlight brightness is controlled with a 1kΩ potentiometer marked "BRIGHTNESS" which is accessible when the back cover is taken off. Display contrast is controlled with the 10kΩ potentiometer tip located on the back.

## Front panel

![image](https://user-images.githubusercontent.com/517919/235322713-c45c8b5e-9223-4557-a0f6-6c5bba58042f.png)

Front panel is made from 0.25mm polycarbonate with dimensions 145x90mm with 39 embossed buttons each 10mm in diameter. Attached with a double-sided adhesive tape, it can be replaced with a different one.

Front panel buttons are controlled with a TCA8418 chip connected to IO5 and IO6 of the ESP32-S3, see schematic below. Software libraries available for this chip making it easy to handle button events in your code.

## Power and USB

Device is powered with 5V via the USB-C port on the back protected with a 300mA holding / 600mA instantaneous current resettable fuse. USB data and power lines are connected to USB ground through ESD diodes.

## Uploading software

USB data lines are connected to the CH9102 USD-to-UART chip that is connected with RX and TX lines of the ESP32-S3. When using Arduino IDE, select "ESP32S3 Dev Module" to upload your sketch. Due to the [module firmware issue](https://github.com/espressif/arduino-esp32/issues/6762) you might have to unplug USB after upload.

## Terminals

![back side](https://user-images.githubusercontent.com/517919/235322800-1e0a9a55-7eab-484f-b63f-092a1d36257d.JPG)

Pluggable screw terminals with 3.5mm pitch are located on the back side of the device. All terminals have ESD and short-circuit protection.

| Group | Terminal | I/O | Description |
| ----- | -------- | --- | ----------- |
| Encoder | GND | output | Ground / neutral |
| Encoder | 5V | output | Encoder 5V power with resettable fuse tripping at 100mA continuous or 200mA instantaneous current at 25°C |
| Encoder | ENCB | in/out | 5V general purpose digital input/output line, IO7 |
| Encoder | ENCA | in/out | 5V general purpose digital input/output line, IO15 |
| Z axis | 5V | output | 5V signal line current-limited with a 200Ω resistor |
| Z axis | ENA | in/out | 5V general purpose digital input/output line, IO16 |
| Z axis | DIR | in/out | 5V general purpose digital input/output line, IO17 |
| Z axis | STEP | in/out | 5V general purpose digital input/output line, IO18 |
| X axis | 5V | output | 5V signal line current-limited with a 200Ω resistor |
| X axis | ENA | in/out | 5V general purpose digital input/output line, IO8 |
| X axis | DIR | in/out | 5V general purpose digital input/output line, IO19 |
| X axis | STEP | in/out | 5V general purpose digital input/output line, IO20 |
| A1 | 5V | output | 5V signal line current-limited with a 200Ω resistor |
| A1 | ENA | in/out | 5V general purpose digital input/output line, IO9 |
| A1 | DIR | in/out | 5V general purpose digital input/output line, IO10 |
| A1 | STEP | in/out | 5V general purpose digital input/output line, IO11 |
| A2 | 5V | output | 5V signal line current-limited with a 200Ω resistor |
| A2 | ENA | in/out | 5V general purpose digital input/output line, IO12 |
| A2 | DIR | in/out | 5V general purpose digital input/output line, IO13 |
| A2 | STEP | in/out | 5V general purpose digital input/output line, IO14 |

## Buzzer

Passive buzzer is connected to IO4 allowing the device to emit a variety of sounds.

## Main board schematic

![nanoels h4 schematic](https://user-images.githubusercontent.com/517919/235243083-bcb5f049-8b22-48ac-9893-384d90eb027f.png)

## Keyboard schematic

![nanoels h4 keypad schematic](https://user-images.githubusercontent.com/517919/235243339-f8324757-1175-4306-bf85-bc3c6ad79657.png)

## Usage limits

- Not a safety device
- Use in temperatures above freezing and below 40°C, not exposed to direct sunlight
- Do not connect over 5.5V on any input, output or terminal
- Flammable

## Disposal

Don't dispose this kit in the unsorted waste, please check with your municipality for electronic parts disposal options.
