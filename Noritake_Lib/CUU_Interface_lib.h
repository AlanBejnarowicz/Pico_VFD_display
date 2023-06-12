#ifndef _CUU_Interface_lib_h_
#define _CUU_Interface_lib_h_


#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

/*

#define DIRECTION(X,D)  if (D) pinMode(X##_PIN, OUTPUT); else pinMode(X##_PIN, INPUT)
#define RAISE(X)	digitalWrite(X##_PIN, HIGH)
#define LOWER(X)	digitalWrite(X##_PIN, LOW)
#define CHECK(X)	digitalRead(X##_PIN)
#define SETPIN(X,V) digitalWrite(X##_PIN, (V)? HIGH: LOW)

*/


#define DIRECTION(X,D)  if (D) gpio_set_dir(X, GPIO_OUT); else gpio_set_dir(X, GPIO_IN)
#define INIT(X)     gpio_init(X)
#define RAISE(X)	gpio_put(X, 1)
#define LOWER(X)	gpio_put(X, 0)
#define CHECK(X)	gpio_get(X)
#define SETPIN(X,V) if (V == 1)gpio_put(X, 1) else gpio_put(X, 0)

#define _delay_ms(X) sleep_ms(X)
#define _delay_us(X) sleep_us(X)

class CUU_Interface {
public:
    virtual void init() = 0;
    virtual void write(uint8_t data, bool rs) = 0;
    virtual uint8_t read(bool rs) = 0;
    virtual bool is8bit() = 0;
};
#endif