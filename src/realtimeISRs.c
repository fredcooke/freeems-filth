/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke, Sean Keys
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
 * @ingroup interruptHandlers
 *
 * @brief Real time interrupts
 *
 * This file contains real time interrupt handlers. Mainly it holds the RTI
 * handler itself, however the modulus down counter and ETC timer overflow
 * functions are here too.
 */


#define REALTIMEISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/commsISRs.h"
#include "inc/decoderInterface.h"
#include "inc/xgateVectors.h"

/** @brief Real Time Interrupt Handler
 *
 * Handles time keeping, including all internal clocks, and generic periodic
 * tasks that run quickly and must be done on time.
 *
 * @author Fred Cooke
 */

#ifdef XGATE //TODO move to "XGS unit test include files"
//static unsigned char waitCycles = 44;
static unsigned char speed = 100;
static unsigned short test = 1;
static unsigned char testCH = 0;
//static unsigned char testDelayHigh = 0;
//static unsigned short testDelayLow = 5000;
//static unsigned short testRuntimeHigh = 0;
static unsigned long delay = 10000;
static unsigned short testRuntimeLow = 2500; //0x0FFE - 40;

static unsigned long delay2 = 50;
static unsigned long delay3 = 10;
// total rutime should equal 9e62
#endif

void RTIISR(){
	/* Clear the RTI flag */
	CRGFLG = 0x80;

	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT3, PORTB);

	/* Increment the counter */
	Clocks.realTimeClockMain++;

	/* This function could be performed without the extra variables by rolling over the main ones at the largest multiples of the next ones, but I'm not sure thats better */

	// TODO add content to eighths of a milli RTC ?

	/// @todo TODO refactor this entire file, especially to remove apparently expensive modulus operations which could be replaced with >= instead. Maybe much more.
	/* Every 8th RTI execution is one milli */
	if(Clocks.realTimeClockMain % 8 == 0){
		/* Increment the milli counter */
		Clocks.realTimeClockMillis++;

		/* Increment the milli roll over variable */
		Clocks.millisToTenths++;

		/* Perform all tasks that are once per millisecond here or preferably main */
		Clocks.timeoutADCreadingClock++;
		if(Clocks.timeoutADCreadingClock > fixedConfigs2.sensorSettings.readingTimeout){
			/* Set force read adc flag */
			coreStatusA |= FORCE_READING;
			Clocks.timeoutADCreadingClock = 0;
		}else if (CoreVars->RPM > 0){ // turn on very quickly if rpm appears non zero, temp impl...
			PORTA |= BIT7;
		}


#ifdef XGATE
<<<<<<< HEAD
//#include "xgateTests.c"
=======


/* TODO test
 * <Cheetah> sample TCNT into a var with the same name as the decoders edgeTimeStamp, then do a sleep scaled down from some clock source or a floating ADC or something and then call your XG stuff with that value and verify that its always correct, regardless of where the mid point between sched and edge is
<Cheetah> ie
<Cheetah> sched everything 2ms out from the edge
<Cheetah> and sleep 0-1ms randomly
<Cheetah> and hit a pin when you sample TCNT to mark the "edge"
<Cheetah> and hit one when you do the sched
<Cheetah> and then fire them
<Cheetah> THAT is a real test
<Cheetah> do that
<seank-efi> will do !
<seank-efi> thx!
<Cheetah> np
<Cheetah> use a diff pin for the edge and the sched pulses
<Cheetah> and
<Cheetah> run 5 of yours and one ECT all at the same delay
<Cheetah> and then do 3 of eahc with 3 pairs of delays
 */
		 //TODO Globalize
		struct XGOutputEvent *XGOutputEvents = (struct XGOutputEvent*)(parametersBase - RPAGE_TUNE_TWO_WINDOW_DIFFERENCE);
		unsigned short *xgsInStamp = (unsigned short*)(xGSInputEdgeStamp - RPAGE_TUNE_TWO_WINDOW_DIFFERENCE);
		unsigned char *xgsEventToSch = (unsigned char*)(xgsNumOfEventsToSchedule - RPAGE_TUNE_TWO_WINDOW_DIFFERENCE);

//		if(1){
//		if(Clocks.millisToTenths % 5 == 0){
//		if(1){
			if(Clocks.millisToTenths % 5 == 0){
//				goto skip;
//			}
			if(test == 1){
				//PORTB |= (1 << testCH);

			unsigned char savedRPage = RPAGE;
			RPAGE = RPAGE_TUNE_TWO;

//			unsigned short j, k;
//			for(j=0;j<ATD0DR7;j++){
//				for(k=0;k<5714;k++){
//				}
//			}

			if(testCH == 0){
			*xgsInStamp = TCNT;
			PORTB |= 0x3F;

			unsigned short j, k;
							for(j=0;j<(delay3);j++){
								for(k=0;k<6;k++){
								}
							}

			PORTB &= 0xC0;

			*xgsEventToSch = 2;

			XGOutputEvents[0].channelID = testCH;
			XGOutputEvents[0].delay = delay;
			XGOutputEvents[0].runtime = testRuntimeLow;

			XGOutputEvents[1].channelID = testCH + 1;
			XGOutputEvents[1].delay = delay2;
			XGOutputEvents[1].runtime = 5000;

			XGSCHEDULE();
			//delay -= 5000;
			//delay2 *= 2;
			delay3 += 5;

			}else if(testCH == 1 ){
			//XGOutputEvents[1].channelID = testCH + 1;
			//GOutputEvents[1].delay = 200;
			//XGOutputEvents[1].runtime = 5000;

			}else if(testCH == 2){




			}else if(testCH == 3){

			}else if(testCH == 4){

			}else if(testCH == 5){

			}else if(testCH == 6){
//				XGOutputEvents[0].channelID = testCH;
//				XGOutputEvents[0].delayHigh = 0;
//				XGOutputEvents[0].delay = 0;
//				XGOutputEvents[0].runtime = ATD0DR7 * 100;

			}else{
//				XGOutputEvents[0].channelID = testCH;
//				XGOutputEvents[0].delayHigh = 0;
//				XGOutputEvents[0].delay = 5000;
//				XGOutputEvents[0].runtime = 5000;
			}



testCH++;
			speed -= 10;
			if(speed == 0){
				speed = 100;
			}
			if(testCH > 7){
				testCH = 0;
			}
			RPAGE = savedRPage;
			}
		}

>>>>>>> c39da6f9d1f25b09058da52e46415f2f424df30a
#endif



		/* Every 100 millis is one tenth */
		if(Clocks.millisToTenths % 100 == 0){
			/* Increment the tenths counter */
			Clocks.realTimeClockTenths++;

			/* Increment the tenths roll over variable */
			Clocks.tenthsToSeconds++;

			/* Reset the millis roll over variable */
			Clocks.millisToTenths = 0;

			/* Perform all tasks that are once per tenth of a second here or preferably main */
			// decrement port H debounce variable till it's zero again.
			if(portHDebounce != 0){
				portHDebounce -= 1;
			}

			/* Every 10 tenths is one second */
			if(Clocks.tenthsToSeconds % 10 == 0){
				/* Increment the seconds counter */
				Clocks.realTimeClockSeconds++;

				/* Increment the seconds roll over variable */
				Clocks.secondsToMinutes++;

				/* Reset the tenths roll over variable */
				Clocks.tenthsToSeconds = 0;
				/* Perform all tasks that are once per second here or preferably main */

				// temp fuel pump prime and safety off impl
				if(coreStatusA & FUEL_PUMP_PRIME){
					if(Clocks.secondsToMinutes == 4){
						coreStatusA &= CLEAR_FUEL_PUMP_PRIME;
						PORTA &= NBIT7;
					}
				}else if(CoreVars->RPM == 0){ /// @todo TODO This is too quick to turn off, average 0.5 seconds, which is OK, but fastest = 0seconds which is difficult to understand, needs a flag and to be 1 - 2 with average 1.5.
					PORTA &= NBIT7;
				}

				/* Every 60 seconds is one minute, 65535 minutes is enough for us :-) */
				if(Clocks.secondsToMinutes % 60 == 0){
					/* Increment the minutes counter */
					Clocks.realTimeClockMinutes++;

					/* Potentially put an hours field in here and below, but that would be excessive */
					// TODO add hours RTC ?

					/* Reset the seconds roll over variable */
					Clocks.secondsToMinutes = 0;

					/* Perform all tasks that are once per minute here or preferably main */
					// TODO add content in minutes RTC ?

					/* Hours if statement here if we do hours which we probably won't */
				}
			}
		}
	}
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT3, PORTB);
}


/** @brief ECT overflow handler
 *
 * When the ECT free running timer hits 65535 and rolls over, this is run. Its
 * job is to extend the timer to an effective 32 bits for longer measuring much
 * longer periods with the same resolution. Please see section 10.5.5 of the
 * 68HC11 reference manual for more information on this technique!
 *
 * @warning The extension var should be incremented before the flag is cleared!
 *
 * @author Fred Cooke
 */
void TimerOverflow(){
	/* Increment the timer extension variable */
	timerExtensionClock++;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT5, PORTB); // TODO Should this go after the flag, or before the timer inc??? 6 possibilities here!
	/* Clear the timer overflow interrupt flag */
	TFLGOF = 0x80;
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT5, PORTB);
}


/** @todo TODO This could be useful in future once sleeping is implemented.
// Generic periodic interrupt (This only works from wait mode...)
void VRegAPIISR(){
	// Clear the flag needs check because writing a 1 can set this one
	//if(VREGAPICL & 0x01){ // if the flag is set...
		VREGAPICL |= 0x01; // clear it...
	//} // and not otherwise!

	// DO stuff
}
*/
