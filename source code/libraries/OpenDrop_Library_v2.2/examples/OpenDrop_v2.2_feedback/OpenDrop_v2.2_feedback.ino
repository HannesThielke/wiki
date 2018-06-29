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

int JOY_value;        //Analog value from the joystick
int SW2_value;        //Digital value that shows the state of button 2
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
  myDrop->begin(7,7);

  // Play sound
  tone(SPK_pin,2000,100);
  delay(100);
  tone(SPK_pin,2000,100);
  delay(200);

  // Wait for button 2 to be pressed
  while(digitalRead(SW2_pin) == HIGH);
  Serial.println("Button pressed: Starting ...");

  // Update the OpenDrop device
  OpenDropDevice.update();
}

/******************************
 * Loop Function: Executed after the setup is done and repeated forever
 ******************************/
void loop() {

  /** Read the joystick position
   *  SW_value is 0 when button is pressed; else 1
   */
  JOY_value = analogRead(JOY_pin);

  /** Wait for changes */
  while(JOY_value>950){
   JOY_value = analogRead(JOY_pin);
  }
  
  /** Move the droplet according to the joystick position */
  if  (JOY_value<300)                     myDrop->move_right(); // Move right
  if  ((JOY_value>700)&&(JOY_value<950))  myDrop->move_up();    // Move up
  if  ((JOY_value>600)&&(JOY_value<700))  myDrop->move_left();  // Move left
  if  ((JOY_value>450)&&(JOY_value<600))  myDrop->move_down();  // Move down

  OpenDropDevice.run(); // Refresh
  delay(del_time);      // Refresh rate

}
