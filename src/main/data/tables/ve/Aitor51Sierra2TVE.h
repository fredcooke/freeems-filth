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

// Low RPM                                                                                                             High RPM
//  200     500     900    1200    1600    2000    2400    2800    3200    3700    4350    5000    5600    6200    6600    7000  // 
VE(35), VE(40), VE(45), VE(50), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //20
VE(35), VE(40), VE(45), VE(50), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //30
VE(35), VE(40), VE(45), VE(50), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //40
VE(35), VE(40), VE(45), VE(50), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //50
VE(35), VE(40), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //60
VE(35), VE(40), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //70
VE(35), VE(40), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //80
VE(35), VE(40), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //90
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //100
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //110
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //130
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //150
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //180
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //190
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //210
VE(35), VE(40), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //250
//  200     500     900    1200    1600    2000    2400    2800    3200    3700    4350    5000    5600    6200    6600    7000  //  WOT
// Low RPM 

