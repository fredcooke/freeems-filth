/* FreeEMS - the open source engine management system
 *
 * Copyright 2010 Sean Keys, Fred Cooke
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

/** @file xgateVectors.h
 * @ingroup xgateHeaders
 *
 * @brief C header for assembly xgate functions
 *
 * Because we need to call the assembly flash burning function from C code an
 * extern function declaration is required to allow successful compilation.
 */
#ifndef FILE_XGATEGLOBALS_H_SEEN
#define FILE_XGATEGLOBALS_H_SEEN


#ifdef XGATEGLOBALS_H
#define EXTERN
#else
#define EXTERN extern
#endif

#define XGSCHEDULE()	XGSWT = 0x0101;
#define DELAYTESTPW		2500 /* two miliseconds in .8us ticks */

// Use this block to schedule an xgate event
typedef struct {
	unsigned short channelID;
	unsigned long delay;
	unsigned short runtimeHigh;
	unsigned short runtime;
	unsigned short inputTS;
} XGOutputEvent;

extern XGOutputEvent *XGOutputEvents;
extern unsigned short *xgsInStamp;
extern unsigned short *xgsEventsToSch;

extern void incrementalTests();
extern void firstLastDiffTest();
extern void singleTest();
extern void scheduleLatencyTest();
extern void delayShiftDiffTest();
extern void competingInterruptsTest();

//for debug
extern void eventFlags1();


#else
        /* let us know if we are being untidy with headers */
        #warning "Header file XGATEVECTORS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
