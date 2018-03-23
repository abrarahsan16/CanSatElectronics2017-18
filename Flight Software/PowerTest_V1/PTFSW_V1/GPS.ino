void setupGPS()  
{
  GPS.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  GPS.sendCommand(PGCMD_ANTENNA);

  useInterrupt(true);

  delay(1000);
  //mySerial.println(PMTK_Q_RELEASE);
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void GPSLoop()                     
{

  if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  if (GPS.newNMEAreceived()) {
  
    if (!GPS.parse(GPS.lastNMEA()))   
      return;  
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    Serial.print("<Time: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.print(">\n");
    if (GPS.fix) {
      Serial.print("<Latitude: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(">\n"); 
      Serial.print("<Longitude: ");
      Serial.print(GPS.longitude, 4); Serial.print(GPS.lon);
      Serial.print(">\n"); 
      Serial.print("<Altitude: "); Serial.print(GPS.altitude); Serial.print(">\n");
      Serial.print("<Satellites: "); Serial.print((int)GPS.satellites); Serial.print(">\n\n");
    }
  }
}
