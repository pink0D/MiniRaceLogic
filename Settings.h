#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <Arduino.h>

#define WATCHDOG_ENABLE 0   // WARNING! works only with optiboot (new bootloader). old bootloader can go into bootloop

#define DEVICE_TYPE_START  0
#define DEVICE_TYPE_FINISH 1

#define DEVICE_TYPE DEVICE_TYPE_START 
//#define DEVICE_TYPE DEVICE_TYPE_FINISH

#define CAR_LENGTH_MM 70.0 // car length in mm (type must be double!)
#define CAR_VELOCITY_SCALE 64.0 // velocity multiplier for 1:64 scale cars (type must be double!)

#define RACE_DEFAULT_TIMEOUT 5000 // timeout for system status reset (after finish / false start)
#define RACE_START_FINISH_TIMEOUT 30000 // timeout for race status reset (in track mode)
#define RACE_LAP_TIMEOUT  60000 // race timeout (in lap mode)
#define RACE_LAP_MINIMUM  2000 // min lap time (in lap mode)

#define POWER_ON_TIMEOUT 500 // ms to wait for button power on
#define POWER_OFF_TIMEOUT 1000 // ms to wait for button power off
#define POWER_IDLE_TIMEOUT 300000 // ms for auto power off

#define POWER_CTL_PIN 4
#define POWER_BTN_PIN 5
#define POWER_LED_PIN 6

#define RC_PIN 3 

#define LED_SIGNAL_PIN   7

#define LCD_ADDRESS 0x7c>>1
#define LCD_ROWS 2
#define LCD_COLUMNS 16

#define BUZZER_PIN   8
#define BUZZER_OFF_VALUE HIGH // some buzzers are low-level triggered, so HIGH value turns VCC off

#define OPTIC_SIGNAL_PIN 2
#define OPTIC_SENSOR_POWER_PIN A3
#define OPTIC_LED_POWER_PIN A2

#define RF_CE_PIN 10
#define RF_CSN_PIN 9
#define RF_CHANNEL 27
#define RF_DATARATE RF24_1MBPS
#define RF_PALEVEL RF24_PA_MAX

const byte RF_ADDRESS_START[6] = "MRL2S";
const byte RF_ADDRESS_FINISH[6] = "MRL2F";

#define RC_TIMEOUT 1000

#define RC1_BUTTON1 0x0F7A88
#define RC1_BUTTON2 0x0F7A84
#define RC1_BUTTON3 0x0F7A82
#define RC1_BUTTON4 0x0F7A81

#define RC2_BUTTON1 0x8B2E88
#define RC2_BUTTON2 0x8B2E84
#define RC2_BUTTON3 0x8B2E82
#define RC2_BUTTON4 0x8B2E81

#endif
