/* FreeEMS - the open source engine management system
 *
 * Copyright 2010-2012 Fred Cooke
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


/** @file
 *
 * @ingroup allHeaders
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Objects through which a decoder communicates.
 *
 * This file contains the declarations of objects used as a common interface
 * between all of the different wheel decoders and the main loop scheduler.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_DECODER_INTERFACE_H_SEEN
#define FILE_DECODER_INTERFACE_H_SEEN


#include "syncLossIDs.h"


#define BENCH_TEST_NAME "BenchTest"

// http://duckduckgo.com/?q=%281250+*+60%29+*+50
// 1250 ticks per milli second
// 1250000 ticks per second
// 60 seconds per minute
// 360 degrees per revolution
// 10 ticks per degree multiplier
// 2 rpm scaler
// unused, already excluded 50 units per degree
// 1250000 * 60 = 75000000
// 75000000 / 360 = 208333.333333333333333
// 208333.333333333333333 * 2 * 10 = 4166666.666666666666667
#define degreeTicksPerMinute 4166667 // rounded up by 1/3
#define ticks_per_degree_multiplier (10 * ANGLE_FACTOR) // FIX <<< shouldn't be done like this.
/// @todo TODO make this ^ scaling better x10 yields 64rpm minimum functional engine speed.


/// @todo Introduce the concept of sync level to schedule for if NOT synced
/// @todo and a way of deciding what to do in different sync states
/// @todo and proper dividers for pulsewidths
/// @todo and ability to lock pulsewidht/dwell for scheduling
/// @todo and generalise scheduling to all pins
/// @todo and provide a way of choosing a source of pulsewidth dwell or fuel duration
/// @todo and a way of allowing overly advanced scheduling instead of none, when its fuel
#define COMBUSTION_SYNC      BIT0 ///< Sync sufficient for Dizzy/Batch Injection
#define CRANK_SYNC           BIT1 ///< Sync sufficient for Wasted Spark/Semi-Sequential
#define CAM_SYNC             BIT2 ///< Sync sufficient for COP/CNP/Sequential
#define LAST_TIMESTAMP_VALID BIT3 ///< Set when first decoder ISR runs post a reset
#define LAST_PERIOD_VALID    BIT4 ///< Set when second decoder ISR runs post a reset
#define LAST_MATCH_VALID     BIT5 ///< Missing teeth style decoders set this when a valid match is found
#define LAST_TPD_VALID       BIT6 ///< Set once sync is found and we've stored a Ticks Per Degree value
#define OK_TO_SCHEDULE       BIT7 ///< Sync confirmed OK by configured number of checks
// WARNING: Entire flag var is cleared with loss of sync!


#define ARBITRARY_DECODER_NAME_MAX_LENGTH 64
#define SIZE_OF_EVENT_ARRAYS 256
#if (SIZE_OF_EVENT_ARRAYS > 256)
#error "Event array size larger than variable used to index it!"
#endif // Is it paranoid to check myself like this? :-)


#define SET_SYNC_LEVEL_TO(SYNC_LEVEL) \
/* Otherwise caught-on event would be reset constantly */             \
if(!(KeyUserDebugs.decoderFlags & SYNC_LEVEL)){                       \
    KeyUserDebugs.decoderFlags |= SYNC_LEVEL;                         \
    KeyUserDebugs.syncCaughtOnThisEvent = KeyUserDebugs.currentEvent; \
}                                                                     \
                                                                      \
/* Reason for last loss of sync was not timeout (0) */                \
if(KeyUserDebugs.syncLostWithThisID){                                 \
    if(syncConfirmationsRunningCounter){                              \
        syncConfirmationsRunningCounter--;                            \
    }else{                                                            \
        KeyUserDebugs.decoderFlags |= OK_TO_SCHEDULE;                 \
    }                                                                 \
}else{                                                                \
    if(syncConfirmationsStartingCounter){                             \
        syncConfirmationsStartingCounter--;                           \
    }else{                                                            \
        KeyUserDebugs.decoderFlags |= OK_TO_SCHEDULE;                 \
    }                                                                 \
}                                                                     // End of macro.


