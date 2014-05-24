#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4

unsigned long num = 12345678;
unsigned long now = 0;
unsigned long last = 1;



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

char alphabeth[] = 
{
  '0','1','2','3','4','5','6','7','8','9','-','L','h','o','b','H','d','U','F','C','E','D','P','A'}; 


unsigned char byteChar[] = 
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
  0xE6,  // = 9
  0x02,  // = -
  0x1C,  // = L
  0x2E,  // = h 
  0x3A,  // = o
  0x3E,  // = b
  0x6E,  // = H
  0x7A,  // = d
  0x7C,  // = U
  0x8E,  // = F
  0x9C,  // = C
  0x9E,  // = E
  0xC6,  // = ° (has to be referenced as D)
  0xCE,  // = P
  0xEE   // = A
};

void setup() 
{                
  initseg(2,3,4);
}

void loop() 
{
  boolean dp=false;
  if((millis() % 1000) > 500){
    dp=true;
  } 
  now=millis();

  float freq = now-last;


charseg(2,3,4,dp,"1234AbCd");
//writeseg(2,3,4,dp,12345678);
  //writeseg(2,3,4,dp,freq);

  last=millis();


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

char getbyte(char c)
{
  for (int i=0; i<24; i++)
  {
    if (c == alphabeth[i]){
      return byteChar[i];
    }
    return 0x7E;
  }
}

void charseg(int DIN, int LOAD , int CLK, boolean dp, char text[])
{
  char digSelect = 0xFF;//0x7F;
  int dpSelect = 0x08;//0x8F;
  if(dp){
    dpSelect = 0x08F;
  }

int index=0;

  for (int seg = 0; seg < 8; seg++) 
  {
    int output = 0;
    //unsigned long numCopy = num;
    char segMask = 1 << (7 - seg);

    for (int dig = 0; dig < 8; dig++)
    {
      //char curNum = getbyte(text[index]);
      Serial.println(index);
      Serial.println(text[index]);
      Serial.println(getbyte(text[index]));

      if ((getbyte(text[index]) & segMask) && (digSelect & (1 << dig)))
      {
        output |= 1 << dig;
      }

      if ((seg == 7) && (dpSelect & (1 << dig)))
      {
        output |= 1 << dig;//(7 - dig);
      }
      index++;
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




