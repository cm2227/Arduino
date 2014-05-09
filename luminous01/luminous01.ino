/*
  LiquidCrystal Library - Hello World
 
 
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd1(12, 11, 10,9,8,7);
LiquidCrystal lcd2(22, 24, 26, 28, 30, 32);
LiquidCrystal lcd3(23, 25, 27, 29, 31, 33);

//status variables
boolean masteralarm=false;
int flightmode = 0; //0 = flight, 1=take-off, 2=landing


//values from KSP

byte id;             //1   packet id
float AP;            //2   apoapsis (m to sea level)
float PE;            //3   periapsis (m to sea level)
float SemiMajorAxis; //4   orbit semi major axis (m)
float SemiMinorAxis; //5   orbit semi minor axis (m)
float VVI;           //6   vertical velocity (m/s)
float e;             //7   orbital eccentricity (unitless, 0 = circular, > 1 = escape)
float inc;           //8   orbital inclination (degrees)
float G;             //9   acceleration (Gees)
long TAp;             //10  time to AP (seconds)
 long TPe;             //11  time to Pe (seconds)
 float TrueAnomaly;   //12  orbital true anomaly (degrees)
 float Density;       //13  air density (presumably kg/m^3, 1.225 at sea level)
 long period;          //14  orbital period (seconds)
 float RAlt;          //15  radar altitude (m)
 float Alt;           //16  altitude above sea level (m)
 float Vsurf;         //17  surface velocity (m/s)
 float Lat;           //18  Latitude (degree)
 float Lon;           //19  Longitude (degree)
 float LiquidFuelTot; //20  Liquid Fuel Total
 float LiquidFuel;    //21  Liquid Fuel remaining
 float OxidizerTot;   //22  Oxidizer Total
 float Oxidizer;      //23  Oxidizer remaining
 float EChargeTot;    //24  Electric Charge Total
 float ECharge;       //25  Electric Charge remaining
 float MonoPropTot;   //26  Mono Propellant Total
 float MonoProp;      //27  Mono Propellant remaining
 float IntakeAirTot;  //28  Intake Air Total
 float IntakeAir;     //29  Intake Air remaining
 float SolidFuelTot;  //30  Solid Fuel Total
 float SolidFuel;     //31  Solid Fuel remaining
 float XenonGasTot;   //32  Xenon Gas Total
 float XenonGas;      //33  Xenon Gas remaining
 float LiquidFuelTotS;//34  Liquid Fuel Total (stage)
 float LiquidFuelS;   //35  Liquid Fuel remaining (stage)
 float OxidizerTotS;  //36  Oxidizer Total (stage)
 float OxidizerS;     //37  Oxidizer remaining (stage)
 uint32_t MissionTime;  //38  Time since launch (s)
 float deltaTime;     //39  Time since last packet (s)
 float VOrbit;        //40  Orbital speed (m/s)
 uint32_t MNTime;       //41  Time to next node (s) [0 when no node]
 float MNDeltaV;      //42  Delta V for next node (m/s) [0 when no node]


void setup() {
  // set up the LCD's number of columns and rows:                                   
  lcd1.begin(20, 4);
  // Print a message to the LCD.
  lcd1.print("hello LCD#1");
  // set up the LCD's number of columns and rows: 
  lcd2.begin(16, 2);
  // Print a message to the LCD.
  lcd2.print("hello LCD#2");
  // set up the LCD's number of columns and rows: 
  lcd3.begin(20, 4);
  // Print a message to the LCD.
  lcd1.print("hello LCD#3");
}

void loop() {

  //Poll all switches

  //receive serial input

  //write input to variables

  //draw conclusions

  //display results in LCD

  //display results in 7seg

  //illuminate correct LEDs

  //master alarm blink & sound if necessary


  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd1.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd1.print(millis()/1000);
}


