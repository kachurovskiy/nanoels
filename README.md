**This software and instructions are provided as is, without warranty of any kind. This is a hobby project. Using this might damage your equipment, cause injury or death. Use at your own risk.**

[🇷🇺 перевод на русский](https://translate.google.com/translate?hl=en&sl=en&tl=ru&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)
[🇩🇪 Deutsche Übersetzung](https://translate.google.com/translate?hl=en&sl=en&tl=de&u=https%3A%2F%2Fgithub.com%2Fkachurovskiy%2Fnanoels%2Fblob%2Fmain%2FREADME.md)

# NanoEls

Cheap DIY Electronic Lead Screw (ELS) based on Arduino Nano for metal lathes.

There are 2 hardware versions of NanoEls, [H1](https://github.com/kachurovskiy/nanoels/blob/main/h1/) is older, [H2 is newer](https://github.com/kachurovskiy/nanoels/blob/main/h2/) and more capable.

|  | [NanoEls H1](https://github.com/kachurovskiy/nanoels/blob/main/h1/) | [NanoEls H2](https://github.com/kachurovskiy/nanoels/blob/main/h2/) |
| --- | --- | --- |
|  | ![h1](https://user-images.githubusercontent.com/517919/192354717-12b16d0e-4f9f-4f10-a7f7-c1daaba6f542.png) | ![h2](https://user-images.githubusercontent.com/517919/192354510-d96355d4-31e2-4ce4-a190-048795a8c274.png) |
| Metric pitches (+/-) | Yes | Yes |
| Imperial pitches | Yes (specify in mm) | Yes (specify in mm) |
| Position indication | Yes | Yes |
| Angle indication | Yes | Yes |
| Automatic stops | Yes | Yes |
| Independent carriage moves | Yes | Yes |
| Precision moves 1mm, 0.1mm and 0.01mm |   | Yes |
| Moving while ON |   | Yes |
| Big screen |  | Yes |
| Pluggable terminals |   | Yes |
| On/off switch |  | Yes |
| Disabling stepper when not in use |   | Yes |

# Features

- Positive and negative screw pitches
  - From -10mm to 10mm
  - Resolution 0.01mm
- Automatic lead screw stops
- Independent carriage moves without losing the thread
- Lead screw position indication
- Spindle angle indication

# Example builds

## H1

- [Dididu12](https://github.com/kachurovskiy/nanoels/discussions/40#discussioncomment-2019521)
- [Hedning003](https://github.com/kachurovskiy/nanoels/discussions/16)
- [HW61](https://github.com/kachurovskiy/nanoels/discussions/43)
- [kachurovskiy](https://www.youtube.com/watch?v=9uTdDk2EqG4?t=272)
- [mockendon](https://github.com/kachurovskiy/nanoels/discussions/32)
- [Sonny Madlangbayan](https://www.youtube.com/watch?v=qiPQUa50Uog)
- [wberggren](https://github.com/kachurovskiy/nanoels/discussions/13)
- [WillieJilesen](https://github.com/kachurovskiy/nanoels/discussions/39)
- [zabu83](https://github.com/kachurovskiy/nanoels/discussions/11)

## H2

- [kachurovskiy](https://youtu.be/jR4tBBHSl3c?t=62)

# Contributing to the project

- Questions: please open a new GitHub Discussion
- Successful/failed builds: please file a GitHub Issue with explanations and photos
- Code changes: to maximize the chance of your PR being accepted, [discuss the planned change](https://github.com/kachurovskiy/nanoels/discussions/new) beforehand
  - Only make the necessary minimal edits
  - Run in the `TEST` mode, add new tests if needed
  - Split unrelated changes into separate PRs
- PCB changes: please open a new GitHub Discussion
- 3D models: in most cases, don't edit the model, add a new file. PNG preview and a dimension would be nice too.

# Looking for resellers and manufacturers

If you're willing to manufacture this device and/or sell it as a kit, we'd be happy to link to your page for free - especially if it makes the build cheaper than buying all the components separately.
