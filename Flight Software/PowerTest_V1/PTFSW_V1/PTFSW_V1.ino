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
#define gpsRX 4
#define gpsTX 3
#define xbeeDIN 6
#define xbeeDOUT 5

int packetCount = 0;
float TeleArray[TeleArrayLength];

SoftwareSerial gpsserial(gpsRX, gpsTX);
SoftwareSerial radio(xbeeDOUT, xbeeDIN);

Adafruit_GPS GPS(&gpsserial);
Adafruit_BMP085 bmp;
//HMC5338L compass;
MPU6050 mpu;


#define GPSECHO  false

boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
}
uint32_t timer = millis();

unsigned long mputimer = 0;
float timeStep = 0.01;
float pitch = 0;
float roll = 0;
float yaw = 0;


void setup()
{
  Serial.begin(9600);
  //radio.begin(19200);
  setupFunctions();
}

void loop()
{
  collectData();
  packetCount++;
  Serial.print(TeleArray[0]);
  Serial.print(", ");
  //printTelemetry();
  delay(1000);
}


