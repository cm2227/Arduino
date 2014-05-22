#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4

  unsigned long num = 12345678;
  int dpSelect = 0x08;//0x8F;
  char digSelect = 0xFF;//0x7F;

unsigned char segDigits[] = 
{ 
  0xFC,  // = 0
  0x60,  // = 1
  0xDA,  // = 2
  0xF2,  // = 3
  0x66,  // = 4
  0xB6,  // = 5
  0xBE,  // = 6
  0xE0,  // = 7
  0xFE,  // = 8
  0xE6   // = 9
};

void setup() 
{                
  Serial.begin(9600);

  pinMode(13, OUTPUT);     

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

void loop() 
{



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

    digitalWrite(SEG_LOAD, LOW);
    shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, seg + 1);
    shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, output);
    digitalWrite(SEG_LOAD, HIGH);
  }

}











