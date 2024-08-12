const LedColor led_color_palette[] = {
  {'R',0xFF0000},
  {'G',0x00FF00},
  {'B',0x0000FF},
  {'Y',0xF7B500},
  {'O',0xFF8000},
  {'W',0xAAAAAA}
};
const size_t led_color_palette_size = sizeof(led_color_palette);


const LedPattern led_empty_pattern = {
0,
{
"        ", 
"        ", 
"        ", 
"        "
}
};


const LedPattern led_welcome[] PROGMEM = {
  {
    100,
    {
    "RRRRRRRR", 
    "        ", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "RRRRRRRR", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "RRRRRRRR", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "        ", 
    "RRRRRRRR"
    }
  },
  {
    100,
    {
    "YYYYYYYY", 
    "        ", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "YYYYYYYY", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "YYYYYYYY", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "        ", 
    "YYYYYYYY"
    }
  },
  {
    100,
    {
    "GGGGGGGG", 
    "        ", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "GGGGGGGG", 
    "        ", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "GGGGGGGG", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "        ", 
    "GGGGGGGG"
    }
  }
};
const size_t led_welcome_size = sizeof(led_welcome);

const LedPattern led_passthrough[] PROGMEM = {
  {
    50,
    {
    "        ", 
    "        ", 
    "        ", 
    "GGGGGGGG"
    }
  },
  {
    50,
    {
    "        ", 
    "        ", 
    " GGGGGG ", 
    "        "
    }
  },
  {
    50,
    {
    "        ", 
    "  GGGG  ", 
    "        ", 
    "        "
    }
  },
  {
    50,
    {
    "   GG   ", 
    "        ", 
    "        ", 
    "        "
    }
  }
};
const size_t led_passthrough_size = sizeof(led_passthrough);

const LedPattern led_false_start[] PROGMEM = {
  {
    500,
    {
    "   RR   ", 
    "  RRRR  ", 
    "  RRRR  ", 
    "   RR   "
    }
  },
  {
    500,
    {
    "        ", 
    "        ", 
    "        ", 
    "        "
    }
  }
};
const size_t led_false_start_size = sizeof(led_false_start);

const LedPattern led_error[] PROGMEM = {
  {
    500,
    {
    "        ", 
    " YYYYYY ", 
    " YYYYYY ", 
    "        "
    }
  },
  {
    500,
    {
    "        ", 
    "        ", 
    "        ", 
    "        "
    }
  }
};
const size_t led_error_size = sizeof(led_error);

const LedPattern led_f1[] PROGMEM = {
  {
    1000,
    {
    "   GG   ", 
    "   YY   ", 
    "   RR   ", 
    "   RR   "
    }
  }
};
const size_t led_f1_size = sizeof(led_f1);

const LedPattern led_f1_start[] PROGMEM = {
  {
    5000,
    {
    "GGGGGGGG", 
    "        ", 
    "        ", 
    "        "
    }
  },
  {
    5000,
    {
    "        ", 
    "YYYYYYYY", 
    "        ", 
    "        "
    }
  },
  {
    5000,
    {
    "        ", 
    "        ", 
    "RRRRRRRR", 
    "RRRRRRRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    " RRRRRRR", 
    " RRRRRRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "  RRRRRR", 
    "  RRRRRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "   RRRRR", 
    "   RRRRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "    RRRR", 
    "    RRRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "     RRR", 
    "     RRR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "      RR", 
    "      RR"
    }
  },
  {
    1000,
    {
    "        ", 
    "        ", 
    "       R", 
    "       R"
    }
  }
};
const size_t led_f1_start_size = sizeof(led_f1_start);
const unsigned long led_f1_start_countdown = 22000;

const LedPattern led_simple[] PROGMEM = {
  {
    1000,
    {
    "   RR   ", 
    "   YY   ", 
    "   GG   ", 
    "   GG   "
    }
  }
};
const size_t led_simple_size = sizeof(led_simple);

const LedPattern led_simple_start[] PROGMEM = {
  {
    5000,
    {
    "RRRRRRRR", 
    "        ", 
    "        ", 
    "        "
    }
  },
  {
    2000,
    {
    "        ", 
    "YYYYYYYY", 
    "        ", 
    "        "
    }
  },
  {
    5000,
    {
    "        ", 
    "        ", 
    "GGGGGGGG", 
    "GGGGGGGG"
    }
  }
};
const size_t led_simple_start_size = sizeof(led_simple_start);
const unsigned long led_simple_start_countdown = 7000;

const LedPattern led_finish[] PROGMEM = {
  {
    100,
    {
    "WW  WW  ", 
    "WW  WW  ", 
    "  WW  WW", 
    "  WW  WW"
    }
  },
  {
    100,
    {
    " WW  WW ", 
    " WW  WW ", 
    "W   WW  W", 
    "W   WW  W"
    }
  },
  {
    100,
    {
    "  WW  WW", 
    "  WW  WW",
    "WW  WW  ", 
    "WW  WW  " 
    }
  },
  {
    100,
    {
    "W  WW  W", 
    "W  WW  W",
    " WW  WW ", 
    " WW  WW " 
    }
  }  
};
const size_t led_finish_size = sizeof(led_finish);

const LedPattern led_lap_mode[] PROGMEM = {
  {
    100,
    {
    " BBBOBB ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBOB ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBO ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      O", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      O", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " BBBBBO "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " BBBBOB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " BBBOBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " BBOBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " BOBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "B      B", 
    " OBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "B      B", 
    "O      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBBBBB ", 
    "O      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " OBBBBB ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BOBBBB ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  },
  {
    100,
    {
    " BBOBBB ", 
    "B      B", 
    "B      B", 
    " BBBBBB "
    }
  }  
};
const size_t led_lap_mode_size = sizeof(led_lap_mode);

const LedPattern led_track_mode[] PROGMEM = {
  {
    100,
    {
    "        ", 
    "        ", 
    "OBBBBBBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BOBBBBBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBOBBBBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBBOBBBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBBBOBBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBBBBOBB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBBBBBOB", 
    "        "
    }
  },
  {
    100,
    {
    "        ", 
    "        ", 
    "BBBBBBBO", 
    "        "
    }
  }
};
const size_t led_track_mode_size = sizeof(led_track_mode);
