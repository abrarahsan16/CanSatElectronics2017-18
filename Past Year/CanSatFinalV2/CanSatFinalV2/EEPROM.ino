///////////////////////////////////////////////////////////////////////
//                         Instructions                              //
///////////////////////////////////////////////////////////////////////

//Writing Float Array to External EEPROM
//extEEPROMWrite(Address of Array, Number of Values)

//Reading All of External EERPOM
//extEEPROMRead()

//Writing Float to Internal EEPEOM
//EEPROM.put(Address, Variable)

//Reading Float from Internal EEPROM
//EEPROM.get(Address, Variable to store value in)



///////////////////////////////////////////////////////////////////////
//                 Writing Float Arrays to EEPROM                    //
///////////////////////////////////////////////////////////////////////

void extEEPROMRead(long numValues) {
  float value;
  long eeAddress_R = 0;
  //long numValues = 64000; //256000 / sizeof(float)
  for (long i = 0; i <= numValues; i++) {
    if (eeAddress_R + sizeof(float) >= 256000) {
      eeAddress_R = 0;
    }
    EEPROM_readAnything(eeAddress_R, value);
    if (value == (float) - 888.0) {
      Serial.print("\n");
    } else {
      Serial.print(value, DEC);
      Serial.print(",");
    }
    eeAddress_R += sizeof(float);
  }
}

void extEEPROMWrite(float data[], int dataSize) {
  for (int i = 0; i < dataSize; i++) {
    if (eeAddress_W + sizeof(float) >= 256000) {
      eeAddress_W = 0;
    }
    EEPROM_writeAnything(eeAddress_W, data[i]);
    eeAddress_W += sizeof(float);
  }
  EEPROM_writeAnything(eeAddress_W, (float) - 888.0);
  eeAddress_W += sizeof(float);
  //Stores current ext EEPROM location in the internal eeprom
  EEPROM.put(eeExtAddress, eeAddress_W);
}

///////////////////////////////////////////////////////////////////////
//                 Writing Variables to EEPROM                       //
///////////////////////////////////////////////////////////////////////


template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
  const byte* p = (const byte*)(const void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    EXTwriteEEPROM_byte(EEPROM_ID, ee++, *p++);
  return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value)
{
  byte* p = (byte*)(void*)&value;
  unsigned int i;
  for (i = 0; i < sizeof(value); i++)
    *p++ = EXTreadEEPROM_byte(EEPROM_ID, ee++);
  return i;
}


///////////////////////////////////////////////////////////////////////
//                 Writing Bytes to EEPROM                           //
///////////////////////////////////////////////////////////////////////


void EXTwriteEEPROM_byte(int deviceaddress, unsigned int eeaddress, byte data )
{
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.write(data);
  Wire.endTransmission();

  delay(5);
}

byte EXTreadEEPROM_byte(int deviceaddress, unsigned int eeaddress )
{
  byte rdata = 0xFF;

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));
  Wire.write((int)(eeaddress & 0xFF));
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress, 1);

  if (Wire.available()) rdata = Wire.read();

  return rdata;
}

///////////////////////////////////////////////////////////////////////////////
//Internal EEPROM Saving
template <class T> int intEEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

template <class T> int intEEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}




