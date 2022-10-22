**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

# NanoEls H2

This is the second hardware version (hence H2) of NanoEls electronic lead screw controller. It still uses Arduino Nano
microcontroller, a [custom PCB board](https://github.com/kachurovskiy/nanoels/blob/main/h2/Gerber_PCB_NanoElsLcd_20220815.zip) you
can print cheaply on jlcpcb.com and a few widely available components allowing you to build a DIY single-axis ELS.

![image](https://user-images.githubusercontent.com/517919/188740458-17936e54-3a53-435a-9475-1c2a5db8f14e.png)

This is still somewhat a work in progress but already much better than the original NanoEls:

- Big screen
- Nice terminals
- Convenient buttons
- Disabling stepper when it's not used (less buzzing)
- Controlling left/right movement step - 1mm, 0.1mm, 0.01mm
- Moving left/right while ON
- On/off switch
- Tachometer

It's still isn't fully tested so use caution and report any problems.

## Components

- Arduino Nano (mini USB style)
- 2004 LCD display
- 12 buttons 6x6mm, each 6mm tall
- 8 1kOhm resistors, one 1MOhm resistor (or similar)
- 6 M3 nylon stand-offs (12mm long) and screws
- 3 KF2EDG sockets (Curved needle, 4P, 3.5MM)
- 3 KF2EDG plugs (Plug Terminal, 4P, 3.5MM)
- MTS-102 on-off switch
- RV09 10kOhm potentiometer
- 6 M3 threaded inserts

All of this can easily be found on AliExpress, eBay or Amazon.

## Case

3D models ready for printing: [main case](https://github.com/kachurovskiy/nanoels/blob/main/h2/nanoels-lcd-case.stl),
[lid](https://github.com/kachurovskiy/nanoels/blob/main/h2/nanoels-lcd-lid.stl),
[button](https://github.com/kachurovskiy/nanoels/blob/main/h2/nanoels-lcd-button.stl).

## Assembly

1. Check that your Arduino Nano is functional before soldering
1. Solder everything except the display onto the PCB, pay attention which side a part should be facing (up/down/left/right) and ensure Arduino pins won't be touching the display later
1. Ensure perfect soldering joints on 1kOhm resistors or the vertical row of buttons won't work well
1. Solder the display on, place something non-conductive between the display and the PCB (not the sticky tape as the glue can actually be conductive)
1. Check that your board is working (connect to a PC via Arduino Nano USB port, upload code) before inserting it into the case
1. Push threaded inserts into the case using your soldering iron
1. Drill out the main case button holes using a 7mm drill and ensure the buttons are moving freely
1. Insert buttons into the case, insert PCB, screw in stand-offs (sorry, it's non-trivial), close the lid and screw it to the stand-offs

## Schematics

![image](https://user-images.githubusercontent.com/517919/188740119-b6828cdd-18e2-4a48-bcff-6731e3227fa5.png)

## PCB

![image](https://user-images.githubusercontent.com/517919/188741755-bee83e05-6a87-45e7-9aa7-31f791054ae7.png)

[Gerber ZIP](https://github.com/kachurovskiy/nanoels/blob/main/h2/Gerber_PCB_NanoElsLcd_20220815.zip)

## Programming the Arduino

- Download the Arduino IDE
- Install `LiquidCrystal` and `FastGPIO` libraries via the Library Manager in the Arduino IDE
- Download and open [NanoEls.ino](https://github.com/kachurovskiy/nanoels/raw/main/h1/NanoEls.ino)
- Check the top constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Upload the sketch to your Arduino Nano
- Swap D2 and D3 pins in the code if carriage direction is inverted, re-upload

# Operating the ELS

![image](https://user-images.githubusercontent.com/517919/197326097-cf824f31-d50e-4964-8bbc-1632c92ff40b.png)

## Safety

- Make sure that stepper motor is turned off using lathe emergency power off switch
- Test the automatic stop and other ELS functionality before relying on it
- **In case of unexpected movements, disengage the half-nut or use the emergency power off switch**

## Setting pitch

Pitch is the distance that carriage will move when the spindle makes the full turn. For example, M14 thread uses 2mm pitch.

Select the desired pitch using `-` and `+` buttons or `0.10mm`, `1mm` and `2mm` shortcut buttons in the top row. If you keep the buttons pressed, the pitch starts changing faster after a few seconds.

Some inch threads require setting the micron part (3rd precision point) of the pitch, to do that click the `Step` button until you're in the `0.001mm` mode. Now clicking `-` or `+` buttons will change the pitch by a micron.

## Turning

- Set desired pitch using `-` and `+` buttons
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
- Use `LEFT` and `RIGHT` buttons to move the carriage within the stops

Setting only one stop is also supported. Stops aren't lost when `ON` button is clicked or pitch is changed.

## Moving the carriage

Use `LEFT` and `RIGHT` buttons to move the carriage. If stops are set, they will be respected during the movement.

When the ELS is off, carriage will move by the distance set using `Step` button (1mm if not shown on screen) but at least 1 stepper motor step.

When the ELS is ON, carriage will move in pitch increments (stay in the thread) and travel at least the distance set by `Step` button (1mm if not shown on screen).

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
