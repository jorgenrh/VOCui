#ifndef _SPLASHPAGE_H_
#define _SPLASHPAGE_H_

#include <ILI9341_t3.h>
#include <font_LiberationSansBold.h>

#include "pages.h"

#include "ui/page.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"

#include "resources/simpro_logo.cpp"


enum {
  SPLASH_PAGE_TEST,
  SPLASH_PAGE_BACK_BUTTON,
  SPLASH_PAGE_FIELD,
  
};


class SplashPage : public Page
{
public:

  unsigned long start = 0;

  SplashPage() 
  {
    setRef(SPLASH_PAGE);
    setBackground(ILI9341_WHITE);

    Label sub = Label(172, 138, "VOC Display v1", SPLASH_PAGE_FIELD);
    sub.fc = ILI9341_BLACK;
    addControl(sub);
  }


  void render(ILI9341_t3 &tft) override
  {
    Page::render(tft);
    tft.writeRect(42, 96, 236, 40, (uint16_t*)simpro_logo);
    start = millis();
  }

  int16_t run(ILI9341_t3 &tft, bool t, TS_Point p) override
  {
    if (t || (millis()-start) >= 1200) {
      return MAIN_PAGE;
    } 
    return -1;
  }

};


#endif