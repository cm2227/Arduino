void initAlphabeth(){
  alphabeth2[48]=0xFC;  // = 0
alphabeth2[49]=  0x60;  // = 1
alphabeth2[50]=  0xDA;  // = 2
alphabeth2[51]=  0xF2;  // = 3
alphabeth2[52]=  0x66;  // = 4
alphabeth2[53]=  0xB6;  // = 5
alphabeth2[54]=  0xBE;  // = 6
alphabeth2[55]=  0xE0;  // = 7
alphabeth2[56]=  0xFE;  // = 8
alphabeth2[57]=  0xE6;  // = 9
alphabeth2[45]=  0x02;  // = -
alphabeth2[76]=  0x1C;  // = L
alphabeth2[104]=  0x2E;  // = h 
alphabeth2[111]=  0x3A;  // = o
alphabeth2[98]=  0x3E;  // = b
alphabeth2[72]=  0x6E;  // = H
alphabeth2[100]=  0x7A;  // = d
alphabeth2[85]=  0x7C;  // = U
alphabeth2[70]=  0x8E;  // = F
alphabeth2[67]=  0x9C;  // = C
alphabeth2[69]=  0x9E;  // = E
alphabeth2[68]=  0xC6;  // = ° (has to be referenced as D)
alphabeth2[80]=  0xCE;  // = P
alphabeth2[65]=  0xEE;  // = A
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

