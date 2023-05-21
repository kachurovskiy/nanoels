# NanoEls H4

4-axis Electronic Lead Screw (ELS) based on ESP32-S3 for metal lathes.

[![h4-600px](https://user-images.githubusercontent.com/517919/235074149-307f8b7f-a9d5-4ade-b29a-13809ba81e75.JPG)](https://kachurovskiy.com/)

Controller itself is available for purchase on https://kachurovskiy.com/ or you can DIY with the hardware design files provided.

## Features

- Metric, inch and TPI support, cut any thread with utmost precision
- Controls 2 axis - lead screw (Z) and cross-slide (X)
- Manual movement of both axis: by eye, in precise steps or by a precise amount
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
- GCode over USB (work in progress)

No computer or CAD software needed! Coming soon:

- Automatic conical threads
- Spheres and curves

## Hardware

[Datasheet PDF](https://raw.githubusercontent.com/kachurovskiy/nanoels/main/h4/h4-20230429.pdf) contains schematic, screen, terminals and other hardware details that aren't specific do the electronic lead screw application.

[Case 3D models](https://github.com/kachurovskiy/nanoels/tree/main/h4/case), [front panel graphics](https://github.com/kachurovskiy/nanoels/tree/main/h4/graphics) and [PCB Gerber and EasyEDA files](https://github.com/kachurovskiy/nanoels/tree/main/h4/pcbs) can be found in respective sub-folders.

## Usage manual

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

- Metric: `1mm`, `0.1mm`, `0.01mm`, `0.001mm`
- Imperial: `0.1"`, `0.01"`, `0.001"`

Use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a custom step value. Pressing ![IconSteps](https://github.com/kachurovskiy/nanoels/assets/517919/52ce78e4-4202-4642-9433-e61ca39de9d5) when the screen bottom line shows `Use 1.234mm?` will make the step equal to `1.234mm`.

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

One way to set a soft limit is to move the carriage or cross-slide to the desired position and press one of the ![IconLimitLeft](https://github.com/kachurovskiy/nanoels/assets/517919/0e3d005e-b917-4389-84b3-76bddbd989a4) ![IconLimitRight](https://github.com/kachurovskiy/nanoels/assets/517919/9890c846-c7af-4082-a862-39bb0a1ffcd7) ![IconArrowUp](https://github.com/kachurovskiy/nanoels/assets/517919/0a1320df-5ec8-4f6d-93f2-f8c1bdfe93b8) ![IconLimitDown](https://github.com/kachurovskiy/nanoels/assets/517919/b18703de-9408-45aa-83e0-812069a3a674) limit buttons. Pressing the button again removes the limit regardless of the current position.

Another way to set a soft limit is to use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a distance relative to the current position. Pressing a limit button when the screen bottom line shows `Use 1.234mm?` will set corresponding limit `1.234mm` away from the current position.

Soft limits are used when preparing an automatic operation like turning, facing, threading and cutting off.

### Gearbox mode / electronic lead screw

Press ![IconGears](https://github.com/kachurovskiy/nanoels/assets/517919/d926a776-79a8-4abe-9589-734ef546daf5) to switch to the gearbox mode. After turning the controller `ON` with the ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/250b0641-6d5c-4ffb-a88c-b483e98c04c5) button, lead screw will move the distance of 1 pitch for 1 spindle turn.

With a small pitch like `0.07mm` this mode is useful for turning - gradually taking off material from the outer diameter of the part.

With a large pitch like `0.5"` one can cut a corresponding thread. Moving with ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/e75e40a9-8a75-4375-90e7-4dbcf1305ab0) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/47cd6d04-ca6f-4af9-83f3-b15af942c588) buttons is supported and does not result in losing the thread.

Direction of movement can be quickly reversed with ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/d820c1cd-8ce3-4d02-91f9-d240f4ea51cc) button which toggles the pitch sign. Negative pitch can also be used to cut left threads.

Soft limits are respected in this mode allowing to finish the cut in a precise position.

Cross-slide can be moved with manual move buttons or disabled using ![IconA](https://github.com/kachurovskiy/nanoels/assets/517919/3059b6ed-0197-4e48-91a7-80a7e1317176) and be operated manually.

Press ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/9ed2da6c-7461-419f-827d-781980c9ddde) to turn gearbox mode `off` and decouple lead screw movements from spindle turns.

### Automatic turning

Press ![IconTurning](https://github.com/kachurovskiy/nanoels/assets/517919/00abcae7-0cc3-430d-be56-c8ec22d1d9d0) to switch to the automatic turning mode which is usually used to take large amount of material from the inside or outside diameter of the part in multiple passes.

Set the desired pitch to a suitable value e.g. `0.05mm`. Negative pitch will make turning start from the left limit, positive pitch will make it start from the right. All soft limits (left, right, up, down) must be set before the operation can be started.

Pressing ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d) guides through remaining steps:

- Entering the numer of passes - use numpad or ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b), confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Selecting `External` or `Internal` operation - use ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/28a59458-0f91-42a5-9ba4-412d050dc462) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/0ff9ab80-0ce1-45fc-bc00-86d34ecac9f1) to change selection, confirm with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)
- Confirm the final `Go?` question with ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/c9fb0ef5-94d7-4b42-b1a3-4c85c704e80d)

Turn on the spindle. Operation will proceed fully automatically and the cutter will return to the starting position when done. Pitch can be adjusted on the fly using ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/3c0e1c27-820a-4d34-ae97-4b362b537e72) and ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/75db2ae9-97d6-4d39-9fff-e98e889ee84b).

Operation can be stopped at any time by pressing ![IconStop](https://github.com/kachurovskiy/nanoels/assets/517919/cf4b9b31-dda3-4469-9667-1d1c44ea39b4) or using manual move buttons.

### Work in progress

Instructions for other modes and features are coming soon.

### GCode

Commands can be sent to device e.g. using [our Web-based GCode sender](https://kachurovskiy.github.io/nanoels/h4/sender.html) while connected over USB. The following commands are currently implemented:

- G0, G1 - linear move
- G20, G21 - inch or metric mode
- F - setting feed as mm/min or inch/min
- X, Z - single axis move
- G90, G91 - absolute or relative positioning
- G18 - ZX plane

Sample command `G1 X5 Z2 F100` will move the cutter to X=5mm, Z=2mm at 100 mm/sec in absolute metric mode.
