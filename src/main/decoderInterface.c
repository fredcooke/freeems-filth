/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2013 Fred Cooke
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
 * @ingroup enginePositionRPMDecoders
 *
 * @brief shared functions used by all decoders
 *
 * To maximise code reuse and minimise bugs it is strongly recommended that you
 * use these pre-canned functions to do work required in your decoder.
 */


#define DECODER_INTERFACE_C
#include "inc/freeEMS.h"
#include "inc/decoderInterface.h"

/* Global Variables */
// ADC


/* Self set flags for starting from ECT out ISR code. */
unsigned char selfSetTimer;          /* Set the start time of injection at the end of the last one in the channels ISR instead of the input ISR */
// RPM - need some sort of state to say not to use these first time through...
unsigned short ticksPerDegree0; // to be replaced with logging scheme for teeth.
unsigned short ticksPerDegree1; // to be replaced with logging scheme for teeth.
unsigned short* ticksPerDegree; // final output variable, probably move into inputVars struct?
unsigned short* ticksPerDegreeRecord; // intermediate storage variable, do something with this?

// Time/Sync

/*
what is common between different setups? Add others here as required/desired/discussed.

        M-N setup - to sync we need gap that has just passed, and gap before, cases are: two gaps approx equal = who knows where. current gap = N * bigger means tooth after gap, current gap = N times smaller = second tooth after gap. Two opportunities to sync. by definition we always have these two gap measurements once synced. from these two gap measurements we can obtain a rough first RPM, then later RPM can be got from opposing teeth.
        4and1 setup - sync is obtained via logic, to get a rough RPM we need only one gap measurement, to verify noise free operation we need two. When we sync we may or may not have a previous gap measurement. For one sync opportunity we could have 0, 1, 2 gaps, for another we could have 0 or 1 gaps, and for the rest we will not have a gap measurement till a subsequent  event.
        24and2 setup - sync is obtained simply by watching for second trigger, sync is maintained by checking that second trigger falls when it should again. When a second trigger arrives, we could have 0, 1, 2 - ~12 primary gaps measured
        Simple setup - sync is not required, fire on all valid pulses. check for noise based on previous gaps, one event per ign event, correctly spaced timing required. Can be V twin, dizzy/points/outer of dsm/4and1 cas units, etc.

From this we need:

this stamp - have while running only. - so not required in header
previous stamp
stamp before previous stamp - only required on previous execution, at which time it is actually previous stamp, so not required.

this gap - have while running only. - so not required in header
previous gap - stored last time

flags to know if gap and stamp are valid - if gap is valid, stamp is not the oldest we effectively have.
previous gap valid - one flag
previous stamp valid - one flag

event counter - single unsigned value, 256 enough? probably can't cope with more than that anyway, except at low rpm, which is useless.

event angles - array of shorts, range required is 0 - 719.9999999999999 - can we provide sub degree accuracy with an unsigned short array? yes, what is best scale figure?

States:
* no sync (not of or of other three, no flag required, obviously)
* cylinder sync - one flag
* crank sync - one flag
* cam sync - one flag

from the above we can check one gap+angle with the next gap+angle and ensure smooth noise free operation is occurring.

*/
// unsigned long thisEventTimeStamp; recommended variable naming, may be enforced for/with macro use
// unsigned long thisInterEventPeriod; ditto
/// @todo TODO sync loss/gain semantics - how paranoid? under what circumstances? should we make it configurable whether a decoder that is in a situation where it would find sync if not synced, resets sync, or loses sync. Likewise, at initial sync gain time, should it go "prelim sync found" and only verify sync on the second lap around, or start firing events straight off the bat. Starting will suck if paranoid, but if there is noise at high load/rpm and events get mis-scheduled before sync is lost, that is serious. This is philosophical, and the reality is that you must assume that your signal is clean to some level and verified clean under lower risk conditions.
unsigned long lastEventTimeStamp;
unsigned long lastPrimaryEventTimeStamp;
unsigned long lastSecondaryEventTimeStamp;
unsigned short lastTicksPerDegree;
unsigned short lastPrimaryTicksPerDegree;
unsigned short lastSecondaryTicksPerDegree;
unsigned long skipEventFlags;
unsigned char numberScheduled; /// @todo TODO remove DEBUG
unsigned char syncConfirmationsRunningCounter;  // TODO move to a struct?
unsigned char syncConfirmationsStartingCounter; // TODO move to a struct?

