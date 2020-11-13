# Simple XYZ
Simple python interface for moving stepper motors through Arduinos and step+dir sticks.

## Configuring and Uploading
1. Configure your pins and pin definition file in simple_xyz.c
2. Check the makefile and match it to your device
3. `make` to make the firmware
4. `make flash` to flash the firmware

## Requirements
- avrdude
- avr-gcc
- pyserial
- python3 (not tested on python2.7 but should work)
