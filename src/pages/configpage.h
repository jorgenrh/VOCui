#ifndef _CONFIGPAGE_H_
#define _CONFIGPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"

#include "common.h"

extern sense_data_t SensorData;
extern config_t ConfigData;


enum {
  CONFIG_PAGE_TEST,
  CONFIG_PAGE_CALI_BUTTON,
  CONFIG_PAGE_BACK_BUTTON,
  CONFIG_PAGE_SENSOR_OFFSET_LABEL,
  CONFIG_PAGE_SENSOR_OFFSET = 100,
  CONFIG_PAGE_SENSOR_LOG_LABEL,
  CONFIG_PAGE_SENSOR_LOG = 500,
  
};


class ConfigPage : public Page
{
public:

  int8_t sensor_offset = 0;

  int16_t last_ppm = 0;

  ConfigPage() 
  {
    setRef(CONFIG_PAGE);
    setBackground(ILI9341_NAVY);

    addControl(Label(160, 25, true, "Sensor offset (0 ppm)", CONFIG_PAGE_SENSOR_OFFSET_LABEL));
    Spinner offset_spn = Spinner(40, 35, 240, 30, 50, CONFIG_PAGE_SENSOR_OFFSET);
    offset_spn.text_val.setBackground(bc);
    offset_spn.setValue("0 ppm");
    addControl(offset_spn);

    addControl(Label(160, 80, true, "Log frequency", CONFIG_PAGE_SENSOR_LOG_LABEL));
    Spinner log_spn = Spinner(40, 90, 240, 30, 50, CONFIG_PAGE_SENSOR_LOG);
    log_spn.text_val.setBackground(bc);
    log_spn.setValue("180 sec");
    addControl(log_spn);

    addControl(Button(40, 140, 240, 30, "Calibrate touch screen", CONFIG_PAGE_CALI_BUTTON));

    Button back = Button(0, 190, 320, 50, "BACK", CONFIG_PAGE_BACK_BUTTON);
    back.setFont(LiberationSans_14_Bold);
    addControl(back);

  }
  
  void render(ILI9341_t3 &tft) override
  {
    snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_offset);
    updateControlValue(tft, CONFIG_PAGE_SENSOR_OFFSET, buffer);

    Page::render(tft);
  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {
    if (SensorData.ppm != last_ppm) {
      last_ppm = SensorData.ppm;
      snprintf(buffer, sizeof(buffer), "Sensor offset (%d ppm)", last_ppm);
      updateControlValue(tft, CONFIG_PAGE_SENSOR_OFFSET_LABEL, buffer);
    }


    if (t) {
      int16_t hit = getHitRef(p);
      Serial.print("Hit time: "); Serial.println(hit_time);
      switch (hit)
      {
/*
      case (CONFIG_PAGE_SENSOR_OFFSET|SPINNER_MINUS):
        ConfigData.ppm_offset = constrain(--ConfigData.ppm_offset, -100, 100);
        snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_offset);
        updateControlValue(tft, CONFIG_PAGE_SENSOR_OFFSET, buffer);
        break;

      case (CONFIG_PAGE_SENSOR_OFFSET|SPINNER_PLUS):
        ConfigData.ppm_offset = constrain(++ConfigData.ppm_offset, -100, 100);
        snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_offset);
        updateControlValue(tft, CONFIG_PAGE_SENSOR_OFFSET, buffer);
        break;
*/
      case (CONFIG_PAGE_SENSOR_LOG|SPINNER_MINUS):
        ConfigData.log_freq = constrain(--ConfigData.log_freq, 1, 100);
        snprintf(buffer, sizeof(buffer), "%d sec", ConfigData.log_freq);
        updateControlValue(tft, CONFIG_PAGE_SENSOR_LOG, buffer);
        break;

      case (CONFIG_PAGE_SENSOR_LOG|SPINNER_PLUS):
        ConfigData.log_freq = constrain(++ConfigData.log_freq, 1, 100);
        snprintf(buffer, sizeof(buffer), "%d sec", ConfigData.log_freq);
        updateControlValue(tft, CONFIG_PAGE_SENSOR_LOG, buffer);
        break;

      case CONFIG_PAGE_CALI_BUTTON:
        Serial.println("ALARM FIELD PRESSED");
        return CALIBRATE_PAGE;
        break;
      case CONFIG_PAGE_BACK_BUTTON:
        return MENU_PAGE;
        break;
      case -1:
        Serial.println("TOUCHED CONFIG PAGE");
        break;
      default:
        Serial.print("UNKNOWN: ");
        Serial.println(hit);
        break;
      }

      delay(50);

    } else {
      hit_time = 0;
    }


    return -1;
  }

};


#endif