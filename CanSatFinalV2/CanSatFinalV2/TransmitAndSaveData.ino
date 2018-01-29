
void transmitData_Serial() {

  //transmits data via serial & saves data to SD

  if (1 == 1) {
    Serial.print(TeamID);
    Serial.print(',');
    Serial.print("GLIDER");
    Serial.print(',');

    for (int telem = 1; telem < TeleArrayLength; telem++) {
      Serial.print(TeleArray[telem]);
      Serial.print(',');
    }
      Serial.print(-1);
    Serial.println();


    teleTime = millis();

    sleepRadio();
  }
}

void writeToEEPROM() {

  extEEPROMWrite(TeleArray, TeleArrayLength);
  EEPROM.put(eeState, TeleArray[TeleState]);
  EEPROM.put(eePacket, TeleArray[TelePacketCount]);
  EEPROM.put(eeExtAddress, eeAddress_W);
}

void receiveRadioData() {

  //Checks to see if commands have come in via radio
  if (radio.available()) {
    String RadioRecieve = Serial.readString();
    //Preform Task
  }

}




void timeDelay() {
  //delay
  while (millis() - teleTime < (long) 950) {}
  //wake xBee
  wakeRadio();
  while (millis() - teleTime < (long) 1000) {}
}

