#ifndef MICROMUSIC_INSTRUMENTS_INCLUDED
#define MICROMUSIC_INCLUDED

typedef fpt (*InstrumentFunction)(fpt, uint8_t);

#define NOTE_OFF 0
#define NOTE_G3 1
#define NOTE_Ab3 2
#define NOTE_A3 3
#define NOTE_Bb3 4
#define NOTE_B3 5
#define NOTE_C4 6
#define NOTE_Db4 7
#define NOTE_D4 8
#define NOTE_Eb4 9
#define NOTE_E4 10
#define NOTE_F4 11
#define NOTE_Gb4 12
#define NOTE_G4 13
#define NOTE_Ab4 14
#define NOTE_A4 15
#define NOTE_Bb4 16
#define NOTE_B4 17
#define NOTE_C5 18
#define NOTE_Db5 19
#define NOTE_D5 20
#define NOTE_Eb5 21
#define NOTE_E5 22
#define NOTE_F5 23
#define NOTE_Gb5 24
#define NOTE_G5 25
#define NOTE_Ab5 26
#define NOTE_A5 27
#define NOTE_Bb5 28
#define NOTE_B5 29
#define NOTE_C6 30

#define NOTE_MASK 	0b00111111
#define NOTE_SHORT 	0b01000000

const fpt notes[] = {
		FZERO,FREQ_G3,FREQ_Ab3,FREQ_A3,FREQ_Bb3,FREQ_B3,
		FREQ_C4,FREQ_Db4,FREQ_D4,FREQ_Eb4,FREQ_E4,FREQ_F4,
			FREQ_Gb4,FREQ_G4,FREQ_Ab4,FREQ_A4,FREQ_Bb4,FREQ_B4,
		FREQ_C5,FREQ_Db5,FREQ_D5,FREQ_Eb5,FREQ_E5,FREQ_F5,
			FREQ_Gb5,FREQ_G5,FREQ_Ab5,FREQ_A5,FREQ_Bb5,FREQ_B5,
		FREQ_C6};


static inline fpt waveform(fpt time, fpt freq, int8_t const *form) {
	fpt t = mulFreq(time, freq);
	fpt l = t << SINUS_TABLE_BITS;
	uint32_t n = fptToInt(l) & SINUS_LOOKUP_MASK;
	return finterpolate8BitSigned(form[n], form[n + 1], ffrac(l) >> (FPT_FBITS - INTERPOLATION_BITS));
}

#define PERCUSSION_HAT_H	0b00001010
#define PERCUSSION_HAT_L	0b00001101
#define PERCUSSION_BAR_H	0b00101111
#define PERCUSSION_BAR_L	0b10011110
fpt percussions(fpt time, uint8_t data) {
	int noiseVol =  (data & 0b00000011);
	int noiseLen = ((data & 0b00001100) >> 2) + 1;
	int bassVol =  ((data & 0b00110000) >> 4);
	int bassLen =  ((data & 0b11000000) >> 6) + 1;

	return fmul3fst(randomSym(), fptConst(0.2) * noiseVol, pow2nfst(fmulInt(time, 16 * noiseLen))) +
			fmul3fst(sinfrq(fmulInt(time, 55)), fptConst(1.5) * bassVol, pow2nfst(fmulInt(time, 8 * bassLen)));
}

fpt electricPiano(fpt time, uint8_t data) {
	return fmulfst(sinfrq(mulFreq(time, notes[data & NOTE_MASK])), pow2nfst(fmulInt(time, 2)));
}

fpt harmonica(fpt time, uint8_t data) {
	fpt t = mulFreq(time, notes[data & NOTE_MASK]);
	return fmul3fst(
				sinfrq(fmulInt(t, 3)),
				fdivInt(sawfrq(t), 2) + 1,
				pow2nfst(time) - pow2nfst(fmulInt(time, 40))
			);
}

/* Sample-based isntrument */
static const int8_t harmonicaSample[] = {
		2, -40, -7, -33, -66, -9, -8, 31,
		68, 62, 76, 65, 26, -38, -75, -33,
		-52, -12, -11, -3, 73, 46, 25, -43,
		-35, -10, -54, -24, -5, 33, 50, 23,
		2};
fpt harmonicaSampled(fpt time, uint8_t data) {
	return fmulfst(waveform(time, notes[data & NOTE_MASK], harmonicaSample),
				pow2nfst(time) - pow2nfst(fmulInt(time, 40)));
}

#define ODG_DELAY fptConst(0.01f)
#define ODG_EXP_N 	3
#define ODG_EXP_S 	60
#define ODG_DIST_1 	8//2
#define ODG_DIST_2 	32//16
fpt overdrivenGuitar(fpt time, uint8_t data) {
	if (data == 0) return 0;
	int exp = (data & NOTE_SHORT) ? ODG_EXP_S : ODG_EXP_N;
	fpt v =
			fmulfst(sinfrq(mulFreq(time, notes[data & NOTE_MASK] >> 1)), pow2nfst(fmulInt(time, exp))) +
			fmulfst(sinfrq(mulFreqTrim0(time - ODG_DELAY, notes[(data + 7) & NOTE_MASK] >> 1)), pow2nfst(fmulInt(time - ODG_DELAY, exp))) +
			fmulfst(sinfrq(mulFreqTrim0(time - ODG_DELAY * 2, notes[data & NOTE_MASK])), pow2nfst(fmulInt(time - ODG_DELAY * 2, exp)));
	if (v > 0) {
		v = pow2nfst(fmulInt(v, ODG_DIST_1)) - pow2nfst(fmulInt(v, ODG_DIST_2));
	} else {
		v = pow2nfst(-fmulInt(v, ODG_DIST_2)) - pow2nfst(-fmulInt(v, ODG_DIST_1));
	}
	return v;
}


fpt bass(fpt time, uint8_t data) {
	fpt n = notes[data & NOTE_MASK] >> 2;
	return fmulfst(
			sinfrq(mulFreq(time, n)) +
			sinfrq(mulFreq(time, n * 2)) / 2 +
			sinfrq(mulFreq(time, n * 3)) * 5 / 16 + // faster than / 3 +
			sinfrq(mulFreq(time, n * 4)) / 4
		, pow2nfst(fmulInt(time, 2)));
}

#define INSTRUMENT_PERCUSSIONS			0
#define INSTRUMENT_ELECTRIC_PIANO		1
#define INSTRUMENT_HARMONICA			2
#define INSTRUMENT_OVERDRIVEN_GUITAR	3
#define INSTRUMENT_BASS					4

const InstrumentFunction instruments[] = {
		percussions,
		electricPiano,
		harmonica,
		overdrivenGuitar,
		bass
};

#endif
