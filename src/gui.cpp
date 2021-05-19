#include "gui.h"

#define TS_MINX 380
#define TS_MINY 400
#define TS_MAXX 3749
#define TS_MAXY 3711

GUI::GUI(ILI9341_t3 &display, XPT2046_Touchscreen &touch) 
{ 
  tft = &display; 
  ts = &touch;
}

void GUI::render()
{
  Serial.print("RENDER PAGE");
  pages[current_page]->render(*tft);
}

void GUI::init()
{
  Serial.println("pages added to memory");
  pages[SPLASH_PAGE] = new SplashPage;
  pages[MAIN_PAGE] = new MainPage;
  pages[MENU_PAGE] = new MenuPage;
  pages[ALARM_PAGE] = new AlarmPage;
  pages[CONFIG_PAGE] = new ConfigPage;
  pages[STAT_PAGE] = new StatPage;
  pages[CALIBRATE_PAGE] = new CalibratePage;
  Serial.println("pages added to memory");
}

void GUI::setPage(int8_t page)
{
  current_page = page;
}

void GUI::run()
{
  TS_Point p = TS_Point(0, 0, 0);
  boolean t = ts->touched();
  
  if (t) {
    p = ts->getPoint();
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 320);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
  }

  int16_t ret = pages[current_page]->run(*tft, t, p);

  if (ret > -1) {
    setPage(ret);
    render();
    while (ts->touched());
  }

  delay(10);
}