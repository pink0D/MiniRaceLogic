#include "Settings.h"
#include "RaceLogic.h"
#include "LedPanel.h"
#include "LedPatterns.h"
#include "TonePlayer.h"
#include "SoundTones.h"
#include "Radio.h"
#include "Optic.h"

void RaceLogicStart::rc_command(unsigned long hex) {
  
  unsigned long time_current = millis();
  if (time_current - time_rc < RC_TIMEOUT)
    return;
  time_rc = time_current;

  //if (! ( (race_status == RaceLogicEnum::IDLE) || (race_status == RaceLogicEnum::FINISH) ) )
  //  return;

  if ( (hex == RC1_BUTTON1) || ((hex == RC2_BUTTON1)) ){
    
    if (logic_mode == RaceLogicEnum::MODE_TRACK)
      event_countdown();

    if (logic_mode == RaceLogicEnum::MODE_LAP) {
      if ( (race_status == RaceLogicEnum::START) || (race_status == RaceLogicEnum::LAP) )
        event_finish();
      else 
        event_countdown();
    }

    send_radio_data();
  }
  
  if ( (hex == RC1_BUTTON2) || ((hex == RC2_BUTTON2)) ){
    toggle_logic_mode();
    event_toggle_mode();
    send_radio_data();
  }
    
  if ( (hex == RC1_BUTTON3) || ((hex == RC2_BUTTON3)) )
    toggle_start_pattern();
  
  if ( (hex == RC1_BUTTON4) || ((hex == RC2_BUTTON4)) )
    s_LedPanel.set_brightness();
}

void RaceLogicStart::toggle_start_pattern() {
  start_signal_type++;
  if (start_signal_type == 2)
    start_signal_type = 0;

  if (start_signal_type == 0) 
    s_LedPanel.start_play_pgm_patterns(led_f1,led_f1_size);
  if (start_signal_type == 1) 
    s_LedPanel.start_play_pgm_patterns(led_simple,led_simple_size);
}

void RaceLogicStart::toggle_logic_mode() {
  if (logic_mode == RaceLogicEnum::MODE_TRACK)
    logic_mode = RaceLogicEnum::MODE_LAP;
  else
    logic_mode = RaceLogicEnum::MODE_TRACK;
}

void RaceLogicStart::loop() {
  unsigned long time_current = millis();

  // COMMON FOR ALL MODES

  if ( (race_status == RaceLogicEnum::COUNTDOWN) && (time_current > time_start) ) {
    event_start();
    send_radio_data();
  }

  if ( (race_status == RaceLogicEnum::COUNTDOWN) && (s_Optic.get_update_flag()) && (s_Optic.get_signal() == 0) ) {
    event_false_start();
    send_radio_data();
  }

  // TRACK MODE SPECIFIC

  if ( (logic_mode == RaceLogicEnum::MODE_TRACK) && (race_status == RaceLogicEnum::START) 
      && (s_Optic.get_update_flag()) && (s_Optic.get_signal() == 1) ) 
      {
        velocity = s_Optic.get_velocity();
        send_radio_data();
      }

  // LAP MODE SPECIFIC

  if ( (logic_mode == RaceLogicEnum::MODE_LAP) && ( (race_status == RaceLogicEnum::START) || (race_status == RaceLogicEnum::LAP) )
    && (s_Optic.get_update_flag()) && (s_Optic.get_signal() == 0) ) 
    {
      bool update = event_lap();
      velocity = 0;
      if (update)
        send_radio_data();
    }

  if ( (logic_mode == RaceLogicEnum::MODE_LAP) && ( (race_status == RaceLogicEnum::START) || (race_status == RaceLogicEnum::LAP) )
      && (time_current > time_lap_start + RACE_LAP_TIMEOUT) ) 
    {
      event_finish();
      send_radio_data();
    }

   RaceLogic::loop();
}

void RaceLogicStart::event_idle() {

  race_status = RaceLogicEnum::IDLE;
  s_LedPanel.stop();
  s_TonePlayer.stop();
}

