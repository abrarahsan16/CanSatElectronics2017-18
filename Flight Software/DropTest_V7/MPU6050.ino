/////////////////////////////////////////
/////// Credits to Warda Noman //////////
/////////////////////////////////////////

// Timers
float timeStep = 0.1;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

void setupMPU()
{
  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void getTilt()
{
  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();
  // Calculate Pitch, Roll and Yaw
  
  pitch = norm.YAxis * timeStep;
  roll =  norm.XAxis * timeStep;
  yaw = norm.ZAxis * timeStep;
  // Make sure the values stay within a range of 0 - 360
  if (pitch < 0){
    pitch = pitch + 360;
  }
  if (pitch > 360){
    pitch = pitch - 360;
  }
  if (roll < 0){
    roll = roll + 360;
  }
  if (roll > 360){
    roll = roll - 360;
  }
  if (yaw < 0){
    yaw = yaw + 360;
  }
  if (yaw > 360){
    yaw = yaw - 360;
  }
  TeleArray[TeleTiltX] = roll;
  TeleArray[TeleTiltY] = pitch;
  TeleArray[TeleTiltZ] = yaw;
}

