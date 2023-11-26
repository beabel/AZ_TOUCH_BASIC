//adjust the brightness of the background led
void tft_setBGLight(uint8_t prct) {
  uint16_t ledb;
  ledb = 255*prct/100;
  if (ledb > 255) ledb = 255;
  if (ledb <3) ledb = 3; //minimal brightness
  if (LED_ON == 0) ledb = 255 - ledb;
  Serial.printf(LANG_setBGLight,prct,ledb);
  //set the LED
  analogWrite(TFT_LED, ledb);
}
//called from the main loop to handle touch events
void tft_TouchLoop() {
    tevent.pollTouchScreen();
}
//clear the whole display
void tft_DisplayClear() {
  tft.fillScreen(COLOR_BG);
}
//encode text from unicode to display code for supplied font
//src and dst buffer needs to exist
void tft_encodeUnicode(const char* src, char* dst){
  uint8_t i = 0, i1 = 0;
  char c;
  uint16_t  m = strlen(src);
  do {
    c = src[i];
    if (c==195) { //UTF8 characters german umlauts
      i++;
      switch (src[i]) {
        case 164: c=130; break; //ä
        case 182: c=131; break; //ö
        case 188: c=132; break; //ü
        case 159: c=133; break; //ß
        case 132: c=127; break; //Ä
        case 150: c=128; break; //Ö
        case 156: c=129; break; //Ü
        default: c=255;
      }
    } else if (c == 194) { //UTF8 char for degree symbol
      i++;
      if (src[i] == 176) c=134; else c=255;
    }
    if (c<135) dst[i1] = c;
    i++;
    i1++;
  } while (i<m);
  dst[i1] = 0;
}
//display a text in a rectangle on position x,y with the size w,h 
//the text can bbe aligned left, center or right text size can be set to standard or big 
//font color and background color can be selected as well as the number of lines
void tft_TextInBox(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* text, uint8_t align = ALIGNLEFT, boolean big = false, uint16_t fc = ILI9341_WHITE , uint16_t bg = ILI9341_BLACK, uint8_t lines = 1 ) {
  char tmp[256];
  char msg[50];
  char * token;
  int16_t xt,yt,h0,x0,sp;
  uint16_t wt,ht,len;
  uint8_t l;
  //first the rectangle will be filled with the background color to erase old content
  tft.fillRect(x,y,w,h,bg);
  if (big) tft.setFont(FNT12); else tft.setFont(FNT9);
  tft.setTextColor(fc);
  //encoding for german umlauts
  tft_encodeUnicode(text, tmp);
  tft.getTextBounds("n",0,100,&xt,&yt,&wt,&ht);
  sp =wt;
  //Serial.printf("Space = %i\n",sp);
  tft.getTextBounds(tmp,0,100,&xt,&yt,&wt,&ht);
  //Serial.printf("Text %s Länge %i\n",text,wt);
  h0 = 100 - yt;
  x0 = x;
  y = y + h0 +1;
  if (wt<w) { //enough space in one line
    if (align == ALIGNCENTER) x0 += (w-wt)/2;
    if (align == ALIGNRIGHT) x0 += (w-wt);
    //Serial.printf("x= %i, y= %i, ht= %i, text = %s\n",x0,y,ht,tmp);
    tft.setCursor(x0, y);
    tft.print(tmp);
  } else { //if there is not enough space in one line we adjust the text by word wrap
    //if only one line is allowed, the text will be cut off on a word boundary
    l=lines;
    token = strtok(tmp," ");
    
    msg[0] = 0;
    len = 0;
    while ((token != NULL) && (l>0)) {
      tft.getTextBounds(token,0,100,&xt,&yt,&wt,&ht); 
      Serial.printf(LANG_TextInBox,token,wt,msg,len,l);
      if ((len + wt + sp) < w) {
        if (len > 0) { strcat(msg," "); len +=sp; }
        len = len + wt;
        strcat(msg,token);
      } else {
        x0 = x;
        if (align == ALIGNCENTER) x0 += (w-len)/2;
        if (align == ALIGNRIGHT) x0 += (w-len);
        tft.setCursor(x0, y);
        tft.print(msg);
        len = wt;
        strcpy(msg,token);
        y = y + ht +1;
        l--;
      }
      Serial.println(token);
      token = strtok(NULL, " ");
      
    }
    if ((len > 0) && (l>0)) {
      x0 = x;
      if (align == ALIGNCENTER) x0 += (w-len)/2;
      if (align == ALIGNRIGHT) x0 += (w-len);
      y = y + h0 +1;
      tft.setCursor(x0, y);
       tft.print(msg);
    }
  }
}
//register a callback for any touch event.
//we get position and type of the event
void tft_OnTouchClick(TS_Point p) {
  char txt[50];
  sprintf(txt,"Touch on %i, %i\n",p.x,p.y);
  tft_TextInBox(0,220,320,20,txt,ALIGNLEFT,false,ILI9341_WHITE,COLOR_BG,1);
  //later on real Project you must select pages or actions here
}

//show the progress of softwareupdate as a bar and a number
void tft_ShowOtaProgress(uint32_t prc) {
  char tmp[20];
  sprintf(tmp,LANG_ShowOtaProgress,prc); 
  tft_TextInBox(5, 50, 310, 30, tmp, ALIGNLEFT, true, ILI9341_GREEN, COLOR_BG,1);
  if (prc == 0) {
    tft.drawRect(5,80,310,20,ILI9341_BLUE);
  } else {
    tft.fillRect(5,80,310 * prc / 100,20,ILI9341_BLUE);
  }
}
//##########################################
//prepare display
void tft_SetupDisplay() {
  pinMode(TFT_LED,OUTPUT);
  tft_setBGLight(80);
  tft.begin();
  tft.fillScreen(COLOR_BG);
  tft.setRotation(3);
  tft.setFont(FNT12);
  touch.begin();
  tevent.setResolution(tft.width(),tft.height());
  tevent.setDrawMode(false);
  //register callback function
  tevent.registerOnTouchClick(tft_OnTouchClick);
}