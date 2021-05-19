#ifndef _LABEL_H_
#define _LABEL_H_

#include <ILI9341_t3.h>

#include "ui/control.h"


class Label : public Control
{
public:
  Label();
  Label(uint16_t x, uint16_t y, const char *title, uint8_t ref);
  Label(uint16_t x, uint16_t y, bool c, const char *title, uint8_t ref);

  void draw(ILI9341_t3* tft, bool clear=false);
  //void setValue(const char* val);

  bool centered = false;
  uint8_t size = 1;
  bool bold = true;



};


#endif