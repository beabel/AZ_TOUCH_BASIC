/*______Import Libraries_______*/
#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>
#include <ArduinoOTA.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <TouchEvent.h>
/*______End of Libraries_______*/
#include "00_font.h"
#include "00_settings.h"
#include "01_lang.h"
#include "02_pref.h"
#include "03_tft.h" 
#include "04_wlan.h"
#include "05_ntp.h"
#include "06_web.h"
#include "07_ota.h"

#include "50_test.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start setup ########################");  
  pref_GetValues();
  //setup display
  tft_SetupDisplay();
  connected = wlan_InitWiFi(ssid, pkey);
  test_ShowSetupWLAN();   
  if (connected) { //successful connection
    //setup real time clock
    ntp_GetTime();
  } else { //connection not successful
    //remember current tick count to allow
    //a retry after five minutes disconnected
    discon = millis();
  }

  //setup the web server
  web_SetupWebserver();
  ota_Setup();
  //remember the tick count for the timed event
  tick = millis();  
  Serial.println("Ende setup ########################");     
}

void loop() {
  // put your main code here, to run repeatedly:
  //Check over the air update
  ArduinoOTA.handle();  
  //Check for http requests
  web_Loop();
  //check for touch events
  tft_TouchLoop();  
  //detect a disconnect
  wlan_DetectConnectionLost();
  //timed event update time every minute  
  if ((millis() - tick) > 60000) {
    //get date and time information
    if (connected  && getLocalTime(&ti)) {
      minutes = ti.tm_hour * 60 + ti.tm_min;
      weekday = ti.tm_wday;
    }
    tick = millis() - ti.tm_sec * 1000;//kingherold ISSUE Time not correct
  }  
  //do a restart if device was disconnected for more then 5 minutes
  if (!connected && ((millis() - discon) > 300000)) ESP.restart();  
}
