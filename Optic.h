#ifndef _OPTIC_H_
#define _OPTIC_H_

class Optic {
  public:

    void begin();

    bool get_update_flag();
    unsigned long get_update_time();
    int get_signal();
    double get_velocity(); // meters per seccond

    void reset_update_flag();
    void reset_velocity();

    void handle_interrupt();

    bool test();

  private:

    int signal = 1;
    double velocity = 0;
    unsigned long update_time = 0;
    bool optic_updated = false;

    bool test_mode = false;
    void set_test_mode(bool mode);
};

extern Optic s_Optic;

#endif