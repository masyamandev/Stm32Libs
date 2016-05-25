/*
 * Sample project for stm32f4-discovery for playing sound samples
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include <stm32f4_discovery.h>
#include <microsound_stm32f4xx.h>
#include <sound_samples.h>

void waitForButton() {
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOff(LEDS_ALL);
	}
	while (isButtonPressed()) {
	}
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOff(LEDS_ALL);
	}
	while (!isButtonPressed()) {
	}
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOn(LEDS_ALL);
	}
	ledsOff(LEDS_ALL);
}

int main(void) {

	initLeds(LEDS_ALL);
	initButton();
	initSound();

//	playSound(sine);
//	while (1) {
//	}
	while (1) {
		waitForButton();
		playSound(beep);
		waitForButton();
		playSound(chord);
		waitForButton();
		playSound(chord2);
	}
}

