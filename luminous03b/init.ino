void initLEDS() {
  
  pinMode(malarmpin,OUTPUT);
  digitalWrite(malarmpin,HIGH);
  
    pinMode(warn1pin,OUTPUT);
  digitalWrite(warn1pin,HIGH);

  pinMode(warn2pin,OUTPUT);
  digitalWrite(warn2pin,HIGH);

  pinMode(warn3pin,OUTPUT);
  digitalWrite(warn3pin,HIGH);
  
  pinMode(warn4pin,OUTPUT);
  digitalWrite(warn4pin,HIGH);

    pinMode(greenpin,OUTPUT);
  digitalWrite(greenpin,HIGH);
  
    pinMode(buzzpin,OUTPUT);
  digitalWrite(buzzpin,HIGH);

pinMode (voltpin, OUTPUT);
analogWrite(voltpin, 127);
  //LEDs vervollständigen
  // drehknopf warp factor
  // on off on für flight mode
  
  pinMode(takeoffpin, INPUT_PULLUP);
  pinMode(landingpin, INPUT_PULLUP);

  // switch dV warning
  pinMode(dVpin, INPUT_PULLUP);
  
  // button master alarm off
  pinMode(maquitpin, INPUT_PULLUP);  
  
    // button master alarm off
  pinMode(matestpin, INPUT_PULLUP); 
  
  // button to trigger random values
  pinMode(randompin, INPUT_PULLUP);
}

void LEDSAllOff() {
  digitalWrite(malarmpin,LOW);
  digitalWrite(warn1pin,LOW);
  digitalWrite(warn2pin,LOW);
  digitalWrite(warn3pin,LOW);
  digitalWrite(warn4pin,LOW);
  digitalWrite(greenpin,LOW);
  digitalWrite(buzzpin,LOW);
  analogWrite(voltpin, 0);
}


void InitTxPackets() {
  HPacket.id = 0;  
  CPacket.id = 1;
}
