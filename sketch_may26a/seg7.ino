void charseg(int DIN, int LOAD , int CLK, boolean dp, String textstring)
{
  char digSelect = 0xFF;//0x7F;
  int dpSelect = 0x08;//0x8F;
  if(dp){
    dpSelect = 0x08F;
  }
 char text[9];
 textstring.toCharArray(text,9);
 Serial.print("Der string: ");
 Serial.println(text);
 Serial.println(textstring);



  for (int seg = 0; seg < 8; seg++) 
  {
    int output = 0;
    //int index=0;
    //unsigned long numCopy = num;
    char segMask = 1 << (7 - seg);

    for (int dig = 0; dig < 8; dig++)
    {
      //char curNum = getbyte(text[index]);
      Serial.print("Aktuelles Element: ");
      Serial.println(7-dig);  //element 7-dig des strings entspricht der jeweils aktuellen Ziffer
      Serial.print("Das aktuelle Zeichen: ");
      Serial.println(text[7-dig]); //text[index] ist das aktuell auszugebende Zeichen, entspricht curNum
      Serial.print("Zugehöriges Bitmuster: ");
      Serial.println(getByte2(text[7-dig]),16); //getbyte soll analog zu getDigit das Bitmuster für ein Zeichen aus dem Alphabeth heraussuchen

      if ((getByte2(text[7-dig]) & segMask) && (digSelect & (1 << dig)))
      {
        output |= 1 << dig;
      }

      if ((seg == 7) && (dpSelect & (1 << dig)))
      {
        output |= 1 << dig;//(7 - dig);
      }
      //index++;
      //numCopy /= 10;
    }

    //output = 0x08;

    digitalWrite(LOAD, LOW);
    shiftOut(DIN, CLK, MSBFIRST, seg + 1);
    shiftOut(DIN, CLK, MSBFIRST, output);
    digitalWrite(LOAD, HIGH);
  }
}

void writeseg(int DIN, int LOAD , int CLK, boolean dp, unsigned long num)
{
  char digSelect = 0xFF;//0x7F;
  int dpSelect = 0x08;//0x8F;
  if(dp){
    dpSelect = 0x08F;
  }
  for (int seg = 0; seg < 8; seg++) 
  {
    int output = 0;
    unsigned long numCopy = num;
    char segMask = 1 << (7 - seg);

    for (int dig = 0; dig < 8; dig++)
    {
      char curNum = numCopy % 10;

      if ((segDigits[curNum] & segMask) && (digSelect & (1 << dig)))
      {
        output |= 1 << dig;
      }

      if ((seg == 7) && (dpSelect & (1 << dig)))
      {
        output |= 1 << dig;//(7 - dig);
      }

      numCopy /= 10;
    }

    //output = 0x08;

    digitalWrite(LOAD, LOW);
    shiftOut(DIN, CLK, MSBFIRST, seg + 1);
    shiftOut(DIN, CLK, MSBFIRST, output);
    digitalWrite(LOAD, HIGH);
  }
}
