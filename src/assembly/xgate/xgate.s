/* FreeEMS - the open source engine management system
 *
 * Copyright 2010-2011 Sean Keys
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

include "assembly/xgate/xgate.inc"
; *****************************************************************************
;
; Thanks to Edward Karpicz for help with getting all the xgate registers sorted.
;
; *****************************************************************************
;	.sect .data
    .sect .ppageE1
startXGATECode:

; *****************************************************************************
;
;	REGISTERS
;
; *****************************************************************************

;PORTF   	=     	0x1005	; Port F register

; *****************************************************************************
;
;	CODE
;
; *****************************************************************************
; -----------------------------------------------------------------------------
;	Interrupts
; -----------------------------------------------------------------------------

;; Default interrupt handler.
def:
;        rts
.global startXGATECode
.global endXGATECode
.global xgateSchedule
.global xgateScheduleEnd
.global xgatePITTurnOn
.global xgatePITTurnOnEnd
.global xgatePITTurnOff
.global xgatePITTurnOffEnd
.global xgateMetronome
.global xGSFlags

.global xGSInputEdgeStamp
.global xgsNumOfEventsToSchedule
;.global parameterInputStamp
.global parametersBase
.global parameterChannelID
.global parameterDelayH
.global parameterDelay
.global parameterRuntime
.global parameterChannelID1
.global parameterDelayH1
.global parameterDelay1
.global parameterRuntime1
.global parameterChannelID2
.global parameterDelayH2
.global parameterDelay2
.global parameterRuntime2
.global parameterChannelID3
.global parameterDelayH3
.global parameterDelay3
.global parameterRuntime3
.global parameterChannelID4
.global parameterDelayH4
.global parameterDelay4
.global parameterRuntime4
.global parameterChannelID5
.global parameterDelayH5
.global parameterDelay5
.global parameterRuntime5


; ----------------------------------------------------------------------------------
;	Schedule Subroutine
;	NOTE: the value of R1 is passed by the vector table we may use it or discard it
;	TODO XGS(chanNum8, numOfDelays8, delayTime16, runtime16)
;           XGS(ECTCNT, numParameters)
; ----------------------------------------------------------------------------------

xgateSchedule: ; SoftWare Trigger 0, call this from the main core when you want to add/update an xgate scheduled event
	;old code
	LDD R3, PITCNT1 ;load current metronome count
	LDW R3, R3, #ZERO_OFFSET
	LDD R4, xGSStartTime
	STW R3, R4, #ZERO_OFFSET
	;clear interrupt flag
	LDD R3, #SW_ISR_FLAG_REG
	LDD R2, #SW_ISR_ZERO_CFLAG_MASK
	STW R2, R3, #ZERO_OFFSET
 ;check to see if ChannelID is within range
 ;NOTE when properly used we actually dont need this code, but there is a chance of mem corruption without it
; LDD R4, parameterChannelID
; LDW R4, R4, #ZERO_OFFSET
; MOV R5, R4
; SUBL R5, #NUMBER_OF_EVENT_STRUCTURES
; BCS validChannel
 	;inc our bad channel counter
; 	LDD R1, xGBBBadChannelRequest
; 	LDW R2, R1, #ZERO_OFFSET
; 	ADDL R2, #1
; 	STW R2, R1, #0
; 	BRA	xgsDone
; validChannel:

;initialize our parameter loop counter
	LDD R1, xGSSystemVars
	LDL R2, #0
	STW R2, R1, #XGS_VARIABLE_NUM_OF_EVENTS_SCHEDULED_OFFSET
	LDD R2, parametersBase
	STW R2, R1, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET; #XGS_VARIABLE_EVENT_ADDRESS_OFFSET
BRA xgsParameterLoopCheck
	xgsParameterLoop:

    ;calculate xGSStartTime taking into account our inputEdge stamp
	LDD R4, TCNT ;load current TCNT
	LDW R4, R4, #ZERO_OFFSET
	LDD R5, xGSInputEdgeStamp ;load saved TCNT
	LDW R5, R5, #ZERO_OFFSET
	SUB R6, R4, R5 ;diff TCNT values to get elapsed time

    ;take our delayTime and add our runTime to get "runtimeDelay"
	LDD R3, xGSSystemVars
	LDW R3, R3, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET
;	LDW R4, R3, #PARAMETER_DELAY_LOWWORD_OFFSET ;Low Word
;   LDW R1, R3, #PARAMETER_DELAY_LOWWORD_OFFSET

LDW R4, R3, #PARAMETER_DELAY_LOWWORD_OFFSET ;load
LDW R7, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET ;load
	;delay low word - time elapsed(R6)
SUB R1, R4, R6 ; subtract inputEdge delay from parameter low word
SBC R5, R7, R0 ; subtract carry from high word

SUB R2, R4, R1 ; is low word zero?
SBC R2, R7, R5 ; is high word zero?
BCS xgsEdgeNotZero
STW R1, R3, #PARAMETER_DELAY_LOWWORD_OFFSET
STW R5, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET

BRA xgsEdgeFactorDone
xgsEdgeNotZero:

STW R0, R3, #PARAMETER_DELAY_LOWWORD_OFFSET
STW R0, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET
xgsEdgeFactorDone:

LDW R4, R3, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;Low Word
LDW R1, R3, #PARAMETER_DELAY_LOWWORD_OFFSET
	ADD R2, R4, R1 ;Add our delays to get runtime countdown
	STW R2, R3, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;save low
	LDW R2, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET ;High Word
	ADC R2, R0, R2 ;Add the carry to the high word if any
	LDW R4, R3, #PARAMETER_RUNTIME_HIGHWORD_OFFSET
	ADD R4, R2, R4 ;TODO a check for 16-range could be added here
	STW R4, R3, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;save high
	;If our times are long enough to use the metronome we need to factor is current counter value for each countdown
	LDW R4, R3, #PARAMETER_RUNTIME_HIGHWORD_OFFSET
	TST R4
BEQ xgsFixUpDone ;if our runtime doesnt have a highword value then our delay doesnt either
	;calculate and apply our metronome offset
	LDD R1, xGSStartTime
	LDW R1, R1, #ZERO_OFFSET
	COM R1 ;Diff our Metronome against itself
	;fix our RunTime
	LDW R4, R3, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;Low Word
	ADD R2, R4, R1 ;Add diff to our parameter countdown(low)
	STW R2, R3, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;save low
	LDW R2, R3, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;High Word
	ADC R2, R0, R2 ;Add the carry to the high word if any ;TODO a check for 16-range could be added here
	STW R2, R3, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;save high
	;fix our DelayTime
	LDW R4, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET
	TST R4
BEQ xgsFixUpDone
		LDW R4, R3, #PARAMETER_DELAY_LOWWORD_OFFSET ;Low Word
		ADD R2, R4, R1 ;Add diff to our parameter countdown(low)
		STW R2, R3, #PARAMETER_DELAY_LOWWORD_OFFSET ;save low
		LDW R2, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET ;High Word
		ADC R2, R0, R2 ;Add the carry to the high word if any ;TODO a check for 16-range could be added here
		STW R2, R3, #PARAMETER_DELAY_HIGHWORD_OFFSET ;save high
    xgsFixUpDone:
 ;calculate our pointer to our event of interest
	LDL R2, #0x00 ;initialize loop register
	LDL R3, #0x00 ;initialize our offset register
	LDD R4, xGSSystemVars
	LDW R4, R4, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET
	LDW R4, R4, #PARAMETER_CHANNEL_ID_OFFSET
BRA XSLoop1
	XSLoop1Block:
		ADDL R2, #0x01 ;i++
		ADDL R3, #EVENT_STRUCTURE_SIZE;++
	XSLoop1:
		CMP R4, R2
BNE XSLoop1Block
	;we can now update and arm our event
	LDD R4, eventsStructStart
	ADD R4, R3, R4 ;add offset to base address R3 still contains offset at this point
	LDD R5, xGSSystemVars
	STW R4, R5, #XGS_VARIABLE_EVENT_ADDRESS_OFFSET
	LDW R5, R5, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET
	;If the event has not happened yet go ahead and over write its delays
	;If the event is running extent only its runtime
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
BITL R6, #EVENT_FLAG_RUNNING ;TODO this may be redundant
BNE xgsExtendRuntime
;BITL R6, #EVENT_FLAG_ARMED
;BNE xgsDoNotSchedule ;do not attempt to scheudle if this event is already waiting to happen TODO make rescheduleable
;BITL R6, #EVENT_FLAG_RUNNING
;BNE xgsDoNotSchedule

	;Incase the event was previously scheduled clear all flags
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	ANDL R6, #EVENT_FLAG_AVAILABLE
	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	;Write our delay and set our flags accordingly
	LDW R6, R5, #PARAMETER_DELAY_LOWWORD_OFFSET;Load high word of parameter
	STW R6, R4, #EVENT_DELAY_LOW_WORD_OFFSET
	LDW R6, R5, #PARAMETER_DELAY_HIGHWORD_OFFSET;Load high word of parameter
	STW R6, R4, #EVENT_DELAY_HIGH_WORD_OFFSET
 	TST R6
BNE xgsNotApproachable ;if zero flag event as approachable
 	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
 	ORL R6, #EVENT_FLAG_APPROACHABLE
 	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
    ;get/save start time stamp so we can diff latency later on TODO move higher up
	LDD R6, xGSStartTime
	LDW R6, R6, #ZERO_OFFSET
	STW R6, R4, #EVENT_DELAY_LATENCY_METROSTAMP_OFFSET
 	xgsNotApproachable:
 	;save delay parameter to proper event
	LDW R6, R5, #PARAMETER_RUNTIME_HIGHWORD_OFFSET;Load high word of parameter
	STW R6, R4, #EVENT_RUNTIME_HIGH_WORD_OFFSET
 	TST R6
BNE xgsNotApproachableShutdown ;if zero flag event as approachable
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	ORL R6, #EVENT_FLAG_APPROACHABLE_SHUTDOWN
	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
    ;get/save start time stamp so we can diff latency later on TODO move higher up
	LDD R6, xGSStartTime
	LDW R6, R6, #ZERO_OFFSET
	STW R6, R4, #EVENT_RUNTIME_LATENCY_METROSTAMP_OFFSET
	xgsNotApproachableShutdown:
	BRA xgsSaveAllParameters

xgsExtendRuntime:
	;clear shutdown approachable flag
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	ANDL R6, #EVENT_FLAG_APPROACHABLE_SHUTDOWN_XOR
	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
    ;get/save start time stamp so we can diff latency later on TODO move higher up
	LDD R6, xGSStartTime
	LDW R6, R6, #ZERO_OFFSET
	STW R6, R4, #EVENT_RUNTIME_LATENCY_METROSTAMP_OFFSET
	;save runtime parameter to proper event
	LDW R6, R5, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;Load low word of parameter
	STW R6, R4, #EVENT_RUNTIME_LOW_WORD_OFFSET
	LDW R6, R5, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;Load high word of parameter
	STW R6, R4, #EVENT_RUNTIME_HIGH_WORD_OFFSET
TST R6
BNE xgsDoneExtendingRuntime ;if zero flag event as approachable
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	ORL R6, #EVENT_FLAG_APPROACHABLE_SHUTDOWN
	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
xgsDoneExtendingRuntime:
BRA xgsApproachableCheck

xgsSaveAllParameters:
	;save runtime parameter to proper event
	LDW R6, R5, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;Load low word of parameter
	STW R6, R4, #EVENT_RUNTIME_LOW_WORD_OFFSET
	LDW R6, R5, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;Load high word of parameter
	STW R6, R4, #EVENT_RUNTIME_HIGH_WORD_OFFSET
	;clear parameter variables TODO test
	STW R0, R5, #PARAMETER_DELAY_HIGHWORD_OFFSET ;Load high word of parameter
	STW R0, R5, #PARAMETER_DELAY_LOWWORD_OFFSET ;Load high word of parameter
	STW R0, R5, #PARAMETER_RUNTIME_HIGHWORD_OFFSET ;Load high word of parameter
	STW R0, R5, #PARAMETER_RUNTIME_LOWWORD_OFFSET ;Load high word of parameter

	;flag our event as armed ;TODO this may be redundant review after code works
	LDW R6, R4, #EVENT_STATUS_FLAGS_OFFSET ;set our event ARMED bit
	ORL	R6, #EVENT_FLAG_ARMED
;    ORL R6, #EVENT_FLAG_NEW ;flag our event as new, this will prevent it's countdown from being decremented until after our first "check and fire" loop
	STW R6, R4, #EVENT_STATUS_FLAGS_OFFSET
	;If this event is approachable or approachable shutdown jump to it!

	;perform loop increments
	LDD R4, xGSSystemVars ;inc our number of events processed
	LDW R2, R4, #XGS_VARIABLE_NUM_OF_EVENTS_SCHEDULED_OFFSET
	ADDL R2, #1 ;i++
	STW R2, R4, #XGS_VARIABLE_NUM_OF_EVENTS_SCHEDULED_OFFSET
	;inc our event parameter address offset
	LDW R2, R4, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET
	ADDL R2, #PARAMETER_SET_SIZE ;i++
	STW R2, R4, #XGS_VARIABLE_PARAMETER_BASE_ADDRESS_OFFSET
xgsParameterLoopCheck:
	LDD R4, xGSSystemVars ;inc our number of events processed
	LDW R2, R4, #XGS_VARIABLE_NUM_OF_EVENTS_SCHEDULED_OFFSET
	LDW R1, R4, #XGS_VARIABLE_NUM_OF_EVENTS_TO_SCHEDULE_OFFSET
	CMP R1, R2
BEQ xgsParameterLoopDone
;BNE xgsParameterLoop ;our loop is now too big so we need to use a JAL
	LDD R7, xgsParameterLoop
	JAL R7
xgsParameterLoopDone:
	;see if we have approachable events
xgsApproachableCheck:
;for debugging/testing just branch reguardless
BRA xgatePITTurnOnUpdate
;	BITL R6, #EVENT_FLAG_APPROACHABLE;
;BNE xgatePITTurnOnUpdate ;if bit set jump
;	BITL R6, #EVENT_FLAG_APPROACHABLE_SHUTDOWN;
;BNE xgatePITTurnOnUpdate ;if bit set jump

	;debug code we have not yet handeled an overlapping schedule
	;TODO just inc a skipped events counter
	;LDD R7, #PORTBA
	;LDD R6, #0xFefe
	;STW R6, R7, #0
	;brk
xgsDoNotSchedule:
	xgsDone:
	RTS
xgateScheduleEnd:

xgateMetronome: ; PIT 2 ISR, called by PIT2 interrupt. Decrement out delayCounter.
    ;TODO save start time stamp
	LDD R2, xGMStartTime
	LDD R3, PITCNT1
	LDW R3, R3, #ZERO_OFFSET
	STW R3, R2, #ZERO_OFFSET
    ;CIF
    LDL R2, #PIT1_CFLAG_MASK
	LDD R3, #PITTF
	STB R2, R3, #ZERO_OFFSET
	;decrement our high word delays and runtimes value by 1
	;calculate our pointer offsets to our structure of interest
	LDL R2, #0x00 ;initialize loop register
	LDL R7, #FALSE ;initialize our branch to update short test var
	LDD R3, eventsStructStart ;initialize our structure pointer to start of onEvents array
	;ADDL R3, #DELAY_HIGH_WORD_OFFSET
	LDD R4, #NUMBER_OF_EVENT_STRUCTURES ;ld the number of structures we need to loop though
BRA XMLoop1
	XMLoop1Block: ; decrement all the high words of our countdown
		;if our event is running dont bother doing anything with the delay
		LDW R5, R3, #EVENT_STATUS_FLAGS_OFFSET
		BITL R5, #EVENT_FLAG_RUNNING
		BNE XMNoApproachableFlag
		;
		LDW R5, R3, #EVENT_DELAY_HIGH_WORD_OFFSET
		SUBL R5, #1 ;subtract 1 from our high word delay
		STW R5, R3, #EVENT_DELAY_HIGH_WORD_OFFSET
		;test to see if our event needs to be armed and schedule
		TST R5 ;see if our countdown is zero if it is see if its flagged for action
		BNE XMNoApproachableFlag ;branch if our channel armed flag is not set
		LDW R5, R3, #EVENT_STATUS_FLAGS_OFFSET
		BITL R5, #EVENT_FLAG_ARMED ;see if your ARMED bit is set
		BEQ XMNoApproachableFlag ;skip setting approachable if our armed flag is not set
		;set EVENT_FLAG_APPROACHABLE bit
		ORL	R5, #EVENT_FLAG_APPROACHABLE
		STW R5, R3, #EVENT_STATUS_FLAGS_OFFSET
		;place metro stamp
		LDD R5, xGMStartTime
		LDW R5, R5, #ZERO_OFFSET
		STW R5, R3, #EVENT_DELAY_LATENCY_METROSTAMP_OFFSET
		LDL R7, #TRUE ;Flag R7 true if we need to branch to process a near countdown
		XMNoApproachableFlag:
		;do the same for our runtime high words
		LDW R5, R3, #EVENT_RUNTIME_HIGH_WORD_OFFSET
		SUBL R5, #1 ;subtract 1 from our high word delay
		STW R5, R3, #EVENT_RUNTIME_HIGH_WORD_OFFSET
		;test to see if our event needs to be armed and schedule
		TST R5 ;see if our countdown is zero if it is see if its flagged for action
		BNE XMNoApproachableShutdownSet ;branch if our channel armed flag is not set
		LDW R5, R3, #EVENT_STATUS_FLAGS_OFFSET
		BITL R5, #EVENT_FLAG_ARMED ;see if your RUNNING bit is set TODO revise wording
		BEQ XMNoApproachableShutdownSet ;skip arming if our flag is not set
		;set EVENT_FLAG_APPROACHABLE_SHUTDOWN bit
		ORL	R5, #EVENT_FLAG_APPROACHABLE_SHUTDOWN
		STW R5, R3, #EVENT_STATUS_FLAGS_OFFSET
		;place RuntimeMetronomeStamp
		LDD R5, xGMStartTime
		LDW R5, R5, #ZERO_OFFSET
		STW R5, R3, #EVENT_RUNTIME_LATENCY_METROSTAMP_OFFSET
		LDL R7, #TRUE ;Flag R7 true if we need to branch to process a near countdown
		XMNoApproachableShutdownSet: ;jump here if countdown is greater than 16 bits
		ADDL R3, #EVENT_STRUCTURE_SIZE
		ADDL R2, #0x01 ;i++
	XMLoop1:
		CMP R4, R2
		BHI XMLoop1Block  ; if R4 >= R2

;LDD R7, #0
;LDD R3, eventsStructStart
;LDW R4, R3, #EVENT_STATUS_FLAGS_OFFSET
;STW R4, R7, #0
;brk

;Debug flip PORTP everytime we overflow
LDD R5, xgatePORTPFlip
JAL R5; jump to xgatePORTPFlip
	TST R7
		BNE xgatePITTurnOnUpdate ;branch to another function, it will issue the RTS when it completes
	RTS
xgateMetronomeEnd:

xgatePITTurnOn: ; PIT 0 ISR, called by PIT0 interrupt. Loop though our que and see if we need to bang any registers
    ;CIF
    LDL R2, #PIT0_CFLAG_MASK
	LDD R3, #PITTF
	STB R2, R3, #ZERO_OFFSET


xgatePITTurnOnUpdate:

	;Disable pit channel 0
	LDD R3, #PITCE
	LDB R4, R3, #ZERO_OFFSET
    ANDL R4, #PIT0_DISABLE_MASK
    STB R4, R3, #ZERO_OFFSET

	;Either the MetroNome or XGScheduler can send us here

	;clear our SELF_UPDATE bit
	LDD R2, pitDelaySubSystemVars
	LDW R3, R2, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
	ANDL R3, #PDS_FLAG_SELF_UPDATE_BIT_XOR
	STW R3, R2, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
	;set this to highest possobile value initially so any value will be the soonest
	LDD R1, pitDelaySubSystemVars
	LDD R3, 0xFFFF
	STW R3, R1, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET
	;************************************************************************************
	; loop thought events if event is flagged as EVENT_FLAG_APPROACHABLE and countdown is zero
	; after we Subtract our last runtime from other events bang the register clear the masks
	;************************************************************************************
	; loop though our events, if the event is zero-time bang the register
	;subtract last runtime from events flagged EVENT_FLAG_APPROACHABLE if result is zero or carry is set bang the register
	LDL R1, #0x00 ;initialize loop register
	LDD R2, eventsStructStart ;initialize our structure pointer to start of onEvents array
	LDL R3, #NUMBER_OF_EVENT_STRUCTURES ;ld the number of structures we need to loop though
	BRA XGPITOnLoop1
	XGPITOnLoop1Block:
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
	;TODO add zero tollerance handeling
	BITL R4, #EVENT_FLAG_APPROACHABLE ;see if your
	BEQ PIT0CheckBangOff ;skip subtracting our last countdown if our approachable flag is not set
		LDD R5, #PITCNT1
		LDW R5, R5, #0
		LDW R6, R2, #EVENT_DELAY_LATENCY_METROSTAMP_OFFSET
		STW R5, R2, #EVENT_DELAY_LATENCY_METROSTAMP_OFFSET
		SUB R5, R6, R5 ;R5 now contains our elapsed time
		LDW R6, R2, #EVENT_DELAY_LOW_WORD_OFFSET
	TST R6
	BEQ PITOnBang ; if zero time jump to bang on
		SUB R7, R6, R5
		STW R7, R2, #EVENT_DELAY_LOW_WORD_OFFSET ;save the updated event approacable delay incase we arent at zero time
		;see if we are now zero time or past zero time :TODO this value could be used for latency calcs
		CMP R6, R5
	BCS PITOnBang
		TST R7 ;CMP R7, R5
	BNE PIT0NotYetBangableOn ;branch if greater than zero
		PITOnBang:
		;bang register
		LDW R4, R2, #EVENT_BANG_REGISTER_OFFSET ;load the address of the register we wish to bang from the event structure
		LDB R5, R4, #ZERO_OFFSET ;save the register value
		LDW	R6, R2, #EVENT_BANG_MASK_OFFSET ;load the mask we want to apply
		OR R5, R6, R5
		STB R5, R4, #ZERO_OFFSET ;TODO add config to maybe bang a 16-bit register
		;clear approach flag
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		ANDL R4, #EVENT_FLAG_APPROACHABLE_XOR
		STW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		;flag event as running
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		ORL R4, #EVENT_FLAG_RUNNING
		STW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		PIT0NotYetBangableOn: ;we end up here if our event was approachable but not zero time
;-------continue loop and see what events need to be banged off ;TODO see if its wiser to check for bang off events
		PIT0CheckBangOff:
        LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
;TODO add zero tollerance handeling
	BITL R4, #EVENT_FLAG_APPROACHABLE_SHUTDOWN ;see if your
	BEQ XGPITOnCheckNext ;skip subtracting our last countdown if our approachable flag is not set
		;subtract our elapsed ticks from our approachable events
		LDD R5, #PITCNT1
		LDW R5, R5, #0
		LDW R6, R2, #EVENT_RUNTIME_LATENCY_METROSTAMP_OFFSET
		STW R5, R2, #EVENT_RUNTIME_LATENCY_METROSTAMP_OFFSET
		SUB R5, R6, R5 ;R5 now contains our elapsed time
		LDW R6, R2, #EVENT_RUNTIME_LOW_WORD_OFFSET
	TST R6
	BEQ PIT0BangOff ; if zero time jump to bang on
		SUB R7, R6, R5
		STW R7, R2, #EVENT_RUNTIME_LOW_WORD_OFFSET ;save the updated event approacable delay incase we arent at zero time
		;see if we are zero time or past zero time :TODO this value could be used for latency calcs
		CMP R6, R5
		BCS PIT0BangOff
		TST R7 ;CMP R7, R5
	BNE XGPITOnCheckNext ;branch if greater than zero
		PIT0BangOff:
		;bang register off
		LDW R4, R2, #EVENT_BANG_REGISTER_OFFSET;load the address of the register we wish to bang from the event structure
		LDB R5, R4, #ZERO_OFFSET ;save the register value
		LDW	R6, R2, #EVENT_BANG_MASK_OFFSET ;load the mask we want to apply
		COM R6 ;make into an AND able mask
		AND R5, R6, R5
		STB R5, R4, #ZERO_OFFSET ;TODO add config to maybe bang a 16-bit register
		;clear approach shutdown flag
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		ANDL R4, #EVENT_FLAG_APPROACHABLE_SHUTDOWN_XOR
		STW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		;clear event to availiable state
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		LDD R4, #EVENT_FLAG_AVAILABLE
		STW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		XGPITOnCheckNext:
		;see if delay countdown is the soonest if it is store it now and schedule it at the end of this thread
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		BITL R4, #EVENT_FLAG_APPROACHABLE ;see if your ARMED bit is set
	BEQ PIT0DelayNotActive ;skip subtracting our last countdown if our approachable flag is not set
		LDD R5, pitDelaySubSystemVars
		LDW R4, R5, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET
		LDW R6, R2, #EVENT_DELAY_LOW_WORD_OFFSET
		CMP R6, R4
		;TODO jump to bang if values is zero or close to it BEQ PITOnBang or something
	BHI PITNotSooner1 ;if currentEvent(R6) < nextEventTime(R4) update it!
		STW R6, R5, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET ;its ok to store zero because the APPROACHABLE bit needs to be set just to get here
		PITNotSooner1:
    	;set our  SELF_UPDATE bit
		LDD R4, pitDelaySubSystemVars
		LDW R5, R4, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
		ORL R5, #PDS_FLAG_SELF_UPDATE_BIT
		STW R5, R4, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
		PIT0DelayNotActive:
		;see if runtime countdown is the soonest if it is store it now and schedule it at the end of this thread
		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		BITL R4, #EVENT_FLAG_APPROACHABLE_SHUTDOWN ;see if your ARMED bit is set
	BEQ PITOnNotApproachableShutdown ;skip subtracting our last countdown if our approachable flag is not set
		LDD R5, pitDelaySubSystemVars
		LDW R4, R5, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET
		LDW R6, R2, #EVENT_RUNTIME_LOW_WORD_OFFSET
		CMP R6, R4
	BHI PITNotSooner2 ;if currentEvent(R6) < nextEventTime(R4) update it!
		STW R6, R5, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET ;its ok to store zero because the APPROACHABLE bit needs to be set just to get here
		PITNotSooner2:
		;set our  SELF_UPDATE bit
		LDD R4, pitDelaySubSystemVars
		LDW R5, R4, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
		ORL R5, #PDS_FLAG_SELF_UPDATE_BIT
		STW R5, R4, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
		PITOnNotApproachableShutdown: ;jump here if we are to not allowed to approach an event for shutdown
		;clear our EVENT_NEW flag
;		LDW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
;		ANDL R4, #EVENT_FLAG_NEW_XOR
;		STW R4, R2, #EVENT_STATUS_FLAGS_OFFSET
		;advance our loop counter and structure
		ADDL R2, #EVENT_STRUCTURE_SIZE
		ADDL R1, #0x01 ;i++
	XGPITOnLoop1:
		CMP R3, R1
		BHI XGPITOnLoop1Block  ; if R4 >= R2

	;Check our SELF_UPDATE bit and set downcounter if we have an approchable event
	LDD R2, pitDelaySubSystemVars
	LDL R3, #0 ;default our last runtime to zero
;	STW R3, R2, #PDS_VARIABLE_PITONLASTCOUNTDOWN_OFFSET ;save
	LDW R3, R2, #PDS_VARIABLE_PITDELAYFLAGS_OFFSET
	BITL R3, #PDS_FLAG_SELF_UPDATE_BIT
BEQ xgPIT0Return
	;set counter and enable interrupt
;	LDD R1, pitDelaySubSystemVars
	LDW R2, R2, #PDS_VARIABLE_PITDELAYNEXTCOUNTDOWN_OFFSET
;	STW R2, R1, #PDS_VARIABLE_PITONLASTCOUNTDOWN_OFFSET
	LDD R1, #PITLD0
	STW R2, R1, #ZERO_OFFSET ;store count down value in register
;debug echo countdown value
;LDD R5, #PORTBA
;STW R2, R5, #ZERO_OFFSET
;brk
	LDD R1, #PITCE
	LDB R2, R1, #ZERO_OFFSET
	ORL R2, #PIT0_ENABLE_MASK
	STB R2, R1, #ZERO_OFFSET
;debug echo channels enabled value
;LDD R5, PORTBA
;LDD R2, #0xFFFF
;STW R2, R5, #ZERO_OFFSET
;brk
	;save last countdown
	xgPIT0Return:
		;For Debugging ++ our thread counter ;TODO comment out when not in use
		LDD R1, pitDelaySubSystemVars
		LDW R2, R1, #PDS_VARIABLE_PITDELAYTHREADRUNS_OFFSET
		ADDL R2, #1
		STW R2, R1, #PDS_VARIABLE_PITDELAYTHREADRUNS_OFFSET
	RTS
xgatePITTurnOnEnd:

xgatePITTurnOff: ; PIT 1 ISR, called by PIT1 interrupt. Loop though our que and see if we need to bang any registers
	;CIF
    LDL R2, #PIT1_CFLAG_MASK
	LDD R3, #PITTF
	STB R2, R3, #ZERO_OFFSET

    ;Disable pit channel 0
	LDD R3, #PITCE
	LDB R4, R3, #ZERO_OFFSET
    ANDL R4, #PIT0_DISABLE_MASK
    STB R4, R3, #ZERO_OFFSET

	RTS
xgatePITTurnOffEnd:

xgateErrorThread:
	;R1 will have the xgate channel number that was executed
	;TODO build some defualt code to increment an error counter, Fred can you give me the addres of a a status var that will show in the log output !
**************************************************
;  utility threads
**************************************************

xgatePORTPFlip: ;Flip bit 7 at PORTP
	LDD R2, #PORTP ;load port-p address
	LDB R1, R2, #ZERO_OFFSET ;load data(1 byte) at port-p address to R1
	COM R3, R1 ;flip the bits
	ANDL R1, #0x7F
	ANDL R3, #0x80
	OR R1, R3, R1
	STB R1, R2, #0x00 ;write the byte to port-p address
	JAL R5 ;return

;IMULU: ; multiply two registers(R1*R2)
;	STW R1, (R0,-R7)
;	STW R4, (R0,-R7)
;    STW R5, (R0,-R7)
;	MOV R4, R2
;	BPL *+6       ;abs = 0x0000403A
;	NEG R4
;    NEG R3
;    LDL R2, #0
;    BRA *+10       ;abs = 0x00004046
;    BFINS R4, R0, R5
;    MOV R1, R3
;    LSL R1, R5
;    ADD R2, R1, R2
;    BFFO R5, R4
;	BCC *-10       ;abs = 0x0000403E
;    LDW R5, (R0,R7+)
;    LDW R4, (R0,R7+)
;    LDW R1, (R0,R7+)
;    JAL       R6

; *****************************************************************************
;
;	VARIABLES
;
;	Remember we are dealing with a 16-bit RISC CPU, alignment care should be
;	taken when defining 8-bit vars/constants
;
; *****************************************************************************

parametersBase:
	parameterChannelID: ;an index to our array of events
		.word 0
	parameterDelayH: ; How long from now to trigger
		.word 0 ;high word
	parameterDelay: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp:
		.word 0
	;second parameter
	parameterChannelID1: ;an index to our array of events
		.word 0
	parameterDelayH1: ; How long from now to trigger
		.word 0 ;high byte
	parameterDelay1: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH1: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime1: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp1:
		.word 0
	;third parameter
	parameterChannelID2: ;an index to our array of events
		.word 0
	parameterDelayH2: ; How long from now to trigger
		.word 0 ;high byte
	parameterDelay2: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH2: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime2: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp2:
		.word 0
	;fourth parameter
	parameterChannelID3: ;an index to our array of events
		.word 0
	parameterDelayH3: ; How long from now to trigger
		.word 0;high byte
	parameterDelay3: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH3: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime3: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp3:
		.word 0
	;fifth parameter
	parameterChannelID4: ;an index to our array of events
		.word 0
	parameterDelayH4: ; How long from now to trigger
		.word 0;high byte
	parameterDelay4: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH4: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime4: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp4:
		.word 0
	;sixth parameter
	parameterChannelID5: ;an index to our array of events
		.word 0
	parameterDelayH5: ; How long from now to trigger
		.word 0;high byte
	parameterDelay5: ; How long from now to trigger
		.word 0 ;Low word countdown
	parameterRuntimeH5: ;How long to run once triggered
		.word 0 ;High word countdown
	parameterRuntime5: ;How long to run once triggered
		.word 0 ;Low word  countdown
	parameterInputStamp5:
		.word 0

pitDelaySubSystemVars:
	pitOnLastCountDown:
		.word 0 ;used to hold the pit count value when cals are needed
	pitDelayNextCountDown:
		.word 0
	pitDelayFlags:
		.word 0 ;keeps status of whats going on
	pitDelayCountSnapShot:
		.word 0
	pitDelayThreadRuns: ;keep track of the number of times the ISR is called
		.word
;	pitDelayThreadEXECTime: ;this variable holds the amount of time in ticks that the thread previously took to run
;		.word
;	pitDelayThreadStartStamp:
;		.word
;	pitDelayThreadStopStamp:
;		.word

; xgateSchedule variables
xGSSystemVars:
	xGSStartTime: ;timestamp that contains the metronomes current count
		.word 0
	xgsEventAddressBase:
		.word 0
	.byte 0 ;TODO only here for alighment
	xgsNumOfEventsToSchedule:
	;	.word 0
	.byte 0
	xgsNumOfEventsScheduled: ;numer of events scheduled the xgs has scheduled in one run
		.word 0
	xGSFlags:
		.word 0
	xGSParameterAddressBase:
		.word 0
	xGSInputEdgeStamp:
		.word 0

xGMSysytemVars:
	xGMStartTime: ;timestamp that contains the metronomes current count
		.word

;offTimeElapsed: ;The ammount of time elapsed during a last OFF countdown
;	.word 0
;offSoonestEvent:
;	.word 0
XGBBCounters:
	xGBBBadChannelRequest: ;num of times an invalid channel tried to be scheduled
		.word
****************************************************************************************
;  Event Structures
****************************************************************************************
/* array of ON event structures */
eventsStructStart:
	eventChannelID0: /* a const that contains this events ENUM ID */
    	.word 0
	eventDelay0:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime0:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags0: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress0: ;The target register we wish to bang
    	.word EVENT_0_REGISTER_ADDRESS
    eventRegisterMask0: ;The mask to apply to the target register when we bang
    	.word EVENT_0_REGISTER_MASK
    eventXGSTicks0: ;TODO this isnt really needed and NOT used right nowhold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp0: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp0: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
	;second event
	eventChannelID1: /* a const that contains this events ENUM ID */
    	.word 1
	eventDelay1:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime1:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags1: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress1: ;The target register we wish to bang
    	.word EVENT_1_REGISTER_ADDRESS
    eventRegisterMask1: ;The mask to apply to the target register when we bang
    	.word EVENT_1_REGISTER_MASK
    eventXGSTicks1: ;TODO this isnt really needed and NOT used right nowhold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp1: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp1: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;third event
	eventChannelID2: /* a const that contains this events ENUM ID */
    	.word 2
	eventDelay2:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime2:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags2: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress2: ;The target register we wish to bang
    	.word EVENT_2_REGISTER_ADDRESS
    eventRegisterMask2: ;The mask to apply to the target register when we bang
    	.word EVENT_2_REGISTER_MASK
    eventXGSTicks2: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp2: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp2: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;forth event
	eventChannelID3: /* a const that contains this events ENUM ID */
    	.word 3
	eventDelay3:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime3:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags3: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress3: ;The target register we wish to bang
    	.word EVENT_3_REGISTER_ADDRESS
    eventRegisterMask3: ;The mask to apply to the target register when we bang
    	.word EVENT_3_REGISTER_MASK
    eventXGSTicks3: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp3: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp3: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;fifth event
	eventChannelID4: /* a const that contains this events ENUM ID */
    	.word 4
	eventDelay4:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime4:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags4: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress4: ;The target register we wish to bang
    	.word EVENT_4_REGISTER_ADDRESS
    eventRegisterMask4: ;The mask to apply to the target register when we bang
    	.word EVENT_4_REGISTER_MASK
    eventXGSTicks4: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp4: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp4: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;sixth event
	eventChannelID5: /* a const that contains this events ENUM ID */
    	.word 5
	eventDelay5:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime5:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags5: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress5: ;The target register we wish to bang
    	.word EVENT_5_REGISTER_ADDRESS
    eventRegisterMask5: ;The mask to apply to the target register when we bang
    	.word EVENT_5_REGISTER_MASK
    eventXGSTicks5: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp5: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp5: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;seventh event
	eventChannelID6: /* a const that contains this events ENUM ID */
    	.word 6
	eventDelay6:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime6:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags6: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress6: ;The target register we wish to bang
    	.word EVENT_6_REGISTER_ADDRESS
    eventRegisterMask6: ;The mask to apply to the target register when we bang
    	.word EVENT_6_REGISTER_MASK
    eventXGSTicks6: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp6: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp6: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
    	.word 0
    ;eigth event
	eventChannelID7: /* a const that contains this events ENUM ID */
    	.word 7
	eventDelay7:
		.word 0 ; high word
   		.word 0 ; low word
   	eventRuntime7:
		.word 0 ; high word
   		.word 0 ; low word
	eventFlags7: /* a var that contains possobile ENUM flags pertaining to this channel*/
    	.word 0
	eventRegisterAddress7: ;The target register we wish to bang
    	.word EVENT_7_REGISTER_ADDRESS
    eventRegisterMask7: ;The mask to apply to the target register when we bang
    	.word EVENT_7_REGISTER_MASK
    eventXGSTicks7: ;hold the amount of time that it took to schedule this event
    	.word 0
    eventDelayLatencyMetroStamp7: ;once an event is flagged as APPROACHABLE we need a metronome stamp to calc latency
    	.word 0
    eventRuntimeLatencyMetroStamp7: ;once an event is flagged as APPROACHABLE_SHUTDOWN we need a metronome stamp to calc latency
		.word 0
onEventsStructEnd:
		.word 0x5555 ;DEBUG TEST
endXGATECode:
.ascii "FreeEMS > MS ; xgate code/tools by sean keys"
end