#define SCHEDULE_ONE_ECT_OUTPUT() \
if(outputEventExtendNumberOfRepeats[outputEventNumber] > 0){                                                      \
	*injectorMainControlRegisters[pin] &= injectorMainDisableMasks[pin];                                          \
	outputEventExtendNumberOfRepeatsRealtime[pin] = outputEventExtendNumberOfRepeats[outputEventNumber];          \
	outputEventExtendNumberOfRepeatsRealtime[pin]--;                                                              \
	outputEventExtendRepeatPeriodRealtime[pin] = outputEventExtendRepeatPeriod[outputEventNumber];                \
	outputEventDelayFinalPeriodRealtime[pin] = outputEventDelayFinalPeriod[outputEventNumber];                    \
	*injectorMainTimeRegisters[pin] = timeStamp.timeShorts[1] + outputEventExtendRepeatPeriod[outputEventNumber]; \
	Counters.pinScheduledWithTimerExtension++;                                                                    \
}else{                                                                                                            \
	*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];                                           \
	*injectorMainTimeRegisters[pin] = startTime;                                                                  \
	Counters.pinScheduledToGoHigh++;                                                                              \
}                                                                                                                 \
TIE |= injectorMainOnMasks[pin];                                                                                  \
TFLG = injectorMainOnMasks[pin];                                                                                  \
outputEventPulseWidthsRealtime[pin] = outputEventPulseWidthsMath[outputEventNumber];                              \
selfSetTimer &= injectorMainOffMasks[pin];                                                                        // End of macro block!


#ifdef DECODER_IMPLEMENTATION_C // See above for information on how to set these values up.

/// @todo TODO behave differently depending upon sync level?
#define SCHEDULE_ECT_OUTPUTS() \
numberScheduled = 0;                                                                                                                \
if(KeyUserDebugs.decoderFlags & OK_TO_SCHEDULE){                                                                                    \
	unsigned char outputEventNumber;                                                                                                \
	for(outputEventNumber=0;outputEventNumber<fixedConfigs1.schedulingSettings.numberOfConfiguredOutputEvents;outputEventNumber++){ \
		if(outputEventInputEventNumbers[outputEventNumber] == KeyUserDebugs.currentEvent){                                          \
			skipEventFlags &= ~(1UL << outputEventNumber);                                                                          \
			schedulePortTPin(outputEventNumber, timeStamp);                                                                         \
			numberScheduled++;                                                                                                      \
		}else if(skipEventFlags & (1UL << outputEventNumber)){                                                                      \
			unsigned char eventBeforeCurrent = 0;                                                                                   \
			if(KeyUserDebugs.currentEvent == 0){                                                                                    \
				eventBeforeCurrent = numberOfRealEvents - 1;                                                                        \
			}else{                                                                                                                  \
				eventBeforeCurrent = KeyUserDebugs.currentEvent - 1;                                                                \
			}                                                                                                                       \
                                                                                                                                    \
			if(outputEventInputEventNumbers[outputEventNumber] == eventBeforeCurrent){                                              \
				schedulePortTPin(outputEventNumber, timeStamp);                                                                     \
				numberScheduled++;                                                                                                  \
			}                                                                                                                       \
		}                                                                                                                           \
	}                                                                                                                               \
}                                                                                                                                   // End of macro block!


// A value of zero = do nothing
#define COARSE_BB_IGNORE 0
#define COARSE_BB_GO_ON  1
#define COARSE_BB_GO_OFF 2
#define COARSE_BB_TOGGLE 3
#define COARSE_BB_MASK   0x03

