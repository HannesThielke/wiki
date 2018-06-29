/** \file
 * 	\include index.h
 * --------------------------------------------------------------------
 * This file is part of the OpenDrop library
 * by Urs Gaudenz, GaudiLabs 2016
 * Documentation by Hannes Thielke - Bio Compute Lab, University of Bristol, 2018
 * --------------------------------------------------------------------
*/

#include "OpenDropII.h"
#include "hardware_def.h"
#include "Adafruit_GFX.h"
#include <Adafruit_SSD1306.h>

/** \var
 * 2D-Array of the size 16x8 that represents the state of the Fluxls.\n
 * Active fields are represented by a binary 1 (true)
 * and inactive fields are represented by a binary 0 (false)
 */
bool Fluxls[FluxlPad_width][FluxlPad_heigth];

/** \var
 * Feedback Array that represents the detected droplets on the OpenDrop device.\n
 * Droplets are represented by a binary 0 (false) and the empty fields are
 * represented by a binary 1 (true)
 */
byte pad_feedback [128];

/**
 * Initialize the OLED display to be used at the SPI bus
 */
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


/**************************************
 * FUNCTIONS
 **************************************/

/**
 * Clear Fluxel Matrix --> set all entries to 0 (false)
 */
void clear_Fluxels()
{
	for (int x = 0; x <FluxlPad_width; x++) 
		for (int y = 0; y <FluxlPad_heigth; y++)
			Fluxls[x][y]=false;
};

/**
 * Check if the electrodes around the current Fluxl and
 * the target Fluxl is free (no droplet on it) or if the
 * edge of the field is reached.\n
 * This can be used to avoid collisions.
 * \image html free_fluxels.svg
 * @param x The x-coordinate of the Fluxel
 * @param y The y-coordinate of the Fluxel
 * @param dir The direction to move
 * @return true (Fluxel is free) or false (Fluxel is blocked or out of the field)
 */
bool free_Fluxel(uint8_t x, uint8_t y, uint8_t dir)
{
	bool check=true;
	if (check&&(x>0)&&(dir==4)) 														check = pad_feedback[pgm_read_byte_near(&FluxelID[x-1][y])]==1; //left
	if (check&&(x<(FluxlPad_width-1))&&(dir==2)) 										check = pad_feedback[pgm_read_byte_near(&FluxelID[x+1][y])]==1; //right
	if (check&&(y>0)&&(dir==1)) 														check = pad_feedback[pgm_read_byte_near(&FluxelID[x][y-1])]==1; //up
	if (check&&(y<(FluxlPad_heigth-1))&&(dir==3)) 										check = pad_feedback[pgm_read_byte_near(&FluxelID[x][y+1])]==1; //bottom
	if (check&&(x>0)&(y>0)&&((dir==1)||(dir==4))) 										check = pad_feedback[pgm_read_byte_near(&FluxelID[x-1][y-1])]==1; //left top
	if (check&&(x>0)&(y<(FluxlPad_heigth-1))&&((dir==3)||(dir==4))) 					check = pad_feedback[pgm_read_byte_near(&FluxelID[x-1][y+1])]==1; //left bottom
	if (check&&(x<(FluxlPad_width-1))&&(y>0)&&((dir==1)||(dir==2))) 					check = pad_feedback[pgm_read_byte_near(&FluxelID[x+1][y-1])]==1; //right top
	if (check&&(x<(FluxlPad_width-1))&&(y<(FluxlPad_heigth-1))&&((dir==2)||(dir==3))) 	check = pad_feedback[pgm_read_byte_near(&FluxelID[x+1][y+1])]==1; //right bottom

	return check;
};

/*************************
 * OPEN DROP OBJECT
 *************************/

/**
 * Constructor
 */
OpenDrop::OpenDrop(uint8_t addr) {
	_addr = addr;
}

/**
 * Show all changes that have been made since the last update of the display.\n
 * --> Load current Fluxls Matrix
 */
