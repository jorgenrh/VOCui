#ifndef _CONFIGPAGE_H_
#define _CONFIGPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"


enum {
  CONFIG_PAGE_TEST,
  CONFIG_PAGE_ALARM_FIELD,
  
};


class ConfigPage : public Page
{
public:

  Label alarm_field;

  ConfigPage() 
  {
    setRef(CONFIG_PAGE);

    alarm_field = Label(320/2., 240/2.-40, true, "1000", CONFIG_PAGE_ALARM_FIELD);
    alarm_field.setFont(LiberationSans_72_Bold);
    addControl(alarm_field);

  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {

    if (t) {
      int16_t hit = getHitRef(p);
      Serial.print("Hit time: "); Serial.println(hit_time);
      switch (hit)
      {
      case CONFIG_PAGE_ALARM_FIELD:
        Serial.println("ALARM FIELD PRESSED");
        if (hit_time > 10) return MENU_PAGE;
        break;
      case -1:
        Serial.println("TOUCHED MAIN PAGE");
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