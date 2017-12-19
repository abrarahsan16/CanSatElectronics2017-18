#include <Adafruit_BMP280.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>

Adafruit_BMP280 bmp;

float bpres, balt;

void setup() {
  // put your setup code here, to run once:
  bmp.begin(0x76);
  Serial.begin(9600);
  /*Determine base altitude and pressure and assign it to a variable*/
  bmp.readTemperature();
  bpres = bmp.readPressure();
  balt = bmp.readAltitude(1013.25);
}

void loop() {

    Serial.print(F("Altitude from base = "));
    Serial.print((bmp.readAltitude(1013.25))- balt); //Get current altitude from base by subtracting current alt from base alt
    Serial.println(" m");
    
    Serial.println();
    delay(2000);
}
