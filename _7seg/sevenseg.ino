

void initseg(byte SEG_DIN, byte SEG_LOAD, byte SEG_CLK)
{
  pinMode(SEG_DIN, OUTPUT);
  pinMode(SEG_LOAD, OUTPUT);
  pinMode(SEG_CLK, OUTPUT);

  digitalWrite(SEG_LOAD, LOW);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0C);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x01);
  digitalWrite(SEG_LOAD, HIGH);

  digitalWrite(SEG_LOAD, LOW);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x09);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x00);
  digitalWrite(SEG_LOAD, HIGH);

  digitalWrite(SEG_LOAD, LOW);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0B);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x07);
  digitalWrite(SEG_LOAD, HIGH);

  digitalWrite(SEG_LOAD, LOW);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0A);
  shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0F);
  digitalWrite(SEG_LOAD, HIGH);
}

void sevenseg(int num, boolean dp,byte SEG_DIN, byte SEG_LOAD, byte SEG_CLK)
{
  if(dp){
    int dpSelect = 0x8F;
  }
  else{
    int dpSelect = 0x08;
  }
  char digSelect = 0xFF;//0x7F;
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

    digitalWrite(SEG_LOAD, LOW);
    shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, seg + 1);
    shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, output);
    digitalWrite(SEG_LOAD, HIGH);
  }
}

