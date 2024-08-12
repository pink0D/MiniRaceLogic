const Tone tone_power_on[] PROGMEM = {
{600,100},
{800,100}
};
const size_t tone_power_on_size = sizeof(tone_power_on);

const Tone tone_power_off[] PROGMEM = {
{800,100},
{600,100}
};
const size_t tone_power_off_size = sizeof(tone_power_off);

const Tone tone_finish[] PROGMEM = {
{1000,100},
{1250,100},
{1500,100}
};
const size_t tone_finish_size = sizeof(tone_finish);

const Tone tone_passthrough[] PROGMEM = {
{1250,50},
{1500,50},
{1750,50},
{2000,50}
};
const size_t tone_passthrough_size = sizeof(tone_passthrough);

const Tone tone_false_start[] PROGMEM = {
{100 ,500}
};
const size_t tone_false_start_size = sizeof(tone_false_start);

const Tone tone_f1_start[] PROGMEM = {
{0  ,5000},
{250,250},
{0  ,4750},
{250,250},
{0  ,4750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{250,250},
{0  ,750},
{500,500}
};
const size_t tone_f1_start_size = sizeof(tone_f1_start);

const Tone tone_simple_start[] PROGMEM = {
{250,250},
{0  ,4750},
{250,250},
{0  ,1750},
{500,500}
};
const size_t tone_simple_start_size = sizeof(tone_simple_start);

const Tone tone_error[] PROGMEM = {
{400,500}
};
const size_t tone_error_size = sizeof(tone_error);
