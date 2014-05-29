#include "Seg7CA.h"
#include "Arduino.h"

// Seg7CA can be initialized in several ways
// Seg7CA(DIN, CLK, LOAD) sets three pins as output and initializes with standard register bytes
// Seg7CA(DIN) sets three pins as output, assuming CLK and LOAD are the next higher numbered pins from DIN and initializes
// the standard register bytes
// These bytes are 0x0C, 0x01, 0x09, 0x00 0x0B, 0x07, 0x0A, 0x0F.
// Insert explanation for register bytes here
// Seg7CA(byte DIN, byte CLK, byte LOAD, byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7)
// allows you to use different register bytes


/********** Constructors with various options */

Seg7CA::Seg7CA(byte DIN, byte CLK, byte LOAD)
{
  pinMode(DIN, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLK, OUTPUT);

  _DIN=DIN;
  _LOAD=LOAD;
  _CLK=CLK;
    init();
}


Seg7CA::Seg7CA(byte DIN)
{
  pinMode(DIN, OUTPUT);
  pinMode(DIN+1, OUTPUT);
  pinMode(DIN+2, OUTPUT);
  _DIN=DIN;
  _LOAD=DIN+1;
  _CLK=DIN+2;
  init();

}

Seg7CA::Seg7CA(byte DIN, byte CLK, byte LOAD, byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7)
{
  pinMode(DIN, OUTPUT);
  pinMode(LOAD, OUTPUT);
  pinMode(CLK, OUTPUT);
  _DIN=DIN;
  _LOAD=LOAD;
  _CLK=CLK;
  init(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7)

}
/********** init with default bytes */
void Seg7CA::init();
{
  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x0C);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x01);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x09);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x00);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x0B);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x07);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x0A);
  shiftOut(_DIN, _CLK, MSBFIRST, 0x0F);
  digitalWrite(_LOAD, HIGH);
  
  _digSelect = 0xFF;//0x7F;
  _dpSelect = 0x08;//0x8F;
  initAlphabeth();
}
/********** init with custom bytes*/
void Seg7CA::init(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7)
{
  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, b0);
  shiftOut(_DIN, _CLK, MSBFIRST, b1);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, b2);
  shiftOut(_DIN, _CLK, MSBFIRST, b3);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, b4);
  shiftOut(_DIN, _CLK, MSBFIRST, b5);
  digitalWrite(_LOAD, HIGH);

  digitalWrite(_LOAD, LOW);
  shiftOut(_DIN, _CLK, MSBFIRST, b6);
  shiftOut(_DIN, _CLK, MSBFIRST, b7);
  digitalWrite(_LOAD, HIGH);
  
  _digSelect = 0xFF;//0x7F;
  _dpSelect = 0x08;//0x8F;
  initAlphabeth();
}

/********** high level commands, for the user! */
void write(String text)
{
	charseg(false, text);
}
void write(int number)
{
	writeseg(false, (unsigned long) number);
}
void write(unsigned long number)
{
	writeseg(false, number);
}
void write(long)
{
	writeseg(false, (unsigned long) number);
}
void write(float number)
{

}
void write(double number)
{
	String output="";
	if (number<0)
	{
		//number is negative
		String+="-"; //add minus, only seven digits left
		if (number<-9999999) //number is too large to display, switch to exponent notation. KSP is not likely to return negative numbers parameters larger than
		{
			number=number/1000;
			number=number*(-1);
			string+=number;
			string+="E03";
		}
		else //number can be displayed on seven digits
		{
			string+=number*(-1);
		}
		
	}
	else
	{
		//number is positive or zero
	}
}
void write(byte)
{
}
void write(double, double)
{
}
void write(int, int)
{
}
void write(long, long)
{
}
void write(unsigned long, unsigned long)
{
}


/********** medium level commands, for the expert user! */
void Seg7CA::autoscroll()
{
_autoscroll=true;
}
void noAutoscroll()
{
_autoscroll=false;
}
void dpOn()
{
_dpSelect=0x8F;
}
void dpOff()
{
_dpSelect=0x08;
}
void dpBlink()
{
_dpBlink = true;
}
void dpNoBlink()
{
_dpBlink = false;
}
  
