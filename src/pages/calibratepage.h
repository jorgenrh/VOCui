#ifndef _CALIBRATEPAGE_H_
#define _CALIBRATEPAGE_H_


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
  CALI_PAGE_TEST,
  CALI_PAGE_INFO_FIELD1,
  CALI_PAGE_INFO_FIELD2,
  
};


class CalibratePage : public Page
{
public:
  
  struct cali_t {
    uint16_t x;
    uint16_t y;
    uint16_t cx;
    uint16_t cy;
    boolean ok;
  };

  cali_t point[4];


  CalibratePage() 
  {
    setRef(CALIBRATE_PAGE);
    setBackground(ILI9341_NAVY);

    Label info1 = Label(320/2., 240/2.-16, true, "press points", CALI_PAGE_INFO_FIELD1);
    info1.setFont(LiberationSans_16_Bold);
    addControl(info1);
    Label info2 = Label(320/2., 240/2.+16, true, "to calibrate", CALI_PAGE_INFO_FIELD2);
    info2.setFont(LiberationSans_16_Bold);
    addControl(info2);

  }

  void drawPoint(ILI9341_t3 &tft, uint16_t x, uint16_t y, bool pressed=false)
  {
    if (pressed) tft.fillCircle(x, y, 24, ILI9341_GREEN);
    tft.drawCircle(x, y, 24, ILI9341_WHITE);
    tft.drawFastHLine(x-32, y, 64, ILI9341_WHITE);
    tft.drawFastVLine(x, y-32, 64, ILI9341_WHITE);
  }

  void render(ILI9341_t3 &tft) override
  {
    Page::render(tft);

    point[0] = { 40, 40, false };
    point[1] = { 280, 40, false };
    point[2] = { 280, 200, false };
    point[3] = { 40, 200, false };

    for (uint8_t i=0; i < 4; i++) {
      drawPoint(tft, point[i].x, point[i].y);
    }

  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {

    if (t) {

      uint8_t r = 24;
      for (uint8_t i=0; i < 4; i++) {
        if (p.x >= point[i].x-r && p.x <= point[i].x+r && p.y >= point[i].y-r && p.y <= point[i].y+r) {
          drawPoint(tft, point[i].x, point[i].y, true);
          //drawPoint(tft, p.x, p.y, true);
          point[i].ok = true;
          point[i].cx = p.x;
          point[i].cy = p.y;
        }
      }

      if (point[0].ok && point[1].ok && point[2].ok && point[3].ok) {
        delay(100);
        return CONFIG_PAGE;
      }
        



      int16_t hit = getHitRef(p);
      Serial.print("Hit time: "); Serial.println(hit_time);
      switch (hit)
      {
      case CALI_PAGE_INFO_FIELD1:
      case CALI_PAGE_INFO_FIELD2:
        Serial.println("CALI FIELD PRESSED");
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