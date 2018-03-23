void setupFunctions(){
  Wire.begin();
  setupBMP();
  setupCamera();
  setupBuzzer();
  setupRTC();
//  setupGPS();
  setupRadio();
  setupTilt();
  setupVoltage();
  //radio.begin(19200); This line is included in setupRadio();
}
//Buzzer is to turn on at 10meters

void collectData()
{
  getTemp();
  getPressure();
  getAlt();
//  GPSLoop();
  getTime();
  getTilt();
  callVoltage();
}

