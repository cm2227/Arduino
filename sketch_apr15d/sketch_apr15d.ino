

String cString ="";
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:

  cString.reserve(200);
  Serial.println("System ready.");

}

void loop() {
  // print the string when a newline arrives:

  if (stringComplete) {
    Serial.println(cString);

    if (cString.startsWith("dump")) {
      Serial.println(cString);
    }
  } 
  cString = "";
  stringComplete = false;
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

    if (inChar == 'x') {
      stringComplete = true;
    }
  }


}


