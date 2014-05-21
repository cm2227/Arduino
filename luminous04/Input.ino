void input() {
  now = millis();

  if (KSPBoardReceiveData()){
    pilot.setCursor(3,15);
    pilot.print("Data");
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
      pilot.setCursor(3,15);
    pilot.print("nix!");
    }    
  }
}
