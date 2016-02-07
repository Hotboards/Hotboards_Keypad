/* @file loopCounter.ino
|| @version 1.1
|| @modified by Diego (http://hotboards.org)
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the effect of debounce time, just change the
|| | debounce time using the fucntion setDebounceTime
|| #
*/
#include <Hotboards_Keypad.h>


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
/* define the keymap that will reŕesent our keypad */
char keys[ ROWS ][ COLS ] =
{
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};
byte rowPins[ ROWS ] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[ COLS ] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

/* create a new keypad object */
Keypad kpd = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

unsigned long loopCount = 0;
unsigned long timer_t = 0;

void setup( void )
{
	Serial.begin( 9600 );
	Serial.println( "Press any key: " );

	// Try playing with different debounceTime settings to see how it affects
	// the number of times per second your loop will run. The library prevents
	// setting it to anything below 1 millisecond.
	kpd.setDebounceTime( 100 );	// setDebounceTime(mS)
}

void loop( void )
{
	/* poll the keypad to look for any activation */
	char key = kpd.getKey( );

	// Report the number of times through the loop in 1 second. This will give
	// you a relative idea of just how much the debounceTime has changed the
	// speed of your code. If you set a high debounceTime your loopCount will
	// look good but your keypresses will start to feel sluggish.
	if ( ( millis( ) - timer_t ) > 1000 )
	{
		Serial.print( "Your loop code ran " );
		Serial.print( loopCount );
		Serial.println( " times over the last second" );
		loopCount = 0;
		timer_t = millis( );
	}
	loopCount++;

	/* if any key was pressed */
    if( key )
    {
        /* display the key pressed on serial port */
        Serial.println( key );
	}
}
