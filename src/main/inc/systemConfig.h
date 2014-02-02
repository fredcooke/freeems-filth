/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 *
 * @brief System configuration defines
 *
 * This holds various hash defined configuration constants and literals.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_SYSTEM_CONFIG_H_SEEN
#define FILE_SYSTEM_CONFIG_H_SEEN


// Custom builds config setup, makes usage more clear and robust

// Vehicle IDs to avoid typos
#define DEFAULT_ID       1 // RIP original Volvo! (should have been 1)
#define SEANKLT1_ID      5 // Driven yearly, maybe
//efine MARCOS_ID        6 // Only idled for one minute, never since. No config available for this vehicle. http://forum.diyefi.org/viewtopic.php?f=55&t=1303
#define SNOTROCKET_ID    7 // Another one that's too reliable
#define PETERJSERIES_ID 10 // Winter thrasher, works so well he refuses to whinge
#define DEUCECOUPE_ID   11 // Work in progress, ignition not setup yet
#define PETERTRUCK_ID   12 // Work horse vehicle, about to get boosted
#define SEANKR1_ID      14 // Desert/Sand Rail Turbo Yamaha R1
#define SCAVENGER_ID    15 // Hacked up Miata turbo from the south!
#define DEUCES10_ID     16 // Work in progress


// Convert labels into IDs for use in code and set the ID string
#ifdef CONFIG
#warning "CONFIG variable already defined! Manual use not advised!"
#elif defined DEFAULT
#define CONFIG DEFAULT_ID
#define PRELIM_CONFIG "Default"
#elif defined SEANKLT1
#define CONFIG SEANKLT1_ID
#define PRELIM_CONFIG "SEANKLT1"
#elif defined SNOTROCKET
#define CONFIG SNOTROCKET_ID
#define PRELIM_CONFIG "SNOTROCKET"
#elif defined PETERJSERIES
#define CONFIG PETERJSERIES_ID
#define PRELIM_CONFIG "PETERJSERIES"
#elif defined DEUCECOUPE
#define CONFIG DEUCECOUPE_ID
#define PRELIM_CONFIG "DEUCECOUPE"
#elif defined PETERTRUCK
#define CONFIG PETERTRUCK_ID
#define PRELIM_CONFIG "PETERTRUCK"
#elif defined SCAVENGER
#define CONFIG SCAVENGER_ID
#define PRELIM_CONFIG "SCAVENGER"
#elif defined DEUCES10
#define CONFIG DEUCES10_ID
#define PRELIM_CONFIG "DEUCES10"
#elif defined SEANKR1
#define CONFIG SEANKR1_ID
#define PRELIM_CONFIG "SEANKR1"
#elif defined CLIFLAGS && !(defined XGATE)
#error "CLIFLAGS defined, but no build matched! Not allowing config to fall back to default!"
#define CONFIG -1
#else
#define CONFIG DEFAULT_ID
#define PRELIM_CONFIG "Default"
#endif

// Ensure we didn't end up with config undefined or defined as zero
#if CONFIG == 0
#warning "CONFIG variable has value of zero, which it has without being defined, this is not allowed!"
#endif

/* TODO make the default the inverse of this */
#ifdef XGATE
#define BUILD_CONFIG PRELIM_CONFIG "-XGATE"

#else
#define BUILD_CONFIG PRELIM_CONFIG
#endif


// Scheduling stuff used in configuration and scheduler
#define MAX_NUMBER_OF_OUTPUT_EVENTS 24
#define ECT_OUTPUT_CHANNELS          6    /* How many ECT output channels the code should support */
#define MAX_NUMBER_OF_CYLINDERS     12    /* How many cylinders/chambers we support */

/* The TX and RX buffers are slightly larger than 2k because the RX buffer */
/* needs to also receive a header, checksum and attributes for the data    */
/* involved and the TX buffer needs to handle all of those two fold.       */
#define TX_BUFFER_SIZE       0x0820 ///< 2k of data plus double maximum header overhead for echo
#define RX_BUFFER_SIZE       0x0810 ///< 2k of data plus maximum header overhead

// ADC values
#define ADC_NUMBER_OF_VALUES                1024 ///< Number of distinct values in 10 bit ADC units
#define ADC_DIVISIONS (ADC_NUMBER_OF_VALUES - 1) ///< The number of gaps between the values
#define ADC_MAX_VALUE (ADC_NUMBER_OF_VALUES - 1) ///< The highest value used in our mode


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file SYSTEM_CONFIG_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
