MCU=atmega328p
PROGRAMMER=arduino
F_CPU=16000000
LOCATION=/dev/ttyUSB0

CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -O3 -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=simply_xyz
SRCS=simple_xyz.c

$(info mcu=$(MCU) f_cpu=$(F_CPU) location=$(LOCATION))

all:
	$(info compiling)
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	$(info flashing)
	avrdude -p ${MCU} -P ${LOCATION} -c ${PROGRAMMER} -U flash:w:${TARGET}.hex:i -F

clean:
	rm -f *.bin *.hex
