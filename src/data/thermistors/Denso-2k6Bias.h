/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
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


/** @file Denso-2k6Bias.h
 * @ingroup dataInitialisers
 *
 * Generated by FreeTherm 0.6 using the following parameters:
 *
 * Bias Resistor:
 * Value: 2600
 *
 * Sensor Sample Points:
 * Temp Low  : 0
 * Temp Mid  : 25.5
 * Temp High : 80
 * Res Low   : 6540
 * Res Mid   : 2040
 * Res High  : 340
 *
 * Temp Units:
 * Input Temp Scale: Celcius
 * Output Temp Scale: Kelvin
 *
 * Nippon Denso data: http://forum.diyefi.org/viewtopic.php?f=24&t=100
 */


65535, 65535, 65535, 61098, 57778, 55447, 53681, 52276, 51118, 50140, 49296, 48559, 47904, 47318, 46789, 46306,
45864, 45457, 45079, 44728, 44400, 44092, 43803, 43530, 43272, 43027, 42795, 42573, 42362, 42160, 41967, 41782,
41604, 41433, 41269, 41110, 40957, 40810, 40667, 40529, 40395, 40265, 40140, 40017, 39899, 39784, 39671, 39562,
39456, 39352, 39251, 39152, 39056, 38962, 38870, 38781, 38693, 38607, 38523, 38440, 38360, 38281, 38203, 38127,
38053, 37980, 37908, 37838, 37769, 37701, 37634, 37568, 37504, 37440, 37378, 37316, 37256, 37196, 37138, 37080,
37023, 36967, 36912, 36858, 36804, 36751, 36699, 36648, 36597, 36547, 36498, 36449, 36401, 36354, 36307, 36260,
36215, 36170, 36125, 36081, 36037, 35994, 35952, 35910, 35868, 35827, 35786, 35746, 35706, 35667, 35628, 35589,
35551, 35513, 35476, 35439, 35402, 35366, 35330, 35294, 35259, 35224, 35190, 35156, 35122, 35088, 35055, 35022,
34989, 34957, 34924, 34892, 34861, 34830, 34799, 34768, 34737, 34707, 34677, 34647, 34618, 34588, 34559, 34530,
34502, 34473, 34445, 34417, 34389, 34362, 34334, 34307, 34280, 34253, 34227, 34201, 34174, 34148, 34123, 34097,
34071, 34046, 34021, 33996, 33971, 33947, 33922, 33898, 33874, 33850, 33826, 33802, 33779, 33755, 33732, 33709,
33686, 33663, 33641, 33618, 33596, 33573, 33551, 33529, 33507, 33486, 33464, 33443, 33421, 33400, 33379, 33358,
33337, 33316, 33295, 33275, 33254, 33234, 33214, 33194, 33174, 33154, 33134, 33114, 33095, 33075, 33056, 33036,
33017, 32998, 32979, 32960, 32941, 32923, 32904, 32885, 32867, 32848, 32830, 32812, 32794, 32776, 32758, 32740,
32722, 32704, 32687, 32669, 32652, 32634, 32617, 32600, 32583, 32565, 32548, 32531, 32515, 32498, 32481, 32464,
32448, 32431, 32415, 32398, 32382, 32366, 32350, 32333, 32317, 32301, 32285, 32269, 32254, 32238, 32222, 32207,
32191, 32175, 32160, 32145, 32129, 32114, 32099, 32084, 32068, 32053, 32038, 32023, 32008, 31994, 31979, 31964,
31949, 31935, 31920, 31906, 31891, 31877, 31862, 31848, 31834, 31819, 31805, 31791, 31777, 31763, 31749, 31735,
31721, 31707, 31693, 31679, 31666, 31652, 31638, 31625, 31611, 31597, 31584, 31570, 31557, 31544, 31530, 31517,
31504, 31491, 31477, 31464, 31451, 31438, 31425, 31412, 31399, 31386, 31373, 31360, 31348, 31335, 31322, 31309,
31297, 31284, 31271, 31259, 31246, 31234, 31221, 31209, 31197, 31184, 31172, 31160, 31147, 31135, 31123, 31111,
31098, 31086, 31074, 31062, 31050, 31038, 31026, 31014, 31002, 30990, 30979, 30967, 30955, 30943, 30931, 30920,
30908, 30896, 30885, 30873, 30862, 30850, 30838, 30827, 30815, 30804, 30793, 30781, 30770, 30758, 30747, 30736,
30724, 30713, 30702, 30691, 30680, 30668, 30657, 30646, 30635, 30624, 30613, 30602, 30591, 30580, 30569, 30558,
30547, 30536, 30525, 30514, 30504, 30493, 30482, 30471, 30461, 30450, 30439, 30428, 30418, 30407, 30396, 30386,
30375, 30365, 30354, 30344, 30333, 30323, 30312, 30302, 30291, 30281, 30270, 30260, 30250, 30239, 30229, 30219,
30208, 30198, 30188, 30177, 30167, 30157, 30147, 30137, 30126, 30116, 30106, 30096, 30086, 30076, 30066, 30056,
30045, 30035, 30025, 30015, 30005, 29995, 29985, 29976, 29966, 29956, 29946, 29936, 29926, 29916, 29906, 29896,
29887, 29877, 29867, 29857, 29847, 29838, 29828, 29818, 29809, 29799, 29789, 29779, 29770, 29760, 29750, 29741,
29731, 29722, 29712, 29702, 29693, 29683, 29674, 29664, 29655, 29645, 29636, 29626, 29617, 29607, 29598, 29588,
29579, 29569, 29560, 29550, 29541, 29532, 29522, 29513, 29504, 29494, 29485, 29475, 29466, 29457, 29447, 29438,
29429, 29420, 29410, 29401, 29392, 29383, 29373, 29364, 29355, 29346, 29336, 29327, 29318, 29309, 29300, 29291,
29281, 29272, 29263, 29254, 29245, 29236, 29227, 29217, 29208, 29199, 29190, 29181, 29172, 29163, 29154, 29145,
29136, 29127, 29118, 29109, 29100, 29091, 29082, 29073, 29064, 29055, 29046, 29037, 29028, 29019, 29010, 29001,
28992, 28983, 28974, 28965, 28956, 28947, 28938, 28929, 28920, 28911, 28902, 28894, 28885, 28876, 28867, 28858,
28849, 28840, 28831, 28823, 28814, 28805, 28796, 28787, 28778, 28769, 28761, 28752, 28743, 28734, 28725, 28716,
28708, 28699, 28690, 28681, 28672, 28664, 28655, 28646, 28637, 28628, 28619, 28611, 28602, 28593, 28584, 28576,
28567, 28558, 28549, 28540, 28532, 28523, 28514, 28505, 28497, 28488, 28479, 28470, 28461, 28453, 28444, 28435,
28426, 28418, 28409, 28400, 28391, 28383, 28374, 28365, 28356, 28348, 28339, 28330, 28321, 28313, 28304, 28295,
28286, 28278, 28269, 28260, 28251, 28242, 28234, 28225, 28216, 28207, 28199, 28190, 28181, 28172, 28164, 28155,
28146, 28137, 28128, 28120, 28111, 28102, 28093, 28085, 28076, 28067, 28058, 28049, 28041, 28032, 28023, 28014,
28005, 27997, 27988, 27979, 27970, 27961, 27952, 27944, 27935, 27926, 27917, 27908, 27899, 27891, 27882, 27873,
27864, 27855, 27846, 27837, 27829, 27820, 27811, 27802, 27793, 27784, 27775, 27766, 27757, 27748, 27739, 27731,
27722, 27713, 27704, 27695, 27686, 27677, 27668, 27659, 27650, 27641, 27632, 27623, 27614, 27605, 27596, 27587,
27578, 27569, 27560, 27551, 27542, 27533, 27523, 27514, 27505, 27496, 27487, 27478, 27469, 27460, 27451, 27441,
27432, 27423, 27414, 27405, 27395, 27386, 27377, 27368, 27359, 27349, 27340, 27331, 27322, 27312, 27303, 27294,
27284, 27275, 27266, 27256, 27247, 27238, 27228, 27219, 27209, 27200, 27191, 27181, 27172, 27162, 27153, 27143,
27134, 27124, 27115, 27105, 27096, 27086, 27077, 27067, 27057, 27048, 27038, 27029, 27019, 27009, 27000, 26990,
26980, 26970, 26961, 26951, 26941, 26931, 26921, 26912, 26902, 26892, 26882, 26872, 26862, 26852, 26842, 26832,
26822, 26812, 26802, 26792, 26782, 26772, 26762, 26752, 26742, 26732, 26722, 26711, 26701, 26691, 26681, 26671,
26660, 26650, 26640, 26629, 26619, 26608, 26598, 26588, 26577, 26567, 26556, 26546, 26535, 26524, 26514, 26503,
26493, 26482, 26471, 26460, 26450, 26439, 26428, 26417, 26406, 26395, 26385, 26374, 26363, 26352, 26341, 26329,
26318, 26307, 26296, 26285, 26274, 26262, 26251, 26240, 26228, 26217, 26206, 26194, 26183, 26171, 26160, 26148,
26136, 26125, 26113, 26101, 26090, 26078, 26066, 26054, 26042, 26030, 26018, 26006, 25994, 25982, 25970, 25957,
25945, 25933, 25920, 25908, 25896, 25883, 25870, 25858, 25845, 25833, 25820, 25807, 25794, 25781, 25768, 25755,
25742, 25729, 25716, 25703, 25689, 25676, 25663, 25649, 25636, 25622, 25609, 25595, 25581, 25567, 25553, 25539,
25525, 25511, 25497, 25483, 25468, 25454, 25440, 25425, 25410, 25396, 25381, 25366, 25351, 25336, 25321, 25306,
25290, 25275, 25260, 25244, 25228, 25213, 25197, 25181, 25165, 25149, 25132, 25116, 25099, 25083, 25066, 25049,
25032, 25015, 24998, 24981, 24963, 24946, 24928, 24910, 24892, 24874, 24856, 24838, 24819, 24800, 24781, 24762,
24743, 24724, 24704, 24685, 24665, 24645, 24624, 24604, 24583, 24562, 24541, 24520, 24498, 24477, 24455, 24432,
24410, 24387, 24364, 24341, 24317, 24293, 24269, 24245, 24220, 24195, 24170, 24144, 24118, 24091, 24064, 24037,
24009, 23981, 23952, 23923, 23894, 23864, 23833, 23802, 23770, 23738, 23705, 23671, 23637, 23602, 23566, 23529,
23492, 23454, 23414, 23374, 23332, 23290, 23246, 23201, 23154, 23106, 23056, 23005, 22951, 22896, 22838, 22777,
22714, 22647, 22577, 22503, 22424, 22340, 22250, 22153, 22046, 21929, 21798, 21648, 21473, 21259, 20982, 20566
