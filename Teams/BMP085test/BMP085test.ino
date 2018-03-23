#include <SparkFunDS1307RTC.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SoftwareSerial.h>
SoftwareSerial radio(3, 2);




/*************************************************** 
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout 
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

// Connect VCC of the BMP085 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;
float vi; //Value of voltage supplied
float vo; //Value of voltage read from Arduino
float r1 = 10000; //Value of resistor 1
float r2 = 10000; //Value of resistor 2
float TeleArray[6];
  
void setup() {
  radio.begin(19200);
  rtc.setTime(0, 0, 0, 0, 0, 0, 0);
  Serial.begin(19200);
  if (!bmp.begin()) {
	radio.write("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  pinMode(A0, INPUT);
  
}


  
void loop() {
 
  rtc.update();
 int missionTime = rtc.getSecond() + 60*rtc.getMinute() + 3600*rtc.getHour(); //Time in seconds


   



  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.

    

    
    

    delay(500);
    int sensorValue = analogRead(A0);
 
 // Converts the analog reading to a voltage between 0 - 5V
 //Only applicable as long as the voltage does not exceed 10V
 float vo = sensorValue * (5.0 / 1023.0);

 //Calculates vi using voltage division
 float vi = (vo * (r1 + r2)) / (r2);

 // Serial.println(vi);
 TeleArray[0] = (missionTime);
 TeleArray[1] = (bmp.readTemperature());
 TeleArray[2] = (bmp.readAltitude());
 TeleArray[3] = (bmp.readSealevelPressure());
 TeleArray[4] = (bmp.readPressure());
 TeleArray[5] = (vi);
   for (int i = 0; i < 6; i++) {
radio.write(TeleArray[i]);
}
  }


