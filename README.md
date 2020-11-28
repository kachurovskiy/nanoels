**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

# NanoEls

90€ DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

![Assembled ELS without the metal housing](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/h1-exploded-view.png)

# Features

- Positive and negative screw pitches
  - From -10mm to 10mm
  - Resolution 0.01mm
- Automatic lead screw stops
- Carriage movements without losing the thread

# Hardware overview

- Relies on 3D-printed parts (gears, mounts)
- Uses readily available hardware
  - 52€ Nema 23 stepper and driver
  - 10€ 24V 5A power supply
  - 9€ printed curcuit board (PCB)
  - 9€ rotary encoder
  - 3€ Arduino Nano
  - 3€ push buttons
  - 2€ OLED display
  - A few bolts, nuts, washers, wires and wire connectors
- Does not require metalworking
- Does not require drilling holes in the lathe

# Other hardware required

- Soldering iron, solder
- Hex and screwdrivers
- Soft hammer or a woodworking clamp
- 50T metal gear that your lathe came with
- Grease for the gears

# Supported lathe models

As long as you can securely connect the rotary encoder to the spindle and stepper motor to the leadscrew, most lathes are supported.

3D printed gears and mounts are available for the following models:

- WM210 or WM210V

Please note that any 2 lathes of the same model can have different dimensions and 3D printed parts might not fit. Please share with us your 3D models if you made new ones.

# Instructions

We've tried to simplify the process as much as possible but building NanoEls is still going to take considerable time and effort, basic mechanical and electrical knowledge.

You might need to design your own mounts and gears if the ones we have don't fit.

## Picking hardware, checking dimensions

### Stepper and driver

I used the following one but most Nema 23 or higher steppers should work.

- Nema 23 Stepper Motor Bipolar 1.8deg 3.0 Nm 4.2A 57x57x113mm 4 Wires Open Loop
- DM556Y Driver 1.7-5.6A DC20V~50V

DM556Y is 118.5mm wide which fits the case 3D model. Other drivers might not fit into it.

Closed Loop stepper might be nice to have but not necessary for NanoEls to work on small lathes. For bigger lathes or heavy cuts, closed loop system would be better.

It's entirely reasonable to locate the driver in the electrical cabinet and not under the lathe as shown above - but make sure to get the stepper with a shielded cable in that case.

It's suggested to run the stepper in the 400 steps mode as a balance between Arduino Nano signalling capabilities and the smoothness of the movements.

Check the diameter of the part that you will attach the stepper to: for the provided 3D-printed part to fit, it has to be 28mm. Check that the stepper can rest on e.g. a piece of rubber when attached to the lathe - provided 3D printed part is only held by friction and is not designed to hold the full weight of the stepper long term.

### Encoder

Tested with the [following 600 steps encoder](https://www.amazon.de/-/en/gp/product/B015GYY7XU) but 200 and 400 step encoders will also work. It's possible to salvage one of these from an old printer, they are also readily available on AliExpress as "optical rotary encoder".

Check the distance between the spindle gear and the lathe housing: for the provided conical gear to fit, it has to be 23mm.

### PCB

**Nov 2020: This version of the PCB design is not yet fully tested, please wait a few weeks**

It's a 70mm by 90mm board with holes for M3 mounting bolts, 1.6mm thick. You will need clearance above, below and on the sides of the board for the through-hole components, their pins (legs) and wires coming into the PCB.

PCB is best placed away from the electromagnetic noise sources such as lathe motor wires. Grounded metal housing is ideal.

## Ordering

### Hardware

**Parts you order might not work together. They might not be suitable for your particular setup. Order at your own risk.**

Most parts can be ordered on AliExpress or Banggood.

It might make sense to order the stepper, driver and the 24V power supply locally since these are popular items and are available from local suppliers at comparable prices.

### PCB

**Some PCB production techniques use lead and other hazardous materials. Order at your own risk.**

Ordering it from JLCPCB takes just a few clicks - upload the ZIP file, use all default settings, choose shipping and checkout.

## Assembly

**Working with electrical wiring is dangerous, unplug the lathe. Proceed at your own risk.**

Connect the 24V and 5V power supplies to the lathe power so that the lathe on/off and safety switches cut off the power for the ELS too.

Make sure Arduino Nano is working before soldering it on, unsoldering it without a desoldering station is very hard.

Carefully solder 11 buttons (6X6X11 switches to fit the provided case), OLED 128x64 4-pin display and an Arduino Nano onto it.

Solder 5V/GND wires to the PCB. At this point it can be powered up, display should work.

Solder encoder and stepper driver wires to the PCB according to the input/output labels on the PCB.

## Gears

When connecting the gears, make sure to leave ~0.5mm space between them for optimal threading. This can be achieved e.g. by temporarily placing a piece of paper between them.

## Programming the Arduino

- Download the Arduino IDE
- Install `Adafruit_SSD1306` library via the Library Manager in the Arduino IDE
- Upload the `NanoEls.ino` sketch into your Arduino Nano

# Operating the ELS

ELS remembers all the positions and ON/OFF status when powered off.

## Safety

- Make sure that stepper motor and ELS are turned off using the lathe emergency power off switch
- Test the automatic stop and other ELS functionality before relying on it
- **In case of unexpected movements, disengage the half-nut or use the emergency power off switch**
- **ELS buttons might not respond when stepper is working**

## Turning

- Select the desired pitch using `-` and `+` buttons
- Turn on the lead screw using the `ON` button
- Start the lathe spindle
- **Warning: it's not currently possible to turn `OFF` the ELS while spindle is running due to Arduino Nano limitations**
- Stop the lathe spindle when done
- Turn off the lead screw using the `ON` button

## Automatic stops

- Move the carriage manually or with the help of ELS to the desired stop position
- Turn on the lead screw using the `ON` button
- Set the stop using the `R STOP` button
- Start the lathe spindle
- Stop the lathe spindle when at the end position
- Set the stop using the `L STOP` button

Now you can:

- Use lathe forward/reverse spindle movements to move the carriage between the stops
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more when required to stay on the thread) within the stops in either direction when spindle is not turning
  - Moving exactly onto the stop with `LEFT` and `RIGHT` buttons is not currently supported, carriage will only go to the closest thread position to the stop

Setting only one stop is also supported.

## Carriage movements

- Make sure the cutting tool is not goign to contact the material and there's room to move the carriage physically
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more when required to stay on the thread) when spindle is not turning
- If stops are set, they will be respected
- Behavior when ELS is on and spindle is turning is untested

## Resetting ELS and viewing the software version

- Hold `ON` button for 6 seconds

# Contributing to the project

- Questions: please file a GitHub Issue
- Successful/failed builds: please file a GitHub Issue with explanations and photos
- Code changes: please only make the necessary minimal edits
  - Split unrelated changes into separate PRs
- PCB changes: incompatible changes (move button / display / Arduino / change PCB size / change used pin purpose) will require making `h2` folder with another hardware version of the project, please file an Issue first to confirm. Backward-compatible PCB changes are cool.
- 3D models: in most cases, don't edit the model, add a new file. Also include the PNG preview and a dimension drawing if possible.

# Example builds

![Assembled ELS without the metal housing](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/buildexample1.jpg)
