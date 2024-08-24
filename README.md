# About
This toy project builds some kind of electronic start and finish lines to be used with 1:64 scale cars and tracks (a.k.a. Hot Wheels)

### Features:
- 433 mhz remote control 
- RF communication between start/finish lines
- car velocity and finish time indication
- dual mode logic: track mode (finish time only) and circuit mode (lap time and best time)
- false start trigger
- sound effects with passive buzzer
- auto power off

### Demo videos:

[Demo video 1 on YouTube](https://www.youtube.com/watch?v=u52nJqy7JgE)
[![video2](https://img.youtube.com/vi/u52nJqy7JgE/0.jpg)](https://www.youtube.com/watch?v=u52nJqy7JgE)

[Demo video 2 on YouTube]([https://www.youtube.com/watch?v=u52nJqy7JgE](https://www.youtube.com/watch?v=M21zNXTgTHc))
[![video3](https://img.youtube.com/vi/M21zNXTgTHc/0.jpg)](https://www.youtube.com/watch?v=M21zNXTgTHc)

# Hardware

### Required components
- 2x RF-Nano, resistors, transistors, LEDs (including IR), photodiodes, pushbuttons, passive buzzers, batteries
- 4x8 RGB LED HAT (or similiar addressable LED strip / matrix), 433 mhz remote and receiver for start controller
- LCD1602 with I2C connection for finish controller

### Wiring diagram
Same both for start and finish controllers (the only difference is that LED matrix is connected to start, and LCD is connected to finish)

![Wiring!](https://github.com/pink0D/MiniRaceLogic/blob/main/Wiring/MiniRaceLogic_Wiring_RFNano.png?raw=true "Wiring")

# Firmware
Arduino sketch is common both for start and finish.
Look at `#define` inside `Settings.h` before uploading and comment/uncomment `#define DEVICE_TYPE` line to load sketch to start or to finish controller

# Repo structure
- Arduino code (depends on [LCD_AIP31068_I2C_WCHAR](https://github.com/pink0D/LCD_AIP31068_I2C_WCHAR) library)
- STL files which can be used to 3D print shells. Autodesk Fusion source file is also available
