void Indicators() {
  caution = 0;
  warning = 0;

  caution += VData.G > GCAUTION;
  warning += VData.G > GWARN;
  caution += VData.LiquidFuelS/VData.LiquidFuelTotS*100 < FUELCAUTION;
  warning += VData.LiquidFuelS/VData.LiquidFuelTotS*100 < FUELWARN;

//master alarm under all conditions



  if (((VData.ECharge/VData.EChargeTot)<0.1)&&a1){ //  battery <10%
    masteralarm=true;
    a1=false;
  }
  else {
    a1=true;
  }
  if ((VData.dV<dVlevel)&&a2){  //dV level
    masteralarm=true;
  }
  else{
    a2=true;
  }
  if (((VData.MonoProp/VData.MonoPropTot)<0.1)&&a3){  //Monopropellant level
    masteralarm=true;
  }
  else{
    a3=true;
  }
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

 
 
  
 Take-off
 
 
 Flight
!orbit
.05g
  
 Landing

 
 */
//master alarm under flight conditions only  
if (flightmode ==0){
  //0.05g
  
}
//master alarm under take-off conditions only  
if (flightmode ==1){
}
//master alarm under landing conditions only  
if (flightmode ==2){
}

}


boolean Orbit(){
  if (VData.AP>VData.Atmo){
    return true;
    
  }
  else {
    return false;
  }
}


void Randomize(){
  
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
  float atmo=69900; //atmosphere height
  float R;//current body radius
  */
}





