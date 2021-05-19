#include "plot.h"


Plot::Plot() 
{
}

Plot::Plot(uint8_t ref) 
{
  setRef(ref);
}

Plot::Plot(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t ref)
{
  setCoords(x, y, w, h);
  setRef(ref);
}

void Plot::draw(ILI9341_t3 *tft, bool pressed)
{
  tft->setFont(*font);
  tft->drawRect(coord.x, coord.y, coord.w, coord.h, fc);
}