#ifndef _SPINNER_H_
#define _SPINNER_H_

#include <ILI9341_t3.h>

#include "ui/control.h"
#include "ui/label.h"
#include "ui/button.h"

enum {
  SPINNER_MINUS = 101,
  SPINNER_PLUS = 102,
  SPINNER_LABEL = 103, 
};

class Spinner : public Control
{
public:
  Spinner();
  Spinner(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t btn_w, uint8_t ref);

  void draw(ILI9341_t3 *tft, bool pressed=false);

  //void setValue(int16_t val);
  
  void setValue(const char* val) override;
  int16_t hit(TS_Point p) override;

  Button plus_btn;
  Button minus_btn;
  Label text_val;

  bool val_updated = false;

};


#endif