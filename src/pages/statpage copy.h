#ifndef _STATPAGE_H_
#define _STATPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"


enum {
  STAT_PAGE_TEST,
  STAT_PAGE_BACK_BUTTON,
  STAT_PAGE_FIELD,
  
};


class StatPage : public Page
{
public:

 
  StatPage() 
  {
    setRef(STAT_PAGE);
    setBackground(ILI9341_NAVY);

    Label alarm_field;
     alarm_field = Label(320/2., 170/2., true, "STAT", STAT_PAGE_FIELD);
    alarm_field.setFont(LiberationSans_20_Bold);
    addControl(alarm_field);

    Button back = Button(0, 190, 320, 50, "BACK", STAT_PAGE_BACK_BUTTON);
    back.setFont(LiberationSans_14_Bold);
    addControl(back);

  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {

    if (t) {
      int16_t hit = getHitRef(p);
      Serial.print("Hit time: "); Serial.println(hit_time);

      switch (hit)
      {
      case STAT_PAGE_BACK_BUTTON:
        return MENU_PAGE;
        break;
      case -1:
        Serial.println("TOUCHED STAT PAGE");
        break;
      default:
        Serial.print("UNKNOWN: ");
        Serial.println(hit);
        break;
      }

      //delay(5);

    } else {
      hit_time = 0;
    }


    return -1;
  }

};


#endif