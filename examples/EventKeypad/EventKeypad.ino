/* @file EventSerialKeypad.pde
 || @version 1.1
 || @modified by Diego (http://hotboards.org)
 || @author Alexander Brevig
 || @contact alexanderbrevig@gmail.com
 ||
 || @description
 || | Demonstrates using the KeypadEvent.
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
Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );
byte ledPin = 13;
boolean blink = false;
boolean ledPin_state;

void setup( void )
{
    Serial.begin( 9600 );
    pinMode( ledPin, OUTPUT );              // Sets the digital pin as output.
    digitalWrite( ledPin, HIGH );           // Turn the LED on.
    ledPin_state = digitalRead( ledPin );   // Store initial LED state. HIGH when LED is on.
    keypad.addEventListener( keypadEvent ); // Add an event listener for this keypad
}

void loop( void )
{
    char key = keypad.getKey( );

    if( key )
    {
        Serial.println( key );
    }

    if( blink )
    {
        digitalWrite( ledPin, !digitalRead( ledPin ) );    // Change the ledPin from Hi2Lo or Lo2Hi.
        delay( 100 );
    }
}

// Taking care of some special events.
void keypadEvent( KeypadEvent key )
{
    switch ( keypad.getState( ) )
    {
        case PRESSED:
            if( key == '#' )
            {
                digitalWrite( ledPin, !digitalRead( ledPin ) );
                ledPin_state = digitalRead( ledPin );        // Remember LED state, lit or unlit.
            }
            break;

        case RELEASED:
            if( key == '*' )
            {
                digitalWrite( ledPin, ledPin_state );    // Restore LED state from before it started blinking.
                blink = false;
            }
            break;

        case HOLD:
            if( key == '*' )
            {
                blink = true;    // Blink the LED when holding the * key.
            }
            break;
    }
}
