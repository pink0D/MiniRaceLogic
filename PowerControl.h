#ifndef _POWERCONTROL_H_
#define _POWERCONTROL_H_

class PowerControl {
  public:
    void on();
    void loop();
    void off();
    void timer_reset();

  private:
    unsigned long time_auto_power_off = 0;
};

extern PowerControl s_PowerControl;

#endif