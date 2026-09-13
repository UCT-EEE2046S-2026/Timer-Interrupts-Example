#include "gpio.h"

void Init_LEDs(void) {
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN; // Enable GPIOB clock
	// PB0-PB7 as output
	GPIOB->MODER |=
		(						  //
			GPIO_MODER_MODER0_0	  //
			| GPIO_MODER_MODER1_0 //
			| GPIO_MODER_MODER2_0 //
			| GPIO_MODER_MODER3_0 //
			| GPIO_MODER_MODER4_0 //
			| GPIO_MODER_MODER5_0 //
			| GPIO_MODER_MODER6_0 //
			| GPIO_MODER_MODER7_0
		);
}

void Set_LEDs(uint8_t value) {
	GPIOB->ODR = (GPIOB->ODR & ~0xFF) | value; // Set PB0-PB7 to value
}
