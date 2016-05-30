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

const fpt notes[] = {
		FZERO,FREQ_G3,FREQ_Ab3,FREQ_A3,FREQ_Bb3,FREQ_B3,
		FREQ_C4,FREQ_Db4,FREQ_D4,FREQ_Eb4,FREQ_E4,FREQ_F4,
			FREQ_Gb4,FREQ_G4,FREQ_Ab4,FREQ_A4,FREQ_Bb4,FREQ_B4,
		FREQ_C5,FREQ_Db5,FREQ_D5,FREQ_Eb5,FREQ_E5,FREQ_F5,
			FREQ_Gb5,FREQ_G5,FREQ_Ab5,FREQ_A5,FREQ_Bb5,FREQ_B5,
		FREQ_C6};


#define PIANO_EXP fptFromInt(4)
fpt electricPiano(fpt time, uint8_t data) {
	return fmul(sinfrq(fmul(time, notes[data])), pow2nfst(fmul(time, PIANO_EXP)));
}


#define INSTRUMENT_ELECTRIC_PIANO		0
#define INSTRUMENT_OVERDRIVEN_GUITAR	1

const InstrumentFunction instruments[] = {
		electricPiano,
		electricPiano
};

#endif
