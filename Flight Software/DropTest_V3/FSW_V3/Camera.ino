//Camera
void setupCamera()
{
  pinMode(trig, OUTPUT);
}

void cameraON()
{
  //Turns camera on
  digitalWrite(trig, HIGH);
}

void videoON()
{
  //Starts recording
  digitalWrite(trig, LOW);
}

void videoOFF()
{
  digitalWrite(trig, HIGH);
}
