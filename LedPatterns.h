#ifndef _LEDPATTERNS_H_
#define _LEDPATTERNS_H_

extern const LedColor led_color_palette[];
extern const size_t led_color_palette_size;

extern const LedPattern led_empty_pattern;

extern const LedPattern led_welcome[] PROGMEM;
extern const size_t led_welcome_size;

extern const LedPattern led_passthrough[] PROGMEM;
extern const size_t led_passthrough_size;

extern const LedPattern led_false_start[] PROGMEM;
extern const size_t led_false_start_size;

extern const LedPattern led_f1[] PROGMEM;
extern const size_t led_f1_size;

extern const LedPattern led_f1_start[] PROGMEM;
extern const size_t led_f1_start_size;
extern const unsigned long led_f1_start_countdown;

extern const LedPattern led_simple[] PROGMEM;
extern const size_t led_simple_size;

extern const LedPattern led_simple_start[] PROGMEM;
extern const size_t led_simple_start_size;
extern const unsigned long led_simple_start_countdown;

extern const LedPattern led_finish[] PROGMEM;
extern const size_t led_finish_size;

extern const LedPattern led_error[] PROGMEM;
extern const size_t led_error_size;

extern const LedPattern led_track_mode[] PROGMEM;
extern const size_t led_track_mode_size;

extern const LedPattern led_lap_mode[] PROGMEM;
extern const size_t led_lap_mode_size;

#endif