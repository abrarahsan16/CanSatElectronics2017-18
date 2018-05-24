void setupFunctions(){
  Wire.begin();
  setupBuzzer();
  setupBMP();
  setupCamera();
  setupGPS();
  setupVoltage();
  setupRTC();
  setupMPU();
}

void dataCollection(){
  getTime();
  getTilt();
  TeleArray[TelePacket]=packetCount;
  getVolt();
  getTemp();
  getPressure();
  getAlt();
  getGPS();
  TeleArray[TeleState] = sensorState; 
}

void transmitData()
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

void checkFlown(float alt){
  if(alt>20){
    hasFlown = true;
    eepromCheck = 1;
  }
}

void checkAlt(float alt)
{
  if (alt <= 1.1 * lastAlt && alt >= 0.9 * lastAlt){
    constAlt = constAlt + 1;
  } else {
    lastAlt = alt;
  }
}

void stateCheck(){
  checkFlown(TeleArray[TeleAlt]); //Did it fly
  //checkAlt(TeleArray[TeleAlt]); //is it still flying
  sensorState = PreFlight;

  if(hasFlown == true)
  {
    if(TeleArray[TeleAlt] < 15)
    {
      sensorState = Landed;
    }
    else
    {
      sensorState = Flying;
    }
  }
}

void checkBurn(){
  receiveRadioData();
  if(sensorState == 2 && TeleArray[TeleAlt] < 350 )
  {
    digitalWrite(deployPinA, HIGH);
    digitalWrite(deployPinB, HIGH);
    //videoON();
  }
  if(sensorState == 2 && TeleArray[TeleAlt]<300)
  {
    digitalWrite(deployPinA, LOW);
    digitalWrite(deployPinB, LOW);
  }
  if(sensorState == 3)
  {
    videoOFF();
    startBuzzer();
    eepromCheck = 0;
  }
}

void receiveRadioData() {
  //Checks to see if commands have come in via radio
  if (Serial.available()) {
    String RadioReceive = Serial.readString();
    if(RadioReceive == "a")
    {
        digitalWrite(deployPinA, HIGH);
        digitalWrite(deployPinB, HIGH);
    }
  }
}

void timeDelay(){
  //Get the tilt every tentth of a second
  while (millis() - teleTime < 100){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 200){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 300){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 400){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 500){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 600){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 700){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 800){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 900){}
  getTilt();
  getGPS2();
  while (millis() - teleTime < 1000){}
}

