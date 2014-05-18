void randomize(){

  VData.AP=random(70000,400000);               //2
  VData.PE=random(70000,VData.AP);               //3



  /*
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
   */
  VData.EChargeTot=500;       //24
  VData.ECharge=random(0,0.5*VData.EChargeTot);          //25
  VData.MonoPropTot=1000;      //26
  VData.MonoProp=random(0,0.5*VData.MonoPropTot);         //27

  /*
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
   float atmo=69900; //atmosphere height
   float R;//current body radius
   */
  //VData.dVTot=1000;
  //VData.dV=random(100,600);

}

