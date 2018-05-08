void setupCamera()
{
  pinMode(cameraTrigger, OUTPUT);
}

//Turns camera on
void cameraON()
{
  digitalWrite(cameraTrigger, HIGH);
}

//Starts recording
void videoON()
{
  digitalWrite(cameraTrigger, LOW);
}

//Stops recording
void videoOFF()
{
  digitalWrite(cameraTrigger, HIGH);
}

