#include "Settings.h"
#include "LedPanel.h"
#include "LedPatterns.h"

static LedPanel s_LedPanel;

LedPanel::LedPanel() : pixels(LED_NUMPIXELS, LED_SIGNAL_PIN, NEO_GRB + NEO_KHZ800) {

}

void LedPanel::begin() {
  pixels.begin();
}

void LedPanel::loop() {
  if (play_patterns != NULL) {
    unsigned long current_time = millis();

    if (current_time > next_frame_time) {

      if (play_frame_current == play_frame_count) {
        if (play_repeat_count > 0) {
          play_frame_current = 0;
          if (play_repeat_count != REPEAT_MAX) {
            play_repeat_count--;
          }
        } else {
          stop(play_clear);
          return;
        }
      }

      uint16_t duration = show_pgm_pattern(&play_patterns[play_frame_current]);
      next_frame_time = current_time + duration;

      play_frame_current++;
    }
  }
}

void LedPanel::start_play_pgm_patterns (const LedPattern* patterns, unsigned int size_bytes, int repeat_count = 1, bool clear = true) {
  play_patterns = patterns;
  play_frame_current = 0;
  play_frame_count = size_bytes / sizeof(LedPattern);
  play_repeat_count = (repeat_count == REPEAT_MAX ? REPEAT_MAX : repeat_count - 1);
  play_clear = clear;
  next_frame_time = 0;
}

void LedPanel::stop(bool clear = true) {
  play_patterns = NULL; 
  if (clear) {
    pixels.clear();
    pixels.show();
  }
}

uint16_t LedPanel::show_pgm_pattern(const LedPattern* pattern) {
  pixels.clear();
  pixels.setBrightness(calc_brightness());

  LedPattern p = led_empty_pattern;
  memcpy_P( &p, pattern, sizeof(LedPattern));

  uint8_t sz = led_color_palette_size / sizeof (LedColor);

  for (int r=0; r<LED_ROWS; r++) {
    for (int c=0; c<LED_COLUMNS; c++) {
      
      char code = p.pattern[r][c];
      uint32_t rgb = 0;
      if (code != 0x20) {
        for (int i=0; i<sz; i++) {
          if (led_color_palette[i].code == code) {
            rgb = led_color_palette[i].rgb;
            break;
          }
        }
      }

      pixels.setPixelColor((LED_ROWS-r-1)*LED_COLUMNS + (LED_COLUMNS-c-1), rgb);
    }
 }

  pixels.show();

  return p.duration;
}

uint8_t LedPanel::calc_brightness() {
  return 255.0*((double)led_brightness/8.0);
}

void LedPanel::set_brightness() {

  led_brightness++;
  if (led_brightness == 9)
    led_brightness = 1;

  pixels.clear();
  pixels.setBrightness(calc_brightness());

  for (int i=0; i < led_brightness; i++) {
    pixels.setPixelColor(15-i,0xFFFFFF);
  }

  pixels.show();
  delay(1000);
  pixels.clear();
  pixels.show();
}