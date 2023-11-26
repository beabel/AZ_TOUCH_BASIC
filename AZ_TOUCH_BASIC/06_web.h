//home page and templatefor options
#include "06_index.h"

WebServer server(80);

//called from main loop
void web_Loop() {
    server.handleClient();
}

//handle root request
void web_HandleRoot() {
  if (connected) {
    //if connected send the main page
    server.send(200,"text/html",MAIN_page);
  } else {
    //if not connected we use the config page without ajax
    //we get parameters as arguments in the HTML-request
    Serial.println("Get config:");
    uint8_t a = server.args();
    Serial.print(a); Serial.println(" Arguments");
    for (uint8_t i = 0; i<a; i++)  Serial.println(server.arg(i));
    if (server.hasArg("conf_ssid")) {
      pref.putString("ssid",server.arg("conf_ssid")); //save SSID in the preferences
      Serial.println(server.arg("conf_ssid"));
    }
    if (server.hasArg("conf_pkey")) {
      pref.putString("pkey",server.arg("conf_pkey")); // save PKEY in the preferences
      Serial.println(server.arg("conf_pkey"));
    }
    if (server.hasArg("reset")) {
      Serial.println("Restart!"); //initiate a restart
      ESP.restart();
    }
    server.send(200,"text/html",CONFIG_page); //send the config page to the client
  }
}
//AJAX command /cmd/restart
void web_Restart(){
  ESP.restart();
}
//AJAX command /cmd/setaccess
void web_SetAccessData() {
  //the command expects three arguments
  //access data will be saved in preferences
  if (server.hasArg("ssid")) {
    ssid = server.arg("ssid");
    pref.putString("ssid",ssid);
  }
  if (server.hasArg("pkey")) {
    pkey = server.arg("pkey");
    pref.putString("pkey",pkey);
  }
  if (server.hasArg("ntp")) {
    ntp = server.arg("ntp");
    pref.putString("ntp",ntp);
  }
  //respond with OK
  server.send(200,"text/plain","OK");
}
//AJAX command /cmd/getaccess
void web_GetAccessData() {
  //send access data separated by new line
  String msg = String(ssid) + "\n" + String(pkey) + "\n" + String(ntp);
  //respond with access data
  server.send(200,"text/plain",msg);
}
//#############################################################################
//setup request distribution
void web_SetupWebserver() {
  Serial.println("Start webserver");
  //server.enableCORS(); 
  server.on("/",web_HandleRoot);
  //handle ajax commands
  server.on("/cmd/restart",web_Restart);
  server.on("/cmd/setaccess",web_SetAccessData);
  server.on("/cmd/getaccess",web_GetAccessData);
  //start webserver
  server.begin();
}