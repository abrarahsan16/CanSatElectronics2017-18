// Xbee
void setupRadio()
{
  radio.begin(19200);
  
  //Pins should be declared in main file
}

void radioTransmit()
{
  //Send the TeleArray array values to the ground station
  for (int index = 0; index < sizeof(TeleArray); index++)
  {
    radio.write (TeleArray[index]);
  }
    
  if (radio.available())
  { 
    // If data comes in from XBee, change a certain variable
    
  }
}



