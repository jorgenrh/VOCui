#include "page.h"
#include <ILI9341_t3.h>
#include <XPT2046_Touchscreen.h>

Page::Page()
{
}

void Page::setRef(int8_t ref)
{
  _ref = ref;
}

void Page::addControl(Button btn)
{
  _btns[_btn_idx++] = btn;  
}

void Page::addControl(Label lbl)
{
  _lbls[_lbl_idx++] = lbl;  
}

void Page::addControl(Spinner spn)
{
  _spns[_spn_idx++] = spn;  
}

void Page::addControl(Plot plt)
{
  _plts[_plt_idx++] = plt;  
}

void Page::render(ILI9341_t3 &tft)
{
  tft.fillScreen(bc);

  uint8_t i = 0;

  // Buttons
  for (i=0; i < _btn_idx; i++) {
    _btns[i].draw(&tft);
  }

  // Spinners
  for (i=0; i < _spn_idx; i++) {
    _spns[i].draw(&tft);
  }

  // Plots
  for (i=0; i < _plt_idx; i++) {
    _plts[i].draw(&tft);
  }

  // Labels
  for (i=0; i < _lbl_idx; i++) {
    _lbls[i].draw(&tft);
  }


}

/*
void Page::run(ILI9341_t3 &tft)
{
  Serial.println("Page::run");
}
*/

int16_t Page::getHitRef(TS_Point p)
{
  uint8_t i = 0;
  int16_t hit = -1;
  hit_time++;

  // Buttons
  for (i=0; i < _btn_idx; i++) {
    hit = _btns[i].hit(p);
    if (hit > -1) return hit;
  }

  // Spinners
  for (i=0; i < _spn_idx; i++) {
    hit = _spns[i].hit(p);
    if (hit > -1) return hit;
  }
  
  // Labels
  for (i=0; i < _plt_idx; i++) {
    hit = _plts[i].hit(p);
    if (hit > -1) return hit;
  }

  // Labels
  for (i=0; i < _lbl_idx; i++) {
    hit = _lbls[i].hit(p);
    if (hit > -1) return hit;
  }

  hit_time = 0;
  return -1;
}


void Page::updateControlValue(ILI9341_t3 &tft, int8_t ref, int16_t val)
{
  snprintf(buffer, sizeof(buffer), "%d", val);
  updateControlValue(tft, ref, buffer);
}

void Page::updateControlValue(ILI9341_t3 &tft, int8_t ref, const char* val)
{
  uint8_t i = 0;

  // Buttons
  for (i=0; i < _btn_idx; i++) { 
    if (_btns[i]._ref == ref) {
      _btns[i].setText(val);
      _btns[i].draw(&tft);
    }
  }

  // Spinners
  for (i=0; i < _spn_idx; i++) {
    if (_spns[i]._ref == ref) {
      _spns[i].setValue(val);
      _spns[i].draw(&tft);
    }
  }

  // Labels
  for (i=0; i < _lbl_idx; i++) {
    if (_lbls[i]._ref == ref) {
      _lbls[i].setValue(val);
      _lbls [i].draw(&tft);
    }
  }

}


void Page::setBackground(uint16_t b)
{
  bc = b;
}
