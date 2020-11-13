#include <avr/io.h>
#include <stdint.h>

// Define ports of the digital pins
#define PIN_N 14
// port                   0      1      2      3      4      5      6      7      8      9     10     11     12     13
const uint8_t PIN_PORT[] = { PORTD, PORTD, PORTD, PORTD, PORTD, PORTD, PORTD, PORTD, PORTB, PORTB, PORTB, PORTB, PORTB, PORTB};
const uint8_t PIN_DDR[]   = {  DDRD,  DDRD,  DDRD,  DDRD,  DDRD,  DDRD,  DDRD,  DDRD,  DDRB,  DDRB,  DDRB,  DDRB,  DDRB,  DDRB};
const uint8_t PIN_BIT[]  = {(1<<0),(1<<1),(1<<2),(1<<3),(1<<4),(1<<5),(1<<6),(1<<7),(1<<0),(1<<1),(1<<2),(1<<3),(1<<4),(1<<5)};