#define OUTPUT_COARSE_BBS() \
if(fixedConfigs1.coarseBitBangSettings.outputActions[KeyUserDebugs.currentEvent]){                                                                \
	int offset;                                                                                                                                   \
	for(offset=0;offset<fixedConfigs1.coarseBitBangSettings.numberConfigured;offset++){                                                           \
		unsigned char behaviour = (fixedConfigs1.coarseBitBangSettings.outputActions[KeyUserDebugs.currentEvent] >> (offset*2)) & COARSE_BB_MASK; \
		if(behaviour){                                                                                                                            \
			if(behaviour == COARSE_BB_GO_ON){                                                                                                     \
				*(fixedConfigs1.coarseBitBangSettings.ports[offset]) |= fixedConfigs1.coarseBitBangSettings.masks[offset];                        \
			}else if(behaviour == COARSE_BB_GO_OFF){                                                                                              \
				*(fixedConfigs1.coarseBitBangSettings.ports[offset]) &= (unsigned char)~(fixedConfigs1.coarseBitBangSettings.masks[offset]);      \
			}else if(behaviour == COARSE_BB_TOGGLE){                                                                                              \
				*(fixedConfigs1.coarseBitBangSettings.ports[offset]) ^= fixedConfigs1.coarseBitBangSettings.masks[offset];                        \
			}                                                                                                                                     \
		}                                                                                                                                         \
	}                                                                                                                                             \
}                                                                                                                                                 // End of macro block!


// These give a warning in eclipse because they aren't defined in this file, they are defined per decoder and enforced here.
#ifndef DECODER_MAX_CODE_TIME
#error "Define your code max runtime conservatively at first, then optimise once the code is complete."
#endif
#ifndef NUMBER_OF_REAL_EVENTS
#error "Define how many unique events your decoder sees!"
#endif
#ifndef NUMBER_OF_VIRTUAL_EVENTS
#error "Define the length of the event array!"
#endif
#if ((NUMBER_OF_VIRTUAL_EVENTS % NUMBER_OF_REAL_EVENTS) != 0)
#error "Virtual events should be a multiple of real events!"
#endif

const unsigned char numberOfRealEvents = NUMBER_OF_REAL_EVENTS;
const unsigned char numberOfVirtualEvents = NUMBER_OF_VIRTUAL_EVENTS;
const unsigned short totalEventAngleRange = ANGLE(720); //TOTAL_EVENT_ANGLE_RANGE;
const unsigned short decoderMaxCodeTime = DECODER_MAX_CODE_TIME;
const unsigned char decoderName[] = BASE_FILE_NAME;

#endif


/// @todo TODO two unsigned chars, and two unsigned shorts, which is the MAP ADC value, the MAP value is sampled on every event in a cycle, and if less than the previous stored value, which is reset at every zeroth event, with the old value and old event number stored globally.
/// @todo TODO the same thing could be done, but with a median filter or similar, perhaps map sampling could be done dymanically like this, though it could yield unpredictable results, it could also yield the best running engines, just a thought...


// Helpers - force all these to be inlined!
void decoderInitPreliminary(void);
void perDecoderReset(void);
void resetToNonRunningState(unsigned char uniqueLossID);
void schedulePortTPin(unsigned char pin, LongTime timeStamp);
/** @todo TODO add shared function here that takes a long time stamp and stores
 * it in an array pointed to by a var with a flag saying "do it or not",
 * populate array entry, check pointer, set send flag, and unset record flag OR
 * increment pointer and return. Add call to this from all decoders. Add code
 * to interact with this in commsCore.c and/or main.c
 *
 * probably need to think it through a bit more to support both inputs at the
 * same time. Should also have 16 bits as an option for the purposes of
 * increased storage and not needing 32 bit resolution at higher revs. Better
 * to record stamps or diffs? Perhaps set the relative array sizes in a config
 * var such that if we expect 8 primary for every 2 secondary, then one array
 * is 4x as big as the other, and the population routine knows this. Think
 * about how to decode it later too in olv/mtx.
 */


/// @todo TODO add xgate scheduling functions here! Sean, looking forward to it, but after LT1 goes :-)


/** @todo TODO IDEA: use a two stage mapping scheme for sched. Such that you
 * have event number to joiner number in an unsigned char array such that event
 * 4 and event 7 both are assigned join number 2, then pin X is scheduled to
 * run on join number 2 which could be on any number of real events!! GREAT!
 */



