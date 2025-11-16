# NanoEls H5

Latest version of the electronic lead screw controller for metal lathes.

![PXL_20241218_185410002](https://github.com/user-attachments/assets/1614d9eb-5c23-4cba-9d8e-3f95d866bff7)

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

## Display options

You can use any other Nextion display model including cheaper and smaller ones without touch.

- Requires re-compiling the `h5.tft` file from the [h5.HMI](https://github.com/kachurovskiy/nanoels/blob/main/h5/screen/h5.HMI) for your display
- Needs custom 3D-printed case since `case/h5case.step` will no longer fit

## Ordering PCB

1. Go to https://cart.jlcpcb.com/quote, click "Add gerber file"
2. Use Gerber ZIP file supplied in https://github.com/kachurovskiy/nanoels/tree/main/h5/pcb/
3. Select `LeadFree HASL` and `Global Standard Direct Line` shipping
4. Should cost 5€ and arrive within 2 weeks

## Schematics and PCB component placement

![schematics](pcb/schematics.png)

![image](https://github.com/user-attachments/assets/9f769450-df6a-4440-b288-81dae1a53ff5)

## Assembly instructions

NOTE: throughout the assembly make sure to avoid static electricity accumulation on your body by wearing suitable clothes and shoes, not using chairs known to cause ESD. Touch any grounded metal device housing to check.

![image](https://github.com/user-attachments/assets/8a630150-ad79-434e-bc0c-9a0f711de5bb)

1. Check that ESP32 board is working by uploading [h5.ino](h5.ino) onto it using Arduino IDE. See `Programming the controller` section below for more info.
2. Solder ESP32, 2x SN74HCT245N and optional curved 4-pin header onto the PCB. **Triple check the side and orientation of each piece before soldering.**
3. Insert USB extension into the COM port
4. Separate all terminals into 2 pieces. Insert female terminals into the 3D-printed housing. Place the PCB on top and secure it with 4 M3 bolts. Secure the other end of the USB cable in the access hole with an M3 bolt.
5. Solder 15 terminals to the PCB while everything is positioned in the case.
6. Remove screen back cover. Attach the included 4-lead wire to the screen and to the PCB - each `RX` should be attached to `TX` on the other side.
7. Bolt the case and screen together using the bolts that used to hold the back cover.
8. Use empty MicroSD card 32 GB or smaller formatted as FAT32. Copy [h5.tft](screen/h5.tft) to the card, insert into the screen. Connect 5V power supply to the POWER terminal, wait for screen to report that flashing has finished. Disconnect the power, remove the card.
9. Cut the keyboard cord to the suitable length, find which color corresponds to which line in your particular keyboard [using the port pinout](https://en.wikipedia.org/wiki/PS/2_port) and multimeter continuity tester.
10. Supply up to 2A of power to the `POWER` terminal. You can flash the ESP32 via the USB but 0.5A provided by standard USB is not enough to start the screen.

## Rear label

Print [h5.pdf](case/h5.pdf) on a normal printer as A4 at 19% scale, cut out and glue to the back of the case using e.g. double-sided tape.

If you want, you can modify the label by editing [h5.fig](case/h5.fig) file on figma.com and export a new PDF for printing.

## Wiring

ENCODER terminal:

- 5V - connect to encoder power-in line (usually red)
- GND - connect to encoder power-in line (usually black) and wire shielding if there's any
- ENCB - connect to one of the encoder signal lines
- ENCA - connect to one of the encoder signal lines

Z and X axes - stepper terminal for the lead screws:

- 5V - connect to stepper driver PUL+, DIR+, ENA+ and wire shielding if there's any
- ENA - connect to stepper driver ENA-
- DIR - connect to stepper driver DIR-
- STEP - connect to stepper driver PUL-

Pulse motion wheels for Z and X axes (`ZPULSE`, `XPULSE`) are wired in the same manner as the encoder. For any encoder terminal, switch `A` and `B` wires to invert the encoder direction.

Scale and joystick terminals aren't used in the code yet.

## Programming the controller

- Install the [Arduino IDE](https://docs.arduino.cc/software/ide-v2)
- Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` in [Preferences as "Additional board manager URLs"](https://github.com/kachurovskiy/nanoels/assets/517919/dcc023e6-20fc-4284-ba56-d466dbe4ce53)
- Install `esp32` [via Board Manager](https://github.com/kachurovskiy/nanoels/assets/517919/094d00ff-1e51-4f26-bb81-aa4ad42bde2a)
- Install `PS2KeyAdvanced` and `WebSockets` via Arduino IDE Library Manager
- Download [this repository](https://github.com/kachurovskiy/nanoels/archive/refs/heads/main.zip), unzip, go to `h5` directory and open `h5.ino` file in the Arduino IDE
- Check the top constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Select "ESP32S3 Dev Module" as device at the top, pick COM port that appears when you connect the device with a USB cable
- Upload the sketch to your H5 controller

A few things to check after upload:

- Spindle direction: rotate the chuck forward manually - angle on screen should increase. If it decreases, swap `B` and `A` wires in the terminal
- Motor direction: try moving motors using keyboard arrows - if motor is moving in the wrong direction, change `INVERT_Z` or `INVERT_X` in the code, re-upload the sketch (or swap the motor leads `A+` and `A-` in the stepper driver if it's open loop)

Troubleshooting:

- Arduino IDE doesn't detect NanoEls H5: try a different USB cable
- Arduino IDE fails to upload the sketch: make sure you plugged the extension into the `COM` port, **not** the `USB` port on the ESP32
- Not sure which COM port is NanoEls H5: unplug it, check the list of available ports in Arduino IDE, plug H5 in, see new port that appeared is H5
- `ImportError: No module named serial` error on Linux: try `sudo apt install python3-serial`

## Mounting options

On the back of the case there are 2 holes for M5 threaded inserts 130mm on center.

## GCode over WiFi for complex parts

Specify your WiFi network name and password in https://github.com/kachurovskiy/nanoels/blob/main/h5/h5.ino#L45-L46 and NanoEls will show the IP address on screen once it connects to the network. Enter that address in the browser to see the Web UI. It can be used to save GCode files onto controller and run them later at the machine in the GCODE mode.

To generate GCode for your parts, upload STL model of your part to https://kachurovskiy.com/lathecode/ and specify parameters like stock diameter and tool used.

Handwheels and limits have no effect when GCODE is running.

![image](https://github.com/user-attachments/assets/aa6fadc7-5d02-4daa-a4c3-610740492b99)

## Custom keyboard mapping

Use [`#define B_...`](https://github.com/kachurovskiy/nanoels/blob/main/h5/h5.ino#L124) constants to adjust key mapping, uncomment [a line](https://github.com/kachurovskiy/nanoels/blob/main/h5/h5.ino#L3001) in `void processKeypadEvent()` function to see on Nextion which key code your keyboard sends for any given key.

## Usage manual

Controller can be controlled via touchscreen and/or keyboard. Keyboard is optional but it's much nicer to use mechanical buttons for manual moves and not worrying about accidentally pressing a nearby button on the touchscreen.

### Touchscreen

If descriptions of the buttons below are unclear, don't worry, skip this section and read the rest of the manual, that should clarify things.

![h5v11screen](https://github.com/user-attachments/assets/7634182a-a3e4-4dec-bc8b-5d9a3d7d92bf)

Top line:

- `bStatus` turns the controlled off - stops the ongoing operation or manual move, resets spindle angle and turns to 0
- `bMode` turns the controlled off and changes the mode
- `mMultistart` increases the amounts of starts by 1 when pressed in short intervals, sets amount of starts to 1 if pressed after a pause
- `tPitch` reverses the pitch - makes it positive if it's negative, makes it negative if it's positive. Reversing makes the controller "loose the thread" so don't use it for returning back for another threading pass.
- `bMeasure` changes measuring system between metric, imperial and tpi
- `mPlus` increments the pitch or number of passes in a multi-pass operation
- `mMinus` decrements the pitch or number of passes in a multi-pass operation

Middle line:

- `tStepVal` toggles between different step sizes used in manual moves
- `tRPMVal` shows current rotations per minute of the spindle
- `tTurnsVal` shows the number of full turns performed by the spindle since the last off/stop command
- `tAngleVal` shows the current angle of the spindle

X axis group:

- `mXUp` and `tXUp` clear the up limit if it's set, sets the limit in the current `X` position if it's not set
- `bX` enables or disables the axis. When pressed with active numpad input, considers the input as measured diameter of the part at current cutter position and sets `X` zero to negative half of the given diameter.
- `tX` take current `X` position as zero
- `mXDown` and `tXDown` clear the down limit if it's set, sets the limit in the current `X` position if it's not set
- `m0` moves cross-slide forward
- `m1` moves cross-slide back

Y axis group:

- `mYUp` and `tYUp` clear the positive `Y` limit if it's set, sets the limit in the current negative `Y` position if it's not set
- `bY` enables or disables the axis
- `tY` take current `Y` position as zero
- `mYDown` and `tYDown` clear the down limit if it's set, sets the limit in the current `Y` position if it's not set
- `m2` moves `Y` axis forward
- `m5` moves `Y` axis back

Z axis group:

- `m3` and `tZLeft` clear the left limit if it's set, sets the limit in the current `Z` position if it's not set
- `bZ` enables or disables the axis
- `tZ` take current `Z` position as zero
- `m4` and `tZRight` clear the right limit if it's set, sets the limit in the current `Z` position if it's not set
- `m6` moves the carriage left
- `m7` moves the carriage right

Lower part of the screen:

- `t3` shows diameter, current WiFi status, pending numpad value or mode configuration prompt
- `mStop` turns the controlled off
- `bD0` to `bD9` append a number at end of the numpad input
- `mBack` works as backspace - deletes the last entered number
- `mPlay` starts the current mode or proceeds to the next step of mode configuration

### Keyboard

- ⌨️`Left`, ⌨️`up`, ⌨️`down`, ⌨️`right` arrows control the manual movement
- ⌨️`Plus` / ⌨️`minus` control the pitch
- ⌨️`Enter` turns on the current mode
- ⌨️`Esc` is stop
- ⌨️`A` / ⌨️`W` / ⌨️`D` / ⌨️`S` control limits
- ⌨️`Win` controls angle / rpm display / WiFi status
- ⌨️`Tilda` / ⌨️`backtick` (key under ESC) controls step
- ⌨️`M` changes metric / inch / tpi
- ⌨️`R` for reverse
- Top row numbers ⌨️`0`-⌨️`9` work as number input
- ⌨️`Backspace` removes last number
- Modes:
  - ⌨️`F1`: gearbox
  - ⌨️`F2`: turning
  - ⌨️`F3`: facing
  - ⌨️`F4`: cone
  - ⌨️`F5`: parting
  - ⌨️`F6`: threading
  - ⌨️`F7`: async
  - ⌨️`F8`: ellipse
  - ⌨️`F9`: gcode
  - ⌨️`F10`: y axis (if configured)
- ⌨️`X` zeroes X axis
- ⌨️`Z` zeroes Z axis
- ⌨️`C` disables / enables X axis
- ⌨️`Q` disables / enables Z axis
- ⌨️`O` pressed while a number is entered zeroes X from diameter

### Convention for referring to screen or keyboard buttons in this manual

Text like 🖥️`bMeasure` refers to looking at or pressing on the corresponding area of the screen, in this case green "IN" rectangle in the upper-right part of it.

Text like ⌨️`M` refers to pressing the corresponding letter on the keyboard, in this case letter M.

Dash between symbols refers to all the buttons between the 2 mentioned buttons e.g. ⌨️`1`-`0` means `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8`, `9`, `0` keys on the keyboard.

Slash between symbols refers to either one of the symbols e.g. ⌨️`+`/`-` means "pressing plus or minus key on the keyboard".

### Switching between metric and imperial

Press 🖥️`bMeasure` or ⌨️`M`  to change the system of measurement between:

- Metric (mm)
- Inch
- TPI

It affects how the pitch and position is displayed and changes, move steps for precision moves.

### Setting pitch

Pitch is the distance that carriage will move when the spindle makes the full turn. For example, M14 thread uses 2mm pitch.

Use numpad buttons 🖥️`bD0`-`bD9` or ⌨️`1`-`0` to enter the pitch value, 🖥️`mPlay` or ⌨️`Enter` to accept it.

Adjust the desired pitch using 🖥️`mPlus`/`mMinus` or ⌨️`+`/`-`.

Use negative pitch values e.g. `-2mm` to cut left-to-right threads. To change the pitch sign, press 🖥️`tPitch` or ⌨️`R`.

### Setting step

Step setting is used for manual carriage moves in `off` state - i.e. when no mode is active and no thread is being cut. Current step setting is normally shown in 🖥️`tStepVal`.

Pressing 🖥️`tStepVal` or ⌨️`Key under ESC` cycles through the list of predefined steps:

- Metric: `1mm`, `0.1mm`, `0.01mm`
- Imperial: `0.1"`, `0.01"`, `0.001"`

Use 🖥️`bD0`-`bD9` or ⌨️`1`-`0` to enter a custom step value. Pressing 🖥️`tStepVal` or ⌨️`Key under ESC` when the screen bottom line shows `Use 1.234mm?` will make the step equal to `1.234mm`.

### Zeroing the axes

Z and X position can be counted from any location you'd like. By pressing e.g. 🖥️`tZ` or ⌨️`Z` you can take the current position on the respective axis as `0`.

You can also set the `0` at a position ahead of the current position by entering the required distance using the numpad buttons 🖥️`bD0`-`bD9` or ⌨️`1`-`0` and then pressing 🖥️`tZ` or ⌨️`Z`.

You can set X0 on the lathe centerline by making a light cut, measuring diameter, entering it on the numpad and then pressing 🖥️`BX` or ⌨️`O`.

### Moving left and right, in and out

Press 🖥️`m6`/`m7` / ⌨️`Left`/`Right` buttons to move the carriage, 🖥️`m0`/`m1` / ⌨️`Up`/`Down` to move the cross-slide.

Depending on the state of the controller, pressing the move button will result in traveling the following distance:

- `off` - carriage will move by the step distance but at least 1 stepper motor step
- `ON` - carriage will move in pitch increments (stay in the thread) but at least the step distance

If step is set to `1mm` or `0.1"`, pressing and holding move buttons results in continuous movement allowing for quick tool positioning. If step is set to values other than `1mm` or `0.1"`, there's a short delay betwen steps when manual moves are triggered allowing to precisely position the tool.

Changing direction will result in automatic backlash compensation, for example with backlash `0.65mm` and step `0.1mm`, first move in the opposite direction will result in lead screw turning `0.75mm`. Tool should still only move `0.1mm` assuming backlash is uniform and is specified correclty.

When `off`, use numpad buttons 🖥️`bD0`-`bD9` / ⌨️`1`-`0` to enter a custom move distance. Pressing a move button when the screen bottom line shows `Use 1.234mm?` will move `1.234mm` in the corresponding direction. If there's an automatic stop limiting travel, it will move up to the limit and beep.

### Soft limits / automatic stops

Soft limits allow to cut close to the lathe chuck, part shoulder or rear support without hitting them.

One way to set a soft limit is to move the carriage or cross-slide to the desired position and press one of the 🖥️`tZLeft`/`tZRight`/`tXUp`/`tXDown` / ⌨️`A`/`W`/`D`/`S` limit buttons. Pressing the button again removes the limit regardless of the current position.

Another way to set a soft limit is to use numpad buttons 🖥️`bD0`-`bD9` / ⌨️`1`-`0` to enter a distance relative to the current position. Pressing a limit button when the screen bottom line shows `Use 1.234mm?` will set corresponding limit `1.234mm` away from the current position.

Soft limits are used when preparing an automatic operation like turning, facing, threading and cutting off.

### Gearbox mode / electronic lead screw

Press 🖥️`bMode` to switch to the gearbox mode. After turning the controller `ON` with the 🖥️`mPlay` / ⌨️`Enter` button, lead screw will move the distance of 1 pitch for 1 spindle turn.

With a small pitch like `0.07mm` this mode is useful for turning - gradually taking off material from the outer diameter of the part.

With a large pitch like `0.5"` one can cut a corresponding thread. Moving with 🖥️`m6` and 🖥️`m7` buttons is supported and does not result in losing the thread.

Direction of movement can be quickly reversed with 🖥️`tPitch` / ⌨️`R` button which toggles the pitch sign. Negative pitch can also be used to cut left threads.

Soft limits are respected in this mode allowing to finish the cut in a precise position.

Cross-slide can be moved with manual move buttons or disabled using 🖥️`bX` / ⌨️`C` and be operated manually.

Press 🖥️`mStop` / ⌨️`Esc` to turn gearbox mode `off` and decouple lead screw movements from spindle turns.

### Automatic turning

Press 🖥️`bMode` to switch to the automatic turning mode which is usually used to take large amount of material from the inside or outside diameter of the part in multiple passes.

Set the desired pitch to a suitable value e.g. `0.05mm`. Negative pitch will make turning start from the left limit, positive pitch will make it start from the right. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing 🖥️`mPlay` / ⌨️`Enter` guides through remaining steps:

- Entering the numer of passes - use numpad or 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`, confirm with 🖥️`mPlay` / ⌨️`Enter`
- Selecting `External` or `Internal` operation - use 🖥️`m6` and 🖥️`m7` to change selection. Internal operations start from the 🖥️`tXUp` limit, external from the 🖥️`tXDown` limit. Confirm with 🖥️`mPlay` / ⌨️`Enter`
- Confirm the final `Go?` question with 🖥️`mPlay` / ⌨️`Enter`

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Pitch can be adjusted on the fly using 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`.

You can skip to the next pass using 🖥️`mPlay` / ⌨️`Enter` while the operation is running.

Operation can be stopped at any time by pressing 🖥️`mStop` / ⌨️`Esc` or using manual move buttons.

In previous versions cross-slide would pull back all the way between the passes, starting from H5V12 we only pull back by a small safe distance.

Handwheels are ignored when this mode is on.

### Automatic facing

Press 🖥️`bMode` to switch to the automatic facing mode which is usually used to take large amount of material from the face of the part in 1 or more passes.

It's setup in the same way as automatic turning above. When running, passes are made along the face instead of the side of the part. Negative pitch will make facing start from the inside.

### Cone

Press 🖥️`bMode` to switch to the cone mode which maintains a constant ratio of movement between the X and Z axes. Cone mode doesn't require soft limits to be set but if they are set, they are respected.

Pressing 🖥️`mPlay` / ⌨️`Enter` guides through the setup:

- Enter cone ratio which is calculated as `(major_diameter - minor_diameter) / length`, see [this spreadsheet for most used values](https://docs.google.com/spreadsheets/d/1l0FUMtlWUjPywN9j94DOL84lB8dFrvdRWZIffT2NoHA/edit?usp=sharing). Confirm with 🖥️`mPlay` / ⌨️`Enter`
- Select `External` or `Internal` cone - use 🖥️`m6` and 🖥️`m7` to change selection. Confirm with 🖥️`mPlay` / ⌨️`Enter`

Turn on the spindle. Pitch can be adjusted on the fly using 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`. It's convenient to cut multiple cone passes with 🖥️`tPitch` / ⌨️`R` moving the tool in using manual move buttons.

### Automatic cut-off

Press 🖥️`bMode` to switch to the automatic parting mode which gradually feeds the cross-slide into the part from outside or inside in one or multiple passes.

Set the desired pitch to a suitable value e.g. `0.05mm`. Negative pitch will make turning start from the inside, positive pitch will make it start from the outside. 🖥️`tXUp` and 🖥️`tXDown` soft limits must be set before the operation can be started.

Pressing 🖥️`mPlay` / ⌨️`Enter` guides through remaining steps:

- Entering the numer of passes - use numpad or 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`, confirm with 🖥️`mPlay` / ⌨️`Enter`
- Check that pitch corresponds to the desired direction of cutting, click 🖥️`tPitch` / ⌨️`R` to change it
- Confirm the final `Go?` question with 🖥️`mPlay` / ⌨️`Enter`

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Pitch can be adjusted on the fly using 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`.

Operation can be stopped at any time by pressing 🖥️`mStop` / ⌨️`Esc` or using manual move buttons.

Handwheels are ignored when this mode is on.

### Automatic threading

Press 🖥️`bMode` to switch to the automatic threading which will cut a thread (optionally multi-start one) in multiple passes.

First passes are larger than average, final passes are shallower.

Set the desired pitch to a suitable value e.g. `2mm` or `20tpi`. Negative pitch will result in a left thread and will make the operation start from the left limit, positive pitch will make the operation start from the right. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing 🖥️`mPlay` / ⌨️`Enter` guides through remaining steps:

- Entering the numer of passes - use numpad or 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`, confirm with 🖥️`mPlay` / ⌨️`Enter`
- Selecting `External` or `Internal` operation - use 🖥️`m6`/`m7` or ⌨️`Left`/`Right` to change selection. Internal operations start from the 🖥️`tXUp` limit, external from the 🖥️`tXDown` limit. For multi-start thread, press 🖥️`mPlus` to add more starts. Confirm with 🖥️`mPlay` / ⌨️`Enter`
- Enter optional cone ratio on the numpad. Confirm with 🖥️`mPlay` / ⌨️`Enter`
- Confirm the final `Go?` question with 🖥️`mPlay` / ⌨️`Enter`

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done.

You can skip to the next pass using 🖥️`mPlay` / ⌨️`Enter` while the operation is running.

Operation can be stopped at any time by pressing 🖥️`mStop` / ⌨️`Esc` or using manual move buttons.

### Automatic half-spheres and half-ellipses

Press 🖥️`bMode` several times until `ELLI` is shown on screen. In this mode, cutter will form convex or concave half-ellipses in multiple passes.

Starting operation with positive pitch forms left hemisphere, with negative pitch - right hemisphere. This ensures that X backlash doesn't affect the cut.

`External` mode forms convex hemisphere (curved outward), `Internal` forms concave hemisphere (curved inward). Start and end points are the same in both cases.

Set the desired pitch to a suitable value e.g. `0.07mm`. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing 🖥️`mPlay` / ⌨️`Enter` guides through remaining steps:

- Entering the numer of passes - use numpad or 🖥️`mPlus`/`mMinus` / ⌨️`+`/`-`, confirm with 🖥️`mPlay` / ⌨️`Enter`
- Selecting `External` or `Internal` operation - use 🖥️`m6`/`m7` / ⌨️`Left`/`Right` to change selection. Confirm with 🖥️`mPlay` / ⌨️`Enter`
- Confirm the final `Go?` question with 🖥️`mPlay` / ⌨️`Enter`

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Adjusting the pitch on the fly is not supported.

Operation can be stopped at any time by pressing 🖥️`mStop` / ⌨️`Esc` or using manual move buttons.

Handwheels are ignored when this mode is on.

### Async mode

In this mode the carriage disregards spindle movements and instead moves with constant speed of `pitch` per second. When pitch is positive, `Z` axis moves to the left. When pitch is negative, `Z` axis moves to the right. If pitch is 0, `Z` axis doesn't move.

You can adjust the pitch using 🖥️`mMinus`/`mPlus` to adjust the movement speed.

Async mode respects limits if they are set.
