/*	FreeEMS - the open source engine management system

	Copyright 2011 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Missing teeth, 6-2, Cam only, usually J Series Honda
 *
 * This just defines the required flags and values and includes the base header and base code.
 *
 * @note The decoderInterface header is included from the MissingTeeth header.
 */


#define DECODER_IMPLEMENTATION_C
#define CAM_ONLY
#define TOTAL_TEETH   6
#define MISSING_TEETH  2


typedef struct {
	unsigned lastPair: 4;
	unsigned thisPair: 4;
} twoPairs;

typedef union {
	twoPairs pairs;
	unsigned char pattern;
} match;


#define DECODER_MAX_CODE_TIME 250 // From Spudmn's measurements in NZ. 171us runtime was max = 214 ticks.

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"


// Make current tolerance scheme work properly for different missing levels OOTB
#define TOLERANCE_LEVEL (MISSING_TEETH*1024)


#define NUMBER_OF_WHEEL_EVENTS (TOTAL_TEETH - MISSING_TEETH)


#define NUMBER_OF_REAL_EVENTS NUMBER_OF_WHEEL_EVENTS
#define NUMBER_OF_VIRTUAL_EVENTS NUMBER_OF_REAL_EVENTS
#define ANGLE_BETWEEN_EVENTS ((oneDegree * 720.0) / TOTAL_TEETH)
#define angleOfSingleIteration (720 * oneDegree)


#include "../inc/decoderInterface.h"

const unsigned short eventAngles[] = {
0,
(120.18 * oneDegree),
(239.00 * oneDegree),
(360.18 * oneDegree)
};
// Above, the first angle corresponds to 720 minus the last angle worth of angular width since the previous event
// Each of the others corresponds to the difference between itself and the previous too
// So the standard angular widths of the decoder are really 360, 120, 120, 120, not 0, 120, 240, 360, which are the positions
// This commit changes that to the following: 359.82, 120.18, 118.82, 121.18
// Which results in the following angles in the array: 0.00, 120.18, 239.00, 360.18


/// @todo TODO build this with similar hash if logic: need to reconsider how to use this or whether to even have it. A "corresponding event" table might be good instead, kinda like the mapping above, but from real to real, only when the angles are exactly 360 out.
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // this is only correct while doing pure crank sync, wrong once doing more, i think, TBC...


#include "code/MissingTeeth-Either-XminusY.c"
