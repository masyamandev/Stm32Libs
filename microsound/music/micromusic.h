/**
 * Midi-like music functions for microsound.
 * Currently under development.
 */

#ifndef MICROMUSIC_INCLUDED
#define MICROMUSIC_INCLUDED

#include "microsound.h"

// Should be defined here:
// typedef fpt (*InstrumentFunction)(fpt, uint8_t);
// const InstrumentFunction instruments[] = {...};
#include "micromusic_instruments.h"

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
#define MUSIC_TRACK_8				0x0800
#define MUSIC_TRACK_9				0x0900
#define MUSIC_TRACK_A				0x0A00
#define MUSIC_TRACK_B				0x0B00
#define MUSIC_TRACK_C				0x0C00
#define MUSIC_TRACK_D				0x0D00
#define MUSIC_TRACK_E				0x0E00
#define MUSIC_TRACK_F				0x0F00


volatile static uint16_t const *musicData;
volatile static uint32_t musicDataIndex;
volatile static fpt nextTime = FZERO;
volatile static fpt bpmDelay = FONE;
static fpt clickRemoval = FZERO; // slightly faster without volatile

#define CLICK_REMOVAL_STRENGTH	5 // IN BITS

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

static TrackData tracks[MUSIC_TRACKS]; // volatile might be required


static fpt silenceInstrument(fpt time, uint8_t data) {
	return 0;
}

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
			playSound(silence);
			break;
		case MUSIC_COMMAND_SPEED:
			bpmDelay = fdivInt(fptFromInt(60), command & MUSIC_EXTENDED_DATA_MASK);
			break;
		case MUSIC_COMMAND_INSTRUMENT:
			track->instrument = instruments[data];
			break;
		case MUSIC_COMMAND_VOLUME:
			track->volume = data << 8;
			break;
		case MUSIC_COMMAND_DELAY:
			track->delay = data << 8;
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

//	clickRemoval = moveToZero(clickRemoval, 64);
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


void playMusic(uint16_t const *musicDataArray) {
	playSound(silence);
	musicData = musicDataArray;
	musicDataIndex = 0;
	nextTime = FZERO;
	bpmDelay = FONE;
	//clickRemoval = FZERO;
	for (int i = 0; i < MUSIC_TRACKS; i++) {
		tracks[i].instrument = silenceInstrument;
		tracks[i].volume = FONEHALF;
		tracks[i].startTime = FZERO;
		tracks[i].delay = FZERO;
		tracks[i].data = 0;
	}

	playSound(musicSound);
}



#endif
