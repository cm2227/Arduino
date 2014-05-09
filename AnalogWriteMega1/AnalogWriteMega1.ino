/*
  Mega analogWrite() test
 	
  This sketch fades LEDs up and down one at a time on digital pins 2 through 13.  
  This sketch was written for the Arduino Mega, and will not work on previous boards.
 	
  The circuit:
  * LEDs attached from pins 2 through 13 to ground.

  created 8 Feb 2009
  by Tom Igoe
  
  This example code is in the public domain.
  
 */
// These constants won't change.  They're used to give names
// to the pins used:
const int lowestPin = 2;
const int highestPin = 13;


void setup() {
  // set pin 2 through as outputs:

    pinMode(2, OUTPUT); 
  
}

void loop() {
  // iterate over the pins:
  
    for (int brightness = 0; brightness < 255; brightness++) {
      analogWrite(2, brightness);
      delay(2);
    } 
    // fade the LED on thisPin from brithstest to off:
    for (int brightness = 255; brightness >= 0; brightness--) {
      analogWrite(2, brightness);
      delay(2);
    } 
    // pause between LEDs:
    delay(100);
  
}
