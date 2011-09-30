/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/**	@file BenchTest.c
 *
 * @ingroup enginePositionRPMDecoders
 *
 * To facilitate testing of output circuits and physical hardware such as
 * injectors and coils on the bench or in the car.
 *
 * This "decoder" is intended to generate an output pattern that allows various
 * testing to occur without any external stimulus. This is useful for scheduler
 * testing, injector testing, output hardware testing, coil testing, etc. This
 * will be the only decoder that will be usable with just a cpu and comms interface.
 *
 * @todo TODO setup the timer registers as required.
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    666 // This is optimal!
#define NUMBER_OF_REAL_EVENTS      1 // no events really...
#define NUMBER_OF_VIRTUAL_EVENTS   1 // no events really...


#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/BenchTest.h"


// Setup the timer interrupts as internal timers only triggered by a serial call that returns if this isn't the decoder.
void decoderInitPreliminary(){
	// Configure 0 and 1 as outputs, but decouple them from the interrupts
	TIOS = 0xFF; // All outputs

	// Disable capture when in IC mode.
	TCTL4 = 0x00; // TODO Unrequired, remove.

	// Leave configured to not toggle the pin at all (0,0)
	// Std behaviour, no change required

	// Disable interrupts, to be enabled by a serial trigger
	TIE = 0x00;
}


void perDecoderReset(){} // Nothing special to reset for this code


const unsigned char decoderName[] = BENCH_TEST_NAME;
const unsigned short eventAngles[] = {0};           // no events really...
const unsigned char eventValidForCrankSync[] = {0}; // no events really...


/* Fire from serial, then repeat X revolutions or seconds or whatever and trigger Z outputs of various types etc
 *
 * Possible modes of repetition:
 * - Iterations
 * - Revolutions
 * - Time units
 */
void PrimaryRPMISR(){
	TFLG = 0x01;

	/* Reset the clock for reading timeout */
	Clocks.timeoutADCreadingClock = 0;

	/// @todo TODO Migrate this to the decoder itself once the necessary configuration has been setup.
	unsigned short edgeTimeStamp = TC0;

	// call sched output with args
	LongTime timeStamp;
	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionClock + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionClock;
	}

	unsigned char shouldFire = 1;
//	unsigned long localPeriod = 0; // mutlifire or busy wait, if doing this, check last period for some min, and if too small, shrink second to last and increase last
//	unsigned short localPeriod = 0; // normal mode
	if(testMode == TEST_MODE_ITERATIONS){
		currentEvent++;
		if(currentEvent == testEventsPerCycle){
			currentEvent = 0;
			testNumberOfCycles--;
			if(testNumberOfCycles == 0){
				// Disable the interrupt again, to be enabled by a serial trigger
				TIE &= NBIT0;
				shouldFire = 0;
			}
		}

		// TODO make this more sophisticated
		TC0 += testTicksPerEvent;
	}else if(testMode == TEST_MODE_REVOLUTIONS){
		// sub modes of different patterns, use scheduler for this by setting the ADC array up and probing/triggering/touching/poking/starting/
		// switch statement for selecting different const arrays of angles, use busy wait, or multiple interrupt to do larger gaps for lower rpms/coarse events
		// perhaps accept the pattern in the input packet and busy wait on some "run completed" flag before returning and freeing the buffer.
		// TEMP de-configure timers and leave shouldFire zeroed.
		TIE &= NBIT0;
	}else if(testMode == TEST_MODE_TIME_UNITS_SECONDS){
		// reset all timer modes for first time around, then check for timer >= requested value, check appropriate units of time, obviously...
		// TEMP de-configure timers and leave shouldFire zeroed.
		TIE &= NBIT0;
	}else if(testMode == TEST_MODE_TIME_UNITS_MINUTES){
		// ditto
		// TEMP de-configure timers and leave shouldFire zeroed.
		TIE &= NBIT0;
	}else if(testMode == TEST_MODE_TIME_UNITS_HOURS){
		// ditto again
		// TEMP de-configure timers and leave shouldFire zeroed.
		TIE &= NBIT0;
	}else{
		// de-configure timers and leave shouldFire zeroed.
		TIE &= NBIT0;
	}

	if(shouldFire){
		// configuration for multiple periods setup here?

		// fire outputs here
		unsigned char channel;
		for(channel = 0;channel < 6;channel++){
			if(currentEvent == outputEventInputEventNumbers[channel]){
				schedulePortTPin(channel, timeStamp);
			}
		}
	}
}


void SecondaryRPMISR(){
	TFLG = 0x02;
}
