
///////////////     NOTES     ////////////////////////
//  -Boots to Flying                                //
//////////////////////////////////////////////////////

//Libraries
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <HMC5883L.h>
#include <SparkFunDS1307RTC.h>


//Debug Code
//#define DEBUG
#ifdef DEBUG
 #define Debug(x) Serial.println(x)
#else
 #define Debug(x) 
#endif


bool magno = false;


//Definitions
#define TeleTeamID  0
#define TeleMissionTime 1
#define TelePacketCount 2
#define TeleAltSensor 3
#define TelePressure 4
#define TeleSpeed 5
#define TeleTemp 6
#define TeleVoltage 7
#define TeleHeading 8
#define TeleState 9
#define TeleNumPics 10
#define TeleArrayLength 11

#define RtcMissionTimeReg 0x08

//Pin Declarations
#define SS_Rx 3
#define SS_Tx 4
#define deployPin 7
#define pitotPin A0

#define xBeeSleepPin 8

#define TeamID 6082

#define pitotAddress 0x25
#define RTC_ADDRESS 0x68
#define EEPROM_ID 0x50
#define TeamID 6082

//EEPROM Addresses
#define eeState 0
#define eePacket 32
#define eeBaseAlt 64
#define eeExtAddress 96
#define eeSnapping 128
#define eePicAttempt 160
  
long eeAddress_W = 0;

//Constants
#define GLOBE_DEG -10
#define GLOBE_MIN 45



//Voltage Pins
#define vBus A0
#define vCamCap A1

//GlobalVariables
int packetCount = 0;
float TeleArray[TeleArrayLength];
long teleTime = millis();

int constAlt = 0;
float lastAlt = 0;
boolean hasFlown = false;
int takingPic = 0;
float resetFromPic = false;
float picAttempt = 0;

float baseAlt = 0;

//Software Serials
SoftwareSerial radio(SS_Rx, SS_Tx);

//SoftwareStes
#define Preflight 1
#define Flying 2
#define Landed 3

//Sensor Definitions
Adafruit_BMP085 bmp;
HMC5883L compass;


void setup() {

  //Power on Buzzer Tone
  setupBuzzer();

  //Setup Serial
  Serial.begin(19200);


  //Sensor Setup
  //setupPitot();
  //setupBMP();
  //setupMag();
  //setupRTC();
 // setupPitot();
  setupVoltage();
  setupCam();


  
}


void loop() {

  //Update All telemetery
  callPressure();
  callMagHeading();
  callAlt();
  callTemp();
  callRTC();
  callPitot();//////////////////////////////////Temp Corrected not done
  callVoltage();

  
///////////////////////////////////////////

   picCheck();
  


////////////////////////////////////////

  //Packets
  packetCount = packetCount + 1;
  TeleArray[TelePacketCount] = packetCount;

  timeDelay();
  teleTime = millis();

  transmitData_Serial();




  }




















