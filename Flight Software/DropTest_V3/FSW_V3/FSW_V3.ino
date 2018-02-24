////////////////Notes///////////////////
///                                  ///
///Each variable will have a comment ///
///beside it, stating its use.       ///
///Read well.                        ///
///                                  ///
////////////////////////////////////////

//Libraries
#include <Wire.h>
#include <stdint.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <HMC5883L.h>
#include <MPU6050.h>
#include <SparkFunDS1307RTC.h>

//Definitions: Position of each array variable
#define TeleID 0
#define TeleMissionTime 1
#define TelePacket 2
#define TeleAlt 3
#define TelePressure 4
#define TeleTemp 5
#define TeleVolt 6
#define TeleGTime 7
#define TeleGLat 8
#define TeleGLong 9
#define TeleGAlt 10
#define TeleGSats 11
#define TeleTiltX 12
#define TeleTiltY 13
#define TeleTiltZ 14
#define TeleState 15

#define teleArrayLength 16 //Array Length
#define TeamID 1092
#define voltageBus A0 //Use this pin to find the voltage of the battery
#define SS_Rx 3
#define SS_Tx 4

//Debugger: When 0, prints to serial monitor. When 1, prints to Xbee
int debugger = 0;

//Global Variables
int packetCount = 0; //Count of how many times everything has run
float TeleArray[TeleArrayLength]; //Array to be transmitted
//long teleTime = millis();
float baseAlt = 0;
//int second, min, hour; //Variables for RTC

//Tilt Variables: Credits to Warda on this
int acc_error = 0; //Variable used only to calculate once the Acc data error
float rad_to_degree = [180/3.141592654]; //To convert radians to degrees
float Acc_rawX, Acc_rawY, Acc_rawZ; //Here we store the raw data read
float Acc_angle_x, Acc_angle_y, Acc_angle_z; //Here we store the angle value obtained with Acc data
float Acc_angle_error_x, Acc_angle_error_y, Acc_angle_error_z; //Initial Acc data error
float elapsedTime, tilttime, timePrev; //Variables for time control
float gpstimer;

//Timers
unsigned long timer = 0;
float timeStep = 0.01;

//Pitch, roll, yaw
float pitch = 0;
float roll = 0;
float yaw = 0;

//For the GPS
boolean usingInterrupt = false;
void useInterrupt(boolean); 

SoftwareSerial mySerial(SS_Rx, SS_Tx);

//Sensors
Adafruit_GPS GPS(&mySerial);
Adafruit_BMP085 bmp;
HMC5883L compass;
MPU6050 mpu;

//SoftwareState
#define Preflight 1 //On the ground
#define Flying 2 //Going up
#define Dropping 3 //Going down
#define Landed 4 //Back on the ground

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  setupFunctions();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  packetCount++;
  teleArray[telePacket] = packetCount;

  transmitData_Serial();
}
