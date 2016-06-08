
const uint16_t cMajScaleSample[] = {
		MUSIC_COMMAND_SPEED | 120,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_0 | 255,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_F4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_A4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_B4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C5,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_NEXT | 3,

		MUSIC_COMMAND_STOP
};

const uint16_t ohSusannaSong[] = {
		MUSIC_COMMAND_SPEED | 480,
//		MUSIC_COMMAND_INSTRUMENT | MUSIC_TRACK_0 | INSTRUMENT_ELECTRIC_PIANO,
		MUSIC_COMMAND_INSTRUMENT | MUSIC_TRACK_0 | INSTRUMENT_HARMONICA,
		MUSIC_COMMAND_INSTRUMENT | MUSIC_TRACK_1 | INSTRUMENT_OVERDRIVEN_GUITAR,
		MUSIC_COMMAND_INSTRUMENT | MUSIC_TRACK_2 | INSTRUMENT_BASS,
		MUSIC_COMMAND_INSTRUMENT | MUSIC_TRACK_3 | INSTRUMENT_PERCUSSIONS,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_0 | 96,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 24,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 64,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_3 | 64,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,


//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
//		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_A4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_G3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,


		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 ,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_A4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 ,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_G3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 1,

		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_E4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_G4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_A3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_D4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4 | NOTE_SHORT,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_G3,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,


		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_0 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_1 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_BAR_H,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_G4,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_L,
		MUSIC_COMMAND_NEXT | 2,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_2 | NOTE_C5,
		MUSIC_COMMAND_PLAY_NOTE | MUSIC_TRACK_3 | PERCUSSION_HAT_H,
		MUSIC_COMMAND_NEXT | 6,


		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 21,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 56,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 18,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 48,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 15,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 40,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 12,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 32,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 9,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 24,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 6,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 16,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_1 | 3,
		MUSIC_COMMAND_VOLUME | MUSIC_TRACK_2 | 8,
		MUSIC_COMMAND_NEXT | 1,
		MUSIC_COMMAND_CHANGE_NOTE | MUSIC_TRACK_1 | NOTE_OFF,
		MUSIC_COMMAND_CHANGE_NOTE | MUSIC_TRACK_2 | NOTE_OFF,

		MUSIC_COMMAND_STOP
};
