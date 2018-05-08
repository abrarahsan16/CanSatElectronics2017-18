/////////////////////////////////////////////////
/////////// Credits to Jacky Luo ////////////////
/////////////////////////////////////////////////
// For Wiring, see http://www.learningaboutelectronics.com/Articles/24LC256-EEPROM-circuit-with-an-arduino.php
// No need to have parameters since everything should have been declared as global variables
int startAddress;
//this union is for converting floats into bytes for storing into the EEPROM
union{
  float fValue;
  byte bValue[4];
} floatToByte;

void storeArray ()
{
  startAddress = 0 + (TeleArrayLength * packetCount);
  for (int i = 0; i < TeleArrayLength; i++)
  {
    // The 4 in the next line comes from floats being composed of 4 bytes
    writeFloat(startAddress + (i*4), TeleArray[i]);
  }
}

// Since each address of an EEPROM can only hold a byte, a float must be split up and stored as separate bytes
void writeFloat(int address, float val)
{
  floatToByte.fValue = val;
  writeAddress(address, floatToByte.bValue[0]); 
  address++;
  writeAddress(address, floatToByte.bValue[1]); 
  address++;
  writeAddress(address, floatToByte.bValue[2]); 
  address++;
  writeAddress(address, floatToByte.bValue[3]); 
}

// Writes a byte to an address in an external EEPROM
void writeAddress(int address, byte val)
{
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  
   
  Wire.write(val);
  Wire.endTransmission();

  // Delay must be at least 4 seconds, but 5 seconds is used just in case
  delay(5);
}
