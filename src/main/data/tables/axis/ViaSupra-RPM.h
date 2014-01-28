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
 * @ingroup dataInitialisers
 *
 * @brief Default RPM values spaced at 400RPM after the cranking and idling rows.
 */


// 27 RPM values of which 24 are used by default
  RPM(250),
  RPM(500),
 RPM(900),
 RPM(1200),
 RPM(1600),
 RPM(2000),
 RPM(2400),
 RPM(3000),
 RPM(3600),
 RPM(4000),
 RPM(4600),
 RPM(5200),
 RPM(5800),
 RPM(6400),
 RPM(6800),
 RPM(7200)
