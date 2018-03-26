//Used to test ground software with random but proper telemetery
#include <Servo.h>
//Telemertery data, They are just random
unsigned int TeamID = 1092; //1
unsigned long timer = 0;//2
unsigned long packetID = 0; // 3
float altitude = 0;//4 
float pressure = 0; //5
float temp;// = -10;//6
float voltage = 5;//7
float gTime = timer; //8
float latitude = 0; //9
float longitude = 0; //10
float gAlt = altitude;//11
float gSats = 3; //12
float tiltX = 5; //13
float tiltY = 10; //14
float tiltZ = 8; //15
float state = 1; //16
float deploy = 0;

float counter =0;
float altitudeStep = 0;



//Servo servo1;
void setup() {
  //servo1.attach(8);
  Serial.begin (19200);
  randomSeed(analogRead(0));
}



void loop() {
  ++packetID;
  ++counter;
  temp = random(95,105);
  altitudeStep = random(25,45);
  altitudeStep = altitudeStep/10;
  temp = -1.0*temp/(10.0);
  if (counter <=20) {
    altitude = altitude+altitudeStep;
    tiltX = random(0,180);
    tiltY = random(0,180);
    tiltZ = random(0,180);
  } else if (counter > 20 && counter <24) {
    altitude = altitude;
    tiltX = random(0,180);
    tiltY = random(0,180);
    tiltZ = random(0,180);
  } else if (counter>=24 && counter <=30){
    altitude = altitude-altitudeStep*3;
    tiltX = tiltX - 10;
    tiltY = tiltY - 10;
    tiltZ = tiltZ - 10;
  }
  gAlt = altitude;
 if (counter < 30) {
   Transmit_data();
 }
  delay (1000);
}

void Transmit_data (){
    ++timer;
  String toradio = "";
  toradio += TeamID;
  toradio += ",";
  toradio += timer;
  toradio += ",";
  toradio += packetID;
  toradio += ",";
  toradio += altitude;
  toradio += ",";
  toradio += pressure;
  toradio += ",";
  toradio += temp;
  toradio += ",";
  toradio += voltage;
  toradio += ",";
  toradio += gTime;
  toradio += ",";
  toradio += latitude;
  toradio += ",";
  toradio += longitude;
  toradio += ",";
  toradio += altitude;
  toradio += ",";
  toradio += gSats;
  toradio += ",";
  toradio += tiltX;
  toradio += ",";
  toradio += tiltY;
  toradio += ",";
  toradio += tiltZ;
  toradio += ",";
  toradio += state;

  Serial.println (toradio);
  
}


  
