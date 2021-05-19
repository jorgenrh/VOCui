#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <stdint.h>

#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

class Control
{
public:
  Control();

  void setCoords(uint16_t x, uint16_t y, uint16_t w=0, uint16_t h=0, bool c=false);
  void setRef(uint8_t ref);
  void setText(const char* t);
  void setFont(const ILI9341_t3_font_t &f);
  virtual int16_t hit(TS_Point p);

  //void setValue(int16_t val);
  virtual void setValue(const char* val);
  
  void setBackground(uint16_t b);

  char text[32] = {};
  char old_text[32] = {};

  struct {
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t w = 0;
    uint16_t h = 0;
    boolean centered = false;
  } coord;

  int8_t _ref = -1; 

  uint16_t fc = ILI9341_WHITE;
  uint16_t bc = ILI9341_BLACK;

  const ILI9341_t3_font_t *font;

  bool val_updated = false;
};


#endif 