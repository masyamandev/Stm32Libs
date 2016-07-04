/**
 * Some samples which can be used in microsound.
 */

#include "micromath.h"

fpt sine(fpt time) {
	return sinfrq(fmul(time, FREQ_A4));
}

fpt beep(fpt time) {
	return fmul3fst((sinfrq(mulFreq(time, FREQ_A4)) + sinfrq(mulFreq(time, FREQ_A5))),
			pow2nfst(fmulInt(time, 6)),
			fptConst(0.4));
}

fpt chord(fpt time) {
	return fmul3fst(sinfrq(mulFreq(time, FREQ_C4)) +
			sinfrq(mulFreq(time, FREQ_E4)) +
			sinfrq(mulFreq(time, FREQ_G4)),
			pow2nfst(fmulInt(time, 4)),
			fptConst(0.5));
}

#define CHORD_DELAY fptConst(0.07f)
#define CHORD_EXP 8
#define CHORD_VOL fptConst(0.5)
fpt chord2(fpt time) {
//	fpt res = fmul3(sinfrq(fmul(time, FREQ_C4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	time -= CHORD_DELAY;
//	res += fmul3(sinfrq(fmul(cutNegative(time), FREQ_E4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	time -= CHORD_DELAY;
//	res += fmul3(sinfrq(fmul(cutNegative(time), FREQ_G4)), CHORD_VOL, pow2nfst(fmul(time, CHORD_EXP)));
//	return res;

	return fmulfst(
			fmulfst(sinfrq(mulFreq(time, FREQ_C4)), pow2nfst(fmulInt(time, CHORD_EXP))) +
			fmulfst(sinfrq(mulFreq(cutNegative(time - CHORD_DELAY), FREQ_E4)), pow2nfst(fmulInt(time - CHORD_DELAY, CHORD_EXP))) +
			fmulfst(sinfrq(mulFreq(cutNegative(time - CHORD_DELAY * 2), FREQ_G4)), pow2nfst(fmulInt(time - CHORD_DELAY * 2, CHORD_EXP)))
		, CHORD_VOL);

}

fpt perc(fpt time) {
	return fmul3fst(randomSym(), pow2nfst(fmulfst(time, fptFromInt(48))), fptConst(0.25));
}

fpt drum(fpt time) {
	return fmul3fst(randomSym(), pow2nfst(fmulfst(time, fptFromInt(64))), fptConst(0.5)) +
			fmul3fst(sinfrq(fmulInt(time, 55)), pow2nfst(fmulInt(time, 24)), fptConst(5));
}

fpt wawa(fpt time) {
	return fmul3fst(sinfrq(fmulInt(time + (sinfrq(fmulInt(time, 8)) >> 4), 55)),//sinfrq(fmulInt(time, 8)) * 10)),
			pow2nfst(fmulInt(time, 16)), fptConst(5));
}

fpt pfrr(fpt time) {
	return fmul3(squarefrq(fmulfst(time, fptFromInt(20) + randomSym())), pow2nfst(fmulInt(time, 16)), fptConst(0.5));
}

fpt noise(fpt time) {
	return fmul3(randomSym(), time << 2, pow2nfst(fmulfst(time, fptFromInt(16))));
}

