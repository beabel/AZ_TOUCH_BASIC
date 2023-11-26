uint32_t oldprc;

//on start decide between program or file upload
void ota_onStart() {
  oldprc = 0;
  String type;
  if (ArduinoOTA.getCommand() == U_FLASH)
    type = "sketch";
  else // U_SPIFFS
    type = "filesystem";
  tft_TextInBox(5, 10, 310, 30, LANG_UpdateSketch, ALIGNCENTER, true, ILI9341_YELLOW, ILI9341_BLACK,1);
  tft_ShowOtaProgress(0);    
}
//on end no extra processing
void ota_onEnd() {
  Serial.println("OTA done");// but this normaly you never see on OTA there is no serial Connection ;-)
  tft_TextInBox(5, 120, 310, 30, LANG_Done, ALIGNLEFT, true, ILI9341_GREEN, ILI9341_BLACK,1);
}

//s
void ota_onProgress(unsigned int progress, unsigned int total) {
  uint32_t prc = progress / (total / 100);
  char tmp[20];
  if (prc > oldprc) {
    sprintf(tmp,"Progress %i%%",prc);// but this normaly you never see on OTA there is no serial Connection ;-)
    tft_ShowOtaProgress(prc);
    oldprc = prc;
  }
}

void ota_onError(ota_error_t error) {
  char err[80];
  sprintf(err,"Error[%u]: ", error);
  if (error == OTA_AUTH_ERROR) sprintf(err,"Error[%u]: Auth Failed",error);
  else if (error == OTA_BEGIN_ERROR) sprintf(err,"Error[%u] Begin Failed",error);
  else if (error == OTA_CONNECT_ERROR) sprintf(err,"Error[%u] Connect Failed",error);
  else if (error == OTA_RECEIVE_ERROR) sprintf(err,"Error[%u] Receive Failed",error);
  else if (error == OTA_END_ERROR) sprintf(err,"Error[%u] End Failed",error);
  tft_TextInBox(5,200,310,30,err,ALIGNLEFT,false,ILI9341_RED);
}
//############################################################################
//prepare OTA
void ota_Setup() {
  //set host name and passwort
  ArduinoOTA.setHostname(HOSTNAME);
  ArduinoOTA.setPassword(OTA_PW);
  //register callback routines
  ArduinoOTA.onStart(ota_onStart);
  ArduinoOTA.onEnd(ota_onEnd);
  ArduinoOTA.onProgress(ota_onProgress);
  ArduinoOTA.onError(ota_onError);
  //start OTA handling
  ArduinoOTA.begin();
}