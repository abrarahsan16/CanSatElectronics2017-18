void setupRTC()
{
  rtc.setTime(0,0,0,0,0,0,0);
  //Serial.println("HI");
}

void getTime()
{
  rtc.update();
  int missionTime = rtc.getSecond() + 60*rtc.getMinute() + 3600*rtc.getHour(); //Time in seconds
  TeleArray[TeleMissionTime] = missionTime;
}

