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
 * @brief  AiToR51 Sierra 2.0T tune
 */


 IT(15.0), IT(14.5), IT(14.0), IT(15.0), IT(20.0), IT(25.0), IT(30.0), IT(33.0), IT(35.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), // 15
 IT(13.0), IT(13.0), IT(13.0), IT(14.0), IT(19.0), IT(24.0), IT(28.0), IT(31.0), IT(33.0), IT(34.0), IT(34.0), IT(34.0), IT(34.0), IT(34.0), IT(34.0), IT(34.0), // 30
 IT(11.0), IT(11.0), IT(11.0), IT(12.0), IT(17.0), IT(22.0), IT(26.0), IT(29.0), IT(31.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), // 45
  IT(9.5), IT(10.0), IT(10.0), IT(11.0), IT(13.0), IT(20.0), IT(24.0), IT(27.0), IT(29.0), IT(30.0), IT(31.0), IT(31.0), IT(31.0), IT(31.0), IT(31.0), IT(31.0), // 60
  IT(8.0),  IT(8.0),  IT(8.0),  IT(8.0), IT(12.0), IT(16.0), IT(20.0), IT(23.0), IT(25.0), IT(26.0), IT(27.0), IT(27.0), IT(27.0), IT(27.0), IT(27.0), IT(27.0), // 75
  IT(7.0),  IT(6.5),  IT(6.0),  IT(7.0),  IT(9.0), IT(12.0), IT(16.0), IT(19.0), IT(21.0), IT(22.0), IT(23.0), IT(23.0), IT(23.0), IT(23.0), IT(23.0), IT(23.0), // 90
  IT(6.0),  IT(5.5),  IT(5.0),  IT(6.0),  IT(8.0), IT(11.0), IT(12.0), IT(14.0), IT(16.0), IT(17.0), IT(18.0), IT(18.0), IT(18.0), IT(18.0), IT(18.0), IT(18.0), // 105
  IT(5.0),  IT(5.0),  IT(5.0),  IT(6.0),  IT(7.0),  IT(8.0), IT(11.0), IT(12.0), IT(13.0), IT(14.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), IT(15.0), // 120
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(6.0),  IT(7.0),  IT(9.0), IT(10.0), IT(11.0), IT(12.0), IT(12.0), IT(12.0), IT(13.2), IT(13.2), IT(13.2), IT(13.2), // 135
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(6.0),  IT(7.0),  IT(8.0),  IT(9.0), IT(10.0), IT(11.0), IT(12.0), IT(13.0), IT(13.0), IT(13.0), IT(13.0), // 150
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.5),  IT(6.0),  IT(7.0),  IT(8.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0), // 165
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(6.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0), // 180
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0), // 195
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0), // 210
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0), // 225
  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0),  IT(5.0)  // 240
//    250,      700,     1000,     1600,     2200,     2800,     3400,     4000,     4600,     5200,     5800,     6400,     7000,     7600,     8200,     8800
