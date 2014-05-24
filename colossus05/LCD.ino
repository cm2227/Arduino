byte OCprompt() //causes the LCD to prompt for the next opcode
{
  //write prompt to LCD
  //make sure cursor is as desired
  
  return getByte(); //must be replaced with string to int conversion
}

float ArgPrompt(int a) //causes the LCD to get an argument
{
    lcd.setCursor(0,0);
    lcd.print(opname[opcode]);
    lcd.setCursor(0,1);
    lcd.print("arg"+a);
    return getFloat();
}
