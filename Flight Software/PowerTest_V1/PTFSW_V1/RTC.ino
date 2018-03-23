void setupRTC()
{

  rtc.setTime(0, 0, 0, 0, 0, 0, 0); //Sets time to 0, basically mission time
}

void getTime()
{
  rtc.update();
  int missionTime = rtc.getSecond() + 60*rtc.getMinute() + 3600*rtc.getHour(); //Time in seconds
  TeleArray[TeleMissionTime] = missionTime;
}

