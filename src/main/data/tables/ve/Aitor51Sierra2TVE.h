/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
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
 * @brief A dead flat 60% VE curve to use as a default for typical engines.
 */

 VE(60.0), VE(50.0), VE(35.0), VE(35.0), VE(35.0), VE(35.0), VE(38.0), VE(38.0), VE(38.0), VE(38.0), VE(38.0), VE(38.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 20
 VE(60.0), VE(50.0), VE(38.0), VE(38.0), VE(40.0), VE(40.0), VE(40.0), VE(40.0), VE(40.0), VE(40.0), VE(40.0), VE(40.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 30
 VE(60.0), VE(50.0), VE(38.0), VE(38.0), VE(40.0), VE(41.0), VE(41.0), VE(41.0), VE(41.0), VE(41.0), VE(41.0), VE(41.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 40
 VE(60.0), VE(50.0), VE(40.0), VE(44.0), VE(44.0), VE(45.0), VE(45.0), VE(45.0), VE(45.0), VE(45.0), VE(45.0), VE(45.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 50
 VE(60.0), VE(50.0), VE(40.0), VE(46.0), VE(46.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 60
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 70
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(54.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 80
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(59.0), VE(59.0), VE(59.0), VE(59.0), VE(59.0), VE(59.0), VE(59.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 90
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), VE(60.0), // 100
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), VE(63.0), // 110
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), VE(68.0), // 130
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), VE(71.0), // 150
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), // 180
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), // 190
 VE(60.0), VE(50.0), VE(50.0), VE(50.0), VE(50.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), // 210
 VE(30.0), VE(40.0), VE(50.0), VE(50.0), VE(50.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0), VE(73.0)  // 250
//    200,      500,      900,     1200,     1600,     2000,     2400,     2800,     3200,     3700,     4350,     5000,     5600,     6200,     6600,     7000
