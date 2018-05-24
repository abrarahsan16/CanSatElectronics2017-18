///////////////////////////////////////////
/////// Voltage Divider Circuit ///////////
///////////////////////////////////////////

float vi; //Value of voltage supplied
float vo; //Value of voltage read from Arduino
float r1 = 9100; //Resistor 1
float r2 = 1000; //Resistor 2

void setupVoltage()
{
  pinMode(A0, INPUT); //Analog pin initialization
}

void getVolt()
{
  int sensorValue = analogRead(A0);

  //Converts the analog reading to a voltage between 0-5V
  //Only applicable if the voltage between the resistors
  //Does not exceed 10V

  float vo = sensorValue * (5.0/1023.0);

  //Calculates vi using voltage division
  float vi = (vo * (r1 + r2))/(r2);
  TeleArray[TeleVolt] = vi;
}

