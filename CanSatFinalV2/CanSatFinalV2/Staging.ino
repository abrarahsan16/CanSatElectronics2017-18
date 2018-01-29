void setupConfigMode(){
  pinMode(6, INPUT);
  pinMode(5, INPUT);
}


void boot(){
  
  EEPROM.get(eeState, TeleArray[TeleState]);
  EEPROM.get(eePacket, TeleArray[TelePacketCount]);
  EEPROM.get(eeBaseAlt, baseAlt);

baseAlt = 388;

  //Check for reset from Pic
  EEPROM.get(eeSnapping, resetFromPic);
  EEPROM.get(eePicAttempt, picAttempt);

  if (resetFromPic == true){
    ++picAttempt;
  }
  
}



void checkAlt(float alt){
  
  if (alt <= 1.1 * lastAlt && alt >= 0.9 * lastAlt){
    constAlt = constAlt + 1;
  } else {
    lastAlt = alt;
  }
  
}

void checkFlown(float alt){
  
  if (alt > 50){
    hasFlown = true;
  }
  
}

void stateCheck(){

  checkFlown(TeleArray[TeleAltSensor]);//Did it fly
  checkAlt(TeleArray[TeleAltSensor]);//Is it still flying
 
  float s = Preflight;

  if (hasFlown == true){
    if(constAlt >= 10){
      s = Landed;
    } else {
      s = Flying;
    }  
  }
  
  TeleArray[TeleState] =  s;

  //////////////////DEBUG//////////////
  TeleArray[TeleState] =  Flying;
}


boolean checkConfigMode(){
  Debug("Checking Config Mode");
  boolean cm = false;

  if ( digitalRead(6) == HIGH){
    cm = true;
  }
  return cm;
}


void configMode(){

  Debug("Entering Confic Mode");

  while(digitalRead(5) ==  LOW){
    
  }

  Debug("Starting Config");
  
  rtc.setTime(0,0,0,0,0,0,0);
  baseAlt = bmp.readAltitude();
  EEPROM.put(eeBaseAlt, baseAlt);

  //Reset ExtEEPROM Address
  eeAddress_W = 0;
  EEPROM.put(eeExtAddress, eeAddress_W);
  
  float zero = 0.0;
  float pf = Preflight;
  EEPROM.put(eePacket, zero); //THIS DOESNT WORK YET
  EEPROM.put(eeState, pf);

  EEPROM.put(eeSnapping, (float) false);
  
  Debug("Set");
  tone(4, 800, 500);


}


void preDeploymentCheck(){
  pinMode(3, OUTPUT);
  pinMode(2, INPUT);

  digitalWrite(3, HIGH);
  
///////////////////////////////////////////////////////
int val = digitalRead(2);

  while(val == HIGH){
    Debug("Waiting for deployment");
    val = digitalRead(2);
    delay(100);
  }

  digitalWrite(3, LOW);

  Debug("Deployed");
  tone(4, 2000);
  delay(150);
  noTone(4);
  delay(850);

  teleTime = millis();
  
}





