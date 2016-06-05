/**
 * Fixed point arithmetics optimized for 32-bits microcontrollers without FPU.
 */

#ifndef MICROMATH_INCLUDED
#define MICROMATH_INCLUDED

typedef int32_t fpt;
typedef	int64_t	fptd;

#define FPT_TBITS	32 // Total bits
#define FPT_FBITS	16 // Fractional bits
#define FPT_PBITS	(FPT_TBITS - FPT_FBITS - 1) // Bits in positive count

#define fptConst(R) ((fpt)((R) * (((fptd)1 << FPT_FBITS) + ((R) >= 0 ? 0.5 : -0.5))))

#define fptFromInt(I) 	(((fpt)(I)) << FPT_FBITS)
#define fptFromUByte(I)	(((fpt)(I)) << (FPT_FBITS - 8)) // from unsigned byte to [0..1)
#define fptFromSByte(I)	(((fpt)(I)) << (FPT_FBITS - 7)) // from signed byte to [-1..1)
#define fptToInt(F) 	((F) >> FPT_FBITS)

#define faddInt(A,B) 	((A) + fptFromInt(B))
#define fadd(A,B) 		((A) + (B))
#define fadd3(A,B,C) 	((A) + (B) + (C))
#define fadd4(A,B,C,D) 	((A) + (B) + (C) + (D))
#define fsub(A,B) 		((A) - (B))

#define fmulInt(A,B)	((A) * (B))
#define fmulfst(A,B)	(((A) * ((B) >> 8)) >> (FPT_FBITS - 8)) // fast non-precise multiplication for small values (<10)
#define fmul(A,B)		((fpt)(((fptd)(A) * (fptd)(B)) >> FPT_FBITS))
#define fmul3(A,B,C)	((fpt)(((fptd)(A) * (fptd)(B) * (fptd)(C)) >> (FPT_FBITS * 2)))
#define fmul4(A,B,C,D)	((fpt)(((((fptd)(A) * (fptd)(B) * (fptd)(C)) >> (FPT_FBITS * 2)) * (fptd)(C)) >> FPT_FBITS))

#define fdivInt(A,B)	((A) / (B))
#define fdiv(A,B)		((fpt)(((fptd)(A) << FPT_FBITS) / (fptd)(B)))
#define fdivfst(A,B)	(fmul((A), (1 << (FPT_FBITS + 7)) / (B)) >> 7) // fast non-precise division, should work for small (<100) values

#define ffloor(A)		((A) & 0xFFFF0000)
#define ffrac(A)		((A) & 0xFFFF)

#define FZERO		0
#define FONE		(1 << FPT_FBITS)
#define FONEHALF 	(FONE >> 1)
#define FTWO		(FONE + FONE)


#define SINUS_TABLE_BITS 5
#define SINUS_LOOKUP_MASK 31
#ifdef PRECISE_SIN_TABLE
const fpt sinTable[33] = {
		0, 12785, 25080, 36410, 46341, 54491, 60547, 64277,
		65536, 64277, 60547, 54491, 46341, 36410, 25080, 12785,
		0, -12785, -25080, -36410, -46341, -54491, -60547, -64277,
		-65536, -64277, -60547, -54491, -46341, -36410, -25080, -12785,
		0}; // last value could be used for interpolation
#else
const int8_t sinTableUB[33] = {
		0, 25, 49, 71, 90, 106, 117, 125,
		127, 125, 117, 106, 90, 71, 49, 25,
		0, -25, -49, -71, -90, -106, -117, -125,
		-127, -125, -117, -106, -90, -71, -49, -25,
		0}; // last value could be used for interpolation
#endif

#define EXP_SCALE_BITS (FPT_FBITS - 5)
#define EXP_LOOKUP_MASK 31
const fpt exp2nTable[33] = {
		65536, 64132, 62757, 61413, 60097, 58809, 57549, 56316,
		55109, 53928, 52773, 51642, 50535, 49452, 48393, 47356,
		46341, 45348, 44376, 43425, 42495, 41584, 40693, 39821,
		38968, 38133, 37316, 36516, 35734, 34968, 34219, 33486,
		32768}; // last value could be used for interpolation
