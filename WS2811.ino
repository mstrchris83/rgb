void initRGB() {
 HTTP.on("/set", LedRGB);
 modes.reserve(5000);

 ws2812fx.init();
 ws2812fx.setMode(DEFAULT_MODE);
 ws2812fx.setColor(DEFAULT_COLOR);
 ws2812fx.setSpeed(DEFAULT_SPEED);
 ws2812fx.setBrightness(DEFAULT_BRIGHTNESS);
 ws2812fx.start();
}



void LedRGB() {
 for (uint8_t i=0; i < HTTP.args(); i++){
  if(HTTP.argName(i) == "c") {
   uint32_t tmp = (uint32_t) strtol(&HTTP.arg(i)[0], NULL, 16);
   if(tmp >= 0x000000 && tmp <= 0xFFFFFF) {
    ws2812fx.setColor(tmp);
   }
  }

  if(HTTP.argName(i) == "m") {
   uint8_t tmp = (uint8_t) strtol(&HTTP.arg(i)[0], NULL, 10);
   ws2812fx.setMode(tmp % ws2812fx.getModeCount());
  }

  if(HTTP.argName(i) == "b") {
   if(HTTP.arg(i)[0] == '-') {
    ws2812fx.decreaseBrightness(BRIGHTNESS_STEP);
   } else {
    ws2812fx.increaseBrightness(BRIGHTNESS_STEP);
   }
  }

  if(HTTP.argName(i) == "s") {
   if(HTTP.arg(i)[0] == '-') {
    ws2812fx.decreaseSpeed(SPEED_STEP);
   } else {
    ws2812fx.increaseSpeed(SPEED_STEP);
   }
  }
 }

 t = HTTP.arg("time").toInt();
 s = HTTP.arg("sound").toInt();
 tickerSetLow.attach(t, setT1, 0);
 sound(buzer_pin, volume, 1000, s*100);
 state0=0;
 chaing = 1;

 HTTP.send(200, "text/plain", "OK");
}




int LedRGBwan() {
 for (uint8_t i=0; i < HTTPWAN.args(); i++){
  if(HTTPWAN.argName(i) == "c") {
   uint32_t tmp = (uint32_t) strtol(&HTTPWAN.arg(i)[0], NULL, 16);
   if(tmp >= 0x000000 && tmp <= 0xFFFFFF) {
    ws2812fx.setColor(tmp);
   }
  }

  if(HTTPWAN.argName(i) == "m") {
   uint8_t tmp = (uint8_t) strtol(&HTTPWAN.arg(i)[0], NULL, 10);
   ws2812fx.setMode(tmp % ws2812fx.getModeCount());
  }

  if(HTTPWAN.argName(i) == "b") {
   if(HTTPWAN.arg(i)[0] == '-') {
    ws2812fx.decreaseBrightness(BRIGHTNESS_STEP);
   } else {
    ws2812fx.increaseBrightness(BRIGHTNESS_STEP);
   }
  }

  if(HTTPWAN.argName(i) == "s") {
   if(HTTPWAN.arg(i)[0] == '-') {
    ws2812fx.decreaseSpeed(SPEED_STEP);
   } else {
    ws2812fx.increaseSpeed(SPEED_STEP);
   }
  }
 }

 t = HTTPWAN.arg("time").toInt();
 s = HTTPWAN.arg("sound").toInt();
 tickerSetLow.attach(t, setT1, 0);
 sound(buzer_pin, volume, 1000, s*100);
 state0=0;
 chaing = 1;

 HTTPWAN.send(200, "text/plain", "OK");

}




void sound(int pin, int volume, int freq, int time_ms) {
 analogWrite(pin, volume);
 analogWriteFreq (freq);
 tickerBizz.attach_ms(time_ms, setPin, 1);
}

void setPin(int state) {
 tickerBizz.detach();
 analogWrite(buzer_pin, 0);
 digitalWrite(buzer_pin,1);
}
