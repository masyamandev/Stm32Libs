
#include "micromath.h"

fpt sine(fpt time) {
	return sinfrq(fmul(time, FREQ_A4));
}

fpt beep(fpt time) {
	return fmul3((sinfrq(fmul(time, FREQ_A4)) + sinfrq(fmul(time, FREQ_A5))),
			fptConst(0.4),
			pow2nfst(fmul(time, fptFromInt(6))));
}

fpt chord(fpt time) {
	return fmul3(sinfrq(fmul(time, FREQ_C4)) +
			sinfrq(fmul(time, FREQ_E4)) +
			sinfrq(fmul(time, FREQ_G4)),
			fptConst(0.5),
			pow2nfst(fmul(time, fptFromInt(4))));
}

#define CHORD_DELAY fptConst(0.07f)
#define CHORD_EXP fptFromInt(8)
#define CHORD_VOL fptConst(0.5)
fpt chord2(fpt time) {
//	fpt res = fmul3(sinfrq(fmul(time, FREQ_C4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	time -= CHORD_DELAY;
//	res += fmul3(sinfrq(fmul(cutNegative(time), FREQ_E4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	time -= CHORD_DELAY;
//	res += fmul3(sinfrq(fmul(cutNegative(time), FREQ_G4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	return res;

	return fmul3(sinfrq(fmul(time, FREQ_C4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP))) +
			fmul3(sinfrq(fmul(cutNegative(time - CHORD_DELAY), FREQ_E4)), CHORD_VOL, pow2nfst(fmul(time - CHORD_DELAY, CHORD_EXP))) +
			fmul3(sinfrq(fmul(cutNegative(time - CHORD_DELAY * 2), FREQ_G4)), CHORD_VOL, pow2nfst(fmul(time - CHORD_DELAY * 2, CHORD_EXP)));
}
