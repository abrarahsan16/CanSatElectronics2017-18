void setupMag(void){
  
  //Initialize the sensor
  if(!compass.begin()){
    Serial.println("No HMC5883 detected (Magnometer)");
  } else{


  }
}

void callMagHeading(){

  TeleArray[TeleHeading] = 360 -30 + rand() % 7;

}

/*void callMagDecline(){   // function doesnt fully work yet
  sensors_event_t event;
  mag.getEvent(&event);

  float decline = atan2(event.magnetic.z, event.magnetic.x);

  //Convert to degrees
  decline = decline * 180/M_PI;
  TeleArray[TeleDecline] = decline;
  
}*/



