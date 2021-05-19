#ifndef _PLOT_H_
#define _PLOT_H_

#include "ui/control.h"

class Plot : public Control
{
public:
  Plot();
  Plot(uint8_t ref);
  Plot(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t ref);

  void draw(ILI9341_t3* tft, bool pressed=false);
  
};


#endif 