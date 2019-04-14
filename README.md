# Arduino-Security-Panel-System
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project is a digital door locking system using concepts of interactive hardware. The presented content in this repository is about a prototype developed according to the proposed design as a part of the final project of the semester. This project is an extension of Security Panel System by [Mert Arduino](http://mertarduinotutorial.blogspot.com/2017/01/arduino-tutorial-22-security-panel.html).

![Alt Text](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/img/open-close-fromwebpage.gif)


## Repository Contents

* **/documentation** - Contains the project proposal and design report of this project which was submitted to the instructor. 
* **/hardware** - Contains PCB design files.
* **/img** - Contains all the image files of this project
* **/libraries** - Contains all the libraries that was required to buid this project.
* **/src** - Contains the .ino files for Arduino Mega and ESP8266 Wifi Module.
* **/LICENSE** - Contains the details of the license for this project.
  


## Requirements and Materials

The libraries required to build this project are as follows:

* [ESP8288.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/ESP8266WiFi.h)
* [Keypad.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/Keypad.h)
* [PCM.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/PCM.h)
* [SoftwareSerial.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/SoftwareSerial.h)
* [Stepper.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/Stepper.h)
* [LiquidCrystal.h](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/libraries/LiquidCrystal.h)

The Software required for this project is [Arduino IDE](https://www.arduino.cc/en/main/software).

Bill of Hardware Materials:
* 1 X Arduino Mega 2560 (Rev3)
* 1 X Breadboard (optional)
* 1 X Piezo Speaker
* 3 X Leds (Red, Blue, Green)
* 1 X Matrix Keypad(4 x 4)
* 1 X 28BYJ-48 Stepper Motor
* 1 X ULN2003A - Stepper Driver Board
* 3 X 220 ohm Resistors
* 1 X Loud Speaker
* 1 X LCD-16x2
* 1 X 1K ohm potentiometer
* 1 X ESP8266 ESP-12E UART WIFI Shield

## Build Instructions
The below schematic gives an idea about how the components are put together to build the system.

![Alt Text](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/img/schematic.png)

To know the connections in detail refer to the below circuit diagram.

![Alt Text](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/img/circuit.jpg)


## Uploading Sketch
To assemble this system gather the materials mentioned in Requirements and Materials.

### Follow these steps to upload the code to Arduino Mega 2560:

1. Connect USB cable of arduino to the PC.
2. Open Arduino IDE then goto  File->New or press Ctrl+N.
3. Then goto Tools->Port and select the COM port for Arduino Mega 2560 (for Mac users it would be something like /dev/tty).
4. Copy the code from [Arduino-Mega_Code.ino](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/src/Arduino-Mega_Code.ino) and paste it in Arduino sketch.
5. Download all the libraries from [here](https://github.com/trushil/Arduino-Security-Panel-System/tree/master/libraries). Then go to Documents\Arduino\libraries and pase them here.
6. Compile the sketch by clicking the check button below file option or press ctrl+R.
7. After the sketch gets compiled with no errors press the right arrow button below edit option or press Ctrl+U to upload the sketch to Arduino Mega 2560.

    Now before uploading the code to ESP8266 ESP-12E UART WIFI Shield we need to manipulate the DIP buttons on the shield. For more details refer to this [link](https://medium.com/@manrick01/arduino-uno-esp8266-esp-12e-uart-wifi-wireless-shield-3a39858e5f25). We can also upload the sketch to the ESP8266 ESP-12E UART WIFI Shield with the help of Arduino Uno or Mega 2560.

### Follow these steps to upload the code to ESP8266 ESP-12E UART WIFI Shield using Arduino Uno:
1. Before connecting align the DIP buttons to (DOWN, DOWN, UP, UP) from 1 to 4 respectively.
2. **Connections:** Make the connections from Arduino Uno to Wifi shield according to the table below.

    | Arduino Uno   | ESP8266 ESP-12E UART WIFI Shield |
    | ------------- |----------------------------------|
    | Rx            | Rx                               |
    | Tx            | Tx                               |
    | GND           | GND                              |
    | +3.3V         | +3.3V                            |
    |   Connect  RESET pin of Arduino Uno to GND       |

3. After the above connections are made, follow next step.
4. Open you IDE and click on "File -> Preferences".
5. In  "Aditional Boards Manager URLs" add this line and click on "OK": "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
6. Go to "Tools -> Board -> Boards Manager", type "ESP8266" and install it.
7. Go again to "Tools -> Board" and select "Generic ESP8266 Module".
8. Copy the code from [here](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/src/ESP8266-HTTP_Server.ino) and paste it in the Arduino IDE.
9. Then compile the sketch and upload it the same way it was done for Arduino Mega.

    After the above steps are completed with no errors disconnect the connections and connect the components again according to the schematic in Build Instructions.

    (**Note**:- Change the DIP pins of Wifi Shield to (DOWN,DOWN,DOWN,DOWN,) respectively before turning on the system.)

## Usage
Before turning on the the system create a hotspot or connect to any access point(**Note**:- Change the credentials accordingly in the code of ESP8266 Wifi shield before uploading to it.). Now Turn ON the system by providing a 9V to 12V power supply.

Now the system can be monitored and controlled by 2 ways:-

### Control and monitor through webpage
First connect your machine or mobile phone to the same hotspot or access point. Then type the IP address of the server (This can be found on the serial monitor of ESP8266 WIfi Module) as URL in the web browser. Now, from here you can perform OPEN/CLOSE to the door lock system and also monitor the state of the system.

### Controlling through hands
The door lock can be opened by entering the 4-digit passcode in the keypad. And, the door can be closed by pressing '*' in the keypad. The status of the system can be monitored simultaneoulsy through the webpage. 

![Alt Text](https://github.com/trushil/Arduino-Security-Panel-System/blob/master/img/open-close-fromkeypad.gif)

## Team
The build team consists of:
* Trushil Patel (Role: Coding and Documentation)
* Akash Singh (Role: Testing and Documentation)

## Credits
These are the third parties which deserves a credit for motivating us for this project:
* Trevor Tomesh, instructor- CS 807 Interactive Hardware
* [Mert Arduino](http://mertarduinotutorial.blogspot.com/)
* [electronic GURU](https://www.youtube.com/watch?v=F28Znry0qcw)
* Family and friends cannot be forgotten :)

## License & Copyrights

© Trushil Patel, Computer Science, University Of Regina

Licensed Under [MIT License](LICENSE).
Just testing pull request





