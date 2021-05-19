#include "control.h"

#include <ILI9341_t3.h>

Control::Control()
{
  
}

void Control::setCoords(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool c)
{
  coord = { x, y, w, h, c };
}

void Control::setRef(uint8_t ref)
{
  _ref = ref;
}

void Control::setText(const char* t)
{
  strcpy(old_text, text);
  strcpy(text, t);
}

void Control::setFont(const ILI9341_t3_font_t &f) 
{ 
  font = &f; 
}

int16_t Control::hit(TS_Point p)
{
  if (coord.centered && p.x >= coord.x-coord.w/2. && p.x <= coord.x+coord.w/2. && p.y >= coord.y-coord.h/2. && p.y <= coord.y+coord.h/2.) {
    return _ref;
  } else if (p.x >= coord.x && p.x <= (coord.x+coord.w) && p.y >= coord.y && p.y <= (coord.y+coord.h)) {
    return _ref;
  }

  return -1;
}

/*
void Control::setValue(int16_t val)
{
  char buff[16] = {};
  snprintf(buff, sizeof(buff), "%d", val);
  setText(buff);
  val_updated = true;
}
*/

void Control::setValue(const char* val)
{
  setText(val);
  val_updated = true;
}

void Control::setBackground(uint16_t b)
{
  bc = b;
}