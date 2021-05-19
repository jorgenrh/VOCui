#ifndef _VOC_H_
#define _VOC_H_

#include <stdint.h>

#include "common.h"
extern sense_data_t SensorData;
extern config_t ConfigData;

class VOC
{
public:
  VOC(const uint8_t pin);

  void read();

  uint8_t _pin;

  int16_t data[120];
  uint8_t idx = 0;


};



#endif