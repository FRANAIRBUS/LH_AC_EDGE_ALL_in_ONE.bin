# LH_AC_EDGE_ALL_in_ONE.bin

![logo_github](https://user-images.githubusercontent.com/56954112/188657542-121a59bb-6500-48c4-bbd1-0480a88ae78b.jpg)

## Requirements

### Supported hardware

  
  * [X] ESP8266/ESP32 modules supported by the Additional Board Manager URLs of the Arduino-IDE.

### Required libraries

EdgeUnified requires the following environment and libraries.

#### Arduino IDE

The current upstream at the 1.8 level or later is needed. Please install from the [official Arduino IDE download page](https://www.arduino.cc/en/Main/Software). This step is not required if you already have a modern version.

#### ESP8266 Arduino core

AutoConnect targets Sketches made on the assumption of [ESP8266 Community's Arduino core](https://github.com/esp8266/Arduino). Stable 3.0.0 or higher required and the [latest release](https://github.com/esp8266/Arduino/releases/latest) is recommended.  
Install third-party platform using the *Boards Manager* of Arduino IDE. Package URL is: 
http://arduino.esp8266.com/stable/package_esp8266com_index.json

#### ESP32 Arduino core

Also, to apply AutoConnect to ESP32, the [arduino-esp32 core](https://github.com/espressif/arduino-esp32) provided by Espressif is needed. Stable 2.0.4 or required and the [latest release](https://github.com/espressif/arduino-esp32/releases/latest) is recommended.  
Install third-party platform using the *Boards Manager* of Arduino IDE. You can add multiple URLs into *Additional Board Manager URLs* field, separating them with commas. Package URL is: 
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json for ESP32.

#### Additional library (Required)

1. [AutoConnect](https://github.com/Hieromon/AutoConnect) library to handling the portal.
2. [PageBuilder](https://github.com/Hieromon/PageBuilder) library to build HTML.
3. [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library to make persistence EdgeData.
4. [HomeKit](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) library to use Homekit Server.

## Installation


## License

Copyright (c) Francisco CB (FRANAIRBUS). All rights reserved.

Licensed under the [MIT](https://github.com/FRANAIRBUS/LH_AC_EDGE/blob/main/LICENSE) license.

## Special thanks

 @ [Hieromon](https://github.com/Hieromon/AutoConnect) For its great library and its [documentation](https://hieromon.github.io/AutoConnect/index.html) that has allowed us to create this application.


