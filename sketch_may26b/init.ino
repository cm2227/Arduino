void initAlphabeth(){
  for (int i=0;i<128;i++);
  alphabeth[48]=0xFC;  // = 0
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
alphabeth[76]=  0x1C;  // = L
alphabeth[104]=  0x2E;  // = h 
alphabeth[111]=  0x3A;  // = o
alphabeth[98]=  0x3E;  // = b
alphabeth[72]=  0x6E;  // = H
alphabeth[100]=  0x7A;  // = d
alphabeth[85]=  0x7C;  // = U
alphabeth[70]=  0x8E;  // = F
alphabeth[67]=  0x9C;  // = C
alphabeth[69]=  0x9E;  // = E
alphabeth[68]=  0xC6;  // = ° (has to be referenced as D)
alphabeth[80]=  0xCE;  // = P
alphabeth[65]=  0xEE;  // = A
// = I
// = _
// = ' '
// = n
// = Y
// = r
// = fail
// = u
// = d
// = c
// = S



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

