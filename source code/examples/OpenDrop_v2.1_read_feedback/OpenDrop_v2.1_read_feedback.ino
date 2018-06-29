/*
  Basic Code to run the OpenDrop V2.1, Research platform for digital microfluidics
  Written by Urs Gaudenz from GaudiLabs
  2016

  Changes made by Hannes Thielke - bio compute lab Bristol
  2018

  This file includes features for moving droplets according to the joystick position 
  and reading the feedback pin. That enables scanning the current droplets on the device
  and receiving their x and y position
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
OpenDrop OpenDropDevice = OpenDrop();     //Create a new OpenDrop Object
Drop *myDrop = OpenDropDevice.getDrop();  //Initialize a droplet

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

  // Begin
  OpenDropDevice.begin();

  // Wait for button 2 to be pressed
  while(digitalRead(SW2_pin) == HIGH);
  Serial.println("Button pressed: Starting ...");

  myDrop->begin(1,1);

  // Update the OpenDrop device
  OpenDropDevice.update();
}

byte* f;
byte pos[16][8];
byte x;
byte y;

/******************************
 * Loop Function: Executed after the setup is done and repeated forever
 ******************************/
void loop() {

  /** 
   *  Read the joystick position and the state of buttons 
   *  SW_value is 0 when button is pressed; else 1
   */
  JOY_value = analogRead(JOY_pin);
  SW1_value = digitalRead(SW1_pin);
  SW2_value = digitalRead(SW2_pin);
  SW3_value = digitalRead(SW3_pin);

  while(JOY_value>950 & SW1_value & SW2_value){
    JOY_value = analogRead(JOY_pin);
    SW1_value = digitalRead(SW1_pin);
    SW2_value = digitalRead(SW2_pin);
    SW3_value = digitalRead(SW3_pin);

    /* 
     * Reading the x and y coordinate of the current droplets
     */
    f = OpenDropDevice.get_feedback();

    // First 64 electrodes that are driven by the first HV507 chip
    for(int i=0;i<64;i++){
      x = pgm_read_byte_near(pad_lookup_x+i);
      y = pgm_read_byte_near(pad_lookup_y+i);
      if(f[i] == 0){
        Serial.print("\nx: ");
        Serial.print(x);
        Serial.print(" , y: ");
        Serial.print(y);
      }
    }

    // Second 64 electrodes that are driven by the second HV507 chip
    for(int i=0;i<64;i++){
      x = 15-pgm_read_byte_near(pad_lookup_x+x);
      y = 7-pgm_read_byte_near(pad_lookup_y+x);
      if(f[i+64] == 0){
        Serial.print("\nx: ");
        Serial.print(x);
        Serial.print(" , y: ");
        Serial.print(y);
      }
    }
    
    OpenDropDevice.run(); // Refresh
  }

  /** Move the droplet according to the joystick position */
  if  (JOY_value<300)                     myDrop->move_right(); // Move right
  if  ((JOY_value>700)&&(JOY_value<950))  myDrop->move_up();    // Move up
  if  ((JOY_value>600)&&(JOY_value<700))  myDrop->move_left();  // Move left
  if  ((JOY_value>450)&&(JOY_value<600))  myDrop->move_down();  // Move down
  
  delay(del_time);      // Refresh rate

}
