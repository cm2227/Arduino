//pins for LEDs
int malarmpin = 13;
int warn1pin = 12;
int warn2pin = 11;
int warn3pin = 10;
int warn4pin = 9;
int greenpin = 8;
int voltpin = 7;
int buzzpin = 2;
boolean a1=true;
boolean a2=true;
boolean a3=true;
boolean a4=true;
boolean a5=true;
boolean a6=true;

/*
.05g
 Proximity h
 Trajectory Peri < 1.1R OR Peri < Atmo NAND 
 Master Alarm LED
 Master Alarm buzzer
 Orbit RED !orbit
 Orbit GREEN orbit
 battery warning <20%
Monopropellant level <10%
//dV warning level 500m/s oder 10% der letzten Stufe

orbit peri & apo > 1.1R oder atmo
 Conditions for Master Alarm during

 
 always
  battery <10%
  dV level
  Monopropellant
  
 Take-off
 
 
 Flight
!orbit
.05g
  
 Landing

 
 */
// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 500;           // interval at which to blink (milliseconds)


//pins for input
//warp factor
//flight mode switch
//alarm reset button

//macro 
#define details(name) (uint8_t*)&name,sizeof(name)

//if no message received from KSP for more than 2s, go idle
#define IDLETIMER 2000
#define CONTROLREFRESH 25

//warnings
#define GWARN 9                  //9G Warning
#define GCAUTION 5               //5G Caution
#define FUELCAUTION 10.0         //10% Fuel Caution
#define FUELWARN 5.0             //5% Fuel warning

unsigned long deadtime, deadtimeOld, controlTime, controlTimeOld;
unsigned long now;

boolean Connected = false;

byte caution = 0, warning = 0, id;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal eecom(23, 25, 27, 29, 31, 33);
LiquidCrystal pilot(22, 24, 26, 28, 30, 32);

//status variables
boolean masteralarm=false;
boolean orbit = false;
int flightmode = 0; //0 = flight, 1=take-off, 2=landing


struct VesselData
{
  byte id;                //1
  float AP;               //2
  float PE;               //3
  float SemiMajorAxis;    //4
  float SemiMinorAxis;    //5
  float VVI;              //6
  float e;                //7
  float inc;              //8
  float G;                //9
  long TAp;               //10
  long TPe;               //11
  float TrueAnomaly;      //12
  float Density;          //13
  long period;            //14
  float RAlt;             //15 Radar Altitude
  float Alt;              //16 Altitude
  float Vsurf;            //17 Surface Velocity
  float Lat;              //18
  float Lon;              //19
  float LiquidFuelTot;    //20
  float LiquidFuel;       //21
  float OxidizerTot;      //22
  float Oxidizer;         //23
  float EChargeTot;       //24
  float ECharge;          //25
  float MonoPropTot;      //26
  float MonoProp;         //27
  float IntakeAirTot;     //28
  float IntakeAir;        //29
  float SolidFuelTot;     //30
  float SolidFuel;        //31
  float XenonGasTot;      //32
  float XenonGas;         //33
  float LiquidFuelTotS;   //34
  float LiquidFuelS;      //35
  float OxidizerTotS;     //36
  float OxidizerS;        //37
  uint32_t MissionTime;   //38
  float deltaTime;        //39
  float VOrbit;           //40
  uint32_t MNTime;        //41
  float MNDeltaV;         //42
  float dVTot;  //dv total
  float dV; //dv current stage
  float Atmo; //atmosphere height
  float R;//current body radius
};

struct HandShakePacket
{
  byte id;
  byte M1;
  byte M2;
  byte M3;
};

struct ControlPacket {
  byte id;
  byte MainControls;                  //SAS RCS Lights Gear Brakes Precision Abort Stage 
  byte Mode;                          //0 = stage, 1 = docking, 2 = map
  unsigned int ControlGroup;          //control groups 1-10 in 2 bytes
  byte AdditionalControlByte1;        //other stuff
  byte AdditionalControlByte2;
  //set warp factor
  int Pitch;                          //-1000 -> 1000
  int Roll;                           //-1000 -> 1000
  int Yaw;                            //-1000 -> 1000
  int TX;                             //-1000 -> 1000
  int TY;                             //-1000 -> 1000
  int TZ;                             //-1000 -> 1000
  int Throttle;                       //    0 -> 1000
};

HandShakePacket HPacket;
VesselData VData;
ControlPacket CPacket;

void setup(){
  Serial.begin(38400);

  initLEDS();
  InitTxPackets();
  controlsInit();

  LEDSAllOff();
  // set up the LCD's number of columns and rows:                                   
  eecom.begin(20, 4);
  // Print a message to the LCD.
  eecom.print("hello LCD#1");
  // set up the LCD's number of columns and rows: 
  pilot.begin(20, 4);
  // Print a message to the LCD.
  pilot.print("hello LCD#2");
  // set up the LCD's number of columns and rows: 

//initialize debug variables
VData.Atmo=69000;
}

void loop()
{  
  input();
  //Poll all switches

  //receive serial input

    //write input to variables

  //draw conclusions

  //display results in LCD

  //display results in 7seg

  //illuminate correct LEDs

  //master alarm blink & sound if necessary
  //master alarm totzeit 


  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  eecom.setCursor(0, 1);
  // print the number of seconds since reset:
  eecom.print(millis()/1000);
  pilot.clear();
  pilot.setCursor(0,0);
  pilot.print("Mode: ");
  switch (flightmode){
    case 0:
    pilot.print("flight");
    break;
    case 1:
    pilot.print("take-off");
    break;
    case 2:
    pilot.print("landing");
    break;
  }
  
  
  //master alarm
  
   unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;

    // set the LED with the ledState of the variable:
    digitalWrite(malarmpin, ledState);
  output();
  }
}



