void OpenDrop::update_Display(void)
{
	//clear Display
	display.clearDisplay();  

	//write coordinates
	display.setCursor(18,4);
	display.print("X: ");
	display.print(drops[0].position_x());
	display.print(" Y: ");
	display.print(drops[0].position_y());

	// draw Grid
	for (int x = 1; x <FluxlPad_width ; x++) 
		for (int y = 1; y <FluxlPad_heigth ; y++) 
			display.drawPixel(x*6+16,y*6+16,WHITE);

	// draw Fluxls
	Serial.print("\nnext y:\n");
	Serial.print(drops[0].next_y());
	for (int x = 0; x <FluxlPad_width ; x++){
		for (int y = 0; y <FluxlPad_heigth ; y++){
			if (Fluxls[x][y]) {
				display.drawRect(x*6+17, y*6+17, 5,5, 1);
			}
		}
	}

	// draw Feedback
	// check if feedback is enabled
	if (feedback_flag) {
		for (int x = 0; x <64 ; x++) 
			// Check if a droplet is detected on the electrode
			if (pad_feedback[x]==0) {
				display.fillRect(pgm_read_byte_near(pad_lookup_x+x)*6+18, pgm_read_byte_near(pad_lookup_y+x)*6+18, 3,3, 1);
			}
		for (int x = 0; x <64 ; x++)
			// Check if a droplet is detected on the electrode
			if (pad_feedback[x+64]==0) {
				display.fillRect((15-pgm_read_byte_near(pad_lookup_x+x))*6+18, (7-pgm_read_byte_near(pad_lookup_y+x))*6+18, 3,3, 1);
			}
	}
	
	//draw cursor
	display.drawRect(_joy_x*6+17, _joy_y*6+18, 5,3, 1);

	// draw Rect
	display.drawRect(16, 16, 97,48, 1);

	// update display
	display.display();
};

/**
 * Fill the chip with Fluxls array data
 * \image html drive_Fluxls.svg
 * \image html block_diagram_fluxls.png
 */
void OpenDrop::drive_Fluxels(void)
{  
	digitalWrite(LE_pin, LOW);  		// reset latch enable (LE) pin
	digitalWrite(CLK_pin, LOW);  		// reset clock (CLK) pin --> reset CLK state

	for (int i = 0; i <64 ; i++) 
	{
		digitalWrite(DI_pin,Fluxls[pgm_read_byte_near(pad_lookup_x+i)][pgm_read_byte_near(pad_lookup_y+i)]);
		digitalWrite(CLK_pin, HIGH);	// set clock (CLK) pin --> shift input
		digitalWrite(CLK_pin, LOW);		// reset clock (CLK) pin --> reset CLK state
	};

	for (int i = 0; i <64 ; i++) 
	{
		digitalWrite(DI_pin,Fluxls[15-pgm_read_byte_near(pad_lookup_x+i)][7-pgm_read_byte_near(pad_lookup_y+i)]);
		digitalWrite(CLK_pin, HIGH);   	// set clock (CLK) pin --> shift input
		digitalWrite(CLK_pin, LOW);    	// reset clock (CLK) pin --> reset CLK state
	};

	digitalWrite(LE_pin, HIGH);			// set latch enable (LE) pin
	digitalWrite(LE_pin, LOW);			// reset latch enable (LE) pin
	digitalWrite(BL_pin, HIGH); 		// set blanking (BL) pin --> turn on
};

/**
 * Read the feedback for all electrodes on the OpenDrop Matrix
 * and update the pad_feedback array with the new data.
 * \image html read_Fluxls.svg
 * \image html block_diagram_fluxls.png
 */
