#ifndef _GUI_H_
#define _GUI_H_


#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

#include "pages/pages.h"

#include "ui/page.h"
#include "pages/mainpage.h"
#include "pages/alarmpage.h"
#include "pages/menupage.h"
#include "pages/calibratepage.h"
#include "pages/configpage.h"
#include "pages/statpage.h"
#include "pages/splashpage.h"


class GUI
{
public:
  GUI(ILI9341_t3 &display, XPT2046_Touchscreen &touch);

  void init();
  void setPage(int8_t page);
  void render();
  void run();

  ILI9341_t3* tft;
  XPT2046_Touchscreen* ts;

  Page** pages = new Page*[8];

  int8_t current_page = MENU_PAGE;

};

#endif