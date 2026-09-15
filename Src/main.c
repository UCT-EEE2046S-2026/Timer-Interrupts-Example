/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 */

#include "main.h"
#include "gpio.h"
#include "lcd.h"
#include "stm32f0xx.h"
#include "timer14.h"
#include <stdio.h>

void Config_TIM14_Interrupt() {
	TIM14->DIER |= TIM_DIER_UIE; // Enable update interrupt
	NVIC_EnableIRQ(TIM14_IRQn);	 // Enable TIM14 interrupt in NVIC
}

volatile uint16_t tim14_count = 0;

void TIM14_IRQHandler(void) {
	if (TIM14->SR & TIM_SR_UIF) { // Check if update interrupt flag is set
		TIM14->SR &= ~TIM_SR_UIF; // Clear update interrupt flag
		Toggle_LEDs(0xE0);		  // Toggle all LEDs (PB0-PB7)
		tim14_count++;			  // Increment count
	}
}

void Delay_ms(uint32_t ms) {
	const uint32_t cycles_per_ms = 8000 / 10;
	for (uint32_t i = 0; i < ms * cycles_per_ms; i++)
		__NOP();
}

LCD_Init_t lcd_init = {
	.delay_ms		  = Delay_ms,
	.set_E_pin		  = lcd_set_e_pin,
	.set_RS_pin		  = lcd_set_rs_pin,
	.set_DB0_DB7_pins = lcd_set_DB0_DB7_pins,
	.pin_mode		  = LCD_4BIT_MODE,
	.line_mode		  = LCD_2LINE,
	.font_size		  = LCD_5x8_DOTS
};

int main(void) {
	Init_LEDs();
	Init_LCD_GPIO();
	Config_TIM14(
		8000 - 1, // 1kHz Counter Tick (8MHz / 8000 = 1kHz)
		1000 - 1  // 1 second period (1000 ticks at 1kHz)
	);
	Config_TIM14_Interrupt(); // Enable TIM14 interrupt
	LCD_Init(&lcd_init);	  // Initialize the LCD

	char	 lcd_line1[17], lcd_line2[17];
	uint16_t delay_count = 0;

	Start_TIM14(); // Start TIM14

	while (1) {
		Delay_ms(1000);	   // Delay for 1 second
		Toggle_LEDs(0x07); // Toggle lower 4 LEDs (PB0-PB3)
		delay_count++;	   // Increment delay count

		snprintf(lcd_line1, sizeof(lcd_line1), "Delay Cnt: %hu", delay_count);
		snprintf(lcd_line2, sizeof(lcd_line2), "TIM14 Cnt: %hu", tim14_count);

		LCD_NewLine(0, 0); // Move to line 1 without clearing
		LCD_PutString(lcd_line1);
		LCD_NewLine(1, 0); // Move to line 2 without clearing
		LCD_PutString(lcd_line2);
	}
}

void Error_Handler(void) {

	while (1) {}
}
