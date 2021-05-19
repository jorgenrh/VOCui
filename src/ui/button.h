#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdint.h>
#include <ILI9341_t3.h>


#include "control.h"

class Button : public Control
{
public:
  Button();
  Button(uint8_t ref);
  Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t ref);
  Button(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char *title, uint8_t ref);

  void draw(ILI9341_t3* tft, bool pressed=false);





};


#endif