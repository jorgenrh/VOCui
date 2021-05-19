#include <Arduino.h>

#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

#define TFT_DC  9
#define TFT_CS 10
#define TOUCH_CS  8

#include "gui.h"



#include "common.h"

sense_data_t SensorData;
config_t ConfigData;

ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts(TOUCH_CS);
GUI gui = GUI(tft, ts);


void setup() 
{
  
  tft.begin();
  tft.setRotation(1);
  
  Serial.begin(9600);
  //while (!Serial);

  tft.fillScreen(ILI9341_DARKCYAN);

  ts.begin();
  ts.setRotation(1);

  gui.init();
  gui.setPage(MAIN_PAGE);
  gui.render();

  Serial.println("READY");
/*
  */

}
unsigned long last_ms = 0;
unsigned long sd = 100;


void loop() 
{
  if ((millis()-last_ms) >= 1000) {
    sd += random(0, 3) * (random(0, 3) > 1 ? 1 : -1);
    if (sd <= 0) sd = 100;
    SensorData.ppm = sd;
    Serial.print("min: "); Serial.print(SensorData.ppm_min); Serial.print(", "); Serial.println(sd);
    SensorData.ppm_min = min(SensorData.ppm_min, sd);
    SensorData.ppm_max = max(SensorData.ppm_max, sd);
    last_ms = millis();
  }

  gui.run();
}