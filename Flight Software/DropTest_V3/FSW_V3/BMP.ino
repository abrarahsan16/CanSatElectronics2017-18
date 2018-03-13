void setupBMP()
{
  if(!bmp.begin())
  {
    Serial.println("BMP Missing");
    //while(1){} //If bmp is not found, it will not progress from this line. Remove it to avoid that
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

