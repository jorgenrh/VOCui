#include "voc.h"

#include <Arduino.h>
#include "config.h"

VOC::VOC(const uint8_t pin)
{ 
  _pin = pin; 
};

void VOC::read()
{
  long v = 0;
  uint16_t last = 100;
  for (uint8_t i=0; i < SENSE_MEASUREMENTS; i++) {
    //analogReadAveraging(SENSE_PIN);
    //last = analogRead(SENSE_PIN);
    last = dummySensor(last);
    v += last;
    delayMicroseconds(100);
  }
  uint16_t val = v / SENSE_MEASUREMENTS;
  uint16_t old_ppm = SensorData.ppm;
  SensorData.read = val;
  SensorData.ppm = map(val, 815, 4094, 0, 1000);
  if (SensorData.ppm >= ConfigData.ppm_alarm) {
    SensorData.status = SENSE_ALARM;
  } else if (SensorData.ppm >= (float)ConfigData.ppm_alarm*((float)ConfigData.ppm_warn/100.0)) {
    SensorData.status = SENSE_WARNING;
  } else if (SensorData.ppm < 0) {
    SensorData.status = SENSE_ERROR;
  } else {
    SensorData.status = SENSE_NORMAL;
  }
}