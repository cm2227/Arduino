#include <LiquidCrystal.h>
char line1[21];
char line2[21];
boolean enterloop = true;
String buffer;
boolean wait=true;
int opcode;
int arg[255];
String opname[255];


LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
char key[51]; //= {'1','4','7','*','2','5','8','0','3','6','9','#'};

int ledPins[] = {
  31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53 }; 
String ergebnis;
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin 

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
boolean bounce = true;
boolean finish = false;
void setup() {
  ergebnis = "Starting up...";
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  // initialize the serial communications:
  ergebnis.toCharArray(line1,21);
  lcd.clear();
  lcd.print(line1);
  lcd.cursor();
  Serial.begin(9600);
  Serial.println("Starting up...");


  // put your setup code here, to run once:
  for (int thisPin = 28; thisPin < 52; thisPin=thisPin +2)  {
    pinMode(thisPin, OUTPUT); 
    ergebnis="Pin "; 
    ergebnis = ergebnis + thisPin + " initialisiert.";
    Serial.println(ergebnis);
    ergebnis ="";

  }
  lcd.setCursor(0,1);
  buffer = "Press # to cont.";
  buffer.toCharArray(line1,21);
  lcd.print(line1);
  while(wait)
  {
    if (digitalRead(44)==HIGH){
      wait=false;
    }
  }
  delay(300);

  lcd.clear();
  buffer="Enter opcode:";
  buffer.toCharArray(line1,21);
  lcd.print(line1);
  lcd.setCursor(0,1);

  key[28]= '.';
  key[30]= '7';
  key[32]= '4';
  key[34]= '1';
  key[36]= '0';
  key[38]= '8';
  key[40]= '5';
  key[42]= '2';
  key[44]= '#';
  key[46]= '9';
  key[48]= '6';
  key[50]= '3';
  
//List of opcodes
  
//11 Ascent guidance to orbit at X1 km with 0° inclination with manual staging
arg[11] = 1;
opname[11] = "asc guid 0° MS";

//12 Ascent guidance to orbit at X1 km with X2° inclination with manual staging
arg[12] = 2;
opname[12] = "asc guid X° MS";

//13 Ascent guidance to orbit at X1 km with X2° inclination with automatic staging to stage X3
arg[11] = 3;
opname[13] = "asc guid X° ASX";

//21 Change apoapsis to X1 at next periapsis
arg[21] = 1;
opname[21] = "apo change to";

//22 Change periapsis to X1 at next apoapsis
arg[22] = 1;
opname[22] = "peri change to";

//23 Circularize at current altitude in X1 seconds
arg[23] = 1;
opname[23] = "circ in X";

//31 New maneuver node?

//32 PTC X1 degrees per minute
arg[32] = 1;
opname[32] = "PTC X deg/min";


//81 Land at KSC
arg[81] = 0;
opname[81] = "land at KSC";
  
}

void loop() {


  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    for (int thisPin = 28; thisPin < 51; thisPin=thisPin+2)  {
      if (digitalRead(thisPin)==HIGH)
      {
        ergebnis+=key[thisPin];
        lcd.print(key[thisPin]);
        //ergebnis.toCharArray(line2,20);
        lastDebounceTime = millis();
        bounce = false;
        delay(300);
        if (ergebnis.endsWith("#"))
        {
          finish = true;
        }
      }

    }

  }
  if (finish)
  {
    lcd.clear();

    opcode = ergebnis.toInt();
    lcd.print(opname[opcode]);
  buffer=arg[opcode] + "arguments";
  buffer.toCharArray(line1,21);
  lcd.setCursor(0,1);
    lcd.print(buffer);
    for (int i=0; i<=arg[opcode]; i++)
    {
      lcd.setCursor(0,0);
      for (int thisPin = 28; thisPin < 51; thisPin=thisPin+2)  {
      if (digitalRead(thisPin)==HIGH)
      {
        ergebnis+=key[thisPin];
        lcd.print(key[thisPin]);
        //ergebnis.toCharArray(line2,20);
        lastDebounceTime = millis();
        bounce = false;
        delay(300);
        if (ergebnis.endsWith("#"))
        {
          finish = true;
        }
      }

    }
    }
    /*
    buffer="Com " + ergebnis;
    Serial.println(buffer);
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    buffer="transmitted";
    lcd.setCursor(0,1);
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    delay(2000);
    */
    lcd.clear();
    finish = false; 
    ergebnis="";
    buffer="Please enter #:";
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    lcd.setCursor(0,1);
  }

}




