void bmpBegin()
{
  if(!bmp.begin()){
    Serial.println("Could not find a valid BMP085 sensor");
    while(1){}
  }
}

void getTemp()
{
  telemetry[4] = bmp.readTemperature();
}

void getPressure()
{
  telemetry[5]=bmp.readPressure();
}

void getAlt()
{
  telemetry[6]=bmp.readAltitude();
}