void RaceLogicStart::event_countdown() {

  if (!s_Optic.test()) {
    system_status = RaceLogicEnum::ERROR_OPTIC_START;
    event_system_status();
    send_radio_data();
    return;
  }

  unsigned long time_countdown = 0;
  unsigned long time_current = millis();

  if (start_signal_type == 0) {
    s_LedPanel.start_play_pgm_patterns(led_f1_start,led_f1_start_size);
    s_TonePlayer.start_play_pgm_tones(tone_f1_start,tone_f1_start_size);
    time_countdown = led_f1_start_countdown;
  }
  if (start_signal_type == 1) {
    s_LedPanel.start_play_pgm_patterns(led_simple_start,led_simple_start_size,1,false);
    s_TonePlayer.start_play_pgm_tones(tone_simple_start,tone_simple_start_size);
    time_countdown = led_simple_start_countdown;
  }

  time_start = time_current + time_countdown;
  velocity = 0;

  race_status = RaceLogicEnum::COUNTDOWN;
  set_time_idle_reset(0);
}

void RaceLogicStart::event_start() {

  time_start = millis();
  time_lap_start = millis();
  lap_count = -1;
  best_time = 0;
  lap_time = 0;

  race_status = RaceLogicEnum::START;

  if (logic_mode == RaceLogicEnum::MODE_TRACK)
    set_time_idle_reset(RACE_START_FINISH_TIMEOUT);

  if (logic_mode == RaceLogicEnum::MODE_LAP)
    set_time_idle_reset(0); 
}

void RaceLogicStart::event_finish() {

  s_LedPanel.start_play_pgm_patterns(led_finish,led_finish_size,10);

  if (logic_mode == RaceLogicEnum::MODE_LAP)
    s_TonePlayer.start_play_pgm_tones(tone_finish,tone_finish_size);

  race_status = RaceLogicEnum::FINISH;
  set_time_idle_reset(RACE_START_FINISH_TIMEOUT);
}

void RaceLogicStart::event_false_start() {

  s_LedPanel.start_play_pgm_patterns(led_false_start,led_false_start_size,3);
  s_TonePlayer.start_play_pgm_tones(tone_false_start,tone_false_start_size);

  race_status = RaceLogicEnum::FALSE_START;
  set_time_idle_reset();
}

void RaceLogicStart::event_passthrough() {
  
  s_LedPanel.start_play_pgm_patterns(led_passthrough,led_passthrough_size);
  s_TonePlayer.start_play_pgm_tones(tone_passthrough,tone_passthrough_size);
}

void RaceLogicStart::event_system_status() {
  s_LedPanel.start_play_pgm_patterns(led_error,led_error_size,REPEAT_MAX);
  s_TonePlayer.stop();
  
  if (system_status == RaceLogicEnum::ERROR_OPTIC_START)
    s_TonePlayer.start_play_pgm_tones(tone_error,tone_error_size);

  race_status = RaceLogicEnum::SYSTEM_STATUS;
  set_time_idle_reset();
}

void RaceLogicStart::event_toggle_mode() {

  if (logic_mode == RaceLogicEnum::MODE_TRACK)
      s_LedPanel.start_play_pgm_patterns(led_track_mode,led_track_mode_size,1);

  if (logic_mode == RaceLogicEnum::MODE_LAP)
      s_LedPanel.start_play_pgm_patterns(led_lap_mode,led_lap_mode_size,1);

  race_status = RaceLogicEnum::TOGGLE_MODE;
  set_time_idle_reset();
}

bool RaceLogicStart::event_lap() {
  unsigned long time_current = millis();

  if (lap_count >= 0) {
    unsigned long new_lap_time = time_current - time_lap_start;

    if (new_lap_time < RACE_LAP_MINIMUM)
      return false;

    lap_time = new_lap_time;
    if ( (lap_time < best_time) || (best_time == 0) )
      best_time = lap_time;
  }

  time_lap_start = millis();
  lap_count++;

  event_passthrough();

  race_status = RaceLogicEnum::LAP;
  return true;
}
