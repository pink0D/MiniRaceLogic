#include "Settings.h"
#include "RaceLogic.h"
#include "Optic.h"
#include "Radio.h"

static RaceLogic *s_pRaceLogic;

void RaceLogic::send_radio_data() {
  s_Radio.send({race_status,system_status,logic_mode,velocity,lap_count,lap_time,best_time});
}

void RaceLogic::process_radio_data (DataPackage data){

  race_status = data.race_status;
  system_status = data.system_status;
  logic_mode = data.logic_mode;
  lap_count = data.lap_count;
  lap_time = data.lap_time;
  best_time = data.best_time;

  switch (data.race_status) {
    case RaceLogicEnum::IDLE: {
      event_idle();
      break;
    }
    case RaceLogicEnum::COUNTDOWN: {
      event_countdown();
      break;
    }
    case RaceLogicEnum::START: {
      event_start();
      break;
    }
    case RaceLogicEnum::FINISH: {
      event_finish();
      break;
    }
    case RaceLogicEnum::FALSE_START: {
      event_false_start();
      break;
    }
    case RaceLogicEnum::SYSTEM_STATUS: {
      event_system_status();
      break;
    }
    case RaceLogicEnum::TOGGLE_MODE: {
      event_toggle_mode();
      break;
    }
    case RaceLogicEnum::LAP: {
      event_lap();
      break;
    }
  }
}

void RaceLogic::loop() {
  if (s_Optic.get_update_flag()){

    if ( (race_status == RaceLogicEnum::IDLE) && (s_Optic.get_signal() == 1) ){
      if (s_Optic.get_velocity() > 0)
        event_passthrough();
    }

    s_Optic.reset_update_flag();
  }

  if ( (time_idle_reset > 0) && (millis() > time_idle_reset) ) {
    time_idle_reset = 0;
    race_status = RaceLogicEnum::IDLE;
    event_idle();
  }
}

void RaceLogic::set_time_idle_reset(unsigned long timeout = RACE_DEFAULT_TIMEOUT) {
  time_idle_reset = millis() + timeout;

  if (timeout == 0)
    time_idle_reset = 0;
}