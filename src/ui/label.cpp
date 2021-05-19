#include "label.h"

#include <font_LiberationSansBold.h>

Label::Label() 
{
  setFont(LiberationSans_10_Bold);
}

Label::Label(uint16_t x, uint16_t y, const char *title, uint8_t ref)
{
  setCoords(x, y);
  setText(title);
  setRef(ref);
  setFont(LiberationSans_10_Bold);
} 

Label::Label(uint16_t x, uint16_t y, bool c, const char *title, uint8_t ref)
{
  setCoords(x, y, 0, 0, c);
  setText(title);
  setRef(ref);
  setFont(LiberationSans_10_Bold);
} 

void Label::draw(ILI9341_t3* tft, bool clear)
{
  tft->setFont(*font);

  if (val_updated) {
    int16_t w = tft->measureTextWidth(old_text);
    int16_t h = tft->measureTextHeight(old_text);
    tft->setTextColor(bc, fc);
    if (coord.centered) {
      tft->setCursor(coord.x-(w/2.0), coord.y-(h/2.0));
    } else {
      tft->setCursor(coord.x, coord.y);
    }
    tft->print(old_text);
    val_updated = false;
  }

  coord.w = tft->measureTextWidth(text);
  coord.h = tft->measureTextHeight(text);
  if (clear) {
    tft->setTextColor(bc, fc);
  } else {
    tft->setTextColor(fc, bc);
  }
  if (coord.centered) {
    tft->setCursor(coord.x-(coord.w/2.0), coord.y-(coord.h/2.0));
  } else {
    tft->setCursor(coord.x, coord.y);
  }
  tft->print(text);
}