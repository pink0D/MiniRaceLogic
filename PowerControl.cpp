#include "Settings.h"
#include "PowerControl.h"
#include "TonePlayer.h"
#include "SoundTones.h"

static PowerControl s_PowerControl;

void PowerControl::on() {
  delay(POWER_ON_TIMEOUT); // delay for POWER ON button pressed
  pinMode(POWER_CTL_PIN, OUTPUT);
  digitalWrite(POWER_CTL_PIN, HIGH);

  pinMode(POWER_LED_PIN, OUTPUT);
  digitalWrite(POWER_LED_PIN, HIGH);

  timer_reset();

  s_TonePlayer.start_play_pgm_tones(tone_power_on,tone_power_on_size);
}

void PowerControl::loop() {
  if (millis() < 5000)
    return;
    
  // power off button
  if (digitalRead(POWER_BTN_PIN) == HIGH) {
    delay(POWER_OFF_TIMEOUT); // check for button is still pressed after timeout
    if (digitalRead(POWER_BTN_PIN) == HIGH)
      off();
  }

  //auto power off
  if ( (time_auto_power_off > 0) && (millis() > time_auto_power_off) )
     off();
}

void PowerControl::off() {
  s_TonePlayer.start_play_pgm_tones_sync(tone_power_off,tone_power_off_size);
  digitalWrite(POWER_CTL_PIN, LOW);
  time_auto_power_off = 0; 
}

void PowerControl::timer_reset() {
  time_auto_power_off = millis() + POWER_IDLE_TIMEOUT; 
}