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

[![video2](https://img.youtube.com/vi/u52nJqy7JgE/0.jpg)](https://www.youtube.com/watch?v=u52nJqy7JgE)

[![video3](https://img.youtube.com/vi/M21zNXTgTHc/0.jpg)](https://www.youtube.com/watch?v=M21zNXTgTHc)

# Hardware

### Required components
- 2x RF-Nano, resistors, transistors, LEDs (including IR), photodiodes, pushbuttons, passive buzzers, batteries
- 4x8 RGB LED HAT (or similiar addressable LED strip / matrix), 433 mhz remote and receiver for start
- LCD1602 with I2C connection for finish

### Wiring diagram
Same both for start and finish (the only difference is that LED matrix is connected to start, and LCD is connected to finish)
[![wiring]https://github.com/pink0D/MiniRaceLogic/blob/main/Wiring/MiniRaceLogic_Wiring_RFNano.png?raw=true]

# Firmware

# Repo structure
