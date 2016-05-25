/*
 * Sample project for measuring performance and write results on 16x2 display
 */

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>

#include <stdlib.h>

#include "stm32f4_discovery.h"

#include "lcd_text_display.h"

#include "microsound.h"
#include "sound_samples.h"


volatile uint32_t testRun = 1;

typedef void (*TestFunction)();

uint32_t runTest(TestFunction testf, uint16_t leds) {
	ledsOff(LEDS_ALL);
	ledsOn(leds);
	testRun = 1;
	uint32_t counter = 0;
	while (testRun) {
		testf();
		counter++;
	}
	return counter;
}


volatile uint32_t tmpVal = 1;
volatile fpt tmpFloat = FONEHALF;

void initTests() {
	playSound(chord2);
}
void t1(void) {
	tmpFloat += sound(fptConst(0.01234f));
}
void t2(void) {
	tmpFloat += getNextSample();
}
void t3(void) {
	tmpFloat += fmulfst(FTWO, tmpVal++);
}
void t4(void) {
	tmpFloat += fmul(FTWO, tmpVal++);
}

void postInitTests() {};

int main(void)
{

	initializeLcd();

	cursor(0,0);
	printStr("Micro benchmark!");
	cursor(1,0);
	printStr("Initializing... ");

	initLeds(LEDS_ALL);
	initButton();

	// Interrupt every second
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM6->PSC =  HSI_VALUE / 1000 - 1;
	TIM6->ARR = 1000;
	TIM6->DIER |= TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM6_DAC_IRQn);

    while(1)
    {
		// wait until first interrupt
    	initTests();
		runTest(postInitTests, 0);

    	uint32_t c1 = runTest(t1, LED_U);
    	uint32_t c2 = runTest(t2, LED_R);
    	uint32_t c3 = runTest(t3, LED_D);
    	uint32_t c4 = runTest(t4, LED_L);

//    	c1 = sinfst(FONEHALF/2);
//    	c2 = sinfst(-FONEHALF/2);
//    	c3 = pow2nfst(FONEHALF);
//    	c4 = pow2pfst(FONEHALF);

    	ledsOn(LEDS_ALL);
    	clearLcdScreen();
		char s[17];
		s[16] = 0;

		itoa(c1, s, 10);
		cursor(0,0);
		printStr(&s[0]);

		itoa(c2, s, 10);
		cursor(0,8);
		printStr(&s[0]);

		itoa(c3, s, 10);
		cursor(1,0);
		printStr(&s[0]);

		itoa(c4, s, 10);
		cursor(1,8);
		printStr(&s[0]);

		// Just prevent optimization
		if (tmpVal >= 0 || tmpFloat >= 0) {
	    	ledsOff(LEDS_ALL);
		}
    }

}


void TIM6_DAC_IRQHandler(void)
{
	testRun = 0;
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
