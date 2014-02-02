/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
 * @ingroup dataInitialisers
 *
 * @brief First fixed config block
 *
 * This file contains the definition of the first fixed configuration block.
 * The declaration can be found in the global constants header file.
 *
 * Please ensure that all variables added here have good default values.
 */


#include "../inc/freeEMS.h"


/// @copydoc fixedConfig1
const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {
	engineSettings:{
#if CONFIG == SEANKLT1_ID
		perCylinderVolume:  CYLINDER_VOLUME(727),
		cylinderCount:		8,
		strokesPerCycle:	4,
		injectorFlow:       CC_PER_MINUTE(525),
		secondaryInjectorFlow: CC_PER_MINUTE(0),
		injectionStrategy: PLAIN_INJECTION,
		maxPrimaryDC:		DUTYCYCLE(85.00),
		maxSecondaryDC:		DUTYCYCLE(85.00),
#elif CONFIG == SEANKR1_ID
		perCylinderVolume:  CYLINDER_VOLUME(250),
		cylinderCount:		4,
		strokesPerCycle:	4,
		injectorFlow:       CC_PER_MINUTE(425), // http://witchhunter.com/flowdatapix/d3920.jpg
		secondaryInjectorFlow: CC_PER_MINUTE(230), // http://witchhunter.com/flowdatapix/bcdh210.jpg
		injectionStrategy:  STAGED_EXTENSION,
		maxPrimaryDC:		DUTYCYCLE(85.00),
		maxSecondaryDC:		DUTYCYCLE(85.00),
#elif CONFIG == PETERJSERIES_ID
		perCylinderVolume:  CYLINDER_VOLUME(585),
		cylinderCount:		6,
		strokesPerCycle:	4,
		injectorFlow:       CC_PER_MINUTE(320),
		secondaryInjectorFlow: CC_PER_MINUTE(0),
#elif CONFIG == DEUCECOUPE_ID
		perCylinderVolume:  CYLINDER_VOLUME(522),
		cylinderCount:		6,
		strokesPerCycle:	4,
		injectorFlow:       CC_PER_MINUTE(235),
		secondaryInjectorFlow: CC_PER_MINUTE(0),
		#elif CONFIG == DEUCES10_ID
		perCylinderVolume:  CYLINDER_VOLUME(548),
		cylinderCount:          4,
		strokesPerCycle:        4,
		injectorFlow:       CC_PER_MINUTE(235),
#elif CONFIG == SCAVENGER_ID
		perCylinderVolume:  CYLINDER_VOLUME(399.25),
		injectorFlow:       CC_PER_MINUTE(540),
#else
		perCylinderVolume:  CYLINDER_VOLUME(500),
		cylinderCount:		4,
		strokesPerCycle:	4,
		injectorFlow:       CC_PER_MINUTE(550),
		secondaryInjectorFlow: CC_PER_MINUTE(0),
		injectionStrategy: PLAIN_INJECTION,
		maxPrimaryDC:		DUTYCYCLE(85.00),
		maxSecondaryDC:		DUTYCYCLE(85.00),
#endif
#if CONFIG == SEANKR1_ID
		stoichiometricAFR:  stoichiometricAFRE85,
		densityOfFuelAtSTP: densityOfE85
#else
		stoichiometricAFR:  stoichiometricAFRPetrol,
		densityOfFuelAtSTP: densityOfPetrol
#endif
	},
	serialSettings:{
		baudDivisor:        SCI_BAUD_DIVISOR(115200) // 21.7013889 (22) http://duckduckgo.com/?q=40000000+%2F+%2816*115200%29
		// http://duckduckgo.com/?q=40000000+%2F+%2816*22%29 113.636 kHz actual speed
		// http://duckduckgo.com/?q=22+%2F+%28%2840000000%2F16%29%2F115200%29 1.376% error in speed
	},
	coarseBitBangSettings:{
#if CONFIG == SNOTROCKET_ID // 24 events for a 24+1 CAS setup with 4 cylinder tacho
		outputActions:      {1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0},
#else
		outputActions:      standardTachoArray,
#endif
		ports:              standardTachoPorts,
		masks:              standardTachoMasks,
		numberConfigured:   1
	},
	schedulingSettings:{

/* XGATE outputs should not be used for ignition control. There can be up to ~15uS of jitter which can translate to
* a few degrees of movement in a high RPM engine. However, worst case fuel accuracy is about 1.5% and that is with
* a 1mS fuel pulse. If you use them for ignition control your engine may appear to run fine, but again this is a bad idea. */

#if CONFIG == SEANKLT1_ID // http://forum.diyefi.org/viewtopic.php?f=55&t=1146
		anglesOfTDC: {ANGLE(0), ANGLE(90), ANGLE(180), ANGLE(270), ANGLE(360), ANGLE(450), ANGLE(540), ANGLE(630), ANGLE(0), ANGLE(90), ANGLE(180), ANGLE(270), ANGLE(360), ANGLE(450), ANGLE(540), ANGLE(630)},
		outputEventPinNumbers:       {0,0,0,0,0,0,0,0,2,3,4,5,2,3,4,5}, // LTCC e-dizzy, semi-sequential injection 1/6, 8/5, 4/7, 3/2, and repeat
		schedulingConfigurationBits: {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1}, // See below two lines
		xgateOutputChannel: {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0,1,2,3,4,5,6,7}, // Disable xgate driven outputs
		decoderEngineOffset:               ANGLE(0.00), // Decoder has a true zero zero mechanically hard coded
		numberOfConfiguredOutputEvents:             16, // First half ignition, second half injection
		numberOfInjectionsPerEngineCycle:            1  // Full sync fully-sequential

#elif CONFIG == SNOTROCKET_ID // http://forum.diyefi.org/viewtopic.php?f=3&t=1263 Sim's 2.1 Volvo, carbed with CNP using LS1 coils.
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)}, // 1,2,3,4: Firing order: 1-3-4-2 set up in loom
		outputEventPinNumbers:           {0,1,2,3}, // COP/CNP ignition only
		schedulingConfigurationBits:     {0,0,0,0}, // All ignition
		decoderEngineOffset:         ANGLE(566.00), // Volvo B21A with DSM/Miata CAS + 24and1 disk
		numberOfConfiguredOutputEvents:          4, // COP setup
		numberOfInjectionsPerEngineCycle:        1  // Ditto

