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
  XBee.write(TeleArray[TeleID]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleMissionTime]);
  XBee.write(", ");
  XBee.write(TeleArray[TelePacket]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleAlt]);
  XBee.write(", ");
  XBee.write(TeleArray[TelePressure]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleTemp]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleVolt]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleGTime]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleGLat]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleGLong]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleGAlt]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleGSats]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleTiltX]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleTiltY]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleTiltZ]);
  XBee.write(", ");
  XBee.write(TeleArray[TeleState]);
  XBee.write("\n");
}

