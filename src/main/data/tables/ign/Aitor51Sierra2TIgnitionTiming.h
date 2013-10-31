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
 * @brief  AiToR51 Sierra 2.0T tune from M$
 */


//  Low RPM                                                                                                            High RPM
//     200       500       900      1200      1600      2000      2400      2800      3200      3700      4350      5000      5600      6200      6600      7000  
  IT(10.0), IT(13.9), IT(14.1), IT(14.3), IT(17.5), IT(22.0), IT(26.3), IT(30.5), IT(32.6), IT(34.0), IT(34.5), IT(35.0), IT(36.1), IT(36.4), IT(36.5), IT(36.5), //  20
  IT(10.0), IT(13.2), IT(12.8), IT(12.9), IT(16.0), IT(21.0), IT(24.5), IT(28.7), IT(30.5), IT(32.2), IT(32.7), IT(33.2), IT(34.7), IT(35.0), IT(35.2), IT(35.2), //  30
  IT(10.0), IT(12.2), IT(11.5), IT(11.8), IT(15.0), IT(19.2), IT(23.1), IT(27.0), IT(29.0), IT(30.4), IT(30.9), IT(31.4), IT(33.3), IT(33.7), IT(33.8), IT(33.8), //  40
  IT(10.0), IT(10.4), IT(10.6), IT(10.8), IT(14.0), IT(17.5), IT(21.3), IT(24.8), IT(26.7), IT(28.6), IT(29.1), IT(29.8), IT(31.9), IT(32.3), IT(32.4), IT(32.4), //  50

  IT(9.0),   IT(9.4),  IT(9.6),  IT(9.7), IT(12.0), IT(15.3), IT(19.2), IT(23.1), IT(24.8), IT(26.8), IT(27.3), IT(28.0), IT(30.5), IT(30.8), IT(30.9), IT(30.9), //  60
  IT(7.0),   IT(8.0),  IT(8.1),  IT(8.3), IT(10.3), IT(13.6), IT(17.1), IT(21.3), IT(23.0), IT(25.0), IT(25.5), IT(26.3), IT(29.1), IT(29.4), IT(29.5), IT(29.5), //  70
  IT(6.0),   IT(7.0),  IT(7.1),  IT(8.0),  IT(9.5), IT(11.5), IT(15.7), IT(19.6), IT(21.3), IT(23.2), IT(23.7), IT(24.5), IT(27.7), IT(28.0), IT(28.1), IT(28.1), // 80
  IT(5.0),   IT(5.5),  IT(5.8),  IT(6.9),  IT(8.0), IT(10.1), IT(13.6), IT(16.8), IT(19.8), IT(21.4), IT(22.0), IT(22.8), IT(26.3), IT(26.6), IT(26.6), IT(26.6), // 90

  IT(5.0),   IT(5.0),  IT(5.0),  IT(6.2),  IT(7.0),  IT(8.3), IT(11.8), IT(14.6), IT(16.0), IT(19.6), IT(21.6), IT(22.0), IT(24.1), IT(24.3), IT(24.8), IT(24.8), // 100
  IT(5.0),   IT(4.5),  IT(4.8),  IT(5.8),  IT(6.5),  IT(7.8),  IT(9.5), IT(12.3), IT(14.6), IT(18.2), IT(19.5), IT(20.1), IT(22.0), IT(22.3), IT(22.8), IT(22.8), // 110
  IT(4.0),   IT(4.0),  IT(4.5),  IT(5.1),  IT(5.5),  IT(6.2),  IT(6.9),  IT(8.3), IT(10.8), IT(15.4), IT(16.2), IT(16.8), IT(17.5), IT(18.0), IT(18.5), IT(18.5), // 130
  IT(4.0) ,  IT(4.0),  IT(4.0),  IT(4.9),  IT(5.1),  IT(5.5),  IT(6.2),  IT(7.0),  IT(7.5), IT(12.8), IT(15.1), IT(15.5), IT(16.1), IT(16.5), IT(16.8), IT(16.8), // 150
 
  IT(4.0),   IT(4.0),  IT(4.0),  IT(4.8),  IT(4.8),  IT(4.8),  IT(5.1),  IT(5.1),  IT(5.1),  IT(5.2),  IT(5.6),  IT(6.8),  IT(7.5),  IT(8.0),  IT(8.3),  IT(8.3), // 180
  IT(4.0),   IT(4.0),  IT(4.0),  IT(4.5),  IT(4.5),  IT(4.5),  IT(4.7),  IT(4.7),  IT(4.7),  IT(4.7),  IT(4.7),  IT(5.0),  IT(5.5),  IT(6.0),  IT(6.0),  IT(6.0), // 190
  IT(4.0),   IT(4.0),  IT(4.0),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.7),  IT(3.8),  IT(4.0),  IT(4.0),  IT(4.0),  IT(4.0), // 210
  IT(3.0),   IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0),  IT(3.0)  // 250
//    200        500       900      1200      1600      2000      2400      2800      3200      3700      4350      5000      5600      6200      6600      7000  //  WOT
//  Low RPM                                                                                                            High RPM
