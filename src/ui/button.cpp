#include "button.h"

#include <font_LiberationSansBold.h>

Button::Button() 
{
  setFont(LiberationSans_10_Bold);
}

Button::Button(uint8_t ref) 
{
  setRef(ref);
  setFont(LiberationSans_10_Bold);
}

Button::Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t ref)
{
  setCoords(x, y, w, h);
  setRef(ref);
  setFont(LiberationSans_10_Bold);
}

Button::Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *title, uint8_t ref)
{
  setCoords(x, y, w, h);
  setText(title);
  setRef(ref);
  setFont(LiberationSans_10_Bold);
}

//void Button::draw(ILI9341_t3 &tft)
//void UIButton::render(ILI9341_t3* tft, bool pressed)
void Button::draw(ILI9341_t3 *tft, bool pressed)
{
  tft->setFont(*font);
  tft->drawRect(coord.x, coord.y, coord.w, coord.h, fc);
  uint16_t pbc = (pressed ? fc : bc);  
  uint16_t pfc = (pressed ? bc : fc);  
  tft->fillRect(coord.x+1, coord.y+1, coord.w-2, coord.h-2, pbc);
  tft->setTextColor(pfc, pbc);
  tft->setCursor(coord.x+coord.w/2.-(tft->measureTextWidth(text)/2.), coord.y+coord.h/2.0-(tft->measureTextHeight(text)/2.0));
  tft->print(text);
}