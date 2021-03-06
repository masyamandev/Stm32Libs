/**
 * Common code for sound management.
 * It defines type SoundFunction which is a function (fpt) -> fpt. It uses time in seconds
 * as parameter of fixed-point type fpt and return fixed-point value -1..1 as output.
 * Output of SoundFunction is scaled to 16-bit output value and sent into DAC or PWM
 * (platform specific).
 */

#ifndef MICROSOUND_INCLUDED
#define MICROSOUND_INCLUDED

#include "micromath.h"

#ifndef MICROSOUND_FREQUENCY
#define MICROSOUND_FREQUENCY 		16000 // PCM sample rate
#endif

#define FREQ_C3 fptConst(130.81)
#define FREQ_Db3 fptConst(138.59)
#define FREQ_D3 fptConst(146.83)
#define FREQ_Eb3 fptConst(155.56)
#define FREQ_E3 fptConst(164.81)
#define FREQ_F3 fptConst(174.61)
#define FREQ_Gb3 fptConst(185.00)
#define FREQ_G3 fptConst(196.00)
#define FREQ_Ab3 fptConst(207.65)
#define FREQ_A3 fptConst(220.00)
#define FREQ_Bb3 fptConst(233.08)
#define FREQ_B3 fptConst(246.94)
#define FREQ_C4 fptConst(261.63)
#define FREQ_Db4 fptConst(277.18)
#define FREQ_D4 fptConst(293.66)
#define FREQ_Eb4 fptConst(311.13)
#define FREQ_E4 fptConst(329.63)
#define FREQ_F4 fptConst(349.23)
#define FREQ_Gb4 fptConst(369.99)
#define FREQ_G4 fptConst(392.00)
#define FREQ_Ab4 fptConst(415.30)
#define FREQ_A4 fptConst(440.00)
#define FREQ_Bb4 fptConst(466.16)
#define FREQ_B4 fptConst(493.88)
#define FREQ_C5 fptConst(523.25)
#define FREQ_Db5 fptConst(554.37)
#define FREQ_D5 fptConst(587.33)
#define FREQ_Eb5 fptConst(622.25)
#define FREQ_E5 fptConst(659.25)
#define FREQ_F5 fptConst(698.46)
#define FREQ_Gb5 fptConst(739.99)
#define FREQ_G5 fptConst(783.99)
#define FREQ_Ab5 fptConst(830.61)
#define FREQ_A5 fptConst(880.00)
#define FREQ_Bb5 fptConst(932.33)
#define FREQ_B5 fptConst(987.77)
#define FREQ_C6 fptConst(1046.50)


typedef fpt (*SoundFunction)(fpt);

fpt silence(fpt time) {
	return 0;
}

#define SOUND_TIMER_SCALE 4 // around 30 minutes max play time

#define soundPlayTime (soundTimeCounter >> SOUND_TIMER_SCALE)

volatile static SoundFunction sound = silence;
volatile static fpt soundTimeCounter = FZERO;
volatile static fpt soundLength = 0x7F000000; // big value, but not MAX_INT

void playSoundWithLength(SoundFunction soundFunction, fpt soundStopAt) {
	soundTimeCounter = FZERO;
	sound = soundFunction;
	soundLength = soundStopAt << SOUND_TIMER_SCALE;
}
void playSound(SoundFunction soundFunction) {
	soundTimeCounter = FZERO;
	sound = soundFunction;
	soundLength = 0x7F000000;
}

// Return 16 bits value [0..65535]
uint16_t getNextSample(void) {
	fpt s = sound(soundPlayTime);
	int32_t val = ((s + FONE) >> 1);
	if (val < 0) {
		val = 0;
	} else if (val >= FONE) {
		val = FONE - 1;
	}
	soundTimeCounter += fdivInt(FONE << SOUND_TIMER_SCALE, MICROSOUND_FREQUENCY);
	// could be removed to get some performance boost
	if (soundTimeCounter > soundLength) {
		playSound(silence); // overflow, stop playing sound
	}
	return val;
}

#endif
