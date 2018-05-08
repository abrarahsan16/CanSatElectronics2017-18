void setupBuzzer()
{
  tone(buzzer, 3000, 150); //Sets the frequency and pin number
  noTone(5);
}

void startBuzzer()
{
  tone(5,3000); //Buzzing starts
}

