/**
 * Implementation of microsound library for stm32f4xx microcontroller with sound output via
 * DAC (Pin PA4 on stm32f407vgt6).
 * This implementation uses timer TIM6.
 */

#include <stm32f4xx_tim.h>

#include "microsound.h"

#define TIMER_CLOCK 	HSI_VALUE
#define TIMER_PRESCALE 	0
#define TIMER_INT_CNT 	(TIMER_CLOCK / MICROSOUND_FREQUENCY / (TIMER_PRESCALE + 1))

void initSound() {
	/* Switch on DAC */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	/* Switch on timer 6 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);

	/* Init DAC Pin */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Init timer */
	TIM6->PSC = TIMER_PRESCALE; // prescaler
	TIM6->ARR = TIMER_INT_CNT; // interrupt counter
	TIM6->DIER |= TIM_DIER_UIE; // allow timer interrupt
	TIM6->CR1 |= TIM_CR1_CEN; // start timer
	NVIC_EnableIRQ(TIM6_DAC_IRQn); // allow interrupt TIM6_DAC_IRQn

	/* Switch on DAC1 */
	DAC->CR |= DAC_CR_EN1;

	playSound(silence);
}

void TIM6_DAC_IRQHandler(void) {
	uint16_t val = getNextSample();

	TIM6->SR &= ~TIM_SR_UIF; // reset flag UIF
	DAC->DHR12L1 = val; // push next value

    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
