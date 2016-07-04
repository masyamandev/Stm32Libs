/**
 * Implementation of microsound library for stm32f030 microcontroller with sound output via
 * PWM (Pin PA2 on stm32f030f4p6). Output sound is 8 bit.
 * This implementation uses 2 timers: TIM3 for interrupts and TIM2 for PWM.
 */

#include <stm32f0xx_gpio.h>
#include <stm32f0xx_tim.h>

#include "microsound.h"

#define TIMER_CLOCK 	HSI_VALUE
#define TIMER_PRESCALE 	0
#define TIMER_INT_CNT 	(TIMER_CLOCK / MICROSOUND_FREQUENCY / (TIMER_PRESCALE + 1))

void initSound() {

	/* Init timer 3 for interrupts */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	TIM3->PSC = TIMER_PRESCALE; // prescaler
	TIM3->ARR = TIMER_INT_CNT; // interrupt counter
	TIM3->DIER |= TIM_DIER_UIE; // allow timer interrupt
	TIM3->CR1 |= TIM_CR1_CEN; // start timer
	NVIC_EnableIRQ(TIM3_IRQn); // allow interrupt TIM6_DAC_IRQn

	/* Init timer 2 for PWM */
	/* Switch on timer 2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_BaseStruct;
    TIM_BaseStruct.TIM_Prescaler = 0;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseStruct.TIM_Period = 255; // 8-bit output
    TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BaseStruct.TIM_RepetitionCounter = 0;
    /* Initialize TIM2 */
    TIM_TimeBaseInit(TIM2, &TIM_BaseStruct);
    TIM_Cmd(TIM2, ENABLE);

    /* Init PWM on timer */
    TIM_OCInitTypeDef TIM_OCStruct;
	TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC3Init(TIM2, &TIM_OCStruct);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* Init output pin */
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_2);
	/* Set pins */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);


	playSound(silence);
}

static uint16_t prevSoundValue;
void TIM3_IRQHandler(void) {
	uint16_t val = getNextSample();

	TIM6->SR &= ~TIM_SR_UIF; // reset flag UIF

	// Filter noise
	if (prevSoundValue > val + 256 || prevSoundValue + 256 < val) {
		TIM2->CCR3 = val >> 8; // push next value
		prevSoundValue = val;
	}
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}
