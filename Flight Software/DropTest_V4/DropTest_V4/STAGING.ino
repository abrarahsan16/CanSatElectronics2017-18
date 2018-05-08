void setupFunctions(){
  Wire.begin();
  setupBMP();
  setupBuzzer();
  setupCamera();
  setupGPS();
  setupMPU();
  setupRTC();
  setupVoltage();
}

void dataCollection(){
  getTime();
  TeleArray[TelePacket]=packetCount;
  getVolt();
  getTemp();
  getPressure();
  getAlt();
  getGPS();
  TeleArray[TeleState] = sensorState; 
  getTilt();
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
  if(alt>50){
    hasFlown = true;
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
  checkAlt(TeleArray[TeleAlt]); //is it still flying
  sensorState = PreFlight;

  if(hasFlown == true)
  {
    if(constAlt>=10)
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
    videoON();
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
  while(millis() - teleTime<(long)1000){}
}

