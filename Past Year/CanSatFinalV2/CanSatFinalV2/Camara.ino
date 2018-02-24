void setupCam(){
  pinMode(7, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(7, HIGH);

  if (picAttempt <= 2){
    digitalWrite(9, HIGH);
  } else {
    digitalWrite(9, LOW);
  }

  
  TeleArray[TeleNumPics] = 0;//////////////////////////////////////////////////////////////////////////////Fix
}


void picCheck() {

  //Checks if finished taking last pic
  if (takingPic >= 3) {
    takingPic = 0;
    TeleArray[TeleNumPics] = TeleArray[TeleNumPics] + 1;
    EEPROM.put(eeSnapping, (float) false);
    Debug("Done");
  }

  //If it's not tkaing a pic check voltage and take pic
  if (takingPic == 0) {
    float camCapVoltage = analogRead(vCamCap) * 3.3 / 1023.0;
  Debug(camCapVoltage);
    //2.69 -> Min Voltage to take pic
    if (camCapVoltage > 4.3 && picAttempt <= 2) {
      takePic();
      Debug("Taking Pic");
    }

  } else {
    takingPic = takingPic + 1;
  }

}


void takePic() {
  takingPic = 1;

  EEPROM.put(eeSnapping, (float) true);
   
  digitalWrite(7, LOW);
  delay(50);
  digitalWrite(7, HIGH);

}

