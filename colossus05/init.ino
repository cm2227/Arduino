void InitButtons()
{
  for (int thisPin = 31; thisPin < 54; thisPin=thisPin +2)  {
    pinMode(thisPin, INPUT); 
  }
    //assign keypad pins to characters
  key[31]= '3';
  key[33]= '6';
  key[35]= '9';
  key[37]= '#';
  key[39]= '2';
  key[41]= '5';
  key[43]= '8';
  key[45]= '0';
  key[47]= '1';
  key[49]= '4';
  key[51]= '7';
  key[53]= '.';
  
  //init interrupt button
  
  //init attitude node button
  
}


void InitTxPackets() {
  HPacket.id = 0;  
  CPacket.id = 1;
}

