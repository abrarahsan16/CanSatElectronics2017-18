/////////////////////////////////////////
/////// Credits to Warda Noman //////////
/////////////////////////////////////////

//Timers
unsigned long mpuTimer = 0;
float mpuTimeStep = 0.01;

//Pitch, Roll, Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

void setupMPU()
{
  //mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE)2G);
  mpu.calibrateGyro(); //Calibrate the gyroscope
  mpu.setThreshold(3); //Set Threshold sensitivity
}

void getTilt()
{
  mpuTimer = millis();

  //Read Normalized Values
  Vector norm = mpu.readNormalizeGyro();

  //Calculate Pitch, roll and yaw
  pitch = pitch + norm.YAxis * mpuTimeStep;
  roll = roll + norm.XAxis * mpuTimeStep;
  yaw = yaw + norm.ZAxis * mpuTimeStep;

  TeleArray[TeleTiltX] = roll;
  TeleArray[TeleTiltY] = pitch;
  TeleArray[TeleTiltZ] = yaw;
}

