**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

# NanoEls H1

**This page is provided for people who have already built or have already started building H1 version of the ELS. If you're just starting, use the new and improved [H2 version](https://github.com/kachurovskiy/nanoels/tree/main/h2).**

Cheap DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

![NanoEls explosion diagram](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/h1-exploded-view.png)

# Features

- Positive and negative screw pitches
  - From -10mm to 10mm
  - Resolution 0.01mm
- Automatic lead screw stops
- Independent carriage moves without losing the thread
- Lead screw position indication
- Spindle angle indication

# Hardware overview

- 5 plastic 3D-printed parts (gears, mounts)
- Uses readily available hardware
  - 46€ Nema 23 stepper and driver (50% more for closed loop)
  - 16€ 48V 5A power supply
  - 9€ printed curcuit board (PCB)
  - 9€ rotary encoder
  - 3€ Arduino Nano
  - 3€ push buttons
  - 2€ OLED display
  - 5V power supply e.g. an old phone charger
  - 8 bolts, 2 nuts, 2 washers and a few wires
  - Optionally, two `2kOhm` resistors
- Does not require metalworking
- Does not require drilling holes in the lathe

# Other hardware required

- Soldering iron, solder
- Hex and screwdrivers
- Soft hammer or a woodworking clamp
- 50T metal gear that your lathe came with
- Grease for the gears

# Build examples