// These are defined per decoder and used elsewhere!
const unsigned char decoderName[sizeof(BASE_FILE_NAME)];
const unsigned char numberOfRealEvents; // How many unique events the decoder sees.
const unsigned char numberOfVirtualEvents; // How many of the members of the eventAngles array are valid. (multiples of real events (1 - 12))
const unsigned short eventAngles[SIZE_OF_EVENT_ARRAYS]; /// @todo TODO From 0 - totalEventAngleRange degrees, scale: x50
const unsigned char eventValidForCrankSync[SIZE_OF_EVENT_ARRAYS]; // For decoders with crank sync possible before cam sync, mark which events are eligble for crank scheduling here 0 = not valid, anything else = valid
const unsigned short totalEventAngleRange;  // 720 for a four stroke, 360 for a two stroke, ? for a rotary. move this to code with a single setting for engine type and generate transformations based on that? All decoders will be 720 for now and only support 4 strokes without hackage.
const unsigned short decoderMaxCodeTime; // The max of how long the primary and secondary ISRs take to run with worst case scheduling loop time!

// Scheduling

//// Config items: These must exist in flash only config, not here...
//const unsigned char ADCSampleEvents[12];
//const unsigned char numberOfOutputEvents;

unsigned char outputEventInputEventNumbers[MAX_NUMBER_OF_OUTPUT_EVENTS];     // 0xFF (disabled) by default, populated to actual input event numbers by the scheduler

unsigned short outputEventPulseWidthsMath[MAX_NUMBER_OF_OUTPUT_EVENTS];
unsigned short outputEventPulseWidthsMathSecondary[MAX_NUMBER_OF_OUTPUT_EVENTS];
unsigned char  outputEventExtendNumberOfRepeats[MAX_NUMBER_OF_OUTPUT_EVENTS];
unsigned short outputEventExtendRepeatPeriod[MAX_NUMBER_OF_OUTPUT_EVENTS];
unsigned short outputEventDelayFinalPeriod[MAX_NUMBER_OF_OUTPUT_EVENTS];
unsigned long  outputEventDelayTotalPeriod[MAX_NUMBER_OF_OUTPUT_EVENTS];

unsigned short outputEventPulseWidthsHolding[ECT_OUTPUT_CHANNELS];
unsigned char outputEventExtendNumberOfRepeatsHolding[ECT_OUTPUT_CHANNELS];
unsigned short outputEventExtendRepeatPeriodHolding[ECT_OUTPUT_CHANNELS];
unsigned short outputEventDelayFinalPeriodHolding[ECT_OUTPUT_CHANNELS];

unsigned short outputEventPulseWidthsRealtime[ECT_OUTPUT_CHANNELS];
unsigned char outputEventExtendNumberOfRepeatsRealtime[ECT_OUTPUT_CHANNELS];
unsigned short outputEventExtendRepeatPeriodRealtime[ECT_OUTPUT_CHANNELS];
unsigned short outputEventDelayFinalPeriodRealtime[ECT_OUTPUT_CHANNELS];

unsigned short injectorMainStartOffsetHolding[ECT_OUTPUT_CHANNELS];

/* Register addresses */
volatile unsigned short * volatile injectorMainTimeRegisters[ECT_OUTPUT_CHANNELS]; // Static during a run, setup at init, shouldn't be in RAM, FIXME
volatile unsigned char * volatile injectorMainControlRegisters[ECT_OUTPUT_CHANNELS]; // Static during a run, setup at init, shouldn't be in RAM, FIXME


/* Timer holding vars (init not required) */
unsigned long injectorMainEndTimes[ECT_OUTPUT_CHANNELS]; // Used for scheduling calculations
/* Channel latencies (init not required) */
unsigned short injectorCodeLatencies[ECT_OUTPUT_CHANNELS]; // Used for injector control in a dysfunctional way.


