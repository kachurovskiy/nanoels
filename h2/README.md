**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

# NanoEls H2

This is the second hardware version (hence H2) of NanoEls electronic lead screw controller. It still uses Arduino Nano
microcontroller, a [custom PCB board](https://github.com/kachurovskiy/nanoels/blob/main/h2/Gerber_PCB_NanoElsLcd_20220815.zip) you
can print cheaply on jlcpcb.com and a few widely available components allowing you to build a DIY single-axis ELS.

![image](https://user-images.githubusercontent.com/517919/188740458-17936e54-3a53-435a-9475-1c2a5db8f14e.png)

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
