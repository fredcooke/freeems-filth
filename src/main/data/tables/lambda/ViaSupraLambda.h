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
 * @ingroup dataInitialisers
 *
 * @brief Initial lambda table for 7mgte supra.
 *
 * @warning MUST be used with 16x16 axis dimensions!!!
 */

//    250,      500,      900,     1200,     1600,     2000,     2400,     3000,     3600,     4000,     4600,     5200,     5800,     6400,     6800,     7200  // Vacuum
 LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  20kPa
 LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  35kPa
 LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  50kPa
 LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  65kPa
 LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(1.00), LR(1.00), LR(1.00), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), //  80kPa
 LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.96), LR(0.96), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), //  90kPa
 LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), // 100kPa
 LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 115kPa
 LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 135kPa
 LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), // 150kPa
 LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), // 165kPa
 LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), // 180kPa
 LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), // 195kPa
 LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), // 210kPa
 LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), // 225kPa
 LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75), LR(0.75)  // 240kPa
//    250,      500,      900,     1200,     1600,     2000,     2400,     3000,     3600,     4000,     4600,     5200,     5800,     6400,     6800,     7200  // Boost
