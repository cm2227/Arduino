float getFloat(){ //causes the keypad to get a float value, finished with #
  char input[32];
  //poll keypad until string is finished with # key
  if ((millis() - lastDebounceTime) > debounceDelay) {
      // whatever the reading is at, it's been there for longer
      // than the debounce delay, so take it as the actual current state:
      for (int thisPin = 31; thisPin < 54; thisPin=thisPin+2)  {
        
        if (digitalRead(37)==HIGH{
        break;
        }
        if (digitalRead(thisPin)==HIGH){
          input+=key[thisPin];
          lcd.print(key[thisPin]);
          lastDebounceTime = millis();
          bounce = false;
        }

      }

  }
  else goto 
}
  
  //add pressed keys to input
  
  //return float number generated from input
  
}

int getInt() //causes the keypad to get an integer value, finished with #
{
  String input;
  //poll keypad until string is finished with # key
  
  //add pressed keys to input
  
  //ignore * key
    
  //return integer generated from string



}

byte getByte() //causes the keypad to get a byte value, finished with #
{
  repeat:
  char[3] input;
  byte counter=0;
  //poll keypad until string is finished with # key
  //also poll voltage divider
  //voltage divider pushbuttons result in direct return of opcode
  
  //add pressed keys to input
  
  //ignore * key
  
  //only allow 3 digits
  
  int result;
  
  //convert string to int result 
  
  //return byte generated from int result if possible
  
  //do again if result is not valid as byte
  if (byte){
    return byte(result);
  }
  else {
    goto repeat;
  }  
}


