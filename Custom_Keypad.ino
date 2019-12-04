/* 
 * Library required to run the keyboard/keypad which this is based on
 * https://www.arduinolibraries.info/libraries/keypad
 */
#include <Keyboard.h>
#include <Key.h>
#include <Keypad.h>

// 21 button MATRIX keymap. Some are unused. Gonna keep adding onto 


const byte COLS = 7; // Seven columns
const byte ROWS = 3; // Three rows
char hexakeys[ROWS][COLS] = {
  {'0', '1', '2', '3', '4', '5', '6'},
  {'7', '8', '9', 'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H', 'I', 'J', 'K'},
};

// Connect keypad rows and columns to the arduino micro pins.


byte colPins[COLS] = { 0, 1, 2, 3, 4, 5, 6 };
byte rowPins[ROWS] = { 7, 8, 9 };
String msg;

// Create the Keypad

Keypad customKeypad = Keypad( makeKeymap(hexakeys), rowPins, colPins, ROWS, COLS );


// MAIN PROGRAM

void setup()
{
  Serial.begin(9600);
  msg = "";
  pinMode(13, OUTPUT); // set the digital pin 13 as output to control a USB to turn on and off for the small USB powered fan
}

void loop()
{

  //keypad button press detection

  if (customKeypad.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole keypad.
    {
      if ( customKeypad.key[i].stateChanged )   // Only find keys that have changed state.
      {

        //keypad button press instructions

        if ( customKeypad.key[i].kchar == '0' ) // FUNCTION 13 (UNUSED AT THIS TIME)
          switch (customKeypad.key[i].kstate) {
            case PRESSED:
              msg = " PRESSED.";
              Keyboard.write(KEY_F13);
              break;
            case HOLD:
              msg = " HOLD.";
              break;
            case RELEASED:
              msg = " RELEASED.";
              Keyboard.release(KEY_F13);
              break;
            case IDLE:
              msg = " IDLE.";
              break;
         }

        if ( customKeypad.key[i].kchar == '1' ) // LANDING GEAR
          switch (customKeypad.key[i].kstate) {
            case PRESSED:
              msg = " PRESSED.";
              Keyboard.write('L');
              break;
            case HOLD:
              msg = " HOLD.";
              break;
            case RELEASED:
              msg = " RELEASED.";
              Keyboard.release('L');
              break;
            case IDLE:
              msg = " IDLE.";
              break;
         }

        if ( customKeypad.key[i].kchar == '2' ) // FUNCTION 14 (UNUSED AT THIS TIME)BUT THE FOLLOWING CODE WORKS FOR A TOGGLE SWITCH 
          switch (customKeypad.key[i].kstate) {
            case PRESSED:
              msg = " PRESSED.";
              Keyboard.write(KEY_F14);
              break;
            case HOLD:
              msg = " HOLD.";
              break;
            case RELEASED:
              msg = " RELEASED.";
              Keyboard.write(KEY_F14);
              break;
            case IDLE:
              msg = " IDLE.";
              break;
         }

        if ( customKeypad.key[i].kchar == '3' ) // FAN CONTROL
          switch (customKeypad.key[i].kstate) {
            case PRESSED:
              msg = " PRESSED.";
              digitalWrite(13, HIGH); // when the Keypad button 3 is pressed turn pin 13 to one
              Keyboard.write(KEY_F15); // when the Keypad button 3 is pressed also press F15
              break;
            case HOLD:
              msg = " HOLD.";
              break;
            case RELEASED:
              msg = " RELEASED.";
              digitalWrite(13, LOW); // when the Keypad button 3 is pressed or unpressed (not sure about the coding/wiring on this one yet) then turn the fan off. This could be a nice toggle switch that opperated the fan just need to make sure fan is always "on" on the back of it.
              Keyboard.write(KEY_F15);
              break;
            case IDLE:
              msg = " IDLE.";
              break;
         }
        Serial.println();
        Serial.print("Key ");
        Serial.print(customKeypad.key[i].kchar);
        Serial.println(msg);
      }
    }
  }
}
