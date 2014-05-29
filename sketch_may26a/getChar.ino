byte getByte(char c)
{
  for (int i=0; i<24; i++)
  {
    if (c == alphabeth[i]){
      return byteChar[i];
    }
  }
  return 0x8E;
}

byte getByte2(char c)
{
  if(alphabeth2[c]!=0){
    return alphabeth2[c];
  }
  else{
    return 0x8E;
  }

}
