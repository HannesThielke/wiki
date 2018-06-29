---
title: Software
nav: true
---

# Programming the OpenDrop
The OpenDrop v2.1 is based on an [Arduino Micro](https://store.arduino.cc/arduino-micro) which is a development board based on the ATmega32U4 microcontroller and acts on a 5V logic level. It has 20 digital input/output pins (of which 7 can be used as PWM outputs and 12 as analog inputs), a 16 MHz crystal oscillator, a micro USB connection, an ICSP header, and a reset button. The Arduino Micro can be programmed via the [Arduino IDE](https://www.arduino.cc/en/Main/Software?).
{% include figure.html file="arduino_micro.jpg" caption="Arduino Micro" src="https://store-cdn.arduino.cc/usa/catalog/product/cache/1/image/1040x660/604a3538c15e081937dbfbd20aa60aad/a/0/a000053_featured_2.jpg" height="3cm"%}

The source code for the [OpenDrop Library](doxygen/html/index.html) is located on our [GitHub repository](https://github.com/BiocomputeLab/opendrop). It is a modified version of the [original source code](https://github.com/GaudiLabs/OpenDrop) where new functions and comments have been added.
 The OpenDrop-Library provides useful functions to operate the system. This includes the initialization of peripherals (Electrodes, Buttons, Joystick, OLED-Display, Potentiometer), the droplet-movement and the feedback reading. For a detailed documentation of the specific functions, have a look on our Library documentation:
 [Library](doxygen/html/index.html)

 This documentation was automatically created from the source code with the help of [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
{% include figure.html file="doxygen_logo.png" caption="Doxygen Logo" src="https://www.macupdate.com/app/mac/51038/doxygen" %}