#include <LiquidCrystal.h>
char line1[17];
char line2[17];
boolean enterloop = true;
String sbuffer;
boolean wait=true;
int opcode;
int arg[255];
String opname[255];

//internal coms section
unsigned long deadtime1, deadtimeOld1, controlTime1, controlTimeOld1;
unsigned long now1;

boolean Connected1 = false;


LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
char key[51]; //= {'1','4','7','*','2','5','8','0','3','6','9','#'};

int ledPins[] = {
  31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53 }; 
String ergebnis;
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin 

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
boolean bounce = true;
boolean finish = false;

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
  float RAlt;             //15
  float Alt;              //16
  float Vsurf;            //17
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
  /*float dVTot;  //dv total
   float dV; //dv current stage
   float Atmo; //atmosphere height
   float R;//current body radius
   byte state; //Used to tell colossus wether MechJeb is active or not or wether the plugin can accept orders
   String mjstatus; //comes from MechJeb*/
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
  int Pitch;                          //-1000 -> 1000
  int Roll;                           //-1000 -> 1000
  int Yaw;                            //-1000 -> 1000
  int TX;                             //-1000 -> 1000
  int TY;                             //-1000 -> 1000
  int TZ;                             //-1000 -> 1000
  int Throttle;                       //    0 -> 1000
  /*byte opcode;                        //opcode for MechJeb Operation
   float arg1;
   float arg2;
   float arg3;
   float arg4;*/
};

HandShakePacket HPacket;
VesselData VData;
ControlPacket CPacket;


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

void setup() {
  //ergebnis = "Colossus 04a";
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  // initialize the serial communications:
  //ergebnis.toCharArray(line1,17);


  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(13,OUTPUT);

  //initLEDS();
  InitTxPackets();
  controlsInit();


  // put your setup code here, to run once:
  for (int thisPin = 31; thisPin < 54; thisPin=thisPin +2)  {
    pinMode(thisPin, INPUT); 
    ergebnis="Pin "; 
    ergebnis = ergebnis + thisPin + " initialisiert.";
    //Serial.println(ergebnis);
    ergebnis ="";
  }
  /*
  lcd.setCursor(0,1);
   sbuffer = "Press # to cont.";
   sbuffer.toCharArray(line1,17);
   lcd.print(line1);
   while(wait)
   {
   input();
   if (digitalRead(37)==HIGH){
   wait=false;
   }
   }
   delay(300);
   */
  key[31]= '3';
  key[33]= '6';
  key[35]= '9';
  key[37]= '#';
  key[39]= '2';
  key[41]= '5';
  key[43]= '8';
  key[45]= '0';
  key[47]= '1';
  key[49]= '4';
  key[51]= '7';
  key[53]= '.';

  //List of opcodes

  //11 Ascent guidance to orbit at X1 km with 0° inclination with manual staging
  arg[11] = 1;
  opname[11] = "Asc gui 0deg MS";

  //12 Ascent guidance to orbit at X1 km with X2° inclination with manual staging
  arg[12] = 2;
  opname[12] = "Asc gui Xdeg MS";

  //13 Ascent guidance to orbit at X1 km with X2° inclination with automatic staging to stage X3
  arg[13] = 3;
  opname[13] = "Asc gui Xdeg ASX";

  //21 Change apoapsis to X1 at next periapsis
  arg[21] = 1;
  opname[21] = "Apo change to";

  //22 Change periapsis to X1 at next apoapsis
  arg[22] = 1;
  opname[22] = "Peri change to";

  //23 Circularize at current altitude in X1 seconds
  arg[23] = 1;
  opname[23] = "circ in X";

  //31 New maneuver node?

  //32 PTC X1 degrees per minute
  arg[32] = 1;
  opname[32] = "PTC X deg/min";


  //81 Land at KSC
  arg[81] = 0;
  opname[81] = "land at KSC";
  /*
CPacket.arg1=0;
   CPacket.arg2=0;
   CPacket.arg3=0;
   CPacket.arg4=0;*/

}

void loop() {
  input();
  output();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Colossus 04b");
  lcd.blink();
  lcd.cursor();
  //sbuffer="Enter opcode:";
  //sbuffer.toCharArray(line1,21);
  lcd.setCursor(0,1);
  lcd.print("Enter opcode:");


  while(!finish){
    input();
    output();

    if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
      for (int thisPin = 31; thisPin < 54; thisPin=thisPin+2)  {
        input();

        if (digitalRead(thisPin)==HIGH)
        {
          ergebnis+=key[thisPin];
          lcd.print(key[thisPin]);
          //ergebnis.toCharArray(line2,20);
          lastDebounceTime = millis();
          bounce = false;
          delay(300);
          if (ergebnis.endsWith("#"))
          {
            finish = true;
            //Serial.println(ergebnis);
            randomize();
          }
        }

      }

    }
  }



  if (finish)
  {
    lcd.clear();
    lcd.noCursor();
    lcd.noBlink();
    lcd.setCursor(0,0);
    opcode = ergebnis.toInt();
    //ergebnis="";
    //Serial.print("Opcode ");
    //Serial.println(opcode);
    lcd.print(opname[opcode]);
    //Serial.println(arg[opcode]);
    //    sbuffer="OC";
    sbuffer="";
    //  sbuffer+=opcode;
    //sbuffer+=",";
    int k = arg[opcode];
    sbuffer+=k;
    sbuffer+=" arguments";
    sbuffer.toCharArray(line1,17);
    //Serial.println(sbuffer);

    lcd.setCursor(0,1);
    lcd.print(line1);
    delay(3000);
    for (int i=1; i<=arg[opcode]; i++)
    {
      lcd.clear();    
      lcd.setCursor(0,0);
      lcd.print(opname[opcode]);
      lcd.setCursor(0,1);
      lcd.print("arg"); 
      lcd.print(i);
      lcd.print(":");
      //Serial.print("Getting argument #");
      //Serial.println(i);
      finish=false;
      while(!finish){
        input();  
        lcd.cursor();
        lcd.blink();
        if ((millis() - lastDebounceTime) > debounceDelay) {
          // whatever the reading is at, it's been there for longer
          // than the debounce delay, so take it as the actual current state:
          for (int thisPin = 31; thisPin < 54; thisPin=thisPin+2)  {
            if (digitalRead(thisPin)==HIGH)
            {
              ergebnis+=key[thisPin];
              lcd.print(key[thisPin]);
              //ergebnis.toCharArray(line2,20);
              lastDebounceTime = millis();
              bounce = false;
              delay(300);
              if (ergebnis.endsWith("#"))
              {
                finish = true;
                //Serial.println(ergebnis);
              }
            }

          }

        }
      }
    }
    //Serial.println(ergebnis);
    /*    CPacket.arg1=0;
     CPacket.arg2=0;
     CPacket.arg3=0;
     CPacket.arg4=0;*/

    KSPBoardSendData(details(CPacket));



    /*
    sbuffer="Com " + ergebnis;
     Serial.println(sbuffer);
     sbuffer.toCharArray(line1,21);
     lcd.print(line1);
     sbuffer="transmitted";
     lcd.setCursor(0,1);
     sbuffer.toCharArray(line1,21);
     lcd.print(line1);
     delay(2000);
     */
    lcd.clear();
    finish = false; 
    ergebnis="";
    //sbuffer="Please enter #:";
    //sbuffer.toCharArray(line1,21);
    //lcd.print(line1);
    //lcd.setCursor(0,1);
  }

}







