#pragma once

#include <stdint.h>

#define LED_BUILTIN (13u)

typedef enum {
  INPUT            = 0x0,
  OUTPUT           = 0x1,
  INPUT_PULLUP     = 0x2,
  INPUT_PULLDOWN   = 0x3,
  OUTPUT_OPENDRAIN = 0x4,
} PinMode;

typedef enum {
  LOW     = 0,
  HIGH    = 1,
  CHANGE  = 2,
  FALLING = 3,
  RISING  = 4,
} PinStatus;

typedef uint8_t pin_size_t;
typedef uint8_t byte;

void pinMode(pin_size_t pin, PinMode mode);
void digitalWrite(pin_size_t pin, PinStatus val);
PinStatus digitalRead(pin_size_t pin);

void delay(unsigned long ms);

void interrupts();
void noInterrupts();
