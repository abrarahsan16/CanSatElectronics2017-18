void setupFunctions(){
  Wire.begin();
    Serial.println("HI");
  setupBMP();
    Serial.println("HI");
  //setupCamera();
  //setupBuzzer();
  //setupRTC();
  //setupGPS();
  //setupRadio();
    Serial.println("HI");
  setupTilt();
    Serial.println("HI");
  setupVoltage();
}

void collectData()
{
  getTemp();
  getPressure();
  getAlt();
  //GPSLoop();
  //getTime();
  getTilt();
  callVoltage();
}

void printTelemetry()
{
  for(int i=0; i<TeleArrayLength; i++)
{
  Serial.print(TeleArray[i]);
  Serial.print(", ");
  //radio.write(TeleArray[i]);
  //radio.write(", ");
}
Serial.println();

}

