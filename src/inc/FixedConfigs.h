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
 * @ingroup allHeaders
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Struct typedefs for fixed configuration
 *
 * This file contains the struct data type definitions for fixed configuration items.
 *
 * Fixed, in this context means that it typically is not tuned in a live way
 * and therefore should not be cached in RAM while running. Usually these are
 * values that do not change such as cylinder volume, injector size, cylinder
 * count and other constants related to physical aspects of the engine setup.
 * When adding configuration values, please consider adding them here first.
 * If a value doesn't need to be live tunable definitely put it here instead.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_FIXED_CONFIGS_H_SEEN
#define FILE_FIXED_CONFIGS_H_SEEN


/// Decoder and scheduling settings
typedef struct {
	unsigned short accelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
	unsigned short decelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
} decoderSetting;


/** @brief Preset values for inputs and other variables
 *
 * In some cases you may want to ignore input readings and just use some
 * configured value for a particular sensor. These are the values used when you
 * choose to use a fixed reading instead of the real thing.
 */
typedef struct {
	unsigned short presetIAT;  ///< Preset variable value to override calculated values.
	unsigned short presetCHT;  ///< @copydoc presetIAT
	unsigned short presetTPS;  ///< @copydoc presetIAT
	unsigned short presetEGO;  ///< @copydoc presetIAT
	unsigned short presetBRV;  ///< @copydoc presetIAT
	unsigned short presetMAP;  ///< @copydoc presetIAT
	unsigned short presetAAP;  ///< @copydoc presetIAT
	unsigned short presetMAT;  ///< @copydoc presetIAT
	unsigned short presetEGO2; ///< @copydoc presetIAT
	unsigned short presetIAP;  ///< @copydoc presetIAT
	unsigned short presetBPW;  ///< @copydoc presetIAT
	unsigned short presetAF;   ///< @copydoc presetIAT
} sensorPreset;


/// Ranges for sensors with linear config
typedef struct {
	unsigned short TPSClosedMAP;  ///< Unused at this time.
	unsigned short TPSOpenMAP;    ///< Unused at this time.
	signed short   MAPMinimum;    ///< Vacuum required to make the sensor reach 0 Volt output. Theoretical only, most do not rail.
	unsigned short MAPRange;      ///< Number of kPa between 0 Volts and 5 Volts.
	unsigned short AAPMinimum;    ///< @copydoc MAPMinimum
	unsigned short AAPRange;      ///< @copydoc MAPRange
	unsigned short EGOMinimum;    ///< Lambda that 0 Volt input corresponds to.
	unsigned short EGORange;      ///< Lambda that 5 Volt input corresponds to.
	unsigned short BRVMinimum;    ///< Battery Voltage that 0 Volt input means. 0 Volts usually.
	unsigned short BRVRange;      ///< Battery Voltage range between 0 Volt and 5 Volt input. FreeEMS standard is 24.5 Volts for 1k and 3k9 resistors on a 12v vehicle.
	unsigned short TPSMinimumADC; ///< This should be zero, but often isn't, this value is what the TPS input reads with the throttle fully closed.
	unsigned short TPSMaximumADC; ///< This should be 1023, but often isn't, this value is what the TPS input reads with the throttle fully open.
/*efine TPS_MINIMUM 0             ///< = 0.00%   For clarity ONLY, always zero. */
#define TPS_RANGE_MAX 64000       ///< = 100.00%
} sensorRange;


/// Fuel injection settings
typedef struct {
	unsigned short perCylinderVolume;  ///< 500cc = 0.5l 0.5 * 32768 = pcv, so divide by 32768 go get litres */
	unsigned short injectorFlow;       ///< Injector flow of 240cc/min / 60 is 4ml/second is multiplied by 1024, so divide by 1024 for ml/second, divide by 1000 for litres/second */
	unsigned short stoichiometricAFR;  ///< 34 for hydrogen, all others less, figure is 14.7 * 1024, divide by 1024 to get AFR */
	unsigned short densityOfFuelAtSTP; ///< 703gm/litre for Octane. 32 * fuel density = number, divide by 32 for the real figure */
} engineSetting;