const fpt exp2pTable[33] = {
		65536, 66971, 68438, 69936, 71468, 73032, 74632, 76266,
		77936, 79642, 81386, 83169, 84990, 86851, 88752, 90696,
		92682, 94711, 96785, 98905, 101070, 103283, 105545, 107856,
		110218, 112631, 115098, 117618, 120194, 122825, 125515, 128263,
		131072}; // last value could be used for interpolation

// Will not work for values > 127
#define INTERPOLATION_BITS 8
#define INTERPOLATION_MASK ((1 << INTERPOLATION_BITS) - 1)
#define finterpolate(A, B, V8) ((((fpt) A) * ((1<<INTERPOLATION_BITS) - (V8)) + ((fpt) B) *(V8)) >> INTERPOLATION_BITS)

#define finterpolate8BitSigned(A, B, V8) ((((fpt) A) * ((1<<INTERPOLATION_BITS) - (V8)) + ((fpt) B) *(V8)) << 1)
#define finterpolate8BitUnigned(A, B, V8) ((((fpt) A) * ((1<<INTERPOLATION_BITS) - (V8)) + ((fpt) B) *(V8)))

// Frequency sinus with period 1 instead of 2*Pi
fpt sinfrq(fpt angle) {
	fpt l = angle << SINUS_TABLE_BITS;
	uint32_t n = fptToInt(l) & SINUS_LOOKUP_MASK;
#ifdef PRECISE_SIN_TABLE
	return finterpolate(sinTable[n], sinTable[n + 1], ffrac(l) >> (FPT_FBITS - INTERPOLATION_BITS));
#else
	return finterpolate8BitSigned(sinTableUB[n], sinTableUB[n + 1], ffrac(l) >> (FPT_FBITS - INTERPOLATION_BITS));
#endif
}
#define cosfrq(angle) sinfrq(FONEHALF + angle)

// Square form with period 1 instead of 2*Pi
fpt squarefrq(fpt angle) {
	return (angle & FONEHALF) ? FONE : -FONE;
}

// Saw form with period 1 instead of 2*Pi
fpt sawfrq(fpt angle) {
	return (ffrac(angle) << 1) - FONE;
}

// Triangle form with period 1 instead of 2*Pi
fpt trianglefrq(fpt angle) {
	fpt val = ffrac(angle) << 2;
	return (val <= FTWO) ? (val - FONE) : (fptFromInt(3) - val);
}


#define cutNegative(T) (T >= 0 ? T : 0)

// Return value closest to 0 with limited maximal difference
fpt moveToZero(fpt value, fpt maxDiff) {
	if (value > maxDiff) {
		return value - maxDiff;
	} else if (value < -maxDiff) {
		return value + maxDiff;
	} else {
		return 0;
	}
}


fpt pow2nfst(fpt minusPow) {
	//if (minusPow <= 0) return FONE;
	// minusPow >= fptFromInt(16), dropping more (eg 0xFFF80000) gives better performance
	if (minusPow & 0xFFF00000) return FZERO;
	uint32_t scale = minusPow >> FPT_FBITS;
	uint32_t n = minusPow >> EXP_SCALE_BITS;
	return exp2nTable[n & EXP_LOOKUP_MASK] >> scale;
}
fpt pow2pfst(fpt plusPow) {
	//if (plusPow <= 0) return FONE;
	uint32_t scale = plusPow >> FPT_FBITS;
	uint32_t n = plusPow >> EXP_SCALE_BITS;
	return exp2pTable[n & EXP_LOOKUP_MASK] << scale;
}
fpt pow2fst(fpt pow) {
	if (pow > 0) {
		return pow2pfst(pow);
	} else {
		return pow2nfst(-pow);
	}
}

// fast pseudo-random generator for noise generation
static fpt randomSeed = 6581;
fpt random() { // random range [0, 1)
	randomSeed = randomSeed * 456987469 + 756436969;
	return randomSeed & 0xFFFF;
}
fpt randomSym() { // random range [-1, 1)
	randomSeed = randomSeed * 456987469 + 756436969;
	return (randomSeed & 0x1FFFF) - FONE;
}

#endif
