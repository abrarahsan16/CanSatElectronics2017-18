void setupFunctions()
{
  HMCSetup();
  TeleArray[TeleID] = TeamID;
  setupRTC();
  setupVoltage();
  setupBMP();
  gpsSetup();
}

void collectData(){
  getTime();
  TeleArray[TelePacket]=packetCount;
  getVolt();
  getTemp();
  getPressure();
  getAlt();
  gpsLoop();
  TeleArray[TeleState] = 1;
  hmcLoop();
}

void printData()
{
  Serial.print(TeleArray[TeleID]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleMissionTime]);
  Serial.print(", ");
  Serial.print(TeleArray[TelePacket]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleAlt]);
  Serial.print(", ");
  Serial.print(TeleArray[TelePressure]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleTemp]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleVolt]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleGTime]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleGLat]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleGLong]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleGAlt]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleGSats]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleTiltX]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleTiltY]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleTiltZ]);
  Serial.print(", ");
  Serial.print(TeleArray[TeleState]);
  Serial.print("\n");
}

