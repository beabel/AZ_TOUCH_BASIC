/*
     _______. _______ .___________.___________. __  .__   __.   _______      _______.
    /       ||   ____||           |           ||  | |  \ |  |  /  _____|    /       |
   |   (----`|  |__   `---|  |----`---|  |----`|  | |   \|  | |  |  __     |   (----`
    \   \    |   __|      |  |        |  |     |  | |  . `  | |  | |_ |     \   \    
.----)   |   |  |____     |  |        |  |     |  | |  |\   | |  |__| | .----)   |   
|_______/    |_______|    |__|        |__|     |__| |__| \__|  \______| |_______/    
                                                                                    
*/
//select english or use german as standard
//#define ENGLISH
//########### TFT Color Settings
#define COLOR_BG  ILI9341_BLACK
//###########
#define HOSTNAME "ESP-Hostname"
#define AP_NAME "ESP_WIFI_AP"
#define OTA_PW "ota_update"
#define TZONE "CET-1CEST,M3.5.0/03,M10.5.0/03" //https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
/*
     _______.___________.    ___      .__   __.  _______       ___      .______       _______                   
    /       |           |   /   \     |  \ |  | |       \     /   \     |   _  \     |       \                  
   |   (----`---|  |----`  /  ^  \    |   \|  | |  .--.  |   /  ^  \    |  |_)  |    |  .--.  |                 
    \   \       |  |      /  /_\  \   |  . `  | |  |  |  |  /  /_\  \   |      /     |  |  |  |                 
.----)   |      |  |     /  _____  \  |  |\   | |  '--'  | /  _____  \  |  |\  \----.|  '--'  |                 
|_______/       |__|    /__/     \__\ |__| \__| |_______/ /__/     \__\ | _| `._____||_______/                  
                                                                                                                
 _______   ______   .__   __.  __.___________.     ______  __    __       ___      .__   __.   _______  _______ 
|       \ /  __  \  |  \ |  | (_ )           |    /      ||  |  |  |     /   \     |  \ |  |  /  _____||   ____|
|  .--.  |  |  |  | |   \|  |  |/`---|  |----`   |  ,----'|  |__|  |    /  ^  \    |   \|  | |  |  __  |  |__   
|  |  |  |  |  |  | |  . `  |        |  |        |  |     |   __   |   /  /_\  \   |  . `  | |  | |_ | |   __|  
|  '--'  |  `--'  | |  |\   |        |  |        |  `----.|  |  |  |  /  _____  \  |  |\   | |  |__| | |  |____ 
|_______/ \______/  |__| \__|        |__|         \______||__|  |__| /__/     \__\ |__| \__|  \______| |_______|
*/                                                                                                               
/*_______Pin definitions____*/
#define BEEPER     21       //
//touchscreen               //
#define TOUCH_CS   14       //
#define TOUCH_IRQ  27       //
//display                   //
#define TFT_CS      5       //
#define TFT_DC      4       //
#define TFT_RST    22       //
#define TFT_LED    15       //
#define TFT_MOSI   23       //
#define TFT_CLK    18       //
#define TFT_MISO   19       //
/*______End of definitions__*/
//define names for fonts
#define FNT9 &AT_Standard9pt7b
#define FNT12 &AT_Bold12pt7b
#define LED_ON 0
//definitions for text output alignment
#define ALIGNLEFT 0
#define ALIGNCENTER 1
#define ALIGNRIGHT 2
//########### Global Variables
uint16_t minutes;                 //current number of minutes since midnight
uint8_t weekday;                  //current weekday
struct tm ti;                     //time structure with current time
boolean connected;                //flag to signal active connection
uint32_t discon = 0;              //tick-counter value to calculate disconnected time
uint32_t tick = 0;                //last tick-counter value to trigger timed event
//########### Variables to hold configuration data
Preferences pref;
String ssid = "";                 //ssid for WLAN connection
String pkey = "";                 //passkey for WLAN connection
String ntp = "de.pool.ntp.org";   //NTP server url

//instance of display driver
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
//instance for touchscreen driver
XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);
//instance to start callbacks on touch events
TouchEvent tevent(touch);