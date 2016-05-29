
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

fpt perc(fpt time) {
	return fmul3(randomSym(), fptConst(0.25) , pow2nfst(fmul(time, fptFromInt(48))));
}

fpt drum(fpt time) {
	return fmul3(randomSym(), fptConst(0.5), pow2nfst(fmul(time, fptFromInt(64)))) +
			fmul3(sinfrq(fmul(time, fptFromInt(55))),
			fptConst(5), pow2nfst(fmulInt(time, 24)));
}

fpt wawa(fpt time) {
	return fmul3(sinfrq(fmul(time + (sinfrq(fmulInt(time, 8)) >> 4), fptFromInt(55))),//sinfrq(fmulInt(time, 8)) * 10)),
			fptConst(5), pow2nfst(fmulInt(time, 16)));
}

fpt pfrr(fpt time) {
	return fmul3(squarefrq(fmul(time, fptFromInt(20) + randomSym())), fptConst(0.5), pow2nfst(fmulInt(time, 16)));
}

fpt noise(fpt time) {
	return fmul3(randomSym(), time << 2, pow2nfst(fmul(time, fptFromInt(16))));
}

