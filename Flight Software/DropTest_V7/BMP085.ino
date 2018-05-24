void setupBMP()
{
  bmp.begin();
  seaLevelPressure = bmp.readPressure();
}

//Temperature
void getTemp()
{
  TeleArray[TeleTemp] = bmp.readTemperature(); 
}

//Pressure
void getPressure()
{
  TeleArray[TelePressure] = bmp.readPressure();
}

//Altitude
void getAlt()
{
  TeleArray[TeleAlt] = bmp.readAltitude(seaLevelPressure);
}

