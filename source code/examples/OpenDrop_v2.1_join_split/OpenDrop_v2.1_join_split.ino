/*
  Basic Code to run the OpenDrop V2.1, Research platform for digital microfluidics
  Written by Urs Gaudenz from GaudiLabs
  2016

  Changes made by Hannes Thielke - bio compute lab Bristol
  2018

  This file includes features for joining two droplets and splitting them afterwards
 */

/******************************
 * Libraries:
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
OpenDrop OpenDropDevice = OpenDrop();      //Create a new OpenDrop Object
Drop *myDrop1 = OpenDropDevice.getDrop();  //Initialize a droplet
Drop *myDrop2 = OpenDropDevice.getDrop();  //Initialize a droplet

int JOY_value;        //Analog value from the joystick
int SW1_value;        //Digital value that shows the state of button 1
int SW2_value;        //Digital value that shows the state of button 2
int SW3_value;        //Digital value that shows the state of button 3 (joystick)
int del_time=10;      //Delay time during update loops

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
  myDrop1->begin(6,4);
  myDrop2->begin(10,4);

  // Play sound
  //tone(SPK_pin,2000,100);
  //delay(100);
  //tone(SPK_pin,2000,100);
  //delay(200);

  // Wait for button 2 to be pressed
  while(digitalRead(SW2_pin) == HIGH);
  Serial.println("Button pressed: Starting ...");

  // Update the OpenDrop device
  OpenDropDevice.update();

}

bool joined = false;

/******************************
 * Loop Function: Executed after the setup is done and repeated forever
 ******************************/
void loop() {

  /** Read the joystick position and the state of buttons 
   *  SW_value is 0 when button is pressed; else 1
   */
  JOY_value = analogRead(JOY_pin);
  SW1_value = digitalRead(SW1_pin);
  SW2_value = digitalRead(SW2_pin);
  SW3_value = digitalRead(SW3_pin);

  while(JOY_value>950 & SW1_value & SW2_value)
  {
    JOY_value = analogRead(JOY_pin);
    SW1_value = digitalRead(SW1_pin);
    SW2_value = digitalRead(SW2_pin);
    SW3_value = digitalRead(SW3_pin);
    OpenDropDevice.run(); // Refresh
  }

  if(!joined)
  {
    myDrop1->move_right();
    myDrop2->move_left();
    OpenDropDevice.run(); // Refresh
    delay(1000);
    myDrop1->move_right();
    myDrop2->move_left();
    joined=true;
    OpenDropDevice.run(); // Refresh
  }
  else
  {
    myDrop1->move_left();
    myDrop2->move_right();
    OpenDropDevice.run(); // Refresh
    delay(5000);
    myDrop1->move_left();
    myDrop2->move_right();
    joined=false;
    OpenDropDevice.run(); // Refresh
  }
  
  delay(del_time);

}
