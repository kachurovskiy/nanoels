This software and instructions are provided as is, [without warranty of any kind](LICENSE).

[🇷🇺 перевод на русский](https://translate.google.com/translate?hl=en&sl=en&tl=ru&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)
[🇩🇪 Deutsche Übersetzung](https://translate.google.com/translate?hl=en&sl=en&tl=de&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)

# NanoEls H2

Cheap DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

No more greasy gear swapping! Control your metal lathe lead screw with a few clicks.

- Set leadscrew pitch for feed or thread
- Soft limits for the carriage
- Multi-start threads in 1 start of the spindle

See [h2 folder](https://github.com/kachurovskiy/nanoels/blob/main/h2/) for more info.

## Hardware

Controller can be built from [generally available components](https://github.com/kachurovskiy/nanoels/tree/main/h2#components):

[![open-source-build](https://user-images.githubusercontent.com/517919/234090559-eb27d066-2bff-4de8-851b-6f3237757085.png)](https://github.com/kachurovskiy/nanoels/tree/main/h2#nanoels-h2)

Or from the [official kit](https://kachurovskiy.com/):

[![kit](h2/kit.jpg)](https://kachurovskiy.com/)

It's suggested to use STEPPERONLINE CL57T closed-loop driver with NEMA 23 3NM motor or stronger with 200 step resolution mode (full step).

See [hardware.md](hardware.md) for more info.

## Build examples

- [EdFleta](https://github.com/kachurovskiy/nanoels/discussions/87)
- [Johannmupa](https://github.com/kachurovskiy/nanoels/discussions/89)
- [kachurovskiy](https://youtu.be/jR4tBBHSl3c?t=62)

# NanoEls H4

ELS controller based on ESP32-S3 that supports up to 4 axis. ELS software for it [is in active developent in the h4 package](https://github.com/kachurovskiy/nanoels/tree/main/h4).

[![h4-600px](https://user-images.githubusercontent.com/517919/235074149-307f8b7f-a9d5-4ade-b29a-13809ba81e75.JPG)](https://kachurovskiy.com/)

Controller itself is available for purchase on https://kachurovskiy.com/

For now there's no DIY option for H4 since ordering from Gerber would be prohibitevely expensive - at least $400 for a minimum order due to the large number of small SMD components. Once the project gets traction, we'll likely have a compatible DIY version of the boards but it would still cost close to the commercial hardware since 2 sizeable PCBs, several critical chips, connectors and terminals are required and they all ship from different suppliers.

# Contributing to the project

- Questions, problems and improvements: please start [a new GitHub Discussion](https://github.com/kachurovskiy/nanoels/discussions/new) or a new Issue
- Successful builds: please start a new GitHub Discussion with photos and comments
