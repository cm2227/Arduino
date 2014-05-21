

#define SEG_NUM 4
#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4


/*
int seg_segments[8] = { 
  30, 31, 32, 33, 34, 35, 36, 37 
};

int seg_mux[4] = { 
  22, 24, 26, 28 
};*/


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


}

void loop() 
{

sevenseg(23456789, true, 2,3,4);








}










