void setupBMP(){
 // Initialize sensor
 if(!bmp.begin()){
  Serial.println("Could not find BMP sensor");
 }
}

void callTemp(){
  TeleArray[TeleTemp] = 29.3 + rand() % 1;
}

void callPressure(){
  TeleArray[TelePressure] = 101300 + rand() % 25;
}

void callAlt(){
  
  float alt = 700 - TeleArray[TelePacketCount] * 4;
  TeleArray[TeleAltSensor] = alt;
}

