void setupRadio(){
  sleepRadio();
}

void sleepRadio(){
  pinMode(8, INPUT);
  digitalWrite(8, HIGH);
}

void wakeRadio(){
  pinMode(8, OUTPUT);
 digitalWrite(8, LOW);
}

