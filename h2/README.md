This software and instructions are provided as is, [without warranty of any kind](LICENSE).

# NanoEls H2

This is the second hardware version (hence H2) of NanoEls electronic lead screw controller. It still uses Arduino Nano
microcontroller, a [custom PCB board](https://github.com/kachurovskiy/nanoels/blob/main/h2/Gerber_PCB_NanoElsLcd_20220815.zip) you
can print cheaply on jlcpcb.com and a few widely available components allowing you to build a DIY single-axis ELS.

![image](https://user-images.githubusercontent.com/517919/217100536-5412f1bf-da5f-4414-a2ed-c4bd029409aa.png)

Features:

- Big screen
- Nice terminals
- Convenient buttons
- Disabling stepper when it's not used (less buzzing)
- Controlling left/right movement step - 1mm, 0.1mm, 0.01mm and 0.001mm
- Higher precision when turning imperial pitches
- Moving left/right while ON
- On/off switch
- Tachometer
- Multi-start threads
- Asynchronous mode
- Metric, inch and TPI support
- Quick reverse

⚠️ Due to Arduino relatively low frequency and realtime requirements (can't plan the motion ahead) H2 can only issue 2800 step impulses per second. This means that the motor can reach ~800 RPM at 200 steps per revolution or ~200 RPM at 800 steps per revolution. Make sure to use a motor with a driver that can do full steps or use the [H4 controller](https://github.com/kachurovskiy/nanoels/tree/main/h4) instead.

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
[button](https://github.com/kachurovskiy/nanoels/blob/main/h2/nanoels-lcd-button.stl). You can print it at home or e.g. at [JLCPCB](https://cart.jlcpcb.com/quote).

## Assembly

1. Check that your Arduino Nano is functional before soldering
1. Solder everything except the display onto the PCB, pay attention which side a part should be facing (up/down/left/right) and ensure Arduino pins won't be touching the display later
1. Ensure perfect soldering joints on 1kOhm resistors or the vertical row of buttons won't work well
1. Solder the display
1. Check that your board is working (connect to a PC via Arduino Nano USB port, upload code) before inserting it into the case
1. Push threaded inserts into the case using your soldering iron
1. Drill out the main case button holes using a 7mm drill and ensure the buttons are moving freely
1. Insert buttons into the case, insert PCB, screw in stand-offs (sorry, it's non-trivial), close the lid and screw it to the stand-offs

## Wiring

Starting from the top terminal:

- 5V - connect to 5V power supply positive output (usually red) through an emergency stop button
- GND - connect to 5V power supply negative output (usually black)

Encoder terminal:

- ENCA - connect to one of the encoder signal lines
- ENCB - connect to one of the encoder signal lines
- 5V - connect to encoder power-in line (usually red)
- GND - connect to encoder power-in line (usually black) and wire shielding if there's any

Stepper terminal:

- STEP - connect to stepper driver PUL-
- DIR - connect to stepper driver DIR-
- ENA - connect to stepper driver ENA-
- 5V - connect to stepper driver PUL+, DIR+, ENA+ and wire shielding if there's any

## Schematics

**WARNING:** trying to build this on a breadboard will result in [interference problems](https://github.com/kachurovskiy/nanoels/discussions/89) and will likely make the device unusable. Please use the PCB instead.

![image](https://user-images.githubusercontent.com/517919/188740119-b6828cdd-18e2-4a48-bcff-6731e3227fa5.png)

## PCB

![image](https://user-images.githubusercontent.com/517919/188741755-bee83e05-6a87-45e7-9aa7-31f791054ae7.png)

[Gerber ZIP](https://github.com/kachurovskiy/nanoels/blob/main/h2/Gerber_PCB_NanoElsLcd_20220815.zip)

## Programming the Arduino

- Download the Arduino IDE
- Install `LiquidCrystal` and `FastGPIO` libraries via the Library Manager in the Arduino IDE
- Download [this repository](https://github.com/kachurovskiy/nanoels/archive/refs/heads/main.zip), unzip, go to `h2` directory and open `h2.ino` file in Arduino IDE
- Check the top constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Upload the sketch to your Arduino Nano
- Spindle direction: show angle on screen using top-right button. Rotate the chuck forward manually - angle should increase. If it decreases, swap `ENC_A` and `ENC_B` values in the code, re-upload the sketch
- Motor direction: try `LEFT` and `RIGHT` buttons - if motor is moving in the wrong direction, change the value of `INVERT_STEPPER` in the code, re-upload the sketch

# Operating the ELS

![image](https://user-images.githubusercontent.com/517919/211652845-b4b8b73f-1903-491a-b49c-170681a01fbd.png)

## Safety

- **In case of unexpected movements use Emergency Stop button.** Ensure that your Emergency Stop button stops all motion and it can't automatically restart when Emergency Stop is lifted.
- Ensure that your machine complies with all applicable laws and regulations e.g. [Machinery Directive](https://eur-lex.europa.eu/legal-content/EN/TXT/?uri=celex%3A32006L0042) in Europe.
- Test the controller functionality before relying on it. Don't operate machinery without the necessary training and knowledge, in a hurry or when tired.

## Switching between metric and imperial

Use button that is second from the bottom in the vertical row of buttons to change the system of measurement between:

- Metric (mm)
- Inch
- TPI

It affects how the pitch and position is displayed and changes, move steps for precision moves.

## Setting pitch

Pitch is the distance that carriage will move when the spindle makes the full turn. For example, M14 thread uses 2mm pitch.

Select the desired pitch using `-` and `+` buttons. If you keep the buttons pressed, the pitch starts changing faster after a few seconds.

Use negative pitch values e.g. `-2mm` to cut left-to-right threads. Do do that, you have 2 options:

- hold the `-` button until the pitch drops below 0 to the required value
- or press the bottom-right button to toggle the pitch sign between `+` and `-`

Some inch threads require setting the micron part (3rd precision point) of the pitch, to do that click the `Step` button until you're in the `0.001mm` mode. Now clicking `-` or `+` buttons will change the pitch by a micron.

## Turning

- Set desired pitch using `-` and `+` buttons
- Turn on the lead screw using the `ON` button
- Start the lathe spindle, use `LEFT` and `RIGHT` buttons to move if needed, stop spindle when done
- Turn off the lead screw using the `ON` button

## Soft limits / automatic stops

Move the carriage using `LEFT` or `RIGHT` to the desired stop position and press `L STOP` or `R STOP` depending on which limit you'd like to set.

When both limits are set, you can:

- Use lathe forward/reverse spindle movements to move the carriage between the stops
- Use `LEFT` and `RIGHT` buttons to move the carriage within the stops

Setting only one stop is also supported. Stops aren't lost when `ON` button is clicked or pitch is changed.

## Moving the carriage

Use `LEFT` and `RIGHT` buttons to move the carriage. If stops are set, they will be respected during the movement.

When the ELS is off, carriage will move by the distance set using `Step` button but at least 1 stepper motor step.

When the ELS is ON, carriage will move in pitch increments (stay in the thread) and travel at least the distance set by `Step` button.

## Multi-start threads

Use middle button in the right-side vertical row of buttons (`Mode` button) and switch into the `MUL` mode. Use `+` and `-` buttons to increase/decrease the number of starts in your multi-start thread.

Set left and right limits. Cut thread normally and use `LEFT` or `RIGHT` buttons to move the carriage between cuts (no need to turn off the spindle). Controller automatically moves to the next start of the thread when a limit is reached.

## Asynchronous mode

Click `Mode` button until you enter the `ASY` mode. In this mode the spindle rotation is ignored and motor moves with a constant speed of 1 pitch per second when ELS is `ON`. Limits and manual movement works normally.

## Losing the thread

The spindle and stepper positions are reset to 0 `ON`, `-` or `+` buttons are pressed.

## Out-of-sync situations

It's possible for the lead screw to go out of sync with the spindle by removing the `L STOP` or `R STOP` while the carriage is standing on it. It's indicated by the `SYN` word on the display.

This situation should resolve itself once the spindle makes a full turn.

## Resetting ELS and viewing the software version

ELS remembers all the positions and ON/OFF status when powered off. Hold `ON` button for 5+ seconds to:

  - Reset stepper and spindle positions to 0
  - Resets pitch to 0
  - Removes stops
  - Removes out-of-sync state
  - Shows NanoEls version
