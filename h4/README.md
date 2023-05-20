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

Pitch is the distance that carriage will move when the spindle makes the full turn. For example, M14 thread uses 2mm pitch.

Use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter the pitch value. For example, pressing ![Icon1](https://github.com/kachurovskiy/nanoels/assets/517919/f0a4eb3c-1e57-441b-96a8-d76dcf0a6cf4) ![Icon5](https://github.com/kachurovskiy/nanoels/assets/517919/2ca23018-d54f-4754-a8f4-aff00ba655e8) ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/1f71946a-14a9-41b0-9c1c-454fb935015c) followed by ![IconPlay](https://github.com/kachurovskiy/nanoels/assets/517919/1bf41a47-f4b5-4896-96a6-72c97ae472e2) will set the pitch to `0.15mm`, `0.15"` or `150tpi` depending on the current measurement system.

Adjust the desired pitch using ![IconMinus](https://github.com/kachurovskiy/nanoels/assets/517919/ed05b417-5714-4e31-9f17-9ff646c85214) and ![IconPlus](https://github.com/kachurovskiy/nanoels/assets/517919/0a5e045c-f670-4e45-8b26-e4e27de9ce7a) buttons.

Use negative pitch values e.g. `-2mm` to cut left-to-right threads. To change the pitch sign, press ![IconReverse](https://github.com/kachurovskiy/nanoels/assets/517919/8eee528a-b628-4207-99b1-6f61b85c8be7).

### Setting step

Step setting is used for manual carriage moves in `off` state - i.e. when no mode is active and no thread is being cut. Current step setting is normally shown on the 1st screen line as e.g. `step 1mm` or `step 0.1"` but can be hidden if there's no space.

Pressing ![IconSteps](https://github.com/kachurovskiy/nanoels/assets/517919/52ce78e4-4202-4642-9433-e61ca39de9d5) cycles through the list of predefined steps:

- Metric: `1mm`, `0.1mm`, `0.01mm`, `0.001mm`
- Imperial: `0.1"`, `0.01"`, `0.001"`

Use numpad buttons ![Icon0](https://github.com/kachurovskiy/nanoels/assets/517919/67f660f1-c6fa-4922-bf03-9f6571023806) to ![Icon9](https://github.com/kachurovskiy/nanoels/assets/517919/6ad6b4e4-5bf1-473f-93ed-65f6ee478d8f) to enter a custom step value. Pressing ![IconSteps](https://github.com/kachurovskiy/nanoels/assets/517919/52ce78e4-4202-4642-9433-e61ca39de9d5) when the screen bottom line shows `Use X.XXX?` will assign that value to step.

### Moving left and right, in and out

Press ![IconArrowLeft](https://github.com/kachurovskiy/nanoels/assets/517919/d110519a-6cf4-491e-b81a-c09aefa49e49) and ![IconArrowRight](https://github.com/kachurovskiy/nanoels/assets/517919/48a0327e-0cc4-465e-b371-644f153f3288) buttons to move the carriage, ![IconArrowUp](https://github.com/kachurovskiy/nanoels/assets/517919/ac350635-4424-4438-bcfb-3cb0431345f8) and ![IconArrowDown](https://github.com/kachurovskiy/nanoels/assets/517919/897b4005-45d0-46ed-977e-b25a98983961) to move the cross-slide.

Depending on the state of the controller, pressing the move button will result in traveling the following distance:

- `off` - carriage will move by the step distance but at least 1 stepper motor step
- `ON` - carriage will move in pitch increments (stay in the thread) but at least the step distance

If step is set to `1mm` or `0.1"`, pressing and holding move buttons results in continuous movement allowing for quick tool positioning. If step is set to values other than `1mm` or `0.1"`, there's a short delay betwen steps when manual moves are triggered allowing to precisely position the tool.

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
