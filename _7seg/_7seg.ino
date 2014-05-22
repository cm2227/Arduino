

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
 initseg(2,3,4);

}

void loop() 
{

sevenseg(23456789, true, 2,3,4);








}