void OpenDrop::read_Fluxels(void) 
{
	// Suppress Interrupts
	noInterrupts();

	/** \var
	 * temporary variable that represents the feedback of the current electrode
	 * that is connected to the feedback pin
	 */
	bool reading;

	// clear driver chip
	digitalWrite(BL_pin, LOW);			// reset blanking (BL) pin --> turn off
	digitalWrite(DI_pin,LOW);			// reset digital input/output (DI) pin
	
	// shift input 128x
	for (int i = 0; i <128 ; i++) 
	{   
		digitalWrite(CLK_pin, HIGH);	// set clock (CLK) pin --> shift input
		digitalWrite(CLK_pin, LOW);		// reset clock (CLK) pin --> reset CLK state
	}

	// turn first Electrode on
	digitalWrite(DI_pin,HIGH);			// set digital input/output (DI) pin
	digitalWrite(CLK_pin, HIGH);   		// set clock (CLK) pin --> shift input
	digitalWrite(CLK_pin, LOW);   		// reset clock (CLK) pin --> reset CLK state
	digitalWrite(LE_pin, HIGH);   		// set latch enable (LE) pin
	digitalWrite(LE_pin, LOW);   		// reset latch enable (LE) pin
	digitalWrite(DI_pin,LOW);			// reset digital input/output (DI) pin

	// read the electrodes one by one
	for (int i = 0; i <128 ; i++) 
	{
		delayMicroseconds(10);				// wait for 10ms
		digitalWrite(BL_pin, HIGH);			// set blanking (BL) pin --> turn on
		reading=digitalRead(FEEDBACK_pin);	// read the state of the Feedback Pin
		pad_feedback[127-i]=reading;		// set entry in the feedback matrix

		digitalWrite(BL_pin, LOW);			// reset blanking (BL) pin --> turn off
		digitalWrite(CLK_pin, HIGH);   		// set clock (CLK) pin --> shift input
		digitalWrite(CLK_pin, LOW);   		// reset clock (CLK) pin --> reset CLK state
		digitalWrite(LE_pin, HIGH);   		// set latch enable (LE) pin
		digitalWrite(LE_pin, LOW);   		// reset latch enable (LE) pin
	};
	
	// Enable Interrupts again
	interrupts();
}

/**
 * Setup all pins and show the initial loading screen.\n
 * This function should be called in the setup function at beginning of the programme.
 * \image html begin.svg
 * \image html block_diagram_fluxls.png
 */
void OpenDrop::begin(uint16_t freq) {

	// Initialize Pins for HV507 Chip
	pinMode(BL_pin, OUTPUT); 		// define blanking (BL) pin as OUTPUT
	pinMode(LE_pin, OUTPUT); 		// define latch enable (LE) pin as OUTPUT
	pinMode(CLK_pin, OUTPUT); 		// define clock (CLK) pin as OUTPUT
	pinMode(DI_pin, OUTPUT); 		// define data input/output (DI) pin as OUTPUT
//	pinMode(POL_pin, OUTPUT); 		// define polarity (POL) pin as OUTPUT
	
	digitalWrite(BL_pin, HIGH);   	// set blanking (BL) pin --> turn on
	digitalWrite(LE_pin, LOW);   	// reset latch enable (LE) pin
	digitalWrite(CLK_pin, LOW);   	// reset clock (CLK) pin --> reset CLK state
	digitalWrite(DI_pin, LOW);   	// reset digital input/output (DI) pin
//	digitalWrite(POL_pin, HIGH);    // set polarity (POL) pin

	// Initialize LED
	pinMode(LED_LIGHT_pin, OUTPUT); //Set LED pin output

	// Initialize Buttons
	pinMode(SW1_pin, INPUT);	// define Button 1 pin as INPUT
	pinMode(SW2_pin, INPUT);	// define Button 2 pin as INPUT
	pinMode(SW3_pin, INPUT);	// define Button 3 pin as INPUT
	pinMode(JOY_pin, INPUT);	// define joystick pin as INPUT
	
	// Use the internal pullup-resistors for Buttons 1-3
	digitalWrite(SW1_pin, HIGH);  
	digitalWrite(SW2_pin, HIGH);  
	digitalWrite(SW3_pin, HIGH);  
	
	// Start Display
	display.begin(SSD1306_SWITCHCAPVCC);
	
	// Show image buffer on the display hardware.
	// Since the buffer is intialized with an Adafruit splashscreen
	// internally, this will display the splashscreen.
	display.display();
	delay(2000);

	// Clear the buffer.
	display.clearDisplay();
	display.dim(false);

	// Show Initial Load Screen
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(5,20);
	display.println("Loading protocol...");
	display.display();
	delay(500);
	display.setCursor(5,29);
	display.println("Press Start");
	display.display();

	// Set joystick values to x=5, y=5
	this->set_joy(5,5);

	// If lights are enabled, turn on the LEDs
	if (light_flag)   digitalWrite(LED_LIGHT_pin, HIGH);
}

