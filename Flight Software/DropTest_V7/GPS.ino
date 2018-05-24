/////////////////////////////////////////////////
//////// Credits to Guy Gidalevich //////////////
/////////////////////////////////////////////////

#define GPSECHO false
boolean usingInterrupt = false;
float gpsTimer;

void useInterrupt(boolean); //Func prototypekeeps Arduino happy

void setupGPS()
{
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  useInterrupt(true);
  gpsTimer = millis();
}

SIGNAL(TIMER0_COMPA_vect){
  char c = GPS.read();
  #ifdef UDR0
    if(GPSECHO)
      if(c)
        UDR0 = c;
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

void getGPS()
{
     if (millis() - gpsTimer > 2000){
    gpsTimer = millis();
    
    TeleArray[TeleGTime] = GPS.hour*3600 + GPS.minute*60 + GPS.seconds;
    
    if (GPS.fix) {
      TeleArray[TeleGLat] = GPS.latitudeDegrees;
      TeleArray[TeleGLong] = GPS.longitudeDegrees;
      TeleArray[TeleGAlt] = GPS.altitude;
      TeleArray[TeleGSats] = GPS.satellites;
    }
  }
}

void getGPS2(){
  if (! usingInterrupt) {
      char c = GPS.read();
      if (GPSECHO)
      if (c) Serial.print(c);
    }
  
    if (GPS.newNMEAreceived()) {
  
      if (!GPS.parse(GPS.lastNMEA()))   
        return;  
    }
}

