void setupRTC()
{
  if (readFloat(0) == 0){
    rtc.setTime(0,0,0,0,0,0,0);
  }
}

void getTime()
{
  rtc.update(); //Updates time from the RTC
  int missionTime = rtc.getSecond() + 60*rtc.getMinute() + 3600*rtc.getHour(); //Time in seconds
  TeleArray[TeleMissionTime] = missionTime;
}

