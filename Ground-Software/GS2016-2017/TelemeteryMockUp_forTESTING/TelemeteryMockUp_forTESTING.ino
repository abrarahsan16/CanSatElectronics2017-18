//Used to test ground software with random but proper telemetery
#include <Servo.h>
//Telemertery data, They are just random
unsigned int TeamID = 6082; //1. Done
String Glider = "GLIDER"; // 2
unsigned long timer = 0;//3.
unsigned long timer2 = timer;//3.
unsigned long packetID = 0; // 4
float altitude = 0;//5 
float pressure = 0; //6
float pitot_speed = 20;//7
float temp;// = -10;//8.
float voltage = 5;//9.
float heading = 58.23; //10
float state = 1; //11
float bonus = 1; //12
float pitch = -1;
float deploy = 0;
float latitude = 0;
float longitude = 0;
float checkTemp = 0;
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
    heading = random(0,360);
  } else if (counter > 20 && counter <24) {
    altitude = altitude;
    heading = random(0,360);
  } else if (counter>=24 && counter <=30){
    altitude = altitude-altitudeStep*3;
    heading = heading -1;
  }
  //if (counter < 11) {
    //Transmit_data2();
  //}
 //else //{
 if (counter < 30) {
   Transmit_data();
 }

 // if(Serial.available() > 0){
   // test= Serial.readString();
    //Serial.println(test);
    //packetID = test.toInt();
    //}
  //servo1.write(ServoPos);

  delay (1000);
}

void Transmit_data (){
    ++timer;
  String toradio = "";
  toradio += TeamID;
  toradio += ",";
  toradio += Glider;
  toradio += ",";
  toradio += timer;
  toradio += ",";
  toradio += packetID;
  toradio += ",";
  toradio += altitude;
  toradio += ",";
  toradio += pressure;
  toradio += ",";
   toradio += pitot_speed;
  toradio += ",";
   toradio += temp;
  toradio += ",";
  toradio += voltage;
  toradio += ",";
  toradio += heading;
  toradio += ",";
  toradio += state;
  toradio += ",";
  toradio += bonus;
  toradio += ",";
  toradio += bonus;


  Serial.println (toradio);


  
}

void Transmit_data2 (){
    ++timer2;
    if (timer2 == 10) {
      deploy =1;
    }
  String toradio = "";
  toradio += TeamID;
  toradio += ",";
  toradio += "CONTAINER";
  toradio += ",";
  toradio += timer2;
  toradio += ",";
  toradio += packetID;
  toradio += ",";
  toradio += altitude;
  toradio += ",";
  toradio += voltage;
  toradio += ",";
  toradio += state;
  toradio += ",";
  toradio += latitude;
  toradio += ",";
  toradio += longitude;
    toradio += ",";
  toradio += longitude;
      toradio += ",";
  toradio += longitude;
  Serial.println (toradio);
}

void Transmit_Emptydata (){
   ++timer2;
    if (timer2 == 10) {
      deploy =1;
    }
  String toradio = "";
  toradio += TeamID;
  toradio += ",";
  toradio += "CONTAINER";
  toradio += ",";
  toradio += timer2;
  toradio += ",";
  toradio += 0;
  toradio += ",";
  toradio += altitude;
  toradio += ",";
  toradio += pressure;
  toradio += ",";
  toradio += pitot_speed;
  toradio += ",";
  toradio += temp;
  toradio += ",";
  toradio += deploy;
  toradio += ",";
  toradio += latitude;
  toradio += ",";
  toradio += longitude;
  Serial.println (toradio);
}


  
