# Simple XYZ
Simple python interface for moving stepper motors through Arduinos and step+dir sticks.

## Configuring and Uploading
1. Configure your pins and pin definition file in configuration.h
2. Check the makefile to make sure it's consistent with your device
3. `make` to make the firmware
4. `make flash` to flash the firmware

## How to Use
```
import simple_xyz
device = simple_xyz.XYZ()
device.step(x=100)
```

## Requirements
- avrdude
- avr-gcc
- pyserial
- python3 (not tested on python2.7 but should work)
