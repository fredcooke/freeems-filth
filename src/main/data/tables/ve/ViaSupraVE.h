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
 * @brief Initial VE table for 7mgte Supra.
 */

//     250,       500,       900,      1200,      1600,      2000,      2400,      3000,      3600,      4000,      4600,      5200,      5800,      6400,      6800,      7200  // Vacuum
  VE(10.0),  VE(15.0),  VE(15.0),  VE(10.0),  VE(10.0),  VE(12.0),  VE(16.0),  VE(17.0),  VE(18.0),  VE(18.0),  VE(19.0),  VE(19.0),  VE(22.0),  VE(24.0),  VE(28.0),  VE(28.0), //  20kPa
  VE(58.0),  VE(36.0),  VE(35.0),  VE(35.0),  VE(35.0),  VE(34.0),  VE(35.0),  VE(37.0),  VE(38.0),  VE(38.0),  VE(38.0),  VE(40.0),  VE(42.0),  VE(42.0),  VE(42.0),  VE(42.0), //  35kPa
  VE(58.0),  VE(49.0),  VE(48.0),  VE(50.0),  VE(50.0),  VE(45.0),  VE(46.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(50.0),  VE(54.0), //  50kPa
  VE(58.0),  VE(46.0),  VE(56.0),  VE(52.0),  VE(52.0),  VE(53.0),  VE(54.0),  VE(53.0),  VE(56.0),  VE(57.0),  VE(57.0),  VE(57.0),  VE(59.0),  VE(60.0),  VE(60.0),  VE(60.0), //  65kPa
  VE(58.0),  VE(50.0),  VE(62.0),  VE(53.0),  VE(56.0),  VE(59.0),  VE(61.0),  VE(65.0),  VE(66.0),  VE(65.0),  VE(65.0),  VE(65.0),  VE(68.0),  VE(68.0),  VE(68.0),  VE(68.0), //  80kPa
  VE(58.0),  VE(56.0),  VE(63.0),  VE(64.0),  VE(65.0),  VE(66.0),  VE(66.0),  VE(67.0),  VE(67.0),  VE(68.0),  VE(70.0),  VE(70.0),  VE(70.0),  VE(70.0),  VE(70.0),  VE(70.0), //  90kPa
  VE(58.0),  VE(63.0),  VE(65.0),  VE(70.0),  VE(72.0),  VE(72.0),  VE(72.0),  VE(72.0),  VE(72.0),  VE(72.0),  VE(75.0),  VE(75.0),  VE(75.0),  VE(75.0),  VE(75.0),  VE(75.0), // 100kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(69.0),  VE(73.0),  VE(74.0),  VE(74.0),  VE(77.0),  VE(80.0),  VE(82.0),  VE(82.0),  VE(82.0),  VE(82.0),  VE(82.0),  VE(82.0), // 115kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(72.0),  VE(74.0),  VE(75.0),  VE(77.0),  VE(80.0),  VE(84.0),  VE(85.0),  VE(85.0),  VE(85.0),  VE(85.0),  VE(85.0),  VE(85.0), // 135kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(72.0),  VE(76.0),  VE(78.0),  VE(82.0),  VE(82.0),  VE(84.0),  VE(88.0),  VE(88.0),  VE(88.0),  VE(89.0),  VE(90.0),  VE(90.0), // 150kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(72.0),  VE(80.0),  VE(80.0),  VE(84.0),  VE(86.0),  VE(90.0),  VE(92.0),  VE(93.0),  VE(93.0),  VE(93.0),  VE(93.0),  VE(93.0), // 165kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(72.0),  VE(82.0),  VE(82.0),  VE(84.0),  VE(90.0),  VE(93.0),  VE(95.0),  VE(96.0),  VE(97.0), VE(100.0), VE(101.0), VE(102.0), // 180kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(67.0),  VE(72.0),  VE(84.0),  VE(84.0),  VE(86.0),  VE(90.0),  VE(96.0), VE(100.0), VE(104.0), VE(106.0), VE(108.0), VE(108.0), VE(110.0), // 195kPa
  VE(60.0),  VE(65.0),  VE(65.0),  VE(65.0),  VE(74.0),  VE(86.0),  VE(87.0),  VE(88.0),  VE(94.0), VE(100.0), VE(105.0), VE(108.0), VE(110.0), VE(111.0), VE(112.0), VE(114.0), // 210kPa
  VE(60.0),  VE(68.0),  VE(68.0),  VE(68.0),  VE(76.0),  VE(88.0),  VE(90.0),  VE(90.0), VE(100.0), VE(105.0), VE(109.0), VE(110.0), VE(113.0), VE(116.0), VE(118.0), VE(122.0), // 225kPa
  VE(60.0),  VE(68.0),  VE(68.0),  VE(68.0),  VE(80.0),  VE(90.0),  VE(92.0),  VE(94.0), VE(105.0), VE(110.0), VE(115.0), VE(117.0), VE(119.0), VE(122.0), VE(124.0), VE(125.0)  // 240kPa
//     250,       500,       900,      1200,      1600,      2000,      2400,      3000,      3600,      4000,      4600,      5200,      5800,      6400,      6800,      7200  // Boost
