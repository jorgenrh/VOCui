#include "spinner.h"

#include <font_LiberationSansBold.h>

#include "ui/label.h"
#include "ui/button.h"

Spinner::Spinner()
{

}

Spinner::Spinner(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t btn_w, uint8_t ref)
{
  setCoords(x, y, w, h);
  setRef(ref);
  minus_btn = Button(x, y, btn_w, h, "-", ref|101);
  plus_btn = Button(x+w-btn_w, y, btn_w, h, "+", ref|102);
  text_val = Label(x+(w/2.0), y+(h/2.0), true, "SPINNER", ref|103);
  text_val.setFont(LiberationSans_14_Bold);
}

void Spinner::draw(ILI9341_t3 *tft, bool pressed)
{
  minus_btn.draw(tft);
  plus_btn.draw(tft);
  text_val.draw(tft);
}

/*
void Spinner::setValue(int16_t val) override
{
  //text_val.setValue(val);
}
*/

void Spinner::setValue(const char* val)
{
  text_val.setValue(val);
}

int16_t Spinner::hit(TS_Point p)
{
  int16_t hit = -1;
  
  hit = minus_btn.hit(p);
  if (hit > -1) return hit;

  hit = plus_btn.hit(p);
  if (hit > -1) return hit;

  hit = text_val.hit(p);
  if (hit > -1) return hit;

  return hit;
}