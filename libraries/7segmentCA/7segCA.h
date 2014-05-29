#ifndef seg7CA_h
#define seg7CA_h

//This library allows to use common anode LED 7-segment displays on a single MAX7219 display driver
//it can not work with common cathode displays and is tailored to my own application

class seg7CA {
public:
  seg7CA(byte DIN, byte LOAD, byte CLK);
  seg7CA(byte DIN);
  
   

  //void noBlink();
  //void blink();
  
  void autoscroll();
  void noAutoscroll();
  void dpOn();
  void dpOff();
  void dpBlink();
  
  void write(String);
  void write(int);
  void write(unsigned long);
  void write(long);
  void write(float);
  void write(double);
  void write(byte);
  void write(double, double);
  void write(int, int);
  void write(long, long);
  void write(unsigned long, unsigned long);

private:
  
  void writeNum(int);
  void writeString(String);
  void init();
  void init(byte b0, byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7);
  byte getbyte(char c);

  byte _DIN_PIN; // LOW: command.  HIGH: character.
  byte _LOAD_PIN; // LOW: write to LCD.  HIGH: read from LCD.
  byte _CLK_PIN; // activated by a HIGH pulse.
  
  byte _digSelect;
  byte _dpSelect;
  char[9] _text;
  
  boolean _autoscroll;
  boolean _dpBlink;
  byte segDigits[] = 
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
  
};

#endif