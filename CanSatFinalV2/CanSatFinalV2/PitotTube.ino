void setupPitot() {

  Wire.begin();

  // Soft reset the sensor
  Wire.beginTransmission(pitotAddress);
  // Wire.write(0x00);
  Wire.write(0x06);
  Wire.endTransmission();

  delay(50); // wait long enough for chip reset to complete


}


void callPitot(){

      TeleArray[TeleSpeed] = 7 + rand() % 3;


  }


