//unsigned long HMCTime = 0;
//float HMCTimeStep = 0.01;

float pitch = 0;
float roll = 0 ;
float yaw = 0;
void HMCSetup()
{
  while(!compass.begin())
  {
    Serial.println("Could not find HMC");
  }
  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_15HZ);
  compass.setSamples(HMC5883L_SAMPLES_1);
}

void hmcLoop()
{
  Vector raw = compass.readRaw();
  Vector norm = compass.readNormalize();

  pitch = norm.YAxis;
  roll = norm.XAxis;
  yaw = norm.ZAxis;
  
  TeleArray[TeleTiltX] = roll;
  TeleArray[TeleTiltY] = pitch;
  TeleArray[TeleTiltZ] = yaw;  
}

