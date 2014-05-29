#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4
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

byte alphabeth[128];
int c=0;
String buffer;
String text="        Hallo Bientie du En9el        ";
void setup() 
{                
  initseg(2,3,4);
  initAlphabeth();

}


void loop() 
{
  boolean dp=false;
  /*
  if((millis() % 1000) > 500){
    dp=true;
  }
 */ 
buffer=text.substring(c,c+8);

charseg(2,3,4,dp,buffer);
delay(500);
c++;
if(c>text.length()){
c=0;
}

//writeseg(2,3,4,dp,12345678);
//delay(2000);

}










