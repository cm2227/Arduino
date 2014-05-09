

String dataString = "";         // a string to hold incoming data
String cString ="";
boolean stringComplete = false;  // whether the string is complete
boolean numberfound = false;
float apo=0;
float peri=0;
float bat=0;
float value=0;
const int analogOutPin = 9; // Analog output pin that the LED is attached to

void dump(){
  Serial.print("Apoapsis= "); 
  Serial.println(apo); 
  Serial.print("Periapsis= "); 
  Serial.println(peri); 
  Serial.print("Batt level= "); 
  Serial.println(bat); 
} 

void stringreset(){
  // clear the string:
  dataString = "";
  cString = "";
  stringComplete = false;
  numberfound=false;
  Serial.end();
  Serial.begin(9600);
}

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  dataString.reserve(200);
  cString.reserve(200);
  Serial.println("System ready.");
  
}

void loop() {
  // print the string when a newline arrives:
analogWrite(analogOutPin, bat);
  if (stringComplete) {
    Serial.println(cString);

    if (cString.startsWith("dump")) {
      dump();
    }

    if (numberfound){
      Serial.print("I found data: ");
      value=dataString.toInt();
      Serial.println(value);
      if (cString.startsWith("apo")) {
        Serial.println("New Apoapsis"); 
        apo=value;
      }
      if (cString.startsWith("peri")) {
        Serial.println("New Periapsis"); 
        peri=value;
      }
      if (cString.startsWith("bat") && (value <= 100)) {
        
        Serial.println("New Batt level"); 
        bat=(value/100)*255;
      }
    } 


    stringreset();
  }



}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {

  while (Serial.available()) {
    int inChar = Serial.read();
    cString += (char)inChar;
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      dataString += (char)inChar; 
      numberfound = true;
    }
    if (inChar == '\n') {
      stringComplete = true;
    }
  }


}

