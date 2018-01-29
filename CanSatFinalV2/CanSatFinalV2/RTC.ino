//Real Time Clock
void setupRTC(){
  rtc.begin();
  //REMOVE THIS LINE LATER******************
  //rtc.setTime(0,0,0,0,0,0,0);
  //****************************************
}

void callRTC(){

  TeleArray[TeleMissionTime] = TeleArray[TelePacketCount];
}


