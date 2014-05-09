void Indicators() {
  caution = 0;
  warning = 0;

  caution += VData.G > GCAUTION;
  warning += VData.G > GWARN;
  caution += VData.LiquidFuelS/VData.LiquidFuelTotS*100 < FUELCAUTION;
  warning += VData.LiquidFuelS/VData.LiquidFuelTotS*100 < FUELWARN;

  if (caution != 0)
    digitalWrite(YLED,HIGH);
  else
    digitalWrite(YLED,LOW);

  if (warning != 0)
    digitalWrite(RLED,HIGH);
  else
    digitalWrite(RLED,LOW);
}

void initLEDS() {
  pinMode(GLED,OUTPUT);
  digitalWrite(GLED,HIGH);

  pinMode(YLED,OUTPUT);
  digitalWrite(YLED,HIGH);

  pinMode(RLED,OUTPUT);
  digitalWrite(RLED,HIGH);
}

void LEDSAllOff() {
  digitalWrite(GLED,LOW);
  digitalWrite(YLED,LOW);
  digitalWrite(RLED,LOW);
}


void InitTxPackets() {
  HPacket.id = 0;  
  CPacket.id = 1;
}