#elif CONFIG == PETERJSERIES_ID // Firing order 1-4-2-5-3-6 http://forum.diyefi.org/viewtopic.php?f=62&t=1533
		anglesOfTDC: {ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600)},
		outputEventPinNumbers:       {0,3,1,4,2,5}, // An example of wiring your engine with cylinder one on output one, harder to grok
		schedulingConfigurationBits: {1,1,1,1,1,1}, // Ones represent scheduling for injection, zeros represent scheduling for ignition
		decoderEngineOffset:           ANGLE(0.00), // Trim fuel injection END point with this value.
		numberOfConfiguredOutputEvents:          6, // THESE ARE NOT IGN, THEY ARE FUEL
		numberOfInjectionsPerEngineCycle:        1  // Sequential, baby, yeah!

#elif CONFIG == DEUCECOUPE_ID // DeuceEFI's GM 3100 V6, firing order 1-6-5-4-3-2, wasted spark DIS ignition http://forum.diyefi.org/viewtopic.php?f=3&t=1278
		anglesOfTDC: {ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600), ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600)},
		outputEventPinNumbers:       {0,0,0,0,0,0,2,3,4,2,3,4}, // DIS E-dizzy and semi-sequential, for now.
		schedulingConfigurationBits: {0,0,0,0,0,0,1,1,1,1,1,1}, // Six E-dizzy style DIS ignition outputs and six injection events, two per cycle, semi sequential
		decoderEngineOffset:           ANGLE(0.00), // Nothing for now, so as to be able to figure out what is going on.
		numberOfConfiguredOutputEvents:         12, // See three lines above
		numberOfInjectionsPerEngineCycle:        2  // Semi-sequential, for now.

