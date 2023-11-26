//connect to the WLAN
boolean wlan_InitWiFi(String ssid, String pkey) {
    Serial.println(LANG_InitWifi);
    boolean connected = false;
    //first disconnect
    Serial.print(LANG_WifiDisconnect);
    WiFi.disconnect();
    Serial.print(LANG_ApDisconnect);
    WiFi.softAPdisconnect(true);
    Serial.print(LANG_SetWifiMode);
    //satrt station mode
    WiFi.setHostname(HOSTNAME); //define hostname
    WiFi.mode(WIFI_STA);
    Serial.print(LANG_TryConnectWifi);
    Serial.println(ssid);
    Serial.print(LANG_WithPassword);
    Serial.println(pkey);
    //if we have a config we try to connect
    if (ssid != "") {   
      WiFi.begin(ssid.c_str(),pkey.c_str());
      uint8_t cnt = 0;
      while ((WiFi.status() != WL_CONNECTED) && (cnt<20)){
        delay(500);
        Serial.print(".");
        cnt++;
      }
      Serial.println();
      if (WiFi.status() == WL_CONNECTED) {
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        connected = true;
      }
    }
    //if we have no connection /no config or wrong config)
    //we start an access point to allow configuration
    if (!connected) {
       Serial.println(LANG_NoConnectionStartAp);
          WiFi.mode(WIFI_AP);
          WiFi.softAP(AP_NAME,"",1);
    }
    return connected;
}

void wlan_DetectConnectionLost(){
  //detect a disconnect
  if (connected && (WiFi.status() != WL_CONNECTED)){
    connected = false;
    //remember tick count for automatic retry
    discon = millis();
    Serial.printf("==>INFO Variable: connected= %i discon = %i weekday = %i\n",connected,discon,weekday);
    Serial.println(LANG_ConnectionLost);
  }  
}