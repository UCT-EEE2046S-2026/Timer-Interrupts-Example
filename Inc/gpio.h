#ifndef GPIO_H
#define GPIO_H

#include "stm32f0xx.h"

void Init_LEDs(void);
void Write_LEDs(uint8_t value);
void Toggle_LEDs(uint8_t pin_mask);

#endif // GPIO_H
