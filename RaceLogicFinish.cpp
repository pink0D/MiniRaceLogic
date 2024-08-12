#include "Settings.h"
#include "RaceLogic.h"
#include "TonePlayer.h"
#include "SoundTones.h"
#include "Radio.h"
#include "Optic.h"
#include "LCD.h"

void RaceLogicFinish::loop() {
  unsigned long time_current = millis();

  // TRACK MODE SPECIFIC

  if ( (logic_mode == RaceLogicEnum::MODE_TRACK) && (race_status == RaceLogicEnum::START ) 
      && (s_Optic.get_update_flag()) && (s_Optic.get_signal() == 0) )   
      {
        event_finish();
        send_radio_data();
      }

  if ( (logic_mode == RaceLogicEnum::MODE_TRACK) && (race_status == RaceLogicEnum::FINISH) ) {
    toggle_finish_display();
  }

  RaceLogic::loop();
}

void RaceLogicFinish::event_idle() {

  race_status = RaceLogicEnum::IDLE;
  s_LCD.clear();
  s_TonePlayer.stop();
}

void RaceLogicFinish::event_countdown() {

  if (!s_Optic.test()) {
    system_status = RaceLogicEnum::ERROR_OPTIC_FINISH;
    event_system_status();
    send_radio_data();
    return;
  } 

  s_LCD.clear();
  set_time_idle_reset(0);
}

void RaceLogicFinish::event_start() {

  s_LCD.clear();

  if (logic_mode == RaceLogicEnum::MODE_TRACK) {

    start_velocity = s_Radio.get_update().velocity;

    if (start_velocity > 0) {
      print_velocity("     СТАРТ",(int)start_velocity);

    } else {
      time_start = millis();     
      
      s_LCD.setCursor(5,0);
      s_LCD.print("СТАРТ"); 
    }

  } 

  race_status = RaceLogicEnum::START;

  if (logic_mode == RaceLogicEnum::MODE_TRACK)
    set_time_idle_reset(RACE_START_FINISH_TIMEOUT);

  if (logic_mode == RaceLogicEnum::MODE_LAP)
    set_time_idle_reset(0); 
}

void RaceLogicFinish::event_finish() {

  if (logic_mode == RaceLogicEnum::MODE_TRACK) {
    time_finish = millis() - time_start; 

    finish_display = 1;
    toggle_finish_display();

    s_TonePlayer.start_play_pgm_tones(tone_finish,tone_finish_size);
  }

  if (logic_mode == RaceLogicEnum::MODE_LAP) {
    s_LCD.clear();

    s_LCD.setCursor(0,0);
    s_LCD.print("ВСЕГО КРУГОВ");
    print_right_with_space(String(lap_count > 0 ? lap_count : 0), 0);

    if (lap_count > 0) {
      s_LCD.setCursor(0,1);
      s_LCD.print("ЛУЧШИЙ");
      s_LCD.setCursor(9,1);
      print_right_with_space(time_to_str(best_time), 1);
    }
  }

  race_status = RaceLogicEnum::FINISH;
  set_time_idle_reset(RACE_START_FINISH_TIMEOUT);
}

void RaceLogicFinish::event_false_start() {

  s_LCD.clear();
  
  s_LCD.setCursor(3,0);
  s_LCD.print("ФАЛЬСТАРТ");

  race_status = RaceLogicEnum::FALSE_START;
  set_time_idle_reset();
}

void RaceLogicFinish::event_passthrough() {
  
  print_velocity("    СКОРОСТЬ",(int)s_Optic.get_velocity());
  s_TonePlayer.start_play_pgm_tones(tone_passthrough,tone_passthrough_size);

  set_time_idle_reset();
}

bool RaceLogicFinish::event_lap() {

  if (lap_count == 0) 
    return;

  s_LCD.clear();

  s_LCD.setCursor(0,0);
  s_LCD.print("КРУГ "+String(lap_count));
  print_right_with_space(time_to_str(lap_time),0);

  s_LCD.setCursor(0,1);
  s_LCD.print("ЛУЧШИЙ");
  print_right_with_space(time_to_str(best_time),1);

  race_status = RaceLogicEnum::LAP;
  return true;
}

void RaceLogicFinish::event_system_status() {

  s_LCD.clear();
  
  s_LCD.setCursor(5,0);
  s_LCD.print("ОШИБКА");

  if (system_status == RaceLogicEnum::ERROR_OPTIC_FINISH) {
    s_TonePlayer.start_play_pgm_tones(tone_error,tone_error_size);
    s_LCD.setCursor(1,1);
    s_LCD.print("ДАТЧИКА ФИНИША");
  }
  if (system_status == RaceLogicEnum::ERROR_OPTIC_START) {
    s_LCD.setCursor(1,1);
    s_LCD.print("ДАТЧИКА СТАРТА");
  }

  race_status = RaceLogicEnum::SYSTEM_STATUS;
  set_time_idle_reset();
}

void RaceLogicFinish::event_toggle_mode() {

  s_LCD.clear();

  if (logic_mode == RaceLogicEnum::MODE_TRACK) {
    s_LCD.setCursor(2,0);
    s_LCD.print("РЕЖИМ ТРАССЫ");
  }

  if (logic_mode == RaceLogicEnum::MODE_LAP){
    s_LCD.setCursor(2,0);
    s_LCD.print("РЕЖИМ КРУГА");
  }

  race_status = RaceLogicEnum::TOGGLE_MODE;
  set_time_idle_reset();
}

void RaceLogicFinish::toggle_finish_display() {
  unsigned long time_current = millis();

  if (time_current < time_next_toggle) 
    return;

  time_next_toggle = time_current + 2500;

  finish_display++;
  if (finish_display == 2)
    finish_display = 0;

  if (finish_display == 0) {
    print_time("     ФИНИШ",time_finish);
  }
  if (finish_display == 1) {
    print_velocity("     СТАРТ",(int)start_velocity);
  }
}

void RaceLogicFinish::print_velocity(String title, double velocity) {

  s_LCD.clear();

  s_LCD.setCursor(0,0);
  s_LCD.print(title);

  String v = String((int)velocity);
  s_LCD.setCursor(LCD_COLUMNS/2 - floor(((double)(v.length()+5))/2),1);
  s_LCD.print(v);
  s_LCD.print(" км/ч");
}

String RaceLogicFinish::time_to_str(unsigned long time) {

  String str = "";

  unsigned long milliseconds = time;

  unsigned long minutes = floor(((double)milliseconds) / 60000.0);
  milliseconds -= minutes * 60000;

  unsigned long seconds = floor(((double)milliseconds) / 1000.0);
  milliseconds -= seconds * 1000;

  if (minutes > 0)
    str += String(minutes)+":";

  if ( (minutes > 0) && (seconds < 10) )
    str += "0";
  str += String(seconds)+".";

  if (milliseconds < 10)
    str += "0";
  if (milliseconds < 100)
    str += "0";
  str += String(milliseconds); 

  return str; 
}

void RaceLogicFinish::print_time(String title, unsigned long time) {
  
  String str = time_to_str(time);

  s_LCD.clear();

  s_LCD.setCursor(0,0);
  s_LCD.print(title);

  s_LCD.setCursor(LCD_COLUMNS/2 - floor(((double)(str.length()+4))/2),1);
  s_LCD.print(str);
  s_LCD.print(" сек");
}

void RaceLogicFinish::print_right_with_space(String str, int row) {
  int len = str.length() + 1;
  s_LCD.setCursor(16-len,row);
  s_LCD.print(" "+str);
}