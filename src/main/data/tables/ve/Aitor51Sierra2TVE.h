/* FreeEMS - the open source engine management system
 *
 * Copyright 2013 Fred Cooke
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
 * @brief AiToR51 Sierra 2T tune from M$
 *
 */


// Low RPM                                                                                                             High RPM
//  200     500     900    1200    1600    2000    2400    2800    3200    3700    4350    5000    5600    6200    6600    7000  // 
VE(40), VE(41), VE(41), VE(42), VE(43), VE(45), VE(45), VE(45), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), //  20
VE(45), VE(45), VE(45), VE(52), VE(48), VE(45), VE(45), VE(48), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), //  30
VE(45), VE(50), VE(55), VE(50), VE(55), VE(50), VE(50), VE(52), VE(55), VE(55), VE(55), VE(52), VE(50), VE(50), VE(50), VE(50), //  40
VE(45), VE(53), VE(60), VE(55), VE(58), VE(55), VE(55), VE(58), VE(60), VE(60), VE(60), VE(55), VE(52), VE(52), VE(52), VE(52),  //  50
VE(50), VE(55), VE(65), VE(65), VE(62), VE(60), VE(65), VE(67), VE(67), VE(70), VE(70), VE(65), VE(62), VE(62), VE(62), VE(62),  //  60
VE(55), VE(60), VE(76), VE(70), VE(70), VE(70), VE(70), VE(75), VE(75), VE(75), VE(75), VE(72), VE(70), VE(70), VE(70), VE(70), //  70
VE(55), VE(60), VE(76), VE(75), VE(75), VE(75), VE(78), VE(80), VE(80), VE(80), VE(80), VE(78), VE(70), VE(70), VE(70), VE(70),  //  80
VE(60), VE(70), VE(80), VE(80), VE(80), VE(78), VE(80), VE(80), VE(82), VE(83), VE(83), VE(80), VE(85), VE(85), VE(85), VE(85),  //  90
VE(65), VE(75), VE(82), VE(81), VE(81), VE(85), VE(85), VE(85), VE(87), VE(88), VE(88), VE(86), VE(85), VE(85), VE(85), VE(85),  // 100
VE(80), VE(80), VE(83), VE(83), VE(83), VE(85), VE(88), VE(88), VE(90), VE(91), VE(91), VE(90), VE(90), VE(90), VE(90), VE(90),  // 110
VE(80), VE(80), VE(84), VE(84), VE(84), VE(86), VE(90), VE(90), VE(92), VE(93), VE(92), VE(90), VE(90), VE(90), VE(90), VE(90),  // 130
VE(80), VE(80), VE(85), VE(85), VE(85), VE(87), VE(92), VE(92), VE(94), VE(95), VE(94), VE(92), VE(90), VE(90), VE(90), VE(90),// 150
VE(80), VE(80), VE(85), VE(86), VE(86), VE(89), VE(94), VE(94), VE(94), VE(96), VE(96), VE(93), VE(90), VE(90), VE(90), VE(90), // 180
VE(80), VE(80), VE(85), VE(87), VE(87), VE(91), VE(96), VE(96), VE(96), VE(97), VE(97), VE(95), VE(90), VE(90), VE(90), VE(90), // 190
VE(80), VE(80), VE(85), VE(88), VE(88), VE(93), VE(98), VE(98), VE(98), VE(98), VE(98), VE(95), VE(90), VE(90), VE(90), VE(90), // 210
VE(89), VE(80), VE(85), VE(90), VE(90), VE(95),VE(100),VE(100),VE(100),VE(100),VE(100), VE(95), VE(90), VE(90), VE(90), VE(90)  // 250
//  200     500     900    1200    1600    2000    2400    2800    3200    3700    4350    5000    5600    6200    6600    7000  //  WOT
// Low RPM                                                                                                             High RPM


