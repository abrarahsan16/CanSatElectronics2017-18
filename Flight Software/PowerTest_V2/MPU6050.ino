

/*void mpuSetup()
{
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

void mpuLoop()
{
  mpuTime = millis();
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * mpuTimeStep;
  roll = roll + norm.XAxis * mpuTimeStep;
  yaw = yaw + norm.ZAxis * mpuTimeStep;

  TeleArray[TeleTiltX] = roll;
  TeleArray[TeleTiltY] = pitch;
  TeleArray[TeleTiltZ] = yaw;
}
*/
