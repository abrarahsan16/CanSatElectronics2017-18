void setupBMP()
{
  if(!bmp.begin())
  {
    Serial.println("BMP Missing");
    while(1){} //If bmp is not found, it will not progress from this line. Remove it to avoid that
  }
}

void getTemp()
{
  teleArray[TeleTemp] = bmp.readTemperature();
}

void getPressure()
{
  teleArray[telePressure] = bmp.readPressure();
}

void getAlt()
{
  teleArray[teleAlt] = bmp.readAltitude();
}