/* Code time to run variables (init not required) */
unsigned short injectorCodeOpenRuntimes[ECT_OUTPUT_CHANNELS]; // Stats only, remove or change to something accessible
unsigned short injectorCodeCloseRuntimes[ECT_OUTPUT_CHANNELS]; // Stats only, remove or change to something accessible


/// @todo TODO Perhaps use some of the space freed by shrinking all timing tables for this:
////unsigned long wheelEventTimeStamps[numberOfWheelEvents]; // For logging wheel patterns as observed
// Could be useful for really nice RPM readings done in the main loop.
// Logging of this nature will use the serial buffer which it will hold a lock over for the duration of the log.


/** @brief Reset key state
 *
 * Reset all important variables to their non-running state.
 *
 * @todo TODO bring this up to date and/or find a better way to do it.
 *
 * @param uniqueLossID 0 is reserved for system use, within your decoder never use the same value twice.
 */
void resetToNonRunningState(unsigned char uniqueLossID){
	extern KeyUserDebug KeyUserDebugs;
	extern Flaggable Flaggables; 
	extern const volatile fixedConfig2 fixedConfigs2;
	if(uniqueLossID){
		KeyUserDebugs.syncResetCalls++;
	}

	// Reset the safe re-sync counters.
	if(fixedConfigs2.decoderSettings.syncConfirmationsRunning == 0xFF){ // Prevent overflow to zero
		syncConfirmationsRunningCounter = 0xFF;
	}else{ // Ensure at least 1 cycle is confirmed
		syncConfirmationsRunningCounter = fixedConfigs2.decoderSettings.syncConfirmationsRunning + 1;
	}
	syncConfirmationsStartingCounter = fixedConfigs2.decoderSettings.syncConfirmationsStarting;

	/* Reset RPM to zero */
	ticksPerDegree0 = 0;
	ticksPerDegree1 = 0;

	// Keep track of lost sync in counters
	if(KeyUserDebugs.decoderFlags & (CAM_SYNC | CRANK_SYNC | COMBUSTION_SYNC)){
		if(KeyUserDebugs.decoderFlags & OK_TO_SCHEDULE){
			FLAG_AND_INC_FLAGGABLE(FLAG_DECODER_SYNC_LOSSES_OFFSET);
		}else{
			FLAG_AND_INC_FLAGGABLE(FLAG_DECODER_SYNCS_NOT_CONFIRMED_OFFSET);
		}
	}else{
		FLAG_AND_INC_FLAGGABLE(FLAG_DECODER_SYNC_STATE_CLEARS_OFFSET);
	}

	// record unique loss ID
	KeyUserDebugs.syncLostWithThisID = uniqueLossID;

	// record current event
	KeyUserDebugs.syncLostOnThisEvent = KeyUserDebugs.currentEvent;

	/* Clear all sync flags to lost state */
	KeyUserDebugs.decoderFlags = 0; // Nothing should use this except for us anyway!
	perDecoderReset();
	// TODO more stuff needs resetting here, but only critical things.
}


/** Schedule an ignition output event on port T
 *
 * @warning If you do not handle the skipEventFlags then excess advance may occur!
 */
