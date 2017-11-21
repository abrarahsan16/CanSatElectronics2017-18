// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
#include <stdint.h>
#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include <SparkFunDS1307RTC.h>
//These are needed for the HMC Magnometer
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


BME280 mySensor;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

#define PRINT_USA_DATE

#define SQW_INPUT_PIN 7   // Input pin to read SQW
#define SQW_OUTPUT_PIN 13 // LED to indicate SQW's state

SoftwareSerial XBee(2, 3); // RX, TX

void setup()
{
  
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;
  
  //renMode can be:
  //  0, Sleep mode
  //  1 or 2, Forced mode
  //  3, Normal mode
  mySensor.settings.runMode = 3; //Normal mode
  
  //tStandby can be:
  //  0, 0.5ms
  //  1, 62.5ms
  //  2, 125ms
  //  3, 250ms
  //  4, 500ms
  //  5, 1000ms
  //  6, 10ms
  //  7, 20ms
  mySensor.settings.tStandby = 0;
  
  //filter can be off or number of FIR coefficients to use:
  //  0, filter off
  //  1, coefficients = 2
  //  2, coefficients = 4
  //  3, coefficients = 8
  //  4, coefficients = 16
  mySensor.settings.filter = 0;
  
  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.tempOverSample = 1;

  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    mySensor.settings.pressOverSample = 1;
  
  //humidOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.humidOverSample = 1;
  
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  XBee.begin(9600);
  Serial.begin(9600);

  mySensor.begin();
  
  pinMode(SQW_INPUT_PIN, INPUT_PULLUP);
  pinMode(SQW_OUTPUT_PIN, OUTPUT);
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));
  rtc.begin();
  rtc.writeSQW(SQW_SQUARE_1);
  rtc.setTime(0, 0, 0, 0, 0, 0, 0);

  Serial.println("HMC5883 Magnetometer Test"); Serial.println(""); //HMC
  
  /* Initialise the sensor */
  if(!mag.begin()) //HMC
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  
}

void loop()
{

  static int8_t lastSecond = -1;
  rtc.update();

  sensors_event_t event;  //HMC
  mag.getEvent(&event); //HMC

   if (rtc.second() != lastSecond) // If the second has changed
  {
    printTime(); // Print the new time

    lastSecond = rtc.second(); // Update lastSecond value
  }

  // Read the state of the SQW pin and show it on the
  // pin 13 LED. (It should blink at 1Hz.)
  digitalWrite(SQW_OUTPUT_PIN, digitalRead(SQW_INPUT_PIN));
  

  XBee.print("< Altitude: ");
  XBee.print((mySensor.readFloatAltitudeMeters() + 114), 2);
  XBee.print(">");
  
  
  XBee.print("< Pressure: ");
  XBee.print(mySensor.readFloatPressure(), 2);
  XBee.print(">");
  
  XBee.print("< Temperature: ");
  XBee.print(mySensor.readTempC(), 2);
  XBee.print(">");

  XBee.print("\n");

  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  "); //HMC
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  
  
  delay(1000);  

}

void printTime()
{
  XBee.print("<" + String(rtc.second()) + ">\n");


  // Print second

}


