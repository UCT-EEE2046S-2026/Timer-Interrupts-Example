#ifndef TIMER14_H
#define TIMER14_H

#include "stm32f0xx.h"

/* Timer Clock Frequency known from Clock Tree */
#define TIM14_CLOCK_FREQ 8000000

void	 Config_TIM14(uint16_t prescaler_value, uint16_t auto_reload_value);
// void	 Config_TIM14_Interrupt(void);
void	 Start_TIM14(void);
void	 Stop_TIM14(void);
uint16_t Count_TIM14(void);

#endif // TIMER14_H
