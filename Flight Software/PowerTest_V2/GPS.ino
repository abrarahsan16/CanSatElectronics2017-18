#define GPSECHO false
boolean usingInterrupt = false;
void useInterrupt(boolean); //Func prototype keeps arduino 0023 happy

void gpsSetup()
{
  GPS.begin(19200);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   
  GPS.sendCommand(PGCMD_ANTENNA);

  useInterrupt(true);
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
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
uint32_t timer = millis();
void gpsLoop()
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

    TeleArray[TeleGTime] = GPS.hour*3600 + GPS.minute*60 + GPS.seconds;
    
    if (GPS.fix) {
      TeleArray[TeleGLat] = GPS.latitude;
      TeleArray[TeleGLong] = GPS.longitude;
      TeleArray[TeleGSats] = GPS.altitude;
      TeleArray[TeleGTime] = GPS.satellites;
    }
  }
}
