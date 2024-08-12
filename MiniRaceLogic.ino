#include <RCSwitch.h>
#include <avr/wdt.h>

#include <LCD_AIP31068_I2C_WCHAR.h>
#include <LCD_CharMap_RUS.h>

#include "Settings.h"
#include "PowerControl.h"
#include "LedPanel.h"
#include "LedPatterns.h"
#include "TonePlayer.h"
#include "SoundTones.h"
#include "LCD.h"
#include "Radio.h"
#include "Optic.h"
#include "RaceLogic.h"

#include "LedPatterns_PROGMEM.h"
#include "SoundTones_PROGMEM.h"

RCSwitch rcswitch;

void setup() {
  s_TonePlayer.begin();

  Serial.begin(9600);

  if (DEVICE_TYPE == DEVICE_TYPE_FINISH) {
    s_LCD.init();
    s_LCD.clear();   
  }
  
  if (DEVICE_TYPE == DEVICE_TYPE_START) {
    rcswitch.enableReceive(digitalPinToInterrupt(RC_PIN)); 
    s_LedPanel.begin();
    s_LedPanel.stop();
  }

  s_PowerControl.on();
  
  if (DEVICE_TYPE == DEVICE_TYPE_START) {
    s_LedPanel.start_play_pgm_patterns(led_welcome,led_welcome_size);
  }

  if (DEVICE_TYPE == DEVICE_TYPE_FINISH) {
    s_LCD.setCursor(5,0);
    s_LCD.print("ПРИВЕТ");
  }

  s_Radio.begin();
  s_Radio.prepare_listen();

  s_Optic.begin();

  if (DEVICE_TYPE == DEVICE_TYPE_START)
    s_pRaceLogic = new RaceLogicStart();
  if (DEVICE_TYPE == DEVICE_TYPE_FINISH)
    s_pRaceLogic = new RaceLogicFinish();

  if (WATCHDOG_ENABLE == 1)
    wdt_enable(WDTO_8S);
}

void loop() {
  wdt_reset();

  if (DEVICE_TYPE == DEVICE_TYPE_START) {
     rcswicth_loop();   
     s_LedPanel.loop();
  }

  s_Radio.loop();
  s_PowerControl.loop();
  s_TonePlayer.loop(); 

  s_pRaceLogic->loop(); 
}

void rcswicth_loop() {
  if (rcswitch.available()) {
    unsigned long hex = rcswitch.getReceivedValue();

    s_pRaceLogic->rc_command(hex);
  
    rcswitch.resetAvailable();
    s_PowerControl.timer_reset(); // reset auto off timer after RC command
  }
}

