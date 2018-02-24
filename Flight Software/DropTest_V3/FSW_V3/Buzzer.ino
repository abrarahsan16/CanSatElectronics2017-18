void setupBuzzer()
{
  //Do not need a MOSFET infront of buzzer for now. This should run normally now
  tone(5, 2000, 150);
  noTone(5);
}

void startBuzzer()
{
  tone(5, 2000);
}

