#ifndef _LEDPANEL_H_
#define _LEDPANEL_H_

#include <Adafruit_NeoPixel.h>

#define LED_ROWS      4
#define LED_COLUMNS   8
#define LED_NUMPIXELS LED_ROWS * LED_COLUMNS

#define REPEAT_MAX 0xFF

struct LedColor {
  char code;
  uint32_t rgb;
};

struct LedPattern {
  uint16_t duration;
  const char pattern[LED_ROWS][LED_COLUMNS+1];
};

class LedPanel {
  public:
    LedPanel();

    void begin();
    void loop();

    uint16_t show_pgm_pattern(const LedPattern* pattern);
    void start_play_pgm_patterns (const LedPattern* patterns, unsigned int size_bytes, int repeat_count = 1, bool clear = true);
    void stop(bool clear = true);
    void set_brightness();
    uint8_t calc_brightness();

  private:
    Adafruit_NeoPixel pixels;

    uint8_t led_brightness = 1;

    const LedPattern* play_patterns = NULL;
    uint8_t play_frame_current = 0;
    uint8_t play_frame_count = 0;
    int play_repeat_count = 0;
    bool play_clear = true;
    unsigned long next_frame_time = 0;
};

extern LedPanel s_LedPanel;

#endif