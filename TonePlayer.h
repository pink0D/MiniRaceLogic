#ifndef _TONEPLAYER_H_
#define _TONEPLAYER_H_

struct Tone {
  uint16_t frequency;
  uint16_t duration;
};

class TonePlayer {
  public:
    void begin();
    void loop();

    void start_play_pgm_tones (const Tone* tones, unsigned int size_bytes, int repeat_count = 1);
    void start_play_pgm_tones_sync (const Tone* tones, unsigned int size_bytes);
    void stop();

  private:
    const Tone* play_tones = NULL;
    uint8_t play_tone_current = 0;
    uint8_t play_tone_count = 0;
    int tones_repeat_count = 0;
    unsigned long next_tone_time = 0;
};

extern TonePlayer s_TonePlayer;

#endif