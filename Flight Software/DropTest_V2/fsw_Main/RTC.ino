void rtcBegin() {
  // put your setup code here, to run once:
  rtc.setTime(0, 0, 0, 0, 0, 0, 0);
  //Serial.println("RTC started");
}

void getTime() {
  // put your main code here, to run repeatedly:
  rtc.update();
  int missionTime = rtc.getSecond() + 60*rtc.getMinute() + 3600*rtc.getHour(); //Reads the time each loop in seconds
  telemetry[2] = missionTime;
}
