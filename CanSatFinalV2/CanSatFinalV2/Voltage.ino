void setupVoltage(){

  pinMode(A0, INPUT);
  
}

void callVoltage(){
  double vin = analogRead(vBus) * 3.3 / 1023.0;
  TeleArray[TeleVoltage] = vin * 5.3;
  
}

