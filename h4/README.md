# NanoEls H4

4-axis Electronic Lead Screw (ELS) based on ESP32-S3 for metal lathes.

[![h4-600px](https://github.com/kachurovskiy/nanoels/assets/517919/86289a74-f70e-4d16-873f-0954dd297f77)](https://kachurovskiy.com/)

Controller itself is available for purchase on https://kachurovskiy.com/ or you can DIY with the hardware design files provided.

## Features

- Metric, inch and TPI support, cut any thread with utmost precision
- Controls 2 axes - lead screw (Z) and cross-slide (X)
- Manual movement of both axes: by eye, in precise steps or by a precise amount
- Disabling/enabling of stepper motors allowing to switch to manual operations in 1 click
- Soft limits allowing to cut e.g. close to the chuck
- Automatic threads: just set length, depth, pitch and number of passes
- Automatic multi-pass turning and facing
- Automatic multi-start threads
- Automatic half-spheres and ellipses
- Cone mode to cut internal or external tapers
- Cut-off mode allowing for smooth in-feed
- RPM and angle indication
- Internal/external and left-to-right versions of each automatic operation
- Backlash compensation
- Rotary encoders to move axes
- Rotary or linear 3rd axis
- GCode over USB (work in progress)

No computer or CAD software needed! Coming soon:

- Automatic conical threads
- Spheres and curves

## Hardware

[Datasheet PDF](https://raw.githubusercontent.com/kachurovskiy/nanoels/main/h4/h4.pdf) contains schematic, screen, terminals and other hardware details that aren't specific do the electronic lead screw application.

See [parts.md](https://github.com/kachurovskiy/nanoels/blob/main/h4/parts.md) for Gerber, BOM, STL and other info required for DIY assembly.

See [hardware.md](https://github.com/kachurovskiy/nanoels/blob/main/hardware.md) for mounts and adapters for encoders and motors. For attaching a cross-slide motor, consider [belt-based](https://www.thingiverse.com/thing:6058899) or [gear-based](https://www.thingiverse.com/thing:4714722) NEMA 17 mounts.

## Wiring

![h4-back-cropped](https://github.com/kachurovskiy/nanoels/assets/517919/bd0fd006-5bda-4b00-a66b-ec7d7cab502e)

Encoder terminal:

- GND - connect to encoder power-in line (usually black) and wire shielding if there's any
- 5V - connect to encoder power-in line (usually red)
- ENCB - connect to one of the encoder signal lines
- ENCA - connect to one of the encoder signal lines

Z axis - stepper terminal for the main lead screw:

- 5V - connect to stepper driver PUL+, DIR+, ENA+ and wire shielding if there's any
- ENA - connect to stepper driver ENA-
- DIR - connect to stepper driver DIR-
- STEP - connect to stepper driver PUL-

X axis - stepper terminal for the cross-slide:

- 5V - connect to stepper driver PUL+, DIR+, ENA+ and wire shielding if there's any
- ENA - connect to stepper driver ENA-
- DIR - connect to stepper driver DIR-
- STEP - connect to stepper driver PUL-

## Programming the controller

- Install the [Arduino IDE](https://docs.arduino.cc/software/ide-v2)
- Add `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json` in [Preferences as "Additional board manager URLs"](https://github.com/kachurovskiy/nanoels/assets/517919/dcc023e6-20fc-4284-ba56-d466dbe4ce53)
- Install `esp32` [via Board Manager](https://github.com/kachurovskiy/nanoels/assets/517919/094d00ff-1e51-4f26-bb81-aa4ad42bde2a)
- Install Adafruit `TCA8418` library [via Library Manager](https://github.com/kachurovskiy/nanoels/assets/517919/90326e0d-6600-4b47-aa66-1177c4b9cc27)
- Download [this repository](https://github.com/kachurovskiy/nanoels/archive/refs/heads/main.zip), unzip, go to `h4` directory and open `h4.ino` file in the Arduino IDE
- Check the top constants (e.g. encoder steps, motor steps, display offset) and adjust if needed
- Select "ESP32S3 Dev Module" as device at the top, pick COM port that appears when you connect the device with a USB cable
- Upload the sketch to your H4 controller

A few things to check after upload:

- Spindle direction: show angle on screen using ![IconDisplay](https://github.com/kachurovskiy/nanoels/assets/517919/60bb723d-4c2d-45af-9208-95c2b26a42d1). Rotate the chuck forward manually - angle should increase. If it decreases, swap `ENCB` and `ENCA` wires in the terminal
- Motor direction: try ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/d110519a-6cf4-491e-b81a-c09aefa49e49) ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/48a0327e-0cc4-465e-b371-644f153f3288) ![IconArrowUp](https://github.com/kachurovskiy/nanoels/assets/517919/ac350635-4424-4438-bcfb-3cb0431345f8) ![IconArrowDown](https://github.com/kachurovskiy/nanoels/assets/517919/897b4005-45d0-46ed-977e-b25a98983961) buttons - if motor is moving in the wrong direction, change `INVERT_Z` or `INVERT_X` in the code, re-upload the sketch (or swap the motor leads `A+` and `A-` in the stepper driver)

Troubleshooting:

- Arduino IDE doesn't detect NanoEls H4: try a different USB cable
- Not sure which COM port is NanoEls H4: unplug it, check the list of available ports in Arduino IDE, plug H4 in, see new port that appeared is H4
- `ImportError: No module named serial` error on Linux: try `sudo apt install python3-serial`

## Usage manual

**This manual corresponds to `NanoEls H4 V6`. To see your software version, hold ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/9ed2da6c-7461-419f-827d-781980c9ddde) for 5 seconds. If you have a different version - e.g. `V5`, please update to the latest one.**

### Switching between metric and imperial

Press ![IconMeasure](https://github.com/kachurovskiy/nanoels/assets/517919/c4b72922-82c7-445a-9954-7bd08abcc6b5) to change the system of measurement between:

- Metric (mm)
- Inch
- TPI

It affects how the pitch and position is displayed and changes, move steps for precision moves.

### Setting pitch

https://github.com/kachurovskiy/nanoels/assets/517919/58da0f90-8adc-4035-a18c-198c88a73c22

Pitch is the distance that carriage will move when the spindle makes the full turn. For example, M14 thread uses 2mm pitch.

Use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter the pitch value. For example, pressing ![Icon1](https://github.com/kachurovskiy/nanoels/assets/517919/f0a4eb3c-1e57-441b-96a8-d76dcf0a6cf4) ![Icon5](https://github.com/kachurovskiy/nanoels/assets/517919/2ca23018-d54f-4754-a8f4-aff00ba655e8) ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/1f71946a-14a9-41b0-9c1c-454fb935015c) followed by ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/1bf41a47-f4b5-4896-96a6-72c97ae472e2) will set the pitch to `0.15mm`, `0.15"` or `150tpi` depending on the current measurement system.

Adjust the desired pitch using ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/ed05b417-5714-4e31-9f17-9ff646c85214) and ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/0a5e045c-f670-4e45-8b26-e4e27de9ce7a) buttons.

Use negative pitch values e.g. `-2mm` to cut left-to-right threads. To change the pitch sign, press ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/8eee528a-b628-4207-99b1-6f61b85c8be7).

### Setting step

https://github.com/kachurovskiy/nanoels/assets/517919/c31d04b4-958b-48af-9717-09322885c12c

Step setting is used for manual carriage moves in `off` state - i.e. when no mode is active and no thread is being cut. Current step setting is normally shown on the 1st screen line as e.g. `step 1mm` or `step 0.1"` but can be hidden if there's no space.

Pressing ![IconSteps](https://github.com/kachurovskiy/nanoels/assets/517919/52ce78e4-4202-4642-9433-e61ca39de9d5) cycles through the list of predefined steps:

- Metric: `1mm`, `0.1mm`, `0.01mm`
- Imperial: `0.1"`, `0.01"`, `0.001"`

Use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a custom step value. Pressing ![IconSteps](https://github.com/kachurovskiy/nanoels/assets/517919/52ce78e4-4202-4642-9433-e61ca39de9d5) when the screen bottom line shows `Use 1.234mm?` will make the step equal to `1.234mm`.

### Zeroing the axes

Z and X position can be counted from any location you'd like. By pressing ![IconZ](https://github.com/kachurovskiy/nanoels/assets/517919/32d95cce-d8be-4f8c-8a9c-399d278a2115) or ![IconX](https://github.com/kachurovskiy/nanoels/assets/517919/fd870901-4cc0-469e-ad88-e558998928d0) you can take the current position on the respective axis as `0`.

You can also set the `0` at a position ahead of the current position by entering the required distance using the numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) and then pressing ![IconZ](https://github.com/kachurovskiy/nanoels/assets/517919/32d95cce-d8be-4f8c-8a9c-399d278a2115) or ![IconX](https://github.com/kachurovskiy/nanoels/assets/517919/fd870901-4cc0-469e-ad88-e558998928d0).

You can set X0 on the lathe centerline by making a light cut, measuring diameter, entering it on the numpad and then pressing ![IconA](https://github.com/kachurovskiy/nanoels/assets/517919/3059b6ed-0197-4e48-91a7-80a7e1317176).

### Moving left and right, in and out

https://github.com/kachurovskiy/nanoels/assets/517919/6b6dfb87-ee3a-4e2c-b272-3af0c08e09fa

Press ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/d110519a-6cf4-491e-b81a-c09aefa49e49) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/48a0327e-0cc4-465e-b371-644f153f3288) buttons to move the carriage, ![IconArrowUp](https://github.com/kachurovskiy/nanoels/assets/517919/ac350635-4424-4438-bcfb-3cb0431345f8) and ![IconArrowDown](https://github.com/kachurovskiy/nanoels/assets/517919/897b4005-45d0-46ed-977e-b25a98983961) to move the cross-slide.

Depending on the state of the controller, pressing the move button will result in traveling the following distance:

- `off` - carriage will move by the step distance but at least 1 stepper motor step
- `ON` - carriage will move in pitch increments (stay in the thread) but at least the step distance

If step is set to `1mm` or `0.1"`, pressing and holding move buttons results in continuous movement allowing for quick tool positioning. If step is set to values other than `1mm` or `0.1"`, there's a short delay betwen steps when manual moves are triggered allowing to precisely position the tool.

Changing direction will result in automatic backlash compensation, for example with backlash `0.65mm` and step `0.1mm`, first move in the opposite direction will result in lead screw turning `0.75mm`. Tool should still only move `0.1mm` assuming backlash is uniform and is specified correclty.

When `off`, use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a custom move distance. Pressing a move button when the screen bottom line shows `Use 1.234mm?` will move `1.234mm` in the corresponding direction. If there's an automatic stop limiting travel, it will move up to the limit and beep.

### Soft limits / automatic stops

https://github.com/kachurovskiy/nanoels/assets/517919/8b29bba1-941e-4e69-8598-6cb8aa0c6929

Soft limits allow to cut close to the lathe chuck, part shoulder or rear support without hitting them.

One way to set a soft limit is to move the carriage or cross-slide to the desired position and press one of the ![IconLimitLeft](https://github.com/kachurovskiy/nanoels/assets/517919/0e3d005e-b917-4389-84b3-76bddbd989a4) ![IconLimitRight](https://github.com/kachurovskiy/nanoels/assets/517919/9890c846-c7af-4082-a862-39bb0a1ffcd7) ![IconLimitUp](https://github.com/kachurovskiy/nanoels/assets/517919/fd552c49-7f50-4e25-b78f-b0d565c0b96c) ![IconLimitDown](https://github.com/kachurovskiy/nanoels/assets/517919/b18703de-9408-45aa-83e0-812069a3a674) limit buttons. Pressing the button again removes the limit regardless of the current position.

Another way to set a soft limit is to use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a distance relative to the current position. Pressing a limit button when the screen bottom line shows `Use 1.234mm?` will set corresponding limit `1.234mm` away from the current position.

Soft limits are used when preparing an automatic operation like turning, facing, threading and cutting off.

### Gearbox mode / electronic lead screw

https://github.com/kachurovskiy/nanoels/assets/517919/df9fa150-0284-4aec-ab81-8e37f4a747bc

Press ![IconGears](https://github.com/kachurovskiy/nanoels/assets/517919/d926a776-79a8-4abe-9589-734ef546daf5) to switch to the gearbox mode. After turning the controller `ON` with the ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/250b0641-6d5c-4ffb-a88c-b483e98c04c5) button, lead screw will move the distance of 1 pitch for 1 spindle turn.

With a small pitch like `0.07mm` this mode is useful for turning - gradually taking off material from the outer diameter of the part.

With a large pitch like `0.5"` one can cut a corresponding thread. Moving with ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/e75e40a9-8a75-4375-90e7-4dbcf1305ab0) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/47cd6d04-ca6f-4af9-83f3-b15af942c588) buttons is supported and does not result in losing the thread.

Direction of movement can be quickly reversed with ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/d820c1cd-8ce3-4d02-91f9-d240f4ea51cc) button which toggles the pitch sign. Negative pitch can also be used to cut left threads.

Soft limits are respected in this mode allowing to finish the cut in a precise position.

Cross-slide can be moved with manual move buttons or disabled using ![IconA](https://github.com/kachurovskiy/nanoels/assets/517919/3059b6ed-0197-4e48-91a7-80a7e1317176) and be operated manually.

Press ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/9ed2da6c-7461-419f-827d-781980c9ddde) to turn gearbox mode `off` and decouple lead screw movements from spindle turns.

### Automatic turning

https://github.com/kachurovskiy/nanoels/assets/517919/30d98d1e-6ddc-4f40-b637-48f76003cd33

Press ![IconTurning](https://github.com/kachurovskiy/nanoels/assets/517919/00abcae7-0cc3-430d-be56-c8ec22d1d9d0) to switch to the automatic turning mode which is usually used to take large amount of material from the inside or outside diameter of the part in multiple passes.

Set the desired pitch to a suitable value e.g. `0.05mm`. Negative pitch will make turning start from the left limit, positive pitch will make it start from the right. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through remaining steps:

- Entering the numer of passes - use numpad or ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b), confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Selecting `External` or `Internal` operation - use ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/28a59458-0f91-42a5-9ba4-412d050dc462) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/0ff9ab80-0ce1-45fc-bc00-86d34ecac9f1) to change selection. Internal operations start from the ![IconLimitUp](https://github.com/kachurovskiy/nanoels/assets/517919/fd552c49-7f50-4e25-b78f-b0d565c0b96c) limit, external from the ![IconLimitDown](https://github.com/kachurovskiy/nanoels/assets/517919/b18703de-9408-45aa-83e0-812069a3a674) limit. Confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Confirm the final `Go?` question with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Pitch can be adjusted on the fly using ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b).

You can skip to the next pass using ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) while the operation is running.

Operation can be stopped at any time by pressing ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or using manual move buttons.

### Automatic facing

Press ![IconFacing](https://github.com/kachurovskiy/nanoels/assets/517919/f37cfd0e-74cc-4e70-80ab-620ab769afb8) to switch to the automatic facing mode which is usually used to take large amount of material from the face of the part in 1 or more passes.

It's setup in the same way as automatic turning above. When running, passes are made along the face instead of the side of the part. Negative pitch will make facing start from the inside.

### Cone

https://github.com/kachurovskiy/nanoels/assets/517919/6dd4a5e6-12ef-45a5-a24e-4a538f206546

Press ![IconCone](https://github.com/kachurovskiy/nanoels/assets/517919/d6fb049a-d93e-4dd4-aec9-4a9ed840ffde) to switch to the cone mode which maintains a constant ratio of movement between the X and Z axes. Cone mode doesn't require soft limits to be set but if they are set, they are respected.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through the setup:

- Enter cone ratio which is calculated as `(major_diameter - minor_diameter) / length`, see [this spreadsheet for most used values](https://docs.google.com/spreadsheets/d/1l0FUMtlWUjPywN9j94DOL84lB8dFrvdRWZIffT2NoHA/edit?usp=sharing). Confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Select `External` or `Internal` cone - use ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/28a59458-0f91-42a5-9ba4-412d050dc462) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/0ff9ab80-0ce1-45fc-bc00-86d34ecac9f1) to change selection. Confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Pitch can be adjusted on the fly using ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b). It's convenient to cut multiple cone passes with ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/d820c1cd-8ce3-4d02-91f9-d240f4ea51cc) moving the tool in using manual move buttons.

### Automatic cut-off

https://github.com/kachurovskiy/nanoels/assets/517919/fe5245b8-4bf4-4001-8762-c786e85a2369

Press ![IconParting](https://github.com/kachurovskiy/nanoels/assets/517919/ba1501b3-89df-4198-9f8d-3ff862add69f) to switch to the automatic parting mode which gradually feeds the cross-slide into the part from outside or inside in one or multiple passes.

Set the desired pitch to a suitable value e.g. `0.05mm`. Negative pitch will make turning start from the inside, positive pitch will make it start from the outside. ![IconArrowUp](https://github.com/kachurovskiy/nanoels/assets/517919/0a1320df-5ec8-4f6d-93f2-f8c1bdfe93b8) and ![IconLimitDown](https://github.com/kachurovskiy/nanoels/assets/517919/b18703de-9408-45aa-83e0-812069a3a674) soft limits must be set before the operation can be started.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through remaining steps:

- Entering the numer of passes - use numpad or ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b), confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Check that pitch corresponds to the desired direction of cutting, click ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/d820c1cd-8ce3-4d02-91f9-d240f4ea51cc) to change it
- Confirm the final `Go?` question with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Pitch can be adjusted on the fly using ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b).

Operation can be stopped at any time by pressing ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or using manual move buttons.

### Automatic threading

Press ![IconThread](https://github.com/kachurovskiy/nanoels/assets/517919/8f07c5bc-fdf5-4eaa-91c4-32a5d656e04a) to switch to the automatic threading which will cut a thread (optionally multi-start one) in multiple passes.

Set the desired pitch to a suitable value e.g. `2mm` or `20tpi`. Negative pitch will result in a left thread and will make the operation start from the left limit, positive pitch will make the operation start from the right. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through remaining steps:

- Entering the numer of passes - use numpad or ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b), confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Selecting `External` or `Internal` operation - use ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/28a59458-0f91-42a5-9ba4-412d050dc462) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/0ff9ab80-0ce1-45fc-bc00-86d34ecac9f1) to change selection. Internal operations start from the ![IconLimitUp](https://github.com/kachurovskiy/nanoels/assets/517919/fd552c49-7f50-4e25-b78f-b0d565c0b96c) limit, external from the ![IconLimitDown](https://github.com/kachurovskiy/nanoels/assets/517919/b18703de-9408-45aa-83e0-812069a3a674) limit. For multi-start thread, press ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) to add more starts. Confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Confirm the final `Go?` question with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done.

You can skip to the next pass using ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) while the operation is running.

Operation can be stopped at any time by pressing ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or using manual move buttons.

### Automatic half-spheres and half-ellipses

Press ![IconM](https://github.com/kachurovskiy/nanoels/assets/517919/902cc062-3b85-4335-8e6c-077ec956f410) several times until `ELLI` is shown on screen. In this mode, cutter will form convex or concave half-ellipses in multiple passes.

Starting operation with positive pitch forms left hemisphere, with negative pitch - right hemisphere. This ensures that X backlash doesn't affect the cut.

`External` mode forms convex hemisphere (curved outward), `Internal` forms concave hemisphere (curved inward). Start and end points are the same in both cases.

Set the desired pitch to a suitable value e.g. `0.07mm`. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through remaining steps:

- Entering the numer of passes - use numpad or ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b), confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Selecting `External` or `Internal` operation - use ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/28a59458-0f91-42a5-9ba4-412d050dc462) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/0ff9ab80-0ce1-45fc-bc00-86d34ecac9f1) to change selection. Confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Confirm the final `Go?` question with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Adjusting the pitch on the fly is not supported.

Operation can be stopped at any time by pressing ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or using manual move buttons.

### GCode

🚧 GCode support and lathecode editor are not ready for general use, below is a preview of what's coming 🚧

Commands can be sent to device e.g. using [our Web-based GCode sender](https://kachurovskiy.github.io/nanoels/h4/sender.html) while connected over USB. The following commands are currently implemented:

- G0, G1 - linear move
- G20, G21 - inch or metric mode
- F - setting feed as mm/min or inch/min
- X, Z - single axis move
- G90, G91 - absolute or relative positioning
- G18 - ZX plane

Sample command `G1 X5 Z2 F100` will move the cutter to X=5mm, Z=2mm at 100 mm/sec in absolute metric mode.

GCode can be generated using e.g. https://kachurovskiy.github.io/lathecode/

**WARNING:** GCode commands currently ignore automatic stops / soft limits. To stop GCode from executing use ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or emergency stop. Clicking `Stop` in the Web UI has a delay and only stops when current command is finished.

### More modes are coming!

Please [start a new discussion](https://github.com/kachurovskiy/nanoels/discussions) to let us know which mode you think should be added next.
