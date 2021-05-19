#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>
#include <Arduino.h>

typedef enum {
  SENSE_NORMAL,
  SENSE_WARNING,
  SENSE_ALARM,
  SENSE_ERROR,
} sense_status_t;

typedef struct {
  uint16_t read = 0;
  int16_t ppm = 0;
  sense_status_t status = SENSE_NORMAL;
  int16_t ppm_min = 1000;
  int16_t ppm_max = 0;
  int16_t ppm_avg = 0;
} sense_data_t;

typedef struct {
  int16_t x = 0;
  int16_t y = 0;
  int16_t z = 0;
  struct {
    uint16_t x = 0;
    uint16_t y = 0;
    uint16_t z = 0;
  } raw;
} ts_point_t;

typedef struct {
  int16_t ppm_offset = 0;
  int16_t ppm_alarm = 120;
  uint8_t ppm_warn = 60;
  struct {
    ts_point_t tl = {  40,  40, 0 };
    ts_point_t tr = { 280,  40, 0 };
    ts_point_t br = { 280, 200, 0 };
    ts_point_t bl = {  40, 200, 0 };
  } ts_cal;
  uint16_t log_freq = 180;
} config_t;



inline float mapf(float x, float in_min, float in_max, float out_min, float out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

inline uint16_t dummySensor(uint16_t last_val, float p=0.1)
{
  //uint16_t r = random(0, last_val);
  uint8_t d = random(0, 1);
  return last_val*p*(d ? 1 : -1);
}


#endif

