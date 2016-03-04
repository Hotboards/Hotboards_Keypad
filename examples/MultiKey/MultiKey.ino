/* @file MultiKey.ino
|| @version 1.1
|| @modified by Diego (http://hotboards.org)
|| @version 1.0
|| @author Mark Stanley
|| @contact mstanley@technologist.com
||
|| @description
|| | The latest version, 3.0, of the keypad library supports up to 10
|| | active keys all being pressed at the same time. This sketch is an
|| | example of how you can get multiple key presses from a keypad or
|| | keyboard.
|| | arduino    keypad
|| | 6 ---------> C4
|| | 7 ---------> C3
|| | 8 ---------> C2
|| | 9 ---------> C1
|| | 2 ---------> R4
|| | 3 ---------> R3
|| | 4 ---------> R2
|| | 5 ---------> R1
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
Keypad kpd = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

String msg;


void setup( void )
{
    Serial.begin( 9600 );
    Serial.println( "Press one or more than one key (up to 10)" );
    msg = "";
}


void loop( void )
{
    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if( kpd.getKeys( ) )
    {
        for( int i=0 ; i<LIST_MAX ; i++ )   // Scan the whole key list.
        {
            if( kpd.key[ i ].stateChanged )   // Only find keys that have changed state.
            {
                switch ( kpd.key[ i ].kstate ) // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                {
                    case PRESSED:
                        msg = " PRESSED.";
                        break;
                    case HOLD:
                        msg = " HOLD.";
                        break;
                    case RELEASED:
                        msg = " RELEASED.";
                        break;
                    case IDLE:
                        msg = " IDLE.";
                        break;
                    default:
                        break;
                }
                // print the current state of the key pressed
                Serial.print( "Key " );
                Serial.print( kpd.key[ i ].kchar );
                Serial.println( msg );
            }
        }
    }
}  // End loop