void schedulePortTPin(unsigned char outputEventNumber, LongTime timeStamp){
	extern Counter Counters;
	extern const volatile fixedConfig1 fixedConfigs1;
	extern const unsigned short injectorSwitchOffCodeTime;
	extern const unsigned char injectorMainOnMasks[];
	extern const unsigned char injectorMainOffMasks[];
	extern const unsigned char injectorMainActiveMasks[];
	extern const unsigned char injectorMainGoHighMasks[];
	extern const unsigned char injectorMainDisableMasks[];
	extern const unsigned char injectorMainEnableMasks[];

	unsigned char pin = fixedConfigs1.schedulingSettings.outputEventPinNumbers[outputEventNumber];
	/* If the pin number is greater than the number of physical pins then this is an xgate only channel */
#define NUMBER_OF_OUTPUT_PINS 6 // FIXME duplicated in main.c
	if (pin < NUMBER_OF_OUTPUT_PINS) {
		unsigned short postReferenceEventDelay = 0;
		if (skipEventFlags & (1UL << outputEventNumber)) {
			postReferenceEventDelay = decoderMaxCodeTime;
			skipEventFlags &= ~(1UL << outputEventNumber); // Clear the flag
		} else {
			postReferenceEventDelay = outputEventDelayFinalPeriod[outputEventNumber];
		}
		// determine the long and short start times
		unsigned short startTime = timeStamp.timeShorts[1] + postReferenceEventDelay;
		// remove this temporarily too, no need for it without the later conditional code
		unsigned long startTimeLong = timeStamp.timeLong + postReferenceEventDelay;

		/// @todo TODO Make this more understandable as right now it is difficult to grok.
		// determine whether or not to reschedule or self schedule assuming pin is currently scheduled
		unsigned long diff = (injectorMainEndTimes[pin] + injectorSwitchOffCodeTime) - startTimeLong;
#define newStartIsAfterOutputEndTimeAndCanSelfSet (diff > LONGHALF)
		// http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861

		/*
		 fresh code again, five states, 6 possible behaviours:

		 not enabled - sched!!! always
		 enabled and low, ready to turn on - if too close, do nothing, or if far enough away, resched
		 enabled and high, ready to turn off - if too close, resched to turn on, if far enough away, self sched
		 */

		// Is it enabled and about to do *something*?
		if (TIE & injectorMainOnMasks[pin]) {
			// If configured to do something specific
			if (*injectorMainControlRegisters[pin] & injectorMainActiveMasks[pin]) {
				// If that something is go high
				if (*injectorMainControlRegisters[pin] & injectorMainGoHighMasks[pin]) {
					// GO HIGH SHOULD DO NOTHING CEPT COUNTER
					// if too close, do nothing, or if far enough away, resched
					// for now just always do nothing as it's going to fire, and whatever configured got it close enough...
					Counters.pinScheduledAlready++;
				} else { // Otherwise it's go low
						 // if too close, resched to turn, ie, stay on... , if far enough away, self sched
					if (newStartIsAfterOutputEndTimeAndCanSelfSet) {
						// self sched
						injectorMainStartOffsetHolding[pin] = startTime - *injectorMainTimeRegisters[pin];
						outputEventPulseWidthsHolding[pin] = outputEventPulseWidthsMath[outputEventNumber];
						outputEventExtendNumberOfRepeatsHolding[pin] = outputEventExtendNumberOfRepeats[outputEventNumber];
						outputEventExtendRepeatPeriodHolding[pin] = outputEventExtendRepeatPeriod[outputEventNumber];
						outputEventDelayFinalPeriodHolding[pin] = outputEventDelayFinalPeriod[outputEventNumber];
						selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
						Counters.pinScheduledToSelfSchedule++;
					} else {
						SCHEDULE_ONE_ECT_OUTPUT();
						Counters.pinScheduledAgainToStayOn++;
					}
				}
			} else { // Configured to do nothing, or toggle
				if (*injectorMainControlRegisters[pin] & injectorMainGoHighMasks[pin]) {
					// TOGGLE SHOULD EARN SOME SORT OF ERROR CONDITION/COUNTER
					Counters.pinScheduledToToggleError++;
				} else {
					// DO NOTHING SHOULD DO THE SAME AS GO HIGH
					// ie, do nothing
					// if too close, do nothing, or if far enough away, resched
					// for now just always do nothing as it's going to fire, and whatever configured got it close enough...
					Counters.pinScheduledToDoNothing++;
				}
			}
		} else { // not enabled, schedule as normal
			SCHEDULE_ONE_ECT_OUTPUT();
			Counters.pinScheduledFromCold++;
		}
	}


#ifdef XGATE // This has to be here because the timing of the ECT stuff is critical and it must run first.
#include "xgateScheduler.c"
#endif // Also, this should always run so can't be inside the above if/else block.
}
