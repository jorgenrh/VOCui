#ifndef _ALARMPAGE_H_
#define _ALARMPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"

#include "common.h"

extern config_t ConfigData;


enum {
  ALARM_PAGE_TEST,
  ALARM_PAGE_BACK_BUTTON,
  ALARM_PAGE_ALARM_LABEL,
  ALARM_PAGE_ALARM_SPINNER = 12,
  ALARM_PAGE_WARN_LABEL,
  ALARM_PAGE_WARN_SPINNER = 22,
};


class AlarmPage : public Page
{
public:

  int16_t alarm_thres = 120;

  int16_t warn_thres = 60;

  Spinner alarm_spn;
  Spinner warn_spn;
  Button back_btn;

  AlarmPage() 
  {
    setRef(ALARM_PAGE);
    setBackground(ILI9341_NAVY);

    
    addControl(Label(160, 28, true, "Alarm threshold", ALARM_PAGE_ALARM_LABEL));
    alarm_spn = Spinner(40, 40, 240, 45, 50, ALARM_PAGE_ALARM_SPINNER);
    alarm_spn.text_val.setBackground(bc);
    alarm_spn.setValue("120 ppm");
    addControl(alarm_spn);
    
    addControl(Label(160, 108, true, "Warning threshold", ALARM_PAGE_ALARM_LABEL));
    warn_spn = Spinner(40, 120, 240, 45, 50, ALARM_PAGE_WARN_SPINNER);
    warn_spn.text_val.setBackground(bc);
    warn_spn.setValue("60 %");
    addControl(warn_spn);

    back_btn = Button(0, 190, 320, 50, "BACK", ALARM_PAGE_BACK_BUTTON);
    back_btn.setFont(LiberationSans_14_Bold);
    addControl(back_btn);
  }

  void render(ILI9341_t3 &tft) override
  {
    Serial.print("alarm thres: "); Serial.print(alarm_thres); 
    Serial.print(", warn thres: "); Serial.print(warn_thres); 

    snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_alarm);
    updateControlValue(tft, ALARM_PAGE_ALARM_SPINNER, buffer);

    snprintf(buffer, sizeof(buffer), "%d %%", ConfigData.ppm_warn);
    updateControlValue(tft, ALARM_PAGE_WARN_SPINNER, buffer);

    Page::render(tft);
  }

  int16_t run(ILI9341_t3 &tft, bool touched, TS_Point p) override
  {

    if (touched) 
    {
      int16_t hit = getHitRef(p);
      //char buffer[10];
      switch (hit)
      {
      case ALARM_PAGE_BACK_BUTTON:
        return MENU_PAGE;
        break;        

      case (ALARM_PAGE_ALARM_SPINNER|SPINNER_MINUS):
        ConfigData.ppm_alarm = constrain(--ConfigData.ppm_alarm, 1, 1000);
        snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_alarm);
        updateControlValue(tft, ALARM_PAGE_ALARM_SPINNER, buffer);
        break;

      case (ALARM_PAGE_ALARM_SPINNER|SPINNER_PLUS):
        ConfigData.ppm_alarm = constrain(++ConfigData.ppm_alarm, 1, 1000);
        snprintf(buffer, sizeof(buffer), "%d ppm", ConfigData.ppm_alarm);
        updateControlValue(tft, ALARM_PAGE_ALARM_SPINNER, buffer);
        break;

      case (ALARM_PAGE_WARN_SPINNER|SPINNER_MINUS):
        ConfigData.ppm_warn = constrain(--ConfigData.ppm_warn, 0, 100);
        snprintf(buffer, sizeof(buffer), "%d %%", ConfigData.ppm_warn);
        updateControlValue(tft, ALARM_PAGE_WARN_SPINNER, buffer);
        break;

      case (ALARM_PAGE_WARN_SPINNER|SPINNER_PLUS):
        ConfigData.ppm_warn = constrain(++ConfigData.ppm_warn, 0, 100);
        snprintf(buffer, sizeof(buffer), "%d %%", ConfigData.ppm_warn);
        updateControlValue(tft, ALARM_PAGE_WARN_SPINNER, buffer);
        break;

      case -1:
        Serial.println("TOUCHED ALARM PAGE");
        break;

      default:
        Serial.print("UNKNOWN: "); Serial.println(hit);
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