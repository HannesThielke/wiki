/*
  Basic Code to run the OpenDrop V2.1, Research platfrom for digital microfluidics
  Object codes are defined in the OpenDrop.h library
  Written by Urs Gaudenz from GaudiLabs
  2016

  Changes made by Hannes Thielke - bio compute lab Bristol
  2018
 */

/******************************
 * Libraries:
 * <SPI.h>: Communication with SPI devices
 * <Wire.h>: Communication with I2C / TWI devices
 * <TimerOne.h>: Collection of routines for configuring the 16 bit hardware timer on the ATmega168/328
 * <avr/pgmspace.h>: Store data in flash (program) memory instead of SRAM
 * "Adafruit_GFX.h" (version 1.1.3): Core graphics library for the OLED display
 * <Adafruit_SSD1306.h> (version 1.0.1): SSD1306 oled driver library for 'monochrome' 128x64 and 128x32 OLEDs
 * <OpenDropII.h>: OpenDrop Library from GaudiLabs
 * "hardware_def.h": Definition of the hardware settings (PINS etc.)
 ******************************/

#include "TimerOne.h"  
#include <avr/pgmspace.h>

#include "Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>

#include <OpenDropII.h>
#include "hardware_def.h"

/******************************
 * Variables
 ******************************/
OpenDrop OpenDropDevice = OpenDrop();     //Create a new OpenDrop Object
Drop *myDrop = OpenDropDevice.getDrop();  //Initialize a droplet

int SW2_value;        //Digital value that shows the state of button 2

/******************************
 * Setup Function: Executed at the beginning of the programme
 ******************************/
void setup() {

  // Initialize the clock speed of the timer (Frequency in Hz
  const int AC_frequency=1000;
  Timer1.initialize(500000/AC_frequency);

  // Enable Serial Output at baudrate 4800
  Serial.begin(4800);

  // Begin with a droplet on the electrode at position (7,7)
  OpenDropDevice.begin();

  // Play sound
  tone(SPK_pin,2000,100);
  delay(100);
  tone(SPK_pin,2000,100);
  delay(200);

  Serial.println("Starting ...");
	myDrop->begin(1,1);
	OpenDropDevice.update();
}

void loop(){
	SW2_value = digitalRead(SW2_pin);

	// Wait for button 2 to be pressed
	while(SW2_value) SW2_value = digitalRead(SW2_pin);
	run_protocol();
}

int del_time=50;

void run_protocol(){
	myDrop->move_left();
	OpenDropDevice.run();
	myDrop->move_left();
	OpenDropDevice.run();
	myDrop->move_left();
	OpenDropDevice.run();
	myDrop->move_down();
	OpenDropDevice.run();
}