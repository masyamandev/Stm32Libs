/**
 * Midi-like music functions for microsound.
 * Currently under development.
 */

#ifndef MICROMUSIC_INCLUDED
#define MICROMUSIC_INCLUDED

#include "microsound.h"

typedef fpt (*InstrumentFunction)(fpt, uint8_t);

#define MUSIC_COMMANDS_MASK			0xF000 // Command mask
#define MUSIC_TRACK_MASK			0x0F00 // Track mask
#define MUSIC_TRACK_OFFSET			8      // Track bits offset
#define MUSIC_DATA_MASK				0x00FF // 8-bit data mask
#define MUSIC_EXTENDED_DATA_MASK	0x0FFF // 12-bit data mask

#define MUSIC_COMMAND_STOP			0x0000 // Stop playing
#define MUSIC_COMMAND_SPEED			0x1000 // Set speed, 12-bit BPM
#define MUSIC_COMMAND_INSTRUMENT	0x2000 // Set instrument for track
#define MUSIC_COMMAND_VOLUME		0x3000 // Set volume for track
#define MUSIC_COMMAND_DELAY			0x4000 // Set start delay in seconds [0..1) for track
#define MUSIC_COMMAND_PLAY_NOTE		0x5000 // Play note in track
#define MUSIC_COMMAND_CHANGE_NOTE	0x6000 // Change note's data withot reseting timer
#define MUSIC_COMMAND_NEXT			0x7000 // Wait {data} beats until proceed next command

#define MUSIC_TRACK_0				0x0000
#define MUSIC_TRACK_1				0x0100
#define MUSIC_TRACK_2				0x0200
#define MUSIC_TRACK_3				0x0300
#define MUSIC_TRACK_4				0x0400
#define MUSIC_TRACK_5				0x0500
#define MUSIC_TRACK_6				0x0600
#define MUSIC_TRACK_7				0x0700


volatile static uint16_t *musicData;
volatile static uint32_t musicDataIndex;
volatile static fpt nextTime = FZERO;
volatile static fpt bpmDelay = FONE;
static fpt clickRemoval = FZERO; // slightly faster without volatile

#define CLICK_REMOVAL_STRENGTH	4 // IN BITS

#ifndef MUSIC_TRACKS
#define MUSIC_TRACKS 	4
#endif

typedef struct {
	InstrumentFunction instrument;
	fpt volume;
	fpt startTime;
	fpt delay;
	uint8_t data;
} TrackData;

volatile static TrackData tracks[MUSIC_TRACKS];

inline static fpt playInstrument(TrackData* track, fpt time) {
	return fmul(
			track->instrument(time - track->startTime, track->data),
			track->volume
		);
}

fpt musicSound(fpt time) {
	while (time >= nextTime) {
		uint16_t command = *(musicData + musicDataIndex++);
		uint8_t trackId = (command & MUSIC_TRACK_MASK) >> MUSIC_TRACK_OFFSET;
		uint8_t data = command & MUSIC_DATA_MASK;
		TrackData *track = tracks + trackId;
		switch (command & MUSIC_COMMANDS_MASK) {
		case MUSIC_COMMAND_STOP:
			musicDataIndex--;
			break;
		case MUSIC_COMMAND_SPEED:
			bpmDelay = fdivInt(fptFromInt(60), command & MUSIC_EXTENDED_DATA_MASK);
			break;
		case MUSIC_COMMAND_INSTRUMENT:
			// TODO
			break;
		case MUSIC_COMMAND_VOLUME:
			tracks->volume = data << 8;
			break;
		case MUSIC_COMMAND_DELAY:
			tracks->delay = data << 8;
			break;
		case MUSIC_COMMAND_PLAY_NOTE:
			clickRemoval += playInstrument(track, time);
			track->startTime = nextTime + track->delay;
			track->data = data;
			clickRemoval -= playInstrument(track, time);
			break;
		case MUSIC_COMMAND_CHANGE_NOTE:
			clickRemoval += playInstrument(track, time);
			track->data = data;
			clickRemoval -= playInstrument(track, time);
			break;
		case MUSIC_COMMAND_NEXT:
			nextTime += fmulInt(bpmDelay, data);
			break;
		default:
			break;
		}
	}

//	clickRemoval = moveToZero(clickRemoval, CLICK_REMOVAL_DELTA);
	clickRemoval -= clickRemoval >> CLICK_REMOVAL_STRENGTH; // Slightly faster

	fpt val = clickRemoval;
	TrackData *track = tracks;
	for (int i = 0; i < MUSIC_TRACKS; i++) {
		if (track->startTime <= time) {
			val += playInstrument(track, time);
		}
		track++;
	}

	return val;
}

int isMusicPlaying() {
	return ((*(musicData + musicDataIndex)) & MUSIC_COMMANDS_MASK) != MUSIC_COMMAND_STOP;
}


fpt electricPiano(fpt time, uint8_t data);// TODO

void playMusic(uint16_t *musicDataArray) {
	playSound(silence);
	musicData = musicDataArray;
	musicDataIndex = 0;
	nextTime = FZERO;
	bpmDelay = FONE;
	//clickRemoval = FZERO;
	for (int i = 0; i < MUSIC_TRACKS; i++) {
		tracks[i].instrument = electricPiano;//silenceInstrument;
		tracks[i].volume = FONEHALF;
		tracks[i].startTime = FZERO;
		tracks[i].delay = FZERO;
		tracks[i].data = 0;
	}

	playSound(musicSound);
}



// TODO: extract instruments
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



fpt silenceInstrument(fpt time, uint8_t data) {
	return 0;
}

#define PIANO_EXP fptFromInt(4)
fpt electricPiano(fpt time, uint8_t data) {
	return fmul(sinfrq(fmul(time, notes[data])), pow2nfst(fmul(time, PIANO_EXP)));
}


//const uint16_t sampleMusic[] = {
//		MUSIC_COMMAND_SPEED | 120,
//		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 255,
//
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_F4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_A4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_B4,
//		MUSIC_COMMAND_NEXT | 1,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C5,
//		MUSIC_COMMAND_NEXT | 1,
//
//		MUSIC_COMMAND_NEXT | 3,
//
//		MUSIC_COMMAND_STOP
//};

const uint16_t sampleMusic[] = {
		MUSIC_COMMAND_SPEED | 480,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 255,
//		MUSIC_COMMAND_DELAY | MUSIC_TRACK_2 | 16,
//		MUSIC_COMMAND_DELAY | MUSIC_TRACK_3 | 8,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_A4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 2,


		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 6,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_A4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 2,


		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 8,

		MUSIC_COMMAND_STOP
};

#endif
