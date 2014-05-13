void Handshake1(){
//  digitalWrite(GLED,HIGH); 

  HPacket.id = 0;
  HPacket.M1 = 3;
  HPacket.M2 = 1;
  HPacket.M3 = 4;

  KSPBoardSendData1(details(HPacket));
  //Serial.println(F("KSP;0"));  
  //delay(1000);
}

uint8_t rx_len1;
uint8_t * address1;
byte buffer1[256]; //address for temporary storage and parsing buffer
uint8_t structSize1;
uint8_t rx_array_inx1;  //index for RX parsing buffer
uint8_t calc_CS1;	   //calculated Chacksum

//This shit contains stuff borrowed from EasyTransfer lib


void KSPBoardSendData1(uint8_t * address, uint8_t len){
  uint8_t CS = len;
  Serial1.write(0xBE);
  Serial1.write(0xEF);
  Serial1.write(len);
  
  for(int i = 0; i<len; i++){
    CS^=*(address+i);
    Serial1.write(*(address+i));
  }
  
  Serial1.write(CS);
}




