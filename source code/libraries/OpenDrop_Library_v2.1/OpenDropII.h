/** \file
 * --------------------------------------------------------------------
 * This file is part of the OpenDrop library
 * by Urs Gaudenz, GaudiLabs 2016
 * documentation written by Hannes Thielke, Bio compute lab, University of Bristol, 2018
 * --------------------------------------------------------------------
 */

// Checking for the version of the Arduino IDE; >100 means it is newer than version 1.0
#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif

#include "Adafruit_GFX.h"

#define max_drops   8	/** Maximal number of droplet that are allowed at the device*/

class OpenDrop;

class Drop {
 	 public:
		 Drop(void);				// Constructor
		 friend class OpenDrop;
		 void(begin(int x,int y));
		 void(move_right());
		 void(move_left());
		 void(move_up());
		 void(move_down());
		 void(go(int x,int y));
		 int position_x();
		 int position_y();
		 int goal_x();
		 int goal_y();
		 int next_x();
		 int next_y();
		 int num();
		 bool is_moving();

 	 private:
		uint8_t _pos_x;
		uint8_t _pos_y;
		uint8_t _goal_x;
		uint8_t _goal_y;
		uint8_t _next_x;
		uint8_t _next_y;
		uint8_t _dropnum;
		bool _moving;
};

class OpenDrop
{
	public:
		OpenDrop(uint8_t addr = 0x60);
		friend class Drop;
		void begin(uint16_t freq = 1600);
		bool run(void);
		void update(void);
		void update_Display(void);
		void update_Drops(void);
		void drive_Fluxels(void);
		void read_Fluxels(void);
		void set_joy(uint8_t x,uint8_t y);
		void setPin(uint8_t pin, boolean val);
		Drop *getDrop();
		void run_circle(Drop *myDrop);

	 private:
		uint8_t _addr;
		uint16_t _freq;
		Drop drops[max_drops];
		uint8_t drop_count=0;
		int _runing;
		uint8_t _joy_x;
		uint8_t _joy_y;
};



