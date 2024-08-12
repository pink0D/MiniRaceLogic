#ifndef _RADIO_H_
#define _RADIO_H_

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include "RaceLogic.h"

class Radio {
  public:
    Radio();
    
    void begin();
    void prepare_listen();
    void prepare_send();
    void loop();

    void send(DataPackage data);
    DataPackage get_update();

  private:
    RF24 rf;

    bool send_update = false;
    DataPackage update;
};

extern Radio s_Radio;

#endif