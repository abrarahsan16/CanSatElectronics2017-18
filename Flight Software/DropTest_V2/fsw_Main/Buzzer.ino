void startBuzz()
{
  if(telemetry[3] == 5){
    digitalWrite(5, HIGH);
  }

  if (telemetry[3] == 10){
    digitalWrite(5, LOW);
  }
}