- [bestbean](https://github.com/kachurovskiy/nanoels/discussions/109)
- [Dididu12](https://github.com/kachurovskiy/nanoels/discussions/40#discussioncomment-2019521)
- [Hedning003](https://github.com/kachurovskiy/nanoels/discussions/16)
- [HW61](https://github.com/kachurovskiy/nanoels/discussions/43)
- [kachurovskiy](https://www.youtube.com/watch?v=9uTdDk2EqG4?t=272)
- [mockendon](https://github.com/kachurovskiy/nanoels/discussions/32)
- [Sonny Madlangbayan](https://www.youtube.com/watch?v=qiPQUa50Uog)
- [wberggren](https://github.com/kachurovskiy/nanoels/discussions/13)
- [WillieJilesen](https://github.com/kachurovskiy/nanoels/discussions/39)
- [zabu83](https://github.com/kachurovskiy/nanoels/discussions/11)

# Limitations

- PLA plastic gears and mounts shouldn't heat up or they will deform and disconnect. Stepper can heat up quite a bit during continuous operation. Depending on the stepper driver current, the limit seems to be ~50% duty cycle with 10min operation / 10min cooldown. For higher duty cycle something like metal HTD 5M gears, belt and a metal stepper mount would be required. Another option is using PETG or ABS.
- Nema 23 stepper usable maximum is ~600 RPM, here a 1:1 stepper to leadscrew ratio is used. In practice this means that cutting e.g. 2mm thread with a 2mm leadscrew spindle top speed should stay under 600 RPM.
  - Cheap brand-less drivers are worse at handling high RPM
  - NanoEls would take the stepper at 1000 RPM and higher but it likely won't have much torque at that point
  - This can be mitigated to some extent by using e.g. 40 tooth gear on the leadscrew and 60 tooth gear on the motor at the expense of the maximum leadsrew torque
- Lead screw position only equals the carriage position if the backlash was taken out before the measurement started. Changing the direction introduces the backlash again.

# Big display

NanoEls also supports LCD2004 displays [such as this one (4€)](https://www.aliexpress.com/item/4001135515638.html). Those are 20-char, 4-line with 5mm tall letters comparing to 2.5mm tall letters on an OLED display. Full update takes `57ms` on an LCD comparing to `46ms` on OLED. The backlight could be a bit uncofortable for the eyes, see [a visual comparison](https://imgur.com/a/TbHg9Y3).

If you're using LCD2004, uncomment the line `#define LCD`, install the library `LiquidCrystal I2C` from [Frank de Brabander](https://github.com/fdebrabander) via the Library Manager and re-upload the sketch.

# Instructions

We've tried to simplify the process as much as possible but building NanoEls is still going to take considerable time and effort, basic mechanical and electrical knowledge.

You might need to design your own mounts and gears if the ones we have don't fit. If you need help designing a 3D printed part, please open a GitHub Issue with exact dimensions of the part that you need.

## Parts

See https://github.com/kachurovskiy/nanoels/blob/main/hardware.md for encoder, motor, gearing and mounting info.

### Arduino Nano

The code was tested using an Arduino Nano V3 clone.

### OLED display

SSD1306 monochrome 4-pin I2C OLED 128x64 display. **Warning:** make sure that your OLED has legs in the following order to work on the PCB - GND VCC SCL SDA.

### Buttons

Using 6x6x13mm switches. 13mm is the optimal height for the provided case, if you're using a different case, desired height might be different. AliExpress has very convenient 200 button sets of different height for a few euros.

6x6 buttons can be too small for fingers to comfortably click, consider buying caps to put on them, keywords for AliExpress are "switch push button hat 6mm".

### 5V power supply

Arduino Nano doesn't draw much current so a 5V 0.5A phone charger would work.

### PCB

![NanoEls H1 PCB](https://github.com/kachurovskiy/nanoels/blob/main/h1/pcb/nanoels-pcb-h1.png)

[Gerber ZIP for production](https://github.com/kachurovskiy/nanoels/blob/main/h1/pcb/nanoels-pcb-h1.zip)

It's a 70mm by 90mm board with holes for M3 mounting bolts, 1.6mm thick. You will need clearance above, below and on the sides of the board for the through-hole components, their pins (legs) and wires coming into the PCB.

PCB is best placed away from the electromagnetic noise sources such as lathe motor wires. Grounded metal housing is ideal.

**Some PCB production techniques use lead and other nasty stuff. Order at your own risk and dispose properly.**

Ordering it from JLCPCB takes just a few clicks - upload the ZIP file, use all default settings, choose shipping and checkout.

### 3D-printed parts

#### Case

![Case](https://github.com/kachurovskiy/nanoels/raw/main/h1/case/case.png)

[STL part 1](https://github.com/kachurovskiy/nanoels/raw/main/h1/case/nanoels-box-part1.stl) and [part 2](https://github.com/kachurovskiy/nanoels/raw/main/h1/case/nanoels-box-part2.stl)

Case size is 102x82x27mm. PCB is mounted onto the case with 4 M3 bolts.

## Assembly

**Working with electrical wiring is dangerous, unplug the lathe. Proceed at your own risk.**

Connect the 24V and 5V power supplies to the lathe power so that the lathe on/off and safety switches cut off the power for the ELS too.

Test Arduino Nano **before** soldering it on, unsoldering it without a desoldering station is very hard.

Don't solder the Arduino upside-down or rotated 180 degrees, check the white outlines on the board.

Carefully solder 10 buttons (6X6X11 switches to fit the provided case), OLED 128x64 4-pin display and an Arduino Nano onto it. Plug USB into Arduino to test - display and buttons shoulad already work.

It's important that buttons are soldered vertically or the result won't fit into a case. To achieve this, solder only 2 diagonal legs for each button first while pressing on the button firmly. Then check all buttons for verticalness, at this point it's easy to correct the angle by pressing on the button and re-heating one of the legs. Once satisfied, proceed to solder all the remaining legs. 

![Assembly](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/h1-assembly.jpg)

Solder 5V/GND wires to the PCB.

Solder encoder and stepper driver wires to the PCB according to the input/output labels on the PCB.

![PCB wiring](https://github.com/kachurovskiy/nanoels/raw/main/h1/buildexamples/nanoels-pcb-h1.jpg)

**Important: there can be a metal mesh under the insulation around your wires, it's shielding, don't just cut it off. Solder it to ground (GND), together with the black ground cable.**

Screw terminals are designed to be soldered on the bottom side of the PCB.

Optinally solder two 2kOhm pull-up resistors. They aren't strictly needed but will improve the stability of the optical encoder readings.

## Programming the Arduino

- Download the Arduino IDE
- Install `Adafruit_SSD1306` and `FastGPIO` libraries via the Library Manager in the Arduino IDE
- Download and open [NanoEls.ino](https://github.com/kachurovskiy/nanoels/raw/main/h1/NanoEls.ino)
- Check the top constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Upload the sketch to your Arduino Nano
- Swap D2 and D3 pins in the code if carriage direction is inverted, re-upload

# Operating the ELS

## Safety

- Make sure that stepper motor and ELS are turned off using the lathe emergency power off switch
- Test the automatic stop and other ELS functionality before relying on it
- **In case of unexpected movements, disengage the half-nut or use the emergency power off switch**

## Turning

- Select the desired pitch using `-` and `+` buttons or `0.10mm`, `1mm` and `2mm` shortcut buttons in the top row
- Turn on the lead screw using the `ON` button
- Start the lathe spindle
- Stop the lathe spindle when done
- Turn off the lead screw using the `ON` button

## Automatic stops

- Move the carriage with the help of ELS to the desired stop position
- Set the stop using e.g. `L STOP` button
- Hold `RIGHT` to move to another stop position and press `R STOP`

Now you can:

- Use lathe forward/reverse spindle movements to move the carriage between the stops
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more when required to stay on the thread) within the stops in either direction when spindle is not turning

Setting only one stop is also supported. Stops aren't lost when `ON` button is clicked or pitch is changed.

## Carriage movements

- Make sure the cutting tool is not going to contact the material and there's room to move the carriage physically
- Use `LEFT` and `RIGHT` buttons to move the carriage ~1mm (possibly more or less when required to stay on the thread) when spindle is not turning
- If stops are set, they will be respected

Using `LEFT` and `RIGHT` buttons is not supported when the spindle is turning and ELS is on.

## Losing the thread

The spindle and stepper positions are reset to 0 every time one of the following happens:

- `ON` button is pressed (including long press for reset)
- Pitch is changed e.g. by pressing `-` or `+`
- Stepper is not in the desired position when ELS is powered up
  - Results in `LTW` lost thread warning
  - Might happen if ELS was abruptly shutdown

Thread is **not** lost when ELS is simply powered off.

## Out-of-sync situations

It's possible for the lead screw to go out of sync with the spindle by removing the `L STOP` or `R STOP` while the carriage is standing on it. It's indicated by the `SYN` word on the display.

This situation should resolve itself once the spindle makes a full turn.

## Resetting ELS and viewing the software version

ELS remembers all the positions and ON/OFF status when powered off.

- Hold `ON` button for 6 seconds
  - Reset stepper and spindle positions to 0
  - Resets pitch to 0
  - Removes stops
  - Removes out-of-sync state
  - Shows NanoEls version

# Troubleshooting

## My stepper is skipping steps

1. Check that `ENCODER_STEPS`, `MOTOR_STEPS` and `LEAD_SCREW_HMM` parameters you used match your hardware. E.g. if you tell ELS that `MOTOR_STEPS` is 400 but your actual driver is set to 200, ELS will try to move the stepper too fast and it will stall.
2. Check the mechanical connection between the stepper and the lead screw, try rotating the stepper by hand when lathe is OFF. It shouldn't be too hard to turn. If you're using gears, ensure they're turning freely, not jamming and have a tiny bit of backlash. If you're using a belt, make sure it's not overtightened.
3. Try using higher voltage, within limits of your stepper and driver. For NEMA 23, best performance is achieved at 48V but the driver has to support it.
4. Try increasing the current on your driver, within the limits of your stepper.
5. If you have a cheap brand-less driver, consider getting a higher quality driver.
6. For an immediate fix, change the acceleration (line 23) PULSE_DELTA_US from `7` to `2`, PULSE_MIN_US (line 21) from `500` to e.g. `700`.
7. Consider using a sufficently strong closed-loop stepper instead. I didn't try them myself but there are some high-rated closed loop stepper-driver sets on AliExpress for 69€.
