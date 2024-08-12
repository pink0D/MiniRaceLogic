#include "Settings.h"
#include "Radio.h"
#include "RaceLogic.h"
#include "PowerControl.h"

static Radio s_Radio;

Radio::Radio() : rf(RF_CE_PIN, RF_CSN_PIN) {

}

void Radio::begin() {
  rf.begin();
  if(rf.isPVariant()) {
    rf.setChannel(RF_CHANNEL);                         
    rf.setDataRate(RF_DATARATE);                 
    rf.setPALevel(RF_PALEVEL);
  }
}

void Radio::prepare_listen() {
  if (DEVICE_TYPE == DEVICE_TYPE_START) {
    rf.openReadingPipe(1, RF_ADDRESS_FINISH);
  } else {
    rf.openReadingPipe(1, RF_ADDRESS_START);
  }
  rf.startListening();
}

void Radio::prepare_send() {
  rf.stopListening();
  if (DEVICE_TYPE == DEVICE_TYPE_START) {
    rf.openWritingPipe(RF_ADDRESS_START);
  } else {
    rf.openWritingPipe(RF_ADDRESS_FINISH);
  }  
}

void Radio::loop() {
  if (rf.available()) {
    rf.read(&update, sizeof(DataPackage));
    s_pRaceLogic->process_radio_data(update);
    s_PowerControl.timer_reset(); // reset auto power off timer if device is receiving data
  }

  if (send_update) {  
    prepare_send();  
    update.timestamp = millis();
    rf.write(&update, sizeof(DataPackage));
    send_update = false;
    prepare_listen();
    s_PowerControl.timer_reset(); // reset auto power off timer if device is sending data
  }
}

void Radio::send(DataPackage data) {
  update = data;
  update.timestamp = millis();
  send_update = true;
}

DataPackage Radio::get_update() {
  return update;
}