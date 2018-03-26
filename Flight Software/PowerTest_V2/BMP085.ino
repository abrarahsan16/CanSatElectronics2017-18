void setupBMP()
{
  if(!bmp.begin())
  {
    Serial.println("BMP Missing");
    //while(1){} //If bmp is not found, it will not progress from this line. Remove it to avoid that
  }
  seaLevelPressure = bmp.readPressure();
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
  TeleArray[TeleAlt] = bmp.readAltitude(seaLevelPressure); //This is giving us height increase from where we start. So anypoint we start at, is taken as point 0.
}