/**
 * Every droplet on the electrode matrix is being checked for updates.
 * If the position has been changed, the new positions will be adopted.
 * 1. Check if feedback feature is enabled\n
 * 2. Check if the position has been changed\n
 * 3. Check if feedback has detected a change\n
 * 4. Call drop.begin()
 */
void OpenDrop::update_Drops(void) {
	for (int i = 0; i <this->drop_count ; i++) 
	{
		// Check if feedback feature is enabled
		if (feedback_flag){
			// Check if the position has been changed
			if ((drops[i].position_x()!=drops[i].next_x())|(drops[i].position_y()!=drops[i].next_y()))
			{
				// Check if feedback has detected a change
				if ((pad_feedback[pgm_read_byte_near(&FluxelID[drops[i].position_x()][drops[i].position_y()])]==1)&(pad_feedback[pgm_read_byte_near(&FluxelID[drops[i].next_x()][drops[i].next_y()])]==0))
				{
					drops[i].begin(drops[i].next_x(),drops[i].next_y());
				};  
			};
		} else
			drops[i].begin(drops[i].next_x(),drops[i].next_y());
	};
}

/**
 * The update-function should be called in the main loop of the programme.\n
 * 1. Clear the Fluxls Array\n
 * 2. Fill the Fluxls Array with the new data\n
 * 3. If the feedback feature is enabled: update the pad_feedback array\n
 * 4. Fill the chip with Fluxls array data\n
 * 5. Update the display
 */
void OpenDrop::update(void) {

	//clear Fluxel Array
	clear_Fluxels();

	//Fill Fluxel Array
	for (int i = 0; i <this->drop_count ; i++) 
	{
		Fluxls[drops[i].next_x()][drops[i].next_y()]=true;
	};

	// If the feedback feature is enabled: 
	// update the pad_feedback array
	if (feedback_flag)
		this->read_Fluxels();
	
	this->drive_Fluxels();	// Fill the chip with Fluxls array data
	this->update_Display();	// Update the display

	// If sounds are enabled --> Play sound
	if(sound_flag)   tone(SPK_pin,1000,10);  
}

/**
 * 1. Check if the droplet is moving or has reached its goal position\n
 * 2. If not, block all directions that would end up in pushing the droplet\n
 * off the field or joining two droplets together
 * 3. Calculate the direction vector\n
 * 4. Move in this direction
 * @return true (a transition has been made) or false (no transition has been made)
 */
bool OpenDrop::run(void) {
	
	bool transition=false;	// Has a transition been made?
	//this->read_Fluxels();	// Read the feedback for all electrodes
	this->update_Drops();	// Update changes in the droplet position

	// Repeat for all droplets
	for (int i = 0; i <this->drop_count ; i++) 
	{
		bool up 	= true;	/** \var Is it allowed to move up? */
		bool down	= true;	/** \var Is it allowed to move down? */
		bool left 	= true;	/** \var Is it allowed to move left? */
		bool right	= true;	/** \var Is it allowed to move right? */
		int d1=6000;		/** \var direction vector */
		int d2=6000;		/** \var direction vector */

		_runing=true;

		// If the droplet hasn't reached it's goal position, set _runing=true
		_runing= ((drops[i].position_x()!=drops[i].goal_x())|(drops[i].position_y()!=drops[i].goal_y()));
		transition=transition|_runing;

		// Check if the droplet is moving already
		if (_runing&!drops[i].is_moving()) {

			// If the droplet is near to the edge of the electrode matrix
			// block the directions that would push the droplet out of the field
			if (drops[i].position_x()==0) 					left =	false;
			if (drops[i].position_x()==(FluxlPad_width-1)) 	right =	false;
			if (drops[i].position_y()==0) 					up =	false;
			if (drops[i].position_y()==(FluxlPad_heigth-1)) down =	false;

			// If the droplet is near to another droplet
			// block the directions to prevent the droplets from joining
//			if (right) 	if (!free_Fluxel(drops[i].position_x()+1,drops[i].position_y(),2)) right =	false;
//			if (left) 	if (!free_Fluxel(drops[i].position_x()-1,drops[i].position_y(),4)) left =	false;
//			if (up) 	if (!free_Fluxel(drops[i].position_x(),drops[i].position_y()-1,1)) up =		false;
//			if (down) 	if (!free_Fluxel(drops[i].position_x(),drops[i].position_y()+1,3)) down =	false;

			// Calculate the direction vector
//			if (right) 	 d1=pow((drops[i].position_x()+1)-(drops[i].goal_x()),2)+pow((drops[i].position_y())-(drops[i].goal_y()),2);
//			if (left) 	{d2=pow((drops[i].position_x()-1)-(drops[i].goal_x()),2)+pow((drops[i].position_y())-(drops[i].goal_y()),2); if (d2<d1) {right=false;d1=d2;} else left=false;};
//			if (up) 	{d2=pow((drops[i].position_x())-(drops[i].goal_x()),2)+pow((drops[i].position_y()-1)-(drops[i].goal_y()),2); if (d2<d1) {left=false;right=false;d1=d2;} else up=false;}
//			if (down) 	{d2=pow((drops[i].position_x())-(drops[i].goal_x()),2)+pow((drops[i].position_y()+1)-(drops[i].goal_y()),2); if (d2<d1) {left=false;up=false;right=false;d1=d2;} else down=false;}

			// Move in the direction
			if (up) drops[i].move_up(); else
				if (down) drops[i].move_down(); else
					if (left) drops[i].move_left(); else
						if (right) drops[i].move_right();
		};
	};

	this->update();
	return transition;
};

