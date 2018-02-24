//////////////////////////////////////////////////////////////
// Credits to Warda Noman for testing and completion of this//
// Contact her for further information on this part         //
//////////////////////////////////////////////////////////////
void setupTilt()
{
  while(!compass.begin()) //Checks if HMC is available
  {
    Serial.println("Could not find a valid HMC5883L");
    //while(1){};
  }
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050");
    //while(1){}
  }
  //HMC setup
  compass.setRange(HMC5883L_RANGE_1_3GA); //Measurement Range
  compass.setMeasurementMode(HMC5883L_CONTINOUS); //Measurement Mode
  compass.setDataRate(HMC5883L_DATARATE_30HZ); //Data Rate
  compass.setSamples(HMC5883L_SAMPLES_8); //Number of samples averaged
  compass.setOffset(0,0); //Calibration offset, see HMC5883L_calibration.ino for more info

  //MPU setup
  mpu.calibrateGyro(); //Comment this line if we do not need to calibrate the gyroscope
  mpu.setThreshold(3); //Comment this line if we do not need to use threshold, or set to 0

  Wire.begin()  //Begin wire communication
  Wire.beginTransmission(0x68); //Send the slave address 68
  Wire.write(0x6B); //Make the reset(place a 0 into the 6B register)
  Wire.write(0x00); 
  Wire.endTransmission(true); //end transmission

  Wire.beginTransmission(0x68) //Start communication with the address found during search\
  Wire.write(0x1C); //we want to write to the ACCEL_CONFIG Register
  Wire.write(0x10); //Set the register bits as 00010000 (+/- 8g full scale range)
  Wire.endTransmission(true);
 
  
  //Acc Error calculation. Average of 200 values is taken
  if(acc_error==0)
  {
    for(int a=0;a<200;a++)
    {
      Wire.beginTransmission(0x68);
      Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
      Wire.endTransmission(false);
      Wire.requestFrom(0x68,6,true);

      Acc_rawX = (Wire.read() << 8 | Wire.read()) / 4096.0 ; //each value needs two registres
      Acc_rawY = (Wire.read() << 8 | Wire.read()) / 4096.0 ;
      Acc_rawZ = (Wire.read() << 8 | Wire.read()) / 4096.0 ;

      /*---X---*/
      Acc_angle_error_x = Acc_angle_error_x + ((atan((Acc_rawY) / sqrt(pow((Acc_rawX), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));
      /*---Y---*/
      Acc_angle_error_y = Acc_angle_error_y + ((atan(-1 * (Acc_rawX) / sqrt(pow((Acc_rawY), 2) + pow((Acc_rawZ), 2))) * rad_to_deg));
      /*---Z---*/
      Acc_angle_error_z = Acc_angle_error_z + ((atan(sqrt(pow((Acc_rawY), 2) + pow((Acc_rawX), 2) / (Acc_rawZ)) * rad_to_deg)));
      if (a == 199){
        Acc_angle_error_x = Acc_angle_error_x / 200;
        Acc_angle_error_y = Acc_angle_error_y / 200;
        Acc_angle_error_z = Acc_angle_error_z / 200;
        acc_error = 1;
      }
    }
  }//End of error calculation

  Wire.begin();                           //begin the wire comunication
  Wire.beginTransmission(0x68);           //begin, Send the slave adress (in this case 68)
  Wire.write(0x6B);                       //make the reset (place a 0 into the 6B register)
  Wire.write(0x00);
  Wire.endTransmission(true);             //end the transmission

  Wire.beginTransmission(0x68);           //begin, Send the slave adress (in this case 68)
  Wire.write(0x1B);                       //We want to write to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                       //Set the register bits as 00010000 (1000dps full scale)
  Wire.endTransmission(true);             //End the transmission with the gyro
  tilttime = millis();                        //Start counting time in milliseconds
}

void getTilt()
{
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
  //To set declination angle, go to http://magnetic-declination.com/
  //Formula: (deg + (min/60))/(180/M_PI)
  //Currently set for Toronto
  float declinationAngle = (-10 + (28/60))/(180/M_PI);
  heading +=declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {heading += 2 * PI;}
  if (heading > 2 * PI)
  {heading -= 2 * PI;}
  // Convert to degrees
  float headingDegrees = heading * 180 / M_PI;

  //Acc Read
  Wire.beginTransmission(0x68);     //begin, Send the slave adress (in this case 68)
  Wire.write(0x3B);                 //Ask for the 0x3B register- correspond to AcX
  Wire.endTransmission(false);      //keep the transmission and next
  Wire.requestFrom(0x68, 6, true);  //We ask for next 6 registers starting withj the 3B
  Acc_rawX = (Wire.read() << 8 | Wire.read()) / 4096.0 ; //each value needs two registres
  Acc_rawY = (Wire.read() << 8 | Wire.read()) / 4096.0 ;
  Acc_rawZ = (Wire.read() << 8 | Wire.read()) / 4096.0 ;
  /*Now in order to obtain the Acc angles we use euler formula with acceleration values
    after that we substract the error value found before*/
  /*---X---*/
  Acc_angle_x = (atan((Acc_rawY) / sqrt(pow((Acc_rawX), 2) + pow((Acc_rawZ), 2))) * rad_to_deg) - Acc_angle_error_x;
  /*---Y---*/
  Acc_angle_y = (atan(-1 * (Acc_rawX) / sqrt(pow((Acc_rawY), 2) + pow((Acc_rawZ), 2))) * rad_to_deg) - Acc_angle_error_y;
  /*---Z---*/
  Acc_angle_z = (atan(sqrt (pow((Acc_rawY), 2) + pow((Acc_rawX), 2)) / (Acc_rawZ)) * rad_to_deg) - Acc_angle_error_z;

/*timePrev = tilttime;                        // the previous time is stored before the actual time read
  tilttime = millis();                        // actual time read
  elapsedTime = (tilttime - timePrev) / 1000; //divide by 1000 in order to obtain seconds

  timer = millis();

  // Read normalized values
  Vector nor = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + nor.YAxis * timeStep;
  roll = roll + nor.XAxis * timeStep;
  yaw = yaw + nor.ZAxis * timeStep;

  // Output raw. Not sure if we NEED Pitch Roll or Yaw, but we have the steps for it
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);*/

  
  teleArray[teleTiltX] = Acc_angle_x;
  teleArray[teleTiltY] = Acc_angle_y;
  teleArray[teleTiltZ] = Acc_angle_z;
}

