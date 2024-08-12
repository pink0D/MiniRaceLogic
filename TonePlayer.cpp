#include "Settings.h"
#include "TonePlayer.h"

static TonePlayer s_TonePlayer;

void TonePlayer::begin() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, BUZZER_OFF_VALUE);
}

void TonePlayer::start_play_pgm_tones (const Tone* tones, unsigned int size_bytes, int repeat_count = 1) {
  stop();
  play_tones = tones;
  play_tone_current = 0;
  play_tone_count = size_bytes / sizeof(Tone);
  tones_repeat_count = repeat_count - 1;
  next_tone_time = 0;
}

void TonePlayer::stop() {
  noTone(BUZZER_PIN);
  play_tones = NULL;
  digitalWrite(BUZZER_PIN, BUZZER_OFF_VALUE);
}

void TonePlayer::loop() {
  if (play_tones != NULL) {
    unsigned long current_time = millis();

    if (current_time > next_tone_time) {

      if (play_tone_current == play_tone_count) {
        if (tones_repeat_count > 0) {
          play_tone_current = 0;
          tones_repeat_count--;
        } else {
          stop();
          return;
        }
      }

      Tone t;
      memcpy_P( &t, &play_tones[play_tone_current], sizeof(Tone));

      uint16_t duration = t.duration;
      uint16_t frequency = t.frequency;

      if (frequency > 0)
        tone(BUZZER_PIN,frequency);
      else {
        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, BUZZER_OFF_VALUE);
      }

      next_tone_time = current_time + duration;

      play_tone_current++;
    }
  }
}

void TonePlayer::start_play_pgm_tones_sync (const Tone* tones, unsigned int size_bytes) {
  int count = count = size_bytes / sizeof(Tone);
  for (int i=0; i<count; i++) {
    Tone t;
    memcpy_P( &t, &tones[i], sizeof(Tone));

    uint16_t duration = t.duration;
    uint16_t frequency = t.frequency;

    if (frequency > 0)
      tone(BUZZER_PIN,frequency);
    else {
      noTone(BUZZER_PIN);
      digitalWrite(BUZZER_PIN, BUZZER_OFF_VALUE);
    }
    delay(duration);
  }
  stop();
}

