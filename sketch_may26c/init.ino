void initAlphabeth(){
for (int i=0;i<128;i++){
alphabeth[i] =  0x00; // = decode error
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

