#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#include "stm32f4_discovery.h"

inline void initLeds(uint16_t leds) {
	// Enable the GPIO Clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// GPIO Configuration
	GPIO_InitTypeDef GPIO_InitStruct_Leds;
	GPIO_InitStruct_Leds.GPIO_Pin = leds; // Leds selected
	GPIO_InitStruct_Leds.GPIO_Mode = GPIO_Mode_OUT; // Mode out !
	GPIO_InitStruct_Leds.GPIO_Speed = GPIO_Speed_50MHz; // 50 MHZ clock frequency
	GPIO_InitStruct_Leds.GPIO_OType = GPIO_OType_PP; // Push pull mode
	GPIO_InitStruct_Leds.GPIO_PuPd = GPIO_PuPd_NOPULL; // No pull
	GPIO_Init(GPIOD, &GPIO_InitStruct_Leds);
}

inline void initButton() {
	// Enable the GPIO Clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// GPIO Configuration
	GPIO_InitTypeDef GPIO_InitStruct_Btn;
	GPIO_InitStruct_Btn.GPIO_Pin = USR_BTN; // Button selected
	GPIO_InitStruct_Btn.GPIO_Mode = GPIO_Mode_IN; // Mod in !
	GPIO_InitStruct_Btn.GPIO_Speed = GPIO_Speed_50MHz; // 50 MHZ clock frequency
	GPIO_InitStruct_Btn.GPIO_OType = GPIO_OType_PP; // Push pull mode
	GPIO_InitStruct_Btn.GPIO_PuPd = GPIO_PuPd_DOWN; // Pull down
	GPIO_Init(GPIOA, &GPIO_InitStruct_Btn);
}
