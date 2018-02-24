void setupFunctions(){
  Wire.begin();
  setupBMP();
  setupBuzzer();
  setupRTC();
  setupGPS();
  setupRadio();
  setupTilt();
  setupVoltage();
  radio.begin(19200);
}


