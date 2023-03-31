**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

[🇷🇺 перевод на русский](https://translate.google.com/translate?hl=en&sl=en&tl=ru&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)
[🇩🇪 Deutsche Übersetzung](https://translate.google.com/translate?hl=en&sl=en&tl=de&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)

# NanoEls H2

Cheap DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

![h2](https://user-images.githubusercontent.com/517919/217100828-9071f6ac-a719-4ce1-8656-21346a133838.png)

## Features

- Metric pitches, -10mm to 10mm, resolution up to 0.001 mm
- Inch and TPI support, resolution up to 0.001 inch
- Position indication
- Angle indication
- Automatic stops
- Independent carriage moves
- Precision moves
- Moving while ON
- Big screen
- Pluggable terminals
- On/off switch
- Disabling stepper when not in use
- Multi-start threads
- Asynchronous mode

See [h2 folder](https://github.com/kachurovskiy/nanoels/blob/main/h2/) for more info.

## Hardware

Controller can be self-built entirely or from the [official kit](https://kachurovskiy.com/products/1-axis-electronic-lead-screw-controller-kit) (shipping to USA, Australia, Canada, New Zealand, Singapore and Ukraine).

Apart from controller, any ELS requires mounting a motor and encoder. It's suggested to use STEPPERONLINE CL57T closed-loop driver with NEMA 23 3NM motor or stronger. If you use some other driver, make sure it has 200 steps per resolution mode, most start from 800. See [hardware.md](hardware.md) for more info.

## Build examples

- [EdFleta](https://github.com/kachurovskiy/nanoels/discussions/87)
- [Johannmupa](https://github.com/kachurovskiy/nanoels/discussions/89)
- [kachurovskiy](https://youtu.be/jR4tBBHSl3c?t=62)

# Contributing to the project

- Questions, problems and improvements: please start [a new GitHub Discussion](https://github.com/kachurovskiy/nanoels/discussions/new) or a new Issue
- Successful/failed builds: please start a new GitHub Discussion with photos and comments
- 3D models: in most cases, don't edit the model, add a new file. PNG preview and a dimension would be nice too
