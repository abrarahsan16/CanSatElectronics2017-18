/////////////////////////////////////////
////////  CanSat Team         ///////////
////////  Tomahawk 2017-2018  ///////////
/////////////////////////////////////////
/////////////////////////////////////////

//Import Libraries
#include <Wire.h>
#include <stdint.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_HMC5883_U.h>
#include <HMC5883L.h>
#include <MPU6050.h>
#include <SparkFunDS1307RTC.h>

//TeleArray Position
#define TeleID 0
#define TeleMissionTime 1 //RTC Time
#define TelePacket 2 //Number of times the telemetry has been transmitted
#define TeleAlt 3 //BMP Altitude
#define TelePressure 4 //BMP Pressure
#define TeleTemp 5 //BMP Temperature
#define TeleVolt 6 //Analog Voltage Reader
#define TeleGTime 7 //GPS Time
#define TeleGLat 8 //GPS Latitude
#define TeleGLong 9 //GPS Longitude
#define TeleGAlt 10 //GPS Altitude
#define TeleGSats 11 //GPS Number of Satellites
#define TeleTiltX 12 //Tilt X
#define TeleTiltY 13 //Tilt Y
#define TeleTiltZ 14 //Tilt Z
#define TeleState 15 //Flight Staging

#define TeleArrayLength 16 //Array Length
#define TeamID 1092 //Team ID

//Pin Declaration
#define voltageBus A0 //Analog Voltage Reader
#define cameraTrigger 2 //Camera Trigger Pin
#define GPS_SS_Rx 3 
#define GPS_SS_Tx 4
#define deployPinA 7
#define deployPinB 8
#define buzzer 9
#define EEPROM_I2C_ADDRESS 0x50 //pins for EEPROM

//Software States
#define PreFlight 1
#define Flying 2
#define Landed 3

//Sensor Declaration
SoftwareSerial gpsSerial(GPS_SS_Rx, GPS_SS_Tx); 
//HMC5883L compass; //HMC initialization, don't think we need it
Adafruit_BMP085 bmp;  //BMP Initialization
MPU6050 mpu;  //MPU Initialization
Adafruit_GPS GPS(&gpsSerial); //GPS Initialization

//Global Variables
int packetCount = 0;
float TeleArray[TeleArrayLength];
float seaLevelPressure;
int sensorState;
long teleTime = millis();

//State Check Variables
int constAlt = 0;
float lastAlt = 0;
boolean hasFlown = false;

void setup(){
  Serial.begin(19200);
  pinMode(deployPinA, OUTPUT);
  pinMode(deployPinB, OUTPUT);
  setupFunctions();
}

void loop(){
  packetCount++;
  dataCollection();
  stateCheck();
  checkBurn();
  transmitData();
  timeDelay();
  teleTime = millis();
}

