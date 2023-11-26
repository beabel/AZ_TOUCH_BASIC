void test_ShowSetupWLAN(){
  char txt[100] = "";
  //Try to connect WLAN show progress on display 
  tft_DisplayClear();
  tft_TextInBox(5, 10, 310, 30, LANG_InitWifi, ALIGNCENTER, true, ILI9341_YELLOW, COLOR_BG,1);
  tft_TextInBox(5, 50, 310, 30, ssid.c_str(), ALIGNCENTER, true, ILI9341_GREEN, COLOR_BG,1);
  if (connected) { //successful connection
    tft_TextInBox(5, 80, 310, 30, LANG_Connected, ALIGNCENTER, true, ILI9341_GREEN, COLOR_BG,1);  
  }else{   
    tft_DisplayClear();
    tft_TextInBox(5, 10, 310, 30, LANG_NotConnected, ALIGNCENTER, true, ILI9341_RED, COLOR_BG,1);
    tft_TextInBox(5, 60, 310, 30, LANG_ConnectAp, ALIGNCENTER, false, ILI9341_WHITE, COLOR_BG,1);
    tft_TextInBox(5, 90, 310, 30, AP_NAME, ALIGNCENTER, false, ILI9341_GREEN, COLOR_BG,1);
    tft_TextInBox(5, 120, 310, 30, LANG_ApIp, ALIGNCENTER, false, ILI9341_WHITE, COLOR_BG,1);
    tft_TextInBox(5, 150, 310, 30, WiFi.softAPIP().toString().c_str(), ALIGNCENTER, false, ILI9341_GREEN, COLOR_BG,1);    
  }
}