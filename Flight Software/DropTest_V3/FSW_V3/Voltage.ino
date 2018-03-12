//Voltage

float vi; //Value of voltage supplied
float vo; //Value of voltage read from Arduino
float r1 = 10000; //Value of resistor 1
float r2 = 10000; //Value of resistor 2

void setupVoltage()
{
  pinMode(A0, INPUT);
}

void callVoltage()
{
  int sensorValue = analogRead(A0);
  
  // Converts the analog reading to a voltage between 0 - 5V
  //Only applicable as long as the voltage does not exceed 10V
  float vo = sensorValue * (5.0 / 1023.0);

  //Calculates vi using voltage division
  float vi = (vo * (r1 + r2)) / (r2); 
  
  //printing out vi
  //Serial.println(vi);
}

