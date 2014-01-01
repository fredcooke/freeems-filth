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
 * @brief initial timing table for 7mgte Supra
 */


//    250,      500,      900,     1200,     1600,     2000,     2400,     3000,     3600,     4000,     4600,     5200,     5800,     6400,     6800,     7200  // Vacuum
 IT(12.0), IT(15.0), IT(18.0), IT(18.0), IT(24.0), IT(28.0), IT(32.0), IT(35.0), IT(36.0), IT(38.0), IT(42.0), IT(42.0), IT(42.0), IT(42.0), IT(42.0), IT(42.0), //  20kPa
 IT(12.0), IT(15.0), IT(18.0), IT(18.0), IT(23.0), IT(26.0), IT(32.0), IT(35.0), IT(36.0), IT(38.0), IT(40.0), IT(40.0), IT(40.0), IT(40.0), IT(40.0), IT(40.0), //  35kPa
 IT(12.0), IT(15.0), IT(18.0), IT(18.0), IT(23.0), IT(24.0), IT(32.0), IT(35.0), IT(36.0), IT(36.0), IT(38.0), IT(40.0), IT(40.0), IT(40.0), IT(40.0), IT(40.0), //  50kPa
 IT(10.0), IT(15.0), IT(18.0), IT(18.0), IT(23.0), IT(24.0), IT(32.0), IT(35.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), //  65kPa
 IT(10.0), IT(15.0), IT(18.0), IT(20.0), IT(23.0), IT(24.0), IT(32.0), IT(35.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), //  80kPa
 IT(10.0), IT(15.0), IT(18.0), IT(20.0), IT(23.0), IT(24.0), IT(32.0), IT(35.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), //  90kPa
 IT(10.0), IT(15.0), IT(18.0), IT(18.0), IT(22.0), IT(24.0), IT(32.0), IT(35.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), // 100kPa
  IT(8.0), IT(10.0), IT(15.0), IT(15.0), IT(15.0), IT(16.0), IT(20.0), IT(22.0), IT(24.0), IT(26.0), IT(28.0), IT(28.0), IT(28.0), IT(28.0), IT(28.0), IT(28.0), // 115kPa
  IT(8.0), IT(10.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(17.0), IT(20.0), IT(22.0), IT(24.0), IT(26.0), IT(25.0), IT(25.0), IT(25.0), IT(25.0), IT(25.0), // 135kPa
  IT(8.0), IT(10.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(17.0), IT(18.0), IT(20.0), IT(22.0), IT(24.0), IT(22.0), IT(22.0), IT(22.0), IT(22.0), IT(22.0), // 150kPa
  IT(8.0), IT(10.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(17.0), IT(18.0), IT(20.0), IT(22.0), IT(20.0), IT(20.0), IT(20.0), IT(20.0), IT(20.0), // 165kPa
  IT(8.0), IT(10.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(17.0), IT(18.0), IT(18.0), IT(17.0), IT(17.0), IT(17.0), IT(17.0), IT(17.0), IT(17.0), // 180kPa
  IT(8.0), IT(10.0), IT(10.0), IT(12.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(13.0), IT(13.0), IT(13.0), IT(13.0), IT(13.0), IT(13.0), // 195kPa
  IT(8.0), IT(10.0), IT(10.0), IT(12.0), IT(12.0), IT(12.0), IT(12.0), IT(12.0), IT(12.0), IT(12.0), IT(12.0), IT(11.0), IT(11.0), IT(11.0), IT(11.0), IT(11.0), // 210kPa
  IT(8.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0), // 225kPa
  IT(8.0), IT(10.0), IT(10.0), IT(10.0), IT(10.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0)  // 240kPa
//    250,      500,      900,     1200,     1600,     2000,     2400,     3000,     3600,     4000,     4600,     5200,     5800,     6400,     6800,     7200  // Boost
