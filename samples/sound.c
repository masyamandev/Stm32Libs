/*
 * Sample project for stm32f4-discovery for playing sound samples
 */

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include <stm32f4_discovery.h>
#include <microsound_stm32f4xx.h>
#include <sound_samples.h>

#include <micromusic.h>
#include <micromusic_sample_songs.h>

//#include <lcd_text_display.h>
//
//void debug() {
//	char s[17];
//	s[16] = 0;
//
//	cursor(0,0);
//	itoa(fptToInt(soundPlayTime), s, 10);
//	printStr(&s[0]);
//	printStr("        ");
//
//	cursor(0,8);
//	itoa(ffrac(soundPlayTime), s, 10);
//	printStr(&s[0]);
//	printStr("        ");
//}

void waitForButton() {
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOff(LEDS_ALL);
	}
	while (isButtonPressed()) {
//		debug();
	}
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOff(LEDS_ALL);
	}
	while (!isButtonPressed()) {
//		debug();
	}
	for (uint32_t i = 0; i < 10000; i++) {
		ledsOn(LEDS_ALL);
	}
	ledsOff(LEDS_ALL);
}

#define SAMPLES_LEN 8
static SoundFunction samples[SAMPLES_LEN] = {
		beep,
		chord,
		chord2,
		pfrr,
		wawa,
		perc,
		drum,
		noise
};
uint32_t currentSound __attribute__ ((section (".noinit")));

int main(void) {

	initLeds(LEDS_ALL);
	initButton();
	initSound();

//	initializeLcd();

	currentSound = (currentSound < 0) ? 0 : (currentSound + 1) % (SAMPLES_LEN + 1);

	while (1) {
		waitForButton();
		if (currentSound < SAMPLES_LEN) {
			playSound(samples[currentSound]);
		} else {
			playMusic(ohSusannaSong);
		}
	}
}

