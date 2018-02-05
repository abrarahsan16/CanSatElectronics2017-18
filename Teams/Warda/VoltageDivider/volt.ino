float vout; //Voltage being read by the arduino
float vin; //Voltage being supplied

float r1= 4.7; //Change according to the value of the first resistor
float r2= 10; //Change according to the value of the second resistor

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);  //This gives the exact reading from the analogue pin
  vout=(sensorValue*5.0)/1023; //Converts the value to a number out of 5V
  vin=vout/(r2/(r1+r2)); //And uses voltage division to find the Voltage entering the circuit

  Serial.println(vin); //Prints the voltage
  //delay(100); 
}
