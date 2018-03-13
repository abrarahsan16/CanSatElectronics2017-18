//Import Libraries
#include <Wire.h>
#include <stdint.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <HMC5883L.h>
#include <SparkFunDS1307RTC.h>


#define dataSize 10//Changeable, array size
#define GPSECHO false

//Global Variables
int second, min, hour; //Time variables for RTC
int teamID = 1234; //Random numbers
float missionID = 1.10; //Version number

int count=0; //Packet Count
float telemetry[dataSize]; //The array to be transmitted
int acc_error=0;                         //We use this variable to only calculate once the Acc data error
float rad_to_deg = 180/3.141592654;      //This value is for pasing from radians to degrees values
float Acc_rawX, Acc_rawY, Acc_rawZ;    //Here we store the raw data read 
float Acc_angle_x, Acc_angle_y, Acc_angle_z;          //Here we store the angle value obtained with Acc data
float Acc_angle_error_x, Acc_angle_error_y, Acc_angle_error_z; //Here we store the initial Acc data error
float elapsedTime, time, timePrev;        //Variables for time control
int gyro_error=0;                         //We use this variable to only calculate once the gyro data error
int16_t Gyr_rawX, Gyr_rawY, Gyr_rawZ;     //Here we store the raw data read 
float Gyro_angle_x, Gyro_angle_y, Gyro_angle_z;         //Here we store the angle value obtained with Gyro data
float Gyro_raw_error_x, Gyro_raw_error_y, Gyro_raw_error_z; //Here we store the initial gyro data error
uint32_t timer = millis();

//Declaring sensor
//SoftwareSerial mySerial(13, 12);
//This should be xbee, either change pins to 13 and 12 or keep at 3 and 4.
SoftwareSerial radio(3,4);

//Adafruit_GPS GPS(&mySerial);
Adafruit_BMP085 bmp;
HMC5883L compass;

boolean usingInterrupt = false;
void useInterrupt(boolean); 


void setup() {
  Serial.begin(9600); //Initializing Serial line
  Wire.begin();
  pinMode(3, OUTPUT); //Buzzer
  radio.begin(9600);
  tiltBegin();
  bmpBegin();
  rtcBegin();
  //GPSBegin();
  //setupRadio();

  //Assigning values
  telemetry[0] = teamID;
  telemetry[1] = missionID;
  //2 is time, 3 is count, 4 is temp, 5 is pressure, 6 is alt
}

void loop() {
  // put your main code here, to run repeatedly:
  getTime(); //Updates time
  telemetry[3] = ++count; //Updates Packet count
  getTemp();
  getPressure();
  getAlt();
  getHeading();
  //GPSloop();
  
  //Change this part to the xbee code you found.
  if (Serial.available())
  { // If data comes in from serial monitor, send it out to XBee
    radio.write(Serial.read());
  }
  if (radio.available())
  { // If data comes in from XBee, send it out to serial monitor
    Serial.write(radio.read());
  }

  //wakeRadio();
  
  
  //This should be inside the xbee code
  for(int i=0; i<dataSize; i++)
  {
    Serial.print(telemetry[i]);
    Serial.print(" ");
  }
  
  //startBuzz();  Temporarily not needed
  //Serial.println();
  //sleepRadio();
  delay(1000);
}
