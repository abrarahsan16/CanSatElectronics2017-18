void setupBMP()
{
  if(!bmp.begin())
  {
    Serial.println("BMP Missing");
  }

}

void getTemp()
{
  TeleArray[TeleTemp] = bmp.readTemperature();
}

void getPressure()
{
  TeleArray[TelePressure] = bmp.readPressure();
}

void getAlt()
{
  TeleArray[TeleAlt] = bmp.readAltitude();
}

