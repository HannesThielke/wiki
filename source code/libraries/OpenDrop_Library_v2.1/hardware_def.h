/**
 * Dimensions of the OpenDrop Electrodes (Fluxls)
 */
#define FluxlPad_width 16 /** Width of the Electrode Matrix */
#define FluxlPad_heigth 8 /** Height of the Electrode Matrix */

/**
 * Variables for SPI bus that is used for communication with the OLED display
 */
#define OLED_MOSI  2 	/** data output pin from SPI master */
#define OLED_CLK   3 	/** clock pin of the SPI bus */
#define OLED_DC    11 	/** OLED display clock (DCKL) pin */
#define OLED_CS    12	/** OLED display chip select (CS) pin */
#define OLED_RESET 13	/** OLED display reset signal input (RES) pin */

/**
*  The HV507 is a low-voltage to high-voltage serial-to-parallel 
*  converter with 64 push-pull outputs.
*  It controlls the electrodes on the OpenDrop device
*/
#define BL_pin         9	/** Blanking (BL) Pin of the HV507 chip */
#define LE_pin         4 	/** Latch enable (LE) Pin */
#define CLK_pin        15 	/** Data Shift Register Clock (CLK). Inputs are shifted into the Shift register on the positive edge of the clock. */
#define DI_pin         16  	/** Digital Out Pin */
#define POL_pin        A1	/** Polarity (POL) Pin */
#define OD_pin		   A1	/** optical density (OD) measurement Pin */

/**
 * Define the pins where the buttons are connected to
 */
#define SW1_pin         8           /** Left button */
#define SW2_pin         A5          /** Right button */
#define SW3_pin         7           /** Joy button */
#define JOY_pin         A4          /** JOY_pin analog */
#define FEEDBACK_pin    A2          /** FEEDBACK pin */

/**
 * Define the pins where the ESP (WIFI chip) can be connected to
 */
#define ESP_RESET_pin   A3          /** Reset pin */
#define ESP_GPIO0_pin   10          /** GPIO pin */
#define ESP_RX_pin      1           /** RX pin */
#define ESP_TX_pin      0           /** RX pin */

/*
 * LEDs and Speaker
 */
#define LED_LIGHT_pin	5           /** Digital Pin for LEDs */
#define SPK_pin			6           /** Digital Pin for speaker */

#define sound_flag false           	/** Activate the sounds */
#define light_flag false            /** Turn the lights on */
#define feedback_flag false	 		/** Turn on the feedback ability */

/** \var
 * Fluxel IDs stored in the Program Space as a Look-up-table
 */
const byte FluxelID [16][8] PROGMEM ={
{3,2,1,0,63,62,61,60},
{6,7,5,4,59,58,56,57},
{10,9,11,8,55,52,54,53},
{13,14,15,12,51,48,49,50},
{17,18,19,16,47,44,45,46},
{20,21,22,23,40,41,42,43},
{24,28,27,31,32,37,35,39},
{29,25,26,30,33,36,38,34},
{98,102,100,97,94,90,89,93},
{103,99,101,96,95,91,92,88},
{107,106,105,104,87,86,85,84},
{110,109,108,111,80,83,82,81},
{114,113,112,115,76,79,78,77},
{117,118,116,119,72,75,73,74},
{121,120,122,123,68,69,71,70},
{124,125,126,127,64,65,66,67}};

/** \var
 * Look-up-tables for the Fluxl matrix are stored in the program space of the Arduino
 * An explanation on how to deal with data in the program space can be found in:
 * https://www.nongnu.org/avr-libc/user-manual/pgmspace.html
 */
 const byte pad_lookup_x [64] PROGMEM = {
0,0,0,0,1,1,1,1,
2,2,2,2,3,3,3,3,
4,4,4,4,5,5,5,5,
6,7,7,6,6,7,7,6,
6,7,7,6,7,6,7,6,
5,5,5,5,4,4,4,4,
3,3,3,3,2,2,2,2,
1,1,1,1,0,0,0,0
};

/** \var
 * Look-up-tables for the Fluxl matrix are stored in the program space of the Arduino
 * An explanation on how to deal with data in the program space can be found in:
 * https://www.nongnu.org/avr-libc/user-manual/pgmspace.html
 */
const byte pad_lookup_y [64] PROGMEM = {
3,2,1,0,3,2,0,1,
3,1,0,2,3,0,1,2,
3,0,1,2,0,1,2,3,
0,1,2,2,1,0,3,3,
4,4,7,6,5,5,6,7,
4,5,6,7,5,6,7,4,
5,6,7,4,5,7,6,4,
6,7,5,4,7,6,5,4
};