#elif CONFIG == DEUCES10_ID // Firing order 1-3-4-2 setup in wiring harness http://forum.diyefi.org/viewtopic.php?f=55&t=1962
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,0,0,0,2,3,4,5}, // DIS E-dizzy and Sequential (2 == Port-T4)
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First 4 ign, Last 4 fuel
		decoderEngineOffset:           ANGLE(0.00), // GM DIS 2x Reference signal is at 0 degrees.
		numberOfConfiguredOutputEvents:          8, // 4 coil events and  4 injector events.
		numberOfInjectionsPerEngineCycle:        1  // Sequential Fueling!

#elif CONFIG == PETERTRUCK_ID // Firing order 1-5-3-6-2-4
		anglesOfTDC: {ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600)},
		outputEventPinNumbers:       {0,4,2,5,1,3}, // An example of wiring your engine with cylinder one on output one, harder to grok
		schedulingConfigurationBits: {0,0,0,0,0,0}, // Ones represent scheduling for injection, zeros represent scheduling for ignition
		decoderEngineOffset:           ANGLE(0.00), // Trim fuel injection END point with this value.
		numberOfConfiguredOutputEvents:          6, // THESE ARE IGN, THEY ARE NOT FUEL
		numberOfInjectionsPerEngineCycle:        1  // Sequential, baby, yeah!

#elif CONFIG == SCAVENGER_ID // hentai
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,1,0,1,2,3,2,3}, // Wasted spark, semi-sequential TODO migrate this to sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four injection
		decoderEngineOffset:      ANGLE(128), // Hentai initial setup value, will change a bit
		numberOfConfiguredOutputEvents:              8, // See two lines above
		numberOfInjectionsPerEngineCycle:            2  // Semi-sequential, for now.

#elif CONFIG == SEANKR1_ID // Firing order 1-2-3-4 COP/CNP
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers: {0,1,2,3,4,0xFF,0xFF,0xFF}, // Only use timer channels for ignition
		schedulingConfigurationBits:    {0,0,0,0,1,1,1,1}, // First 4 ign, 4 fuel
		decoderEngineOffset:                  ANGLE(0.00), //
		numberOfConfiguredOutputEvents:                 8, // 4 coils 8 injectors, the last 4 injectors are driven by the staged function for now
		xgateOutputChannel: {0xFF,0xFF,0xFF,0xFF,0,1,2,3}, // Use XGATE on fuel only
		correspondingCylinder:   {1, 2, 3, 4, 1, 2, 3, 4}, // Used for individual trim calculations
		numberOfInjectionsPerEngineCycle:               1  // COP/Seq accept nothing less :)

#else // Nothing scheduled by default, no sensible default for all possible vehicle setups.
		anglesOfTDC:                            {}, // Depends on cylinder count and other variables
		outputEventPinNumbers:       {0,1,2,3,4,5}, // Default to a variety of pins for testing purposes. Note: Won't do anything without
		schedulingConfigurationBits:            {}, // All ignition by guarantee of C, configured explicitly for real setups.
		decoderEngineOffset:              ANGLE(0), // Start with zero, work your way to the correct value
		numberOfConfiguredOutputEvents:          0, // This disables scheduling completely, should match the first, second and third arrays
		xgateOutputChannel:					    {}, // Disable xgate driven outputs
		correspondingCylinder:					{}, // Set to 0
		numberOfInjectionsPerEngineCycle:        1  // 720 degree decoders with one injection per cycle
