#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <ILI9341_t3.h>

#define COLOR_FG ILI9341_WHITE
#define COLOR_BG ILI9341_BLACK
#define COLOR_PAGE_BG ILI9341_NAVY

#define SENSE_MEASUREMENTS 200 // averaging over

#define RELAY1_PIN 4
#define RELAY2_PIN 5
#define RELAY3_PIN 6

#define TOUCH_IRQ 14

#define PWM_LED 3

#define TFT_WIDTH 320
#define TFT_HEIGHT 240
#define TFT_DC  9
#define TFT_CS 10

#define TOUCH_CS  8
#define SD_CS 17

#define CURRENT_PIN 32
#define SENSE_PIN 21

#define NUM_DATA_POINTS 480

#define LOG_MINUTE_INTERVAL 3 // minutes
#define LOG_BUFFER_SIZE 60/LOG_MINUTE_INTERVAL*8
#define LOG_DELAY 1000 //LOG_MINUTE_INTERVAL*60*1000



#endif