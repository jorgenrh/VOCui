#ifndef _MAINPAGE_H_
#define _MAINPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"
#include "ui/plot.h"

#include "common.h"

extern sense_data_t SensorData;


enum {
  MAIN_PAGE_TEST,
  MAIN_PAGE_ALARM_FIELD,
  MAIN_PAGE_ALARM_MIN_FIELD,
  MAIN_PAGE_ALARM_AVG_FIELD,
  MAIN_PAGE_ALARM_MAX_FIELD,
  MAIN_PAGE_ALARM_PLOT,
    
  
};


class MainPage : public Page
{
public:

  unsigned long last_ms = 0; 

  MainPage() 
  {
    setRef(MAIN_PAGE);
    setBackground(ILI9341_NAVY);


    Label alarm_field = Label(320/2., 240/2.-40, true, "1000", MAIN_PAGE_ALARM_FIELD);
    alarm_field.setFont(LiberationSans_96_Bold);
    alarm_field.setBackground(ILI9341_NAVY);
    addControl(alarm_field);

    snprintf(buffer, sizeof(buffer), "Min: %d ppm", SensorData.ppm_min);
    addControl(Label(200, 158, buffer, MAIN_PAGE_ALARM_MIN_FIELD));
    snprintf(buffer, sizeof(buffer), "Avg: %d ppm", SensorData.ppm_avg);
    addControl(Label(200, 178, buffer, MAIN_PAGE_ALARM_AVG_FIELD));
    snprintf(buffer, sizeof(buffer), "Max: %d ppm", SensorData.ppm_max);
    addControl(Label(200, 198, buffer, MAIN_PAGE_ALARM_MAX_FIELD));

    addControl(Plot(30, 155, 160, 55, MAIN_PAGE_ALARM_PLOT));

  }

  void render(ILI9341_t3 &tft) override
  {
    Page::render(tft);

    snprintf(buffer, sizeof(buffer), "Min: %d ppm", SensorData.ppm_min);
    updateControlValue(tft, MAIN_PAGE_ALARM_MIN_FIELD, buffer);

    snprintf(buffer, sizeof(buffer), "Avg: %d ppm", SensorData.ppm_avg);
    updateControlValue(tft, MAIN_PAGE_ALARM_AVG_FIELD, buffer);

    snprintf(buffer, sizeof(buffer), "Max: %d ppm", SensorData.ppm_max);
    updateControlValue(tft, MAIN_PAGE_ALARM_MAX_FIELD, buffer);
  } 

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {
    if ((millis()-last_ms) >= 1000) {
      updateControlValue(tft, MAIN_PAGE_ALARM_FIELD, SensorData.ppm);

      snprintf(buffer, sizeof(buffer), "Min: %d ppm", SensorData.ppm_min);
      updateControlValue(tft, MAIN_PAGE_ALARM_MIN_FIELD, buffer);

      snprintf(buffer, sizeof(buffer), "Avg: %d ppm", SensorData.ppm_avg);
      updateControlValue(tft, MAIN_PAGE_ALARM_AVG_FIELD, buffer);

      snprintf(buffer, sizeof(buffer), "Max: %d ppm", SensorData.ppm_max);
      updateControlValue(tft, MAIN_PAGE_ALARM_MAX_FIELD, buffer);

      last_ms = millis();
    }

    if (t) {
      int16_t hit = getHitRef(p);
      Serial.print("Hit time: "); Serial.println(hit_time);

      if (hit_time > 10) {
        tft.fillRect(0, 0, ((hit_time-10)/50.)*320, 5, ILI9341_WHITE);
      }

      switch (hit)
      {
      case MAIN_PAGE_ALARM_FIELD:
        Serial.println("ALARM FIELD PRESSED");
        if (hit_time > 50+10) return MENU_PAGE;
        break;
      case -1:
        Serial.println("TOUCHED MAIN PAGE");
        break;
      default:
        Serial.print("UNKNOWN: ");
        Serial.println(hit);
        break;
      }

      //delay(5);

    } else {
      tft.fillRect(0, 0, 320, 5, bc);
      hit_time = 0;
    }

 
    return -1;
  }

};


#endif