/**
 * RPM Calculations:
 *
 * Either need a per decoder function that is called from the main loop OR...
 * RPM calculation is done in real time inside one of the RPM interrupts OR...
 * The choice of either, up to the decoder to decide how it is done, in this
 * case the function can either do nothing, or swap some pointers/var values
 * around or similar.
 *
 * MAP Sampling:
 *
 * Max number of samples = max number of cylinders, has to be handled by
 * decoder due to potential mismatch between wheel pattern and cylinder firing
 * pattern unless it is done on a rough multiple sample basis in generic code
 * that runs often and can approximate timing/position for sampling.
 *
 * Scheduling:
 *
 * Fueling pins could be expected to fire once per cylinder event (1 - 12), or
 * once per engine cycle, or something in between, but what is a reasonable
 * maximum, and is it workable to allow some cases and not others?
 *
 *            |-----------------------------------------------------------|
 *            |                           Pins                            |
 *            |-----------------------------------------------------------|
 *            |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * -----------|-----------------------------------------------------------|
 * |     |  1 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  2 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  3 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  4 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  5 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  6 |    |    |    |    |    |    |    |    |    |    |    |    |
 * | Cyl |----|-----------------------------------------------------------|
 * |     |  7 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  8 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  9 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 10 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 11 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 12 |    |    |    |    |    |    |    |    |    |    |    |    |
 * -----------|-----------------------------------------------------------|
 *
 *
 * Ignition pins will only need to be fired once per cycle (COP/CNP), twice per
 * cycle (Wasted Spark) or once per cylinder event (distributor) unless
 * multiple-spark startup is required, however this could be done with cascaded
 * dwell events, timer self-set:
 *
 * on dwell off spark on dwell off spark on dwell off and disable spark
 *
 * This example is for triple spark, 2 or more than 3 are also possible.
 *
 * When coils are wired one per cylinder for COP/CNP, during starting or loss
 * of cam sync two opposing coils will be fired at the same time in pseudo
 * wasted spark mode.
 *
 * Possible states of sync are as follows:
 *
 * Full cycle engine sync - COP/CNP/Sequential
 * Half cycle revolution sync - Wasted Spark/Semi Sequential
 * Cylinder sync - Distributor/Many pulses or un-timed batch pulses
 *
 * Wheels will have various patterns of rising/falling edges. Scheduling may be
 * done from either the rising or falling edge on some, or only on one edge of
 * others. VR sensors have only one reliable edge, the other varies with speed
 * and associated rise/fall times of the approximately sinusoidal wave form.
 * Simple patterns shall be required to be timed to the engine such that at low
 * engine speeds the timer delays available with high accuracy are sufficient
 * to properly time ignition events. At the least, there should be a wheel
 * event per cylinder event, and in close proximity to that cylinder event.
 * Allowing even more relaxed wheel patterns would mean compromising the
 * performance for other more common setups and/or increasing code complexity
 * by an unacceptable amount.
 *
 * OLD notes:
 *
 * arrays of output channels, iterate and check for wheel event number, if matched, fire:
 * doesn't allow for firing a pin more than once a cycle!! no use.
 * allows multi channel on a single wheel event (virtually useless) but is slow, one loop
 * and array per type of output channel.
 *
 * array of wheel events, do lookup for wheel event, then if output channel valid, schedule it.
 * single channel per tooth event (acceptable, wire in parallel if required), fast, memory hog,
 * need one array per type of channel, array length = max expected tooth count! do we need to
 * support every single tooth on a Nissan 360 style decoder or just cyl event count, what about
 * Porsche 130? next stop is 60, seems good. can we use bit-fields to save memory, 1 bit =
 * 2 possible pins, 2 bits = 4, etc, this will be slower, though. probably just an unsigned char[]
 */


// Init routine:
//
// Allow configuration of timer details? tick size? If so, need to introduce scaling to calcs to
// produce correct tick count and therefore pulsewidth. Migrate dead time to time units and scale
// to get ticks to add to final pw.
//
// We require some configuration to allow the Nissan style decoder to use the pulse accumulators to
// count those one degree slots accurately to a high rpm without excessive cpu load.


// move the following to  fuel calcs or sched code header, it doesn't belong here...
//
// stuff to do with timing and sync etc. ie, figuring out upon which



/* end of the wrapper ifdef from the very top */
#endif
