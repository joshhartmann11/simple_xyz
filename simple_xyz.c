#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <avr/io.h>


// User defined

// Include your board header file defined in "boards" or create your own
#include "boards/arduino_nano.h"

// Define step and direction pins
#define STEP_X_PIN 2
#define DIR_X_PIN 3

#define STEP_Y_PIN 4
#define DIR_Y_PIN 5

#define STEP_Z_PIN 6
#define DIR_Z_PIN 7

// Define communication baudrate, MUST BE THE SAME AS IN "simple_xyz.py"
#define BAUD_RATE 250000



#define clear_bit(port, bit) (*port) &= ~(1 << (bit))
#define set_bit(port, bit) (*port) |= (1 << (bit))


typedef struct packet_t{
  int32_t steps_x;
  int32_t steps_y;
  int32_t steps_z;
  uint16_t delay;
} packet_t;


uint8_t uart_read_byte()
{
    while (!(UCSR0A & (1 << RXC0))){};
    return UDR0;
}


uint16_t uart_read_16()
{
    uint16_t res;
    res = uart_read_byte();
    res |= ((uint16_t)uart_read_byte() << 8);
    return res;
}


uint32_t uart_read_32()
{
    uint32_t res;
    res = uart_read_16();
    res |= ((uint32_t)uart_read_16() << 16);
    return res;
}


void read_packet(packet_t* packet)
{
    packet->steps_x = uart_read_32();
    packet->steps_y = uart_read_32();
    packet->steps_z = uart_read_32();
    packet->delay = uart_read_16();
}


// FIXME: Add linear interpolation?
inline void step_axis(int32_t* steps, uint8_t pin_step, uint8_t pin_dir)
{
    if (*steps)
    {
        clear_bit(PIN_PORT[pin_step], PIN_BIT[pin_step]);
        if (*steps < 0) set_bit(PIN_PORT[pin_dir], PIN_BIT[pin_dir]);
        set_bit(PIN_PORT[pin_step], PIN_BIT[pin_step]);
        *steps = (*steps > 0)? *steps-1: *steps+1;
    }
}


void make_move(packet_t* packet)
{
    int32_t max_moves = (abs(packet->steps_x) > abs(packet->steps_y))? abs(packet->steps_x): abs(packet->steps_y);
    max_moves = (max_moves > abs(packet->steps_z))? max_moves: abs(packet->steps_z);

    // Step at the same time
    for (uint32_t i = 0; i < max_moves; i++)
    {
        step_axis(&packet->steps_x, STEP_X_PIN, DIR_X_PIN);
        step_axis(&packet->steps_y, STEP_Y_PIN, DIR_Y_PIN);
        step_axis(&packet->steps_z, STEP_Z_PIN, DIR_Z_PIN);
        _delay_loop_2(packet->delay);
    }
}


void loop()
{
    packet_t packet;
    read_packet(&packet);
    make_move(&packet);
}


void setup_pin(uint8_t pin)
{
    assert(pin < PIN_N);
    set_bit(PIN_DDR[pin], PIN_BIT[pin]); // set as output
}


void setup()
{
    // Set up pins
    setup_pin(DIR_X_PIN);
    setup_pin(STEP_Y_PIN);
    setup_pin(DIR_Y_PIN);
    setup_pin(STEP_Z_PIN);
    setup_pin(DIR_Z_PIN);

    // Setup first UART to communicate with host
    uint16_t ubbr = (F_CPU / 4 / BAUD_RATE - 1) / 2; // calculate ubbr
    UCSR0B &= ~((1 << RXEN0) | (1 << TXEN0)); // disable rx and tx
    UBRR0H = (uint8_t)(ubbr >> 8); // set ubbr, data transmission speed
    UBRR0L = (uint8_t)ubbr;
    UCSR0A = (1 << U2X0); // set USART transmission doubler
    UCSR0B =  (1 << RXEN0) | (1 << TXEN0); // enable rx and tx
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // set frame format 8 data 2 stop
}


int main(void)
{
    setup();
    while(1) loop();
}