/*************************
 * DROP OBJECT
 *************************/

/** Get a Drop object entity
 * and increase the droplet number
 * @return a droplet entity or NULL if
 * the maximum number of droplets is reached
 */
Drop *OpenDrop::getDrop() {
	uint8_t num=this->drop_count;
	num++;								// Add 1 to the current droplet number
	this->drop_count=num;
	drops[num-1]._dropnum = num;
	if (num > max_drops) return NULL;	// Return NULL if the maximum number of droplets is reached
	return &drops[num-1];
}

/** Constructor */
Drop::Drop(void) {}

/**
 * set joystick value
 */
void OpenDrop::set_joy(uint8_t x,uint8_t y)
{
	_joy_x=x;
	_joy_y=y;
}

/**
 * Begin function
 */
void Drop::begin(int x,int y) {
	_pos_x=x;
	_pos_y=y;
	_next_x=x;
	_next_y=y;
	_moving = false;
}

/**
 * Move the droplet to the right
 */
void Drop::move_right(void) {
	if (_pos_x<FluxlPad_width-1)
		_next_x=_pos_x+1;
	_next_y=_pos_y;
	_moving = true;
}

/**
 * Move the droplet to the left
 */
void Drop::move_left(void) {
	if (_pos_x>0)
		_next_x=_pos_x-1;
	_next_y=_pos_y;
	_moving = true;
}

/**
 * Move the droplet up
 */
void Drop::move_up(void) {
	if (_pos_y>0) 
		_next_y=_pos_y-1;
	_next_x=_pos_x;
	_moving = true;
}

/**
 * Move the droplet down
 */
void Drop::move_down(void) {
	if (_pos_y<(FluxlPad_heigth-1)) 
		_next_y=_pos_y+1;
	_next_x=_pos_x;
	_moving = true;
}

/**
 * Get the x-position
 */
int Drop::position_x(void) {
	return _pos_x;
}

/**
 * Get the y-position
 */
int Drop::position_y(void) {
	return _pos_y;
}

/**
 * Get the next x-position
 */
int Drop::next_x(void) {
	return _next_x;
}

/**
 * Get the next y-position
 */
int Drop::next_y(void) {
	return _next_y;
}

/**
 * Get the goal x-position
 */
int Drop::goal_x(void) {
	return _goal_x;
}

/**
 * Get the goal y-position
 */
int Drop::goal_y(void) {
	return _goal_y;
}

/**
 * Get the number of droplets
 */
int Drop::num(void) {
	return _dropnum;
}

/**
 * Set a goal position
 */
void Drop::go(int x,int y) {
	_goal_x=x;
	_goal_y=y;
}

/**
 * Returns the state of the Droplet
 * @return true: Check if the droplet is moving
 */
bool Drop::is_moving(void) {
	return _moving;
}