#endif
	},
	cutAndLimiterSettings:{
		InjectionRPM:{
#if CONFIG == DEUCES10_ID
			disableThreshold:  RPM(5600),
			reenableThreshold: RPM(5400)
#elif CONFIG == SCAVENGER_ID
			disableThreshold:  RPM(7200),
			reenableThreshold: RPM(7150)
#elif CONFIG == SEANKR1_ID
			disableThreshold:  RPM(12050),
			reenableThreshold: RPM(11800)
#else
			disableThreshold:  RPM(5000),
			reenableThreshold: RPM(4900)  // Come back on before ignition does
#endif
		},
		IgnitionRPM:{
#if CONFIG == SNOTROCKET_ID
			disableThreshold:  RPM(6300),
			reenableThreshold: RPM(6200)
#elif CONFIG == PETERJSERIES_ID
			disableThreshold:  RPM(6000),
			reenableThreshold: RPM(5950)
#elif CONFIG == PETERTRUCK_ID
			disableThreshold:  RPM(5000),
			reenableThreshold: RPM(4950)
#elif CONFIG == DEUCES10_ID
			disableThreshold:  RPM(5600),
			reenableThreshold: RPM(5300)
#elif CONFIG == SCAVENGER_ID
			disableThreshold:  RPM(7200),
			reenableThreshold: RPM(7100)
#elif CONFIG == SEANKR1_ID
			disableThreshold:  RPM(12100),
			reenableThreshold: RPM(11900)
#else
			disableThreshold:  RPM(5000),
			reenableThreshold: RPM(4800)  // Come back on after injection does
#endif
		},
		OverBoost:{
			disableThreshold:  KPA(250), // Cut close to std sensor max
			reenableThreshold: KPA(100)  // Re enable when boost gone all together (force driver to lift)
		},
		cutsEnabled:{
			InjectionRPM: 1,
			IgnitionRPM:  1,
			InjOverBoost: 1,
			IgnOverBoost: 1,
			Spare0: 1,
			Spare1: 1,
			Spare2: 1,
			Spare3: 1,
			Spare4: 1,
			Spare5: 1,
			Spare6: 1,
			Spare7: 1,
			Spare8: 1,
			Spare9: 1,
			SpareA: 1,
			SpareB: 1
		}
	},
	simpleGPIOSettings:{
		outputConfigs:{
#if CONFIG == DEUCECOUPE_ID
			[0] = {
				variable: &CoreVars0.RPM,
				upperValue: RPM(400),
				lowerValue: RPM(300),
				port: (unsigned char*)&PORTT,
				mask: BIT3,
				flags: 0
			},
#elif CONFIG == DEUCES10_ID
			[0] = {
				variable: &CoreVars0.RPM,
				upperValue: RPM(400),
				lowerValue: RPM(300),
				port: (unsigned char*)&PORTT,
				mask: BIT3,
				flags: 0
			},
#else
			[0] = {
				variable: &CoreVars0.RPM,
				upperValue: RPM(5000),
				lowerValue: RPM(4000),
				port: (unsigned char*)&PORTK,
				mask: BIT3,
				flags: 0
			},
#endif
			[1] = {
				variable: &CoreVars0.CHT,
#if	CONFIG == SEANKR1_ID	// At 250HP per liter she needs to stay cool
				upperValue: DEGREES_C(80),
				lowerValue: DEGREES_C(70),
#else
				upperValue: DEGREES_C(100),
				lowerValue: DEGREES_C(90),
#endif
				port: (unsigned char*)&PORTK,
				mask: BIT4,
				flags: 0
			}
		},
		numberConfigured: 2,
		spare: 0
	},
	userTextField:  "Place your personal notes about whatever you like in here!"
			" Don't hesitate to tell us a story about something interesting."
			" Do keep in mind though that when you upload your settings file to "
			"the forum this message WILL be visible to all and sundry, so don't "
			"be putting too many personal details, bank account numbers, "
			"passwords, PIN numbers, license plates, national insurance numbers, "
			" love stories and other private information in this field. In fact it"
			" is probably best if you kee"
};
