int check = 0;
float timer = 0;
void setupCamera()
{
  timer = millis();
  pinMode(cameraTrigger, OUTPUT);
  digitalWrite(cameraTrigger, HIGH);
  while (millis() - timer < 5000){}
  // Leave the video on the whole time
  digitalWrite(cameraTrigger, LOW);
}

//Turns camera on
void cameraON()
{
  digitalWrite(cameraTrigger, HIGH);
}

//Starts recording
void videoON()
{
  if (check == 0){
  digitalWrite(cameraTrigger, LOW);
  check = 1;
  }
}

//Stops recording
void videoOFF()
{
  digitalWrite(cameraTrigger, HIGH);
}

