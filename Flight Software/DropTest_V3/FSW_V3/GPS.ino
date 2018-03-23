//// This code will not work since GPSECHO has not been declared anywhere
//// There is no existing function for .seconds to get time; perhaps its called something else?
//
//void setupGPS()
//{
//  GPS.begin(19200);
//  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
//  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
//  GPS.sendCommand(PGCMD_ANTENNA);
//  useInterrupt(true); 
//  PMTK_Q_RELEASE;
//}
//
//SIGNAL(TIMER0_COMPA_vect) {
//  char c = GPS.read();
//  // if you want to debug, this is a good time to do it!
//#ifdef UDR0
//  if (GPSECHO)
//    if (c) UDR0 = c;  
//    // writing direct to UDR0 is much much faster than Serial.print 
//    // but only one character can be written at a time. 
//#endif
//}
//
//void useInterrupt(boolean v) {
//  if (v) {
//    // Timer0 is already used for millis() - we'll just interrupt somewhere
//    // in the middle and call the "Compare A" function above
//    OCR0A = 0xAF;
//    TIMSK0 |= _BV(OCIE0A);
//    usingInterrupt = true;
//  } else {
//    // do not call the interrupt function COMPA anymore
//    TIMSK0 &= ~_BV(OCIE0A);
//    usingInterrupt = false;
//  }
//}
//
//void GPSLoop()
//{
//  // in case you are not using the interrupt above, you'll
//  // need to 'hand query' the GPS, not suggested :(
//  if (! usingInterrupt) {
//    // read data from the GPS in the 'main loop'
//    char c = GPS.read();
//    // if you want to debug, this is a good time to do it!
//    if (GPSECHO)
//      if (c) Serial.print(c);
//  }
//  // if a sentence is received, we can check the checksum, parse it...
//  if (GPS.newNMEAreceived()) {
//    // a tricky thing here is if we print the NMEA sentence, or data
//    // we end up not listening and catching other sentences! 
//    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
//    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
//  
//    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
//      return;  // we can fail to parse a sentence in which case we should just wait for another
//  }
//  /*//I currently do not believe we need this part, but still need to investigate
//  // if millis() or timer wraps around, we'll just reset it
//  if (gpstimer > millis())  timer = millis();
//  if (millis() - timer > 2000) { 
//  timer = millis(); // reset the timer
//  }*/
//
//  TeleArray[TeleGTime] = (GPS.second,DEC) + 60*(GPS.minute,DEC) + 3600*(GPS.hour,DEC);
//  TeleArray[TeleGLat] = (GPS.latitude, 4); //need to test
//  TeleArray[TeleGLong] = (GPS.longitude, 4); //need to test
//  TeleArray[TeleGAlt] = (GPS.altitude);
//  TeleArray[TeleGSats] = (GPS.satellites);
//
//}

