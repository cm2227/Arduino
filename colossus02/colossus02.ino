#include <LiquidCrystal.h>
char line1[21];
char line2[21];
boolean enterloop = true;
String buffer;
boolean wait=true;
int opcode;
int arg[255];


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char key[51]; //= {'1','4','7','*','2','5','8','0','3','6','9','#'};

int ledPins[] = {
  28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50 }; 
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
  buffer="Please enter #:";
  buffer.toCharArray(line1,21);
  lcd.print(line1);

  key[28]= '*';
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
    buffer="Com " + ergebnis;
    Serial.println(buffer);
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    buffer="transmitted";
    lcd.setCursor(0,1);
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    delay(2000);

    lcd.clear();
    finish = false; 
    ergebnis="";
    buffer="Please enter #:";
    buffer.toCharArray(line1,21);
    lcd.print(line1);
    lcd.setCursor(0,1);
  }

}




