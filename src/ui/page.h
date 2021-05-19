#ifndef _PAGE_H_
#define _PAGE_H_

#include <stdint.h>

#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

#include "ui/control.h"
#include "ui/button.h"
#include "ui/label.h"
#include "ui/spinner.h"
#include "ui/plot.h"

class Page
{
public:
  Page();

  //void test();

  void addControl(Button btn);
  void addControl(Label lbl);
  void addControl(Spinner spn);
  void addControl(Plot plt);

  //Button getControl(int8_t ref);
  //Label getControl(int8_t ref);
  //Spinner* getControl(int8_t ref);


  void updateControlValue(ILI9341_t3 &tft, int8_t ref, int16_t val);
  void updateControlValue(ILI9341_t3 &tft, int8_t ref, const char* val);
  
  virtual void render(ILI9341_t3 &tft);

  virtual int16_t run(ILI9341_t3 &tft, bool t=false, TS_Point p=TS_Point(0,0,0)) { return -1; };

  void setRef(int8_t ref);
  void setBackground(uint16_t b);

  int16_t getHitRef(TS_Point p);

  long hit_time = 0;

  uint16_t bc = ILI9341_NAVY;

  char buffer[32];


private:

  int8_t _ref = -1;

  Button _btns[20];
  uint8_t _btn_idx = 0;

  Label _lbls[10];
  uint8_t _lbl_idx = 0;

  Spinner _spns[8];
  uint8_t _spn_idx = 0;

  Plot _plts[4];
  uint8_t _plt_idx = 0;

};



#endif