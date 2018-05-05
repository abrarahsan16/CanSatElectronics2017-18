//Code for power testing

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

#define TeleArrayLength 16
#define TeamID 1092

#define voltageBus A0
#define GPS_SS_Rx 3
#define GPS_SS_Tx 4
//#define XBEE_SS_Rx 4
//#define XBEE_SS_Tx 3

int packetCount = 0;
float TeleArray[TeleArrayLength];

//SoftwareSerial XBee(XBEE_SS_Rx, XBEE_SS_Tx);
SoftwareSerial gpsserial(GPS_SS_Rx, GPS_SS_Tx);

Adafruit_BMP085 bmp;
HMC5883L compass;
MPU6050 mpu;
Adafruit_GPS GPS(&gpsserial);
float seaLevelPressure;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
 // XBee.begin(19200);
  setupFunctions();
}

void loop() {
  // put your main code here, to run repeatedly:
  packetCount++;
  collectData();
  printData();
  delay(1000);
}
