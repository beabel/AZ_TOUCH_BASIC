
#ifdef ENGLISH/*_____________________ ENGLISH _______________________*/
  //pref.h
  #define LANG_loadPreferences "Load Preferences"
  #define LANG_setPreferences "set pref: ssid= %i password = %i ntp = %i\n"
  //tft.h
  #define LANG_setBGLight "percent = %i LED = %i\n"
  #define LANG_TextInBox "Token %s Length %i total %s Length %i Line %i\n"
  #define LANG_OnTouchClick "Touch on %i, %i\n"
  #define LANG_ShowOtaProgress "Progress %i%%"
  //wlan.h
  #define LANG_InitWifi "Connect WiFi"
  #define LANG_WifiDisconnect "WIFI Disconnect"
  #define LANG_ApDisconnect "AP disconnect"
  #define LANG_SetWifiMode "Start WIFI Mode"
  #define LANG_TryConnectWifi "Try to connect WIFI: "
  #define LANG_WithPassword " with password: "
  #define LANG_NoConnectionStartAp "No Connection! \nStart Access-Point."
  #define LANG_ConnectionLost "Connection Lost !!!"
  //ota.h
  #define LANG_UpdateSketch "Updating Sketch"
  #define LANG_Done "Done"
  //test.h
  #define LANG_Connected "connected"
  #define LANG_NotConnected "Not connected"
  #define LANG_ConnectAp "Please connect to AP SSID:"
  #define LANG_ApIp "Call this IP:"
#else /*_____________________ GERMAN _______________________*/
  //pref.h
  #define LANG_loadPreferences "Lade Einstellungen"
  #define LANG_setPreferences "eingestellt: ssid= %i passwort = %i ntp = %i\n"
  //tft.h  
  #define LANG_setBGLight "prozent = %i LED = %i\n"
  #define LANG_TextInBox "Token %s Länge %i gesamt %s Länge %i Linie %i\n"
  #define LANG_OnTouchClick "Berührung bei %i, %i\n" 
  #define LANG_ShowOtaProgress "Fortschritt %i%%" 
  //wlan.h  
  #define LANG_InitWifi "Verbinde WLAN" 
  #define LANG_WifiDisconnect "WLAN trennen" 
  #define LANG_ApDisconnect "AP trennen" 
  #define LANG_SetWifiMode "Starte WLAN Modus" 
  #define LANG_TryConnectWifi "Versuche Wlan : "
  #define LANG_WithPassword " zu verbinden mit diesem Passwort: " 
  #define LANG_NoConnectionStartAp "Keine Verbindung! \nStarte Access-Point."
  #define LANG_ConnectionLost "Verbindung verloren !!!"    
  //ota.h   
  #define LANG_UpdateSketch "Update Sketch"
  #define LANG_Done "fertig"
  //test.h
  #define LANG_Connected "verbunden"
  #define LANG_NotConnected "nicht verbunden" 
  #define LANG_ConnectAp "Bitte verbinde dich mit AP SSID:"
  #define LANG_ApIp "Rufe dann diese IP auf:"      
#endif