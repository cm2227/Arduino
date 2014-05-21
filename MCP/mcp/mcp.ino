#include "PanasonicEncoder.h"

#define SEG_NUM 4
#define SEG_DIN 2
#define SEG_LOAD 3
#define SEG_CLK 4

int seg_segments[8] = { 
	30, 31, 32, 33, 34, 35, 36, 37 
};

int seg_mux[4] = { 
	22, 24, 26, 28 
};

int seg_si = 30;
int seg_sck = 31;
int seg_rck = 32;

bool flchActive = false;
bool flchSet = false;
bool flchSetLast = false;

bool overspeedFlash = false;

int current_heading = 0;
int current_speed = 100;

int sim_heading = 0;
int sim_speed = 100;

String command;

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

PanasonicEncoder headingEncoder(18, 50);
PanasonicEncoder speedEncoder(19, 22);

void seg_on(int seg) {
	pinMode(seg, OUTPUT);
	digitalWrite(seg, LOW);
}

void seg_off(int seg) {
	pinMode(seg, OUTPUT);
	digitalWrite(seg, HIGH);
}

void seg_off_dig() {
	for (int i = 0; i < 4; i++) {
		digitalWrite(seg_mux[i], LOW);
	}
}

void seg_select_dig(int dig) {
	digitalWrite(seg_mux[dig], HIGH);
}

void seg_set_dig(int num, bool dp) {
	unsigned char output;

	/*if (num < 0) {
	output = 255;

	if (dp) {
	output |= 1 << 7;
	}
	}
	else {  
	for (int i = 0; i < 8; i++) {
	if ((seg_digits[num][i] == 1) || ((i == 7) && dp)) {
	output &= ~(1 << i);
	}
	else {
	output |= 1 << i;
	}
	}
	}*/

	shiftOut(seg_si, seg_sck, MSBFIRST, output);
}

void seg_show(int* num, int del, int dp, int lead) {
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < SEG_NUM; j++) {
			int cur = num[j] % 10;

			if (!((cur == 0) && ((lead + i) <= 3) && (dp != i))) {
				seg_set_dig(cur, dp == i);
			}
			else {
				seg_set_dig(-1, dp == i);
			}

			num[j] /= 10;
		}

		digitalWrite(seg_rck, LOW);
		seg_off_dig();
		digitalWrite(seg_rck, HIGH);
		seg_select_dig(i);

		delay(del);
	}
}

void headingEncoderISR()
{
	headingEncoder.check();
}

void speedEncoderISR()
{
	speedEncoder.check();
}

void serialEvent() {
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read(); 
		// add it to the inputString:
		command += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n') 
		{
			if (command.startsWith("ias"))
				sim_speed = command.substring(3).toInt();
			else if (command.startsWith("osf"))
				overspeedFlash = command.substring(3).toInt();
			else if (command.startsWith("flch"))
				flchActive = command.substring(4).toInt();

			command = "";
		}
	}
}

void setup() 
{                
	Serial.begin(9600);

	pinMode(13, OUTPUT);     

	/*pinMode(22, OUTPUT);
	pinMode(24, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(28, OUTPUT);

	pinMode(52, INPUT);
	pinMode(53, INPUT);

	pinMode(seg_si, OUTPUT);
	pinMode(seg_sck, OUTPUT);
	pinMode(seg_rck, OUTPUT);*/
	pinMode(SEG_DIN, OUTPUT);
	pinMode(SEG_LOAD, OUTPUT);
	pinMode(SEG_CLK, OUTPUT);

	//attachInterrupt(5, headingEncoderISR, CHANGE);
	attachInterrupt(4, speedEncoderISR, CHANGE);

	digitalWrite(SEG_LOAD, LOW);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0C);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x01);
	digitalWrite(SEG_LOAD, HIGH);

	digitalWrite(SEG_LOAD, LOW);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x09);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x00);
	digitalWrite(SEG_LOAD, HIGH);

	digitalWrite(SEG_LOAD, LOW);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0B);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x07);
	digitalWrite(SEG_LOAD, HIGH);

	digitalWrite(SEG_LOAD, LOW);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0A);
	shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, 0x0F);
	digitalWrite(SEG_LOAD, HIGH);
}

void loop() 
{
	int old_heading = current_heading;
	int old_speed = current_speed;

	int heading_diff = headingEncoder.readDifference();
	int speed_diff = speedEncoder.readDifference();

	// Apply heading

	current_heading += heading_diff;

	if (abs(heading_diff) > 9) 
	{
		current_heading += heading_diff;

		digitalWrite(13, HIGH);
	}
	else
	{
		digitalWrite(13, LOW);
	}

	// Apply speed

	current_speed += speed_diff;

	if (abs(speed_diff) > 9) 
	{
		current_speed += speed_diff;

		digitalWrite(13, HIGH);
	}
	else
	{
		digitalWrite(13, LOW);
	}

	// Check heading boundaries

	if (current_heading > 359) {
		current_heading -= 360;
	}
	else if (current_heading < 0) {
		current_heading += 360;
	}

	if (digitalRead(23) == 1) {
		if (!flchSetLast) {
			flchSet = !flchSet;
			flchSetLast = true;

			Serial.println("flch");
		}
	}
	else {
		flchSetLast = false;
	}

	if (flchActive)
		digitalWrite(13, HIGH);
	else
		digitalWrite(13, LOW);	

	if (current_speed != old_speed)
	{
		Serial.print("ias");
		Serial.println(current_speed);

		sim_speed = current_speed;
	}
	else
	{
		current_speed = sim_speed;
	}

	unsigned long num = (unsigned long)current_speed * 10000 + current_heading;
	int dpSelect = 0x08;//0x8F;
	char digSelect = 0x77;//0x7F;

	if (overspeedFlash && ((millis() / 500) % 2 == 0))
	{
		num += 80000000;
		digSelect |= 1 << 7;
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

		digitalWrite(SEG_LOAD, LOW);
		shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, seg + 1);
		shiftOut(SEG_DIN, SEG_CLK, MSBFIRST, output);
		digitalWrite(SEG_LOAD, HIGH);
	}

	/*analogWrite(13, testIntensity);

	testIntensity += 0x01;

	if (testIntensity > 0xFF)
	testIntensity = 0;

	delay(250);*/
}











