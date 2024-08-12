#ifndef _RACELOGIC_H_
#define _RACELOGIC_H_

namespace RaceLogicEnum {
  enum RaceStatus {
    IDLE,
    COUNTDOWN,
    START,
    FINISH,
    FALSE_START,
    SYSTEM_STATUS,
    TOGGLE_MODE,
    LAP
  };

  enum SystemStatus {
    OK,
    ERROR_OPTIC_START,
    ERROR_OPTIC_FINISH
  };

  enum LogicMode {
    MODE_TRACK,
    MODE_LAP
  };
}

struct DataPackage {

  RaceLogicEnum::RaceStatus race_status;
  RaceLogicEnum::SystemStatus system_status;
  RaceLogicEnum::LogicMode logic_mode;

  double velocity;
  int lap_count;
  unsigned long lap_time;
  unsigned long best_time;

  unsigned long timestamp; // timestamp to make RF24 packets different each time 
};

class RaceLogic {
  public:
    virtual void loop();

    virtual void rc_command(unsigned long hex) {}
    virtual void process_radio_data (DataPackage data);

  protected:
    virtual void event_idle() {}
    virtual void event_countdown() {}
    virtual void event_start() {}
    virtual void event_finish() {}
    virtual void event_false_start() {}
    virtual void event_passthrough() {}
    virtual void event_system_status() {}
    virtual void event_toggle_mode() {}
    virtual bool event_lap() {}

    void set_time_idle_reset(unsigned long timeout = RACE_DEFAULT_TIMEOUT);
    void send_radio_data();

    RaceLogicEnum::RaceStatus race_status = RaceLogicEnum::IDLE;
    RaceLogicEnum::SystemStatus system_status = RaceLogicEnum::OK;

    RaceLogicEnum::LogicMode logic_mode = RaceLogicEnum::MODE_TRACK;
    
    unsigned long time_idle_reset = 0;
    unsigned long time_start = 0;
    unsigned long time_finish = 0;
    unsigned long time_lap_start = 0;

    double velocity;
    int lap_count;
    unsigned long lap_time;
    unsigned long best_time;

};

extern RaceLogic *s_pRaceLogic;

class RaceLogicStart : public RaceLogic {
  public:
    void rc_command(unsigned long hex);
    void loop();

  protected:
    virtual void event_idle();
    virtual void event_countdown();
    virtual void event_start();
    virtual void event_finish();
    virtual void event_false_start();
    virtual void event_passthrough();
    virtual void event_system_status();
    virtual void event_toggle_mode();
    virtual bool event_lap();

  private:
    int start_signal_type = 0;
    void toggle_start_pattern();

    void toggle_logic_mode();

    unsigned long time_rc = 0;
};

class RaceLogicFinish : public RaceLogic {
  public:
    void loop();

  protected:
    virtual void event_idle();
    virtual void event_countdown();
    virtual void event_start();
    virtual void event_finish();
    virtual void event_false_start();
    virtual void event_passthrough();
    virtual void event_system_status();
    virtual void event_toggle_mode();
    virtual bool event_lap();

  private:
    double start_velocity = 0;
    void print_velocity(String title, double velocity);
    void print_time(String title, unsigned long time);
    void print_right_with_space(String str, int row);
    String time_to_str(unsigned long time);

    int finish_display = 0;
    unsigned long time_next_toggle = 0;
    void toggle_finish_display();
};

#endif