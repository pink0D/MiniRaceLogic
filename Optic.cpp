#include "Settings.h"
#include "Optic.h"
#include "PowerControl.h"

static Optic s_Optic;

void int_optic() {
  s_Optic.handle_interrupt();
  s_PowerControl.timer_reset();  
}

void Optic::handle_interrupt() {

  if (test_mode) 
    return;

  int new_signal = digitalRead(OPTIC_SIGNAL_PIN); 
  unsigned long old_update_time = update_time;          

  if (signal != new_signal){
      signal = new_signal;
      update_time = millis();

      if (signal == 1) {
        velocity = (CAR_VELOCITY_SCALE * CAR_LENGTH_MM / (double) (update_time - old_update_time)); // meters per second

        if ( (velocity < 5) || (velocity > 500) )
          velocity = 0;
      }

      optic_updated = true;
  }
}

void Optic::begin() {
  pinMode(OPTIC_SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(OPTIC_SENSOR_POWER_PIN, HIGH);

  pinMode(OPTIC_LED_POWER_PIN, OUTPUT);
  digitalWrite(OPTIC_LED_POWER_PIN, HIGH);

  pinMode(OPTIC_SIGNAL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(OPTIC_SIGNAL_PIN), int_optic, CHANGE); 
}

bool Optic::get_update_flag() {
  return optic_updated;
}

unsigned long Optic::get_update_time() {
  return update_time;
}

int Optic::get_signal() {
  return signal;
}

double Optic::get_velocity() { // meters per seccond
  return velocity;
}

void Optic::reset_update_flag() {
  optic_updated = false;
}

void Optic::reset_velocity() {
  velocity = 0;
}

void Optic::set_test_mode(bool mode) {
  noInterrupts();
  test_mode = mode;
  interrupts();
}

bool Optic::test() {

  bool test_result = true;
  set_test_mode(true);
  
  digitalWrite(OPTIC_LED_POWER_PIN, LOW);
  delay(50);
  if ( digitalRead(OPTIC_SIGNAL_PIN) != 0)
    test_result = false;

  digitalWrite(OPTIC_LED_POWER_PIN, HIGH);
  delay(50);
  if ( digitalRead(OPTIC_SIGNAL_PIN) != 1)
    test_result = false;

  set_test_mode(false);
  return test_result;
}