/* @file HelloKeypad.ino
|| @version 1.1
|| @modified by Diego (http://hotboards.org)
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| | Just press any key an it will be displayed on the serial port
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
byte rowPins[ ROWS ] = { 5, 4, 3, 2 }; //connect to the row pinouts of the keypad
byte colPins[ COLS ] = { 9, 8, 7, 6 }; //connect to the column pinouts of the keypad

/* create a new keypad object */
Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

void setup( void )
{
    Serial.begin( 9600 );
    Serial.println( "Press any key: " );
}

void loop( void )
{
    /* poll the keypad to look for any activation */
    char key = keypad.getKey( );

    /* if any key was pressed */
    if( key )
    {
        /* display the key pressed on serial port */
        Serial.println( key );
    }
}
