/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 */

#include "main.h"
#include "gpio.h"
#include "stm32f0xx.h"

/* Timer Clock Frequency known from Clock Tree */
#define TIM_CLOCK_FREQ 8000000

void Config_TIM14(uint16_t prescaler_value, uint16_t auto_reload_value) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN; // Enable TIM14 clock
	TIM14->PSC = prescaler_value;		 // Set prescaler
	TIM14->ARR = auto_reload_value;		 // Set auto-reload value
}

void Start_TIM14(void) {
	TIM14->CR1 |= TIM_CR1_CEN; // Enable TIM14
}

void Stop_TIM14(void) {
	TIM14->CR1 &= ~TIM_CR1_CEN; // Disable TIM14
}

uint16_t Count_TIM14(void) {
	return TIM14->CNT; // Return current count value
}

int main(void) {
	Init_LEDs();
	Config_TIM14(
		(TIM_CLOCK_FREQ / 1000) - 1, //
		(1000 - 1)
	);

	Start_TIM14(); // Start TIM14
	while (1) {
		if (Count_TIM14() <= 500) {
			Set_LEDs(0x0F);
		} else {
			Set_LEDs(0xF0);
		}
	}
}

void Error_Handler(void) {

	while (1) {}
}
