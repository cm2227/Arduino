void input() {
  now = millis();

  if (KSPBoardReceiveData()){
    deadtimeOld = now;
    switch(id) {
    case 0: //Handshake packet
      Handshake();
      break;
    case 1:
      Indicators();
      break;
    }

    //We got some data, turn the green led on
    digitalWrite(greenpin,HIGH);
    Connected = true;
  }
  else
  { //if no message received for a while, go idle
    deadtime = now - deadtimeOld; 
    if (deadtime > IDLETIMER)
    {
      deadtimeOld = now;
      Connected = false;
      LEDSAllOff();
    }    
  }
}
