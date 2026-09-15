#include "timer14.h"

void Config_TIM14(uint16_t prescaler_value, uint16_t auto_reload_value) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN; // Enable TIM14 clock
	TIM14->PSC = prescaler_value;		 // Set prescaler
	TIM14->ARR = auto_reload_value;		 // Set auto-reload value
	TIM14->EGR |= TIM_EGR_UG;			 // Update registers
	TIM14->SR &= ~TIM_SR_UIF;			 // Clear update interrupt flag
}

// void Config_TIM14_Interrupt() {
// 	TIM14->DIER |= TIM_DIER_UIE; // Enable update interrupt
// 	NVIC_EnableIRQ(TIM14_IRQn);	 // Enable TIM14 interrupt in NVIC
// }

void Start_TIM14(void) {
	TIM14->CR1 |= TIM_CR1_CEN; // Enable TIM14
}

void Stop_TIM14(void) {
	TIM14->CR1 &= ~TIM_CR1_CEN; // Disable TIM14
}

uint16_t Count_TIM14(void) {
	return TIM14->CNT; // Return current count value
}
