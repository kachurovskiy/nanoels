## Firmware binary licenses

Precompiled `h5.ino.YYYYMMDD.bin` firmware files are built from NanoEls source in this repository under the [MIT License](../LICENSE). They also include statically linked third-party components from the Arduino/ESP32 toolchain and Arduino libraries.

- [Arduino core for ESP32](https://github.com/espressif/arduino-esp32), licensed under [LGPL-2.1](https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html)
- [WebSockets](https://github.com/Links2004/arduinoWebSockets), licensed under [LGPL-2.1](https://github.com/Links2004/arduinoWebSockets/blob/master/LICENSE)
- [PS2KeyAdvanced](https://github.com/techpaul/PS2KeyAdvanced), licensed under [LGPL-2.1](https://github.com/techpaul/PS2KeyAdvanced/blob/master/LICENSE)
- ESP-IDF components bundled with Arduino-ESP32, mostly under [Apache-2.0](https://www.apache.org/licenses/LICENSE-2.0) and other compatible open-source licenses

The firmware can be rebuilt and relinked by following [Self-compile firmware with Arduino IDE](README.md#self-compile-firmware-with-arduino-ide). If a published build uses modified third-party libraries, publish those modified sources with the binary.
