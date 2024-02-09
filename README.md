This software and instructions are [provided as is](LICENSE), without warranty of any kind. [🇷🇺 Перевод на русский](https://translate.google.com/translate?hl=en&sl=en&tl=ru&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md), [🇩🇪 deutsche Übersetzung](https://translate.google.com/translate?hl=en&sl=en&tl=de&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)

# NanoEls H4

CNC and electronic lead screw controller based on ESP32-S3 that supports up to 4 axes:

- Automatic threads including multi-start
- Multi-pass turning, facing and cones
- Precise movements, soft limits and much more

![h4-600px](https://github.com/kachurovskiy/nanoels/assets/517919/4090779c-ef88-4402-aeef-644f7a086ff2)

See [h4 folder for hardware files, software, assembly and usage manual](https://github.com/kachurovskiy/nanoels/tree/main/h4).

## Build examples

- [fmw626](https://github.com/kachurovskiy/nanoels/discussions/123)
- [Kissys](https://github.com/kachurovskiy/nanoels/discussions/121)

# NanoEls H2

Cheap DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes. No more greasy gear swapping! Control your metal lathe lead screw with a few clicks.

- Set leadscrew pitch for feed or thread
- Soft limits for the carriage
- Multi-start threads in 1 start of the spindle

See [h2 folder for parts list, software, assembly and usage manual](https://github.com/kachurovskiy/nanoels/blob/main/h2/). Controller can be built from [generally available components](https://github.com/kachurovskiy/nanoels/tree/main/h2#components).

It's suggested to use STEPPERONLINE CL57T closed-loop driver with NEMA 23 3NM motor or stronger with 200 step resolution mode (full step) and a 600 PPR optical rotary encoder. [See hardware.md for more info.](hardware.md)

## Build examples

- [EdFleta](https://github.com/kachurovskiy/nanoels/discussions/87)
- [fmw626](https://github.com/kachurovskiy/nanoels/discussions/118)
- [Johannmupa](https://github.com/kachurovskiy/nanoels/discussions/89)
- [kachurovskiy](https://youtu.be/jR4tBBHSl3c?t=62)

# Contributing to the project

- Questions, problems and improvements: please start [a new GitHub Discussion](https://github.com/kachurovskiy/nanoels/discussions/new) or a new Issue
- Successful builds: please start a new GitHub Discussion with photos and comments
