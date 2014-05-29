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

byte alphabeth2[128];

byte byteChar[] = 
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
  initAlphabeth();
  Serial.begin(9600);
for (int i=0;i<128;i++){
  Serial.print(i);
  Serial.print(" = ");
  Serial.println(alphabeth2[i],16);
}
}

void loop() 
{
  boolean dp=false;
  if((millis() % 1000) > 500){
    dp=true;
  } 


//char testtext[]="1234AbCd";
charseg(2,3,4,dp,"1CH-AFFE");
//writeseg(2,3,4,dp,12345678);
  //writeseg(2,3,4,dp,freq);

//while(true);

}










