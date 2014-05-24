#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4

unsigned long num = 12345678;

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
  initseg(2,3,4);
}

void loop() 
{


writeseg(2,3,4,true,23456789);


}
void initseg(int DIN, int LOAD , int CLK)
{
  pinMode(DIN, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLK, OUTPUT);

  digitalWrite(LOAD, LOW);
  shiftOut(DIN, CLK, MSBFIRST, 0x0C);
  shiftOut(DIN, CLK, MSBFIRST, 0x01);
  digitalWrite(LOAD, HIGH);

  digitalWrite(LOAD, LOW);
  shiftOut(DIN, CLK, MSBFIRST, 0x09);
  shiftOut(DIN, CLK, MSBFIRST, 0x00);
  digitalWrite(LOAD, HIGH);

  digitalWrite(LOAD, LOW);
  shiftOut(DIN, CLK, MSBFIRST, 0x0B);
  shiftOut(DIN, CLK, MSBFIRST, 0x07);
  digitalWrite(LOAD, HIGH);

  digitalWrite(LOAD, LOW);
  shiftOut(DIN, CLK, MSBFIRST, 0x0A);
  shiftOut(DIN, CLK, MSBFIRST, 0x0F);
  digitalWrite(LOAD, HIGH);
}

void writeseg(int DIN, int LOAD , int CLK, boolean dp, unsigned long num)
{
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


