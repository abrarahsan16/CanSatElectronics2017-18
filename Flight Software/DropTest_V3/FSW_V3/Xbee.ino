// Xbee
void setupRadio()
{
  radio.begin(9600);
  
  //Pins should be declared in main file
  //SoftwareSerial XBee(2, 3); // RX, TX
}

void radioTransmit()
{
  //Send the TeleArray array values to the ground station
  for (int index = 0; index < sizeof(TeleArray); index++)
  {
    XBee.write (TeleArray[index]);
  }
    
  if (XBee.available())
  { 
    // If data comes in from XBee, change a certain variable
    
  }
}