/// Settings related to serial communications
typedef struct {
	unsigned short baudDivisor; ///< The number used to set the data rate. 22 = (40MHz / (16*115.2kHz)) = 21.7013889
} serialSetting;


/// Settings for coarse bit bang outputs
typedef struct {
	unsigned char outputActions[256]; ///< Nothing, On, Off, Toggle for each input event.
	unsigned char* ports[4];         ///< The addresses of the port control registers.
	unsigned char  masks[4];         ///< The masks to apply to the ports above.
	unsigned char numberConfigured;  ///< How many to loop through, max of 4
} coarseBitBangSetting;


/// Settings for ignition and injection output scheduling
typedef struct {
	unsigned short anglesOfTDC[MAX_NUMBER_OF_OUTPUT_EVENTS];                ///< The effective TDC angle of the event in question.
	unsigned char outputEventPinNumbers[MAX_NUMBER_OF_OUTPUT_EVENTS];       ///< Which of the 6 pins should be associated with this event
	unsigned char schedulingConfigurationBits[MAX_NUMBER_OF_OUTPUT_EVENTS]; ///< 0 = ignition, 1 = injection
	unsigned short decoderEngineOffset;
	/**<
	 * Add decoderEngineOffset to code degrees to find 0/TDC for cyl/output 1
	 * or subtract from real degrees to get code degrees. Make this number
	 * larger to advance the base timing, make it smaller to retard it. IE, if
	 * you have 10btdc in your table, flat, and a timing light shows 5btdc on
	 * the engine, then increase this number by 5 degrees. More here:
	 *
	 * http://forum.diyefi.org/viewtopic.php?f=54&t=1523
	 */
	unsigned char numberOfConfiguredOutputEvents;   ///< Should match the used section of the three arrays above
	unsigned char numberOfInjectionsPerEngineCycle; ///< How much to divide the fuel pulse width by to get the per injection fuel pulse width
} schedulingSetting;


#define simisTachoArray {1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0} // 24 events for a 24+1 CAS setup with 4 cylinder tacho
#define slaterTachoArray {1,0,0,2,0,0,1,0,0,2,0} // 11 events for 12-1 crank setup with 4 cylinder tacho
#define standardTachoArray {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}
#define standardTachoPorts {(unsigned char*)&PORTE,(unsigned char*)&PORTK,(unsigned char*)&PORTK,(unsigned char*)&PORTK}
#define standardTachoMasks {0x80,0x01,0x02,0x04}


/// Settings related to sensor reading
typedef struct {
	unsigned short readingTimeout; ///< How often an ADC reading MUST occur.
} sensorSetting;


#define userTextFieldArrayLength1 (flashSectorSize - (sizeof(engineSetting) + sizeof(serialSetting) + sizeof(coarseBitBangSetting) + sizeof(schedulingSetting)))
/**
 * One of two structs of fixed configuration data such as physical parameters etc.
 *
 * If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in FixedConfig1.c and FixedConfig2.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 */
typedef struct {
	engineSetting engineSettings; ///< @see engineSetting
	serialSetting serialSettings; ///< @see serialSetting
	coarseBitBangSetting coarseBitBangSettings;   ///< @see coarseBitBangSetting
	schedulingSetting schedulingSettings;         ///< @see schedulingSetting
	unsigned char userTextField[userTextFieldArrayLength1]; ///< For on-board meta-data such as which vehicle the unit is from, put your personal tuning notes here!
} fixedConfig1;


#define userTextFieldArrayLength2 (flashSectorSize - (sizeof(sensorPreset) + sizeof(sensorRange) + sizeof(sensorSetting) + sizeof(decoderSetting)))
/** @copydoc fixedConfig1 */
typedef struct {
	sensorPreset sensorPresets;                              ///< @see sensorPreset
	sensorRange sensorRanges;                                ///< @see sensorRange
	sensorSetting sensorSettings;                            ///< @see sensorSetting
	decoderSetting decoderSettings;                          ///< @see decoderSetting
	unsigned char userTextField2[userTextFieldArrayLength2]; ///< For on-board meta-data such as which vehicle the unit is from, put your personal tuning notes here!
} fixedConfig2;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file FIXED_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