/********* low level commands, private! */
void Seg7CA::charseg(boolean dp, String textstring)
{

  if(dp){
    _dpSelect = 0x8F;
  }
 char text[9];
 textstring.toCharArray(text,9);

  for (int seg = 0; seg < 8; seg++) 
  {
    int _output = 0;
    
    char _segMask = 1 << (7 - seg);

    for (int dig = 0; dig < 8; dig++)
    {
     
      if ((getByte(text[7-dig]) & segMask) && (_digSelect & (1 << dig)))
      {
        output |= 1 << dig;
      }

      if ((seg == 7) && (_dpSelect & (1 << dig)))
      {
        output |= 1 << dig;//(7 - dig);
      }
      
    }


    digitalWrite(LOAD, LOW);
    shiftOut(DIN, CLK, MSBFIRST, seg + 1);
    shiftOut(DIN, CLK, MSBFIRST, output);
    digitalWrite(LOAD, HIGH);
  }
}

void Seg7CA::writeseg(boolean dp, unsigned long num)
{
  _digSelect = 0xFF;//0x7F;
  _dpSelect = 0x08;//0x8F;
  if(dp){
    _dpSelect = 0x8F;
  }
  for (int seg = 0; seg < 8; seg++) 
  {
    int output = 0;
    unsigned long numCopy = num;
    char segMask = 1 << (7 - seg);

    for (int dig = 0; dig < 8; dig++)
    {
      char curNum = numCopy % 10;

      if ((segDigits[curNum] & segMask) && (_digSelect & (1 << dig)))
      {
        output |= 1 << dig;
      }

      if ((seg == 7) && (_dpSelect & (1 << dig)))
      {
        output |= 1 << dig;//(7 - dig);
      }

      numCopy /= 10;
    }

   
    digitalWrite(_LOAD, LOW);
    shiftOut(_DIN, _CLK, MSBFIRST, seg + 1);
    shiftOut(_DIN, _CLK, MSBFIRST, output);
    digitalWrite(_LOAD, HIGH);
  }
}

byte Seg7CA::getByte(char c)
{
  if(alphabeth[c]!=0){
    return alphabeth[c];
  }
  else{
    return 0x8E;
  }
}
void initAlphabeth(){
for (int i=0;i<128;i++){
alphabeth[i] =  0x92; // = decode error
}
alphabeth[32]=  0x00;  // = ' '
alphabeth[48]=  0xFC;  // = 0
alphabeth[49]=  0x60;  // = 1
alphabeth[50]=  0xDA;  // = 2
alphabeth[51]=  0xF2;  // = 3
alphabeth[52]=  0x66;  // = 4
alphabeth[53]=  0xB6;  // = 5
alphabeth[54]=  0xBE;  // = 6
alphabeth[55]=  0xE0;  // = 7
alphabeth[56]=  0xFE;  // = 8
alphabeth[57]=  0xE6;  // = 9
alphabeth[45]=  0x02;  // = -
alphabeth[65]=  0xEE;  // = A
alphabeth[97]=  0xEE;  // = a = A
alphabeth[98]=  0x3E;  // = b
alphabeth[66]=  0x3E;  // = B = b
alphabeth[67]=  0x9C;  // = C
alphabeth[99]=  0x1A;  // = c
alphabeth[100]= 0x7A;  // = d
alphabeth[68]= 0x7A;  // = D = d
alphabeth[69]=  0x9E;  // = E
alphabeth[101]=  0x9E;  // = e = E
alphabeth[70]=  0x8E;  // = F
alphabeth[102]=  0x8E;  // = f = F
alphabeth[72]=  0x6E;  // = H
alphabeth[104]= 0x2E;  // = h 
alphabeth[73]=  0x0C;  // = I
alphabeth[105]=  0x0C;  // = I
alphabeth[76]=  0x1C;  // = L
alphabeth[108]=  0x1C;  // = l = L
alphabeth[78]=  0x2A;  // = N = n
alphabeth[110]=  0x2A;  // = n
alphabeth[79] = 0xFC; // = O = 0
alphabeth[111]= 0x3A;  // = o
alphabeth[80]=  0xCE;  // = P
alphabeth[112]=  0xCE;  // = p = P
alphabeth[82] =  0x0A;  // = R = r
alphabeth[114] =  0x0A;  // = r
alphabeth[83] =  0xB6; // = S =5
alphabeth[115] =  0xB6;// = s = S = 5
alphabeth[84] =  0x1E;// = T = t
alphabeth[116] =  0x1E;// = t
alphabeth[85]=  0x7C;  // = U
alphabeth[117]=  0x38;  // = u 
alphabeth[89] =  0x76; // = Y
alphabeth[121] =  0x76; // = y = Y
alphabeth[94]=  0xC6;  // = ° (has to be referenced as ^)
alphabeth[95] =  0x10; // = _
alphabeth[61] = 0x12; // = '='
}