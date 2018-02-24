void setupFunctions(){
  Wire.begin();
  setupBMP();
  setupCamera();
  setupBuzzer();
  setupRTC();
  setupGPS();
  setupRadio();
  setupTilt();
  setupVoltage();
  radio.begin(19200);
}


