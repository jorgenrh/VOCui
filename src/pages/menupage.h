#ifndef _MENUPAGE_H_
#define _MENUPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"

enum {
  MENU_PAGE_TEST,

  MENU_PAGE_BACK_BUTTON,
  MENU_PAGE_OPEN_ALARM_PAGE,
  MENU_PAGE_OPEN_CONFIG_PAGE,
  MENU_PAGE_OPEN_STAT_PAGE,

  MENU_PAGE_LABEL_TEST,
  
  MENU_PAGE_MAIN_SPINNER,

};

class MenuPage : public Page
{
public:

  MenuPage() 
  {
    setRef(MENU_PAGE);
    setBackground(ILI9341_NAVY);

    addControl(Button(20, 70, 80, 60, "Alarm", MENU_PAGE_OPEN_ALARM_PAGE));
    addControl(Button(120, 70, 80, 60, "Config", MENU_PAGE_OPEN_CONFIG_PAGE));
    addControl(Button(220, 70, 80, 60, "Stat", MENU_PAGE_OPEN_STAT_PAGE));

    Button back = Button(0, 190, 320, 50, "BACK", MENU_PAGE_BACK_BUTTON);
    back.setFont(LiberationSans_14_Bold);
    addControl(back);

    //addControl(Label(10, 10, "This is a label", MENU_PAGE_LABEL_TEST));
  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {
    //Serial.println("MenuPage::run");
    /*
    Serial.print("MenuPage: ");
    Serial.print(touched ? "hit" : "no hit");
    Serial.print(" -> ");
    Serial.println(hit);
    */

    if (t) {
      int16_t hit = getHitRef(p);

      switch (hit)
      {
      case MENU_PAGE_BACK_BUTTON:
        Serial.println("MENU BACK");
        return MAIN_PAGE;
        break;
      case MENU_PAGE_OPEN_ALARM_PAGE:
        Serial.println("MENU ALARM");
        return ALARM_PAGE;
        break;
      case MENU_PAGE_OPEN_CONFIG_PAGE:
        Serial.println("MENU CONFIG");
        return CONFIG_PAGE;
        break;
      case MENU_PAGE_OPEN_STAT_PAGE:
        Serial.println("MENU STAT");
        return STAT_PAGE;
        break;
      case -1:
        Serial.println("TOUCHED MENU PAGE!");
        break;
      default:
        Serial.print("UNKNOWN: ");
        Serial.println(hit);
        break;
      }

    } else {
      hit_time = 0;
    }

    return -1;
  }

};

#endif