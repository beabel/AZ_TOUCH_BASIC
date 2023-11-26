void ntp_GetTime(){
    //setup real time clock
    configTzTime(TZONE, ntp.c_str());
    //fill timestarukture ti, minutes and weekday with now
    getLocalTime(&ti);
    minutes = ti.tm_hour * 60 + ti.tm_min;
    weekday = ti.tm_wday; 
    Serial.printf("==>INFO NTP: %i:%i Day: %i\n",ti.tm_hour,ti.tm_min,ti.tm_wday);
    Serial.printf("==>INFO Variable: minutes= %i weekday = %i\n",minutes,weekday);
}