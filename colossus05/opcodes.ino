void initializeOpcodes(){
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

  //90 SmartASS to node
  arg[90] = 0;
  opname[90] = "attitude node";
  
  //91 SmartASS to prograde
  
91	attitude prograde
92	attitude retrograde
93	attitude +normal
94	attitude -normal
95	attitude +radial
96	attitude -radial
97	attitude +target
98	attitude -target
99	attitude +rvel
100	attitude -rvel
101	attitude +par
102	attitude -par


  //120 Toggle SAS
  arg[120]=0;
  opname[120] = "toggle SAS";
}
