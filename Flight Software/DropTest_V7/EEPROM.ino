/////////////////////////////////////////////////
/////////// Credits to Jacky Luo ////////////////
/////////////////////////////////////////////////
// For Wiring, see http://www.learningaboutelectronics.com/Articles/24LC256-EEPROM-circuit-with-an-arduino.php
// In that link, 5V is used, but 3.3V works as well

float oldPacketCount;
int storeCounter = 0;

//this union is for converting floats into bytes for storing into the EEPROM
union{
  float fValue;
  byte bValue[4];
} floatToByte;

// This union is for converting the bytes back to floats to retrieve the data but mostly for testing
union {
  float fValue;
  byte bValue[4];
} byteToFloat;

// Use this function and it will cover everything for the EEPROM
// includes: what to do when the arduino resets and storing telemetry
void storeData()
{
  if (storeCounter < 500){
    if (dataReset() == true) // Need to retrieve old data
    {
      sensorState = readFloat(4); // Need the sensor state
      TeleArray[TeleState] = sensorState;
    }
    else
    {
      writeFloat(0, packetCount); 
      writeFloat(4, sensorState);
      writeFloat(8, seaLevelPressure);
    }
    // Always store the packet count and software state in case of the arduino resetting
    storeArray();
    storeCounter++;
  }
}

// This method checks if the arduino has reset by using the Packet Count
boolean dataReset()
{
  boolean answer;
  oldPacketCount = readFloat(0);
  // If the stored packet count is greater than 2 but the present packet count is 1
  // , the arduino must have reset
  if (packetCount == 1 && oldPacketCount > 2)
  {
    answer = true; // The arduino has reset
    packetCount = oldPacketCount; // Take the old packet count
    TeleArray[TelePacket] = packetCount; // If this line is not added, a packet count of 1 will be transmitted
    seaLevelPressure = readFloat(8); // Take the old sea level pressure to prevent negative altitudes
  }
  else
  {
    answer = false; // Arduino has not reset
  }
  return answer; 
}

// Prints the data to the Serial Monitor
void dataPrint(){
  int address;  
  Serial.print("0: "); // This one is for the packet count
  Serial.println (readFloat(0));
  Serial.print ("4: "); // This one is for the software state
  Serial.println (readFloat(4));
  Serial.print ("8: "); // This one is for the BMP sea level pressure
  Serial.println (readFloat(8));
  int startAddress = 16 + (TeleArrayLength * packetCount * 4);
  for (int i = 0; i < TeleArrayLength; i++)
  {
    address = startAddress + (i*4);
    Serial.print (address);
    Serial.print (": ");
    Serial.println(readFloat(startAddress + (i*4)));
  }
}

// This function only stores the telemetry array
void storeArray ()
{
  // The 16 in the starting address comes from always storing the packet count and software state and other stuff
  int startAddress = 16 + (TeleArrayLength * packetCount * 4);
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

// This function assumes that the next four bytes are a float from the starting address
float readFloat (int address)
{
  byteToFloat.bValue[0] = readAddress(address);
  address++;
  byteToFloat.bValue[1] = readAddress(address);
  address++;
  byteToFloat.bValue[2] = readAddress(address);
  address++;
  byteToFloat.bValue[3] = readAddress(address);
  float answer = byteToFloat.fValue;
  return answer;
}

// Writes a byte to an address in an external EEPROM
void writeAddress(int address, byte val)
{
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.write(val);
  Wire.endTransmission();
  // Delay must be at least 4 milliseconds, but 5 milliseconds is used just in case
  delay(5);
}

// Reads the address on the external EEPROM, which will be a byte
byte readAddress(int address)
{
  byte rData = 0xFF;
  Wire.beginTransmission(EEPROM_I2C_ADDRESS);
  Wire.write((int)(address >> 8));   // MSB
  Wire.write((int)(address & 0xFF)); // LSB
  Wire.endTransmission();  
  Wire.requestFrom(EEPROM_I2C_ADDRESS, 1);  
  rData =  Wire.read();
  return rData;
}
