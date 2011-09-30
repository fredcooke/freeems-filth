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


/** @file GM-2k2Bias.h
 * @ingroup dataInitialisers
 *
 * Generated by FreeTherm 0.6 using the following parameters:
 *
 * Bias Resistor:
 * Value: 2200
 *
 * Sensor Sample Points:
 * Temp Low  : 20
 * Temp Mid  : 70
 * Temp High : 210
 * Res Low   : 13500
 * Res Mid   : 3400
 * Res High  : 185
 *
 * Temp Units:
 * Input Temp Scale: Fahrenheit
 * Output Temp Scale: Kelvin
 *
 * GM thermistor datasheet: http://www.napaechlin.com/upload/NAPAEchlin2/Documents/Tech%20Tip%20PDFs/GM_Coolant&AirTempSensors.pdf
 */


65535, 60188, 54979, 52321, 50581, 49305, 48307, 47492, 46806, 46216, 45700, 45242, 44831, 44459, 44119, 43806,
43518, 43249, 42999, 42765, 42544, 42336, 42139, 41953, 41775, 41606, 41445, 41291, 41143, 41001, 40865, 40734,
40607, 40485, 40367, 40253, 40143, 40036, 39933, 39832, 39735, 39640, 39548, 39458, 39370, 39285, 39202, 39121,
39042, 38964, 38889, 38815, 38743, 38672, 38603, 38535, 38468, 38403, 38339, 38277, 38215, 38155, 38095, 38037,
37980, 37924, 37868, 37814, 37760, 37708, 37656, 37605, 37555, 37505, 37456, 37408, 37361, 37315, 37269, 37223,
37178, 37134, 37091, 37048, 37005, 36964, 36922, 36881, 36841, 36801, 36762, 36723, 36685, 36647, 36609, 36572,
36535, 36499, 36463, 36428, 36393, 36358, 36323, 36289, 36256, 36222, 36189, 36157, 36124, 36092, 36061, 36029,
35998, 35967, 35937, 35906, 35876, 35847, 35817, 35788, 35759, 35730, 35702, 35673, 35645, 35618, 35590, 35563,
35536, 35509, 35482, 35456, 35430, 35404, 35378, 35352, 35327, 35301, 35276, 35251, 35227, 35202, 35178, 35154,
35130, 35106, 35082, 35059, 35035, 35012, 34989, 34966, 34944, 34921, 34898, 34876, 34854, 34832, 34810, 34788,
34767, 34745, 34724, 34703, 34682, 34661, 34640, 34619, 34599, 34578, 34558, 34538, 34518, 34498, 34478, 34458,
34438, 34419, 34399, 34380, 34361, 34342, 34323, 34304, 34285, 34266, 34247, 34229, 34210, 34192, 34174, 34156,
34137, 34119, 34102, 34084, 34066, 34048, 34031, 34013, 33996, 33979, 33961, 33944, 33927, 33910, 33893, 33876,
33860, 33843, 33826, 33810, 33793, 33777, 33760, 33744, 33728, 33712, 33696, 33680, 33664, 33648, 33632, 33616,
33601, 33585, 33570, 33554, 33539, 33523, 33508, 33493, 33478, 33462, 33447, 33432, 33417, 33403, 33388, 33373,
33358, 33343, 33329, 33314, 33300, 33285, 33271, 33256, 33242, 33228, 33214, 33199, 33185, 33171, 33157, 33143,
33129, 33115, 33102, 33088, 33074, 33060, 33047, 33033, 33019, 33006, 32992, 32979, 32966, 32952, 32939, 32926,
32912, 32899, 32886, 32873, 32860, 32847, 32834, 32821, 32808, 32795, 32782, 32769, 32757, 32744, 32731, 32718,
32706, 32693, 32681, 32668, 32656, 32643, 32631, 32618, 32606, 32594, 32581, 32569, 32557, 32545, 32532, 32520,
32508, 32496, 32484, 32472, 32460, 32448, 32436, 32424, 32412, 32401, 32389, 32377, 32365, 32353, 32342, 32330,
32318, 32307, 32295, 32284, 32272, 32261, 32249, 32238, 32226, 32215, 32203, 32192, 32181, 32169, 32158, 32147,
32136, 32124, 32113, 32102, 32091, 32080, 32069, 32058, 32047, 32036, 32025, 32014, 32003, 31992, 31981, 31970,
31959, 31948, 31937, 31926, 31916, 31905, 31894, 31883, 31873, 31862, 31851, 31841, 31830, 31819, 31809, 31798,
31788, 31777, 31767, 31756, 31746, 31735, 31725, 31714, 31704, 31693, 31683, 31673, 31662, 31652, 31642, 31631,
31621, 31611, 31601, 31590, 31580, 31570, 31560, 31550, 31540, 31529, 31519, 31509, 31499, 31489, 31479, 31469,
31459, 31449, 31439, 31429, 31419, 31409, 31399, 31389, 31379, 31369, 31359, 31349, 31340, 31330, 31320, 31310,
31300, 31290, 31281, 31271, 31261, 31251, 31242, 31232, 31222, 31212, 31203, 31193, 31183, 31174, 31164, 31154,
31145, 31135, 31126, 31116, 31106, 31097, 31087, 31078, 31068, 31059, 31049, 31040, 31030, 31021, 31011, 31002,
30992, 30983, 30973, 30964, 30955, 30945, 30936, 30926, 30917, 30908, 30898, 30889, 30879, 30870, 30861, 30851,
30842, 30833, 30824, 30814, 30805, 30796, 30786, 30777, 30768, 30759, 30749, 30740, 30731, 30722, 30713, 30703,
30694, 30685, 30676, 30667, 30657, 30648, 30639, 30630, 30621, 30612, 30603, 30593, 30584, 30575, 30566, 30557,
30548, 30539, 30530, 30521, 30512, 30503, 30493, 30484, 30475, 30466, 30457, 30448, 30439, 30430, 30421, 30412,
30403, 30394, 30385, 30376, 30367, 30358, 30349, 30340, 30331, 30322, 30313, 30304, 30295, 30286, 30277, 30268,
30260, 30251, 30242, 30233, 30224, 30215, 30206, 30197, 30188, 30179, 30170, 30161, 30152, 30143, 30135, 30126,
30117, 30108, 30099, 30090, 30081, 30072, 30063, 30054, 30046, 30037, 30028, 30019, 30010, 30001, 29992, 29983,
29975, 29966, 29957, 29948, 29939, 29930, 29921, 29912, 29904, 29895, 29886, 29877, 29868, 29859, 29850, 29841,
29833, 29824, 29815, 29806, 29797, 29788, 29779, 29771, 29762, 29753, 29744, 29735, 29726, 29717, 29708, 29700,
29691, 29682, 29673, 29664, 29655, 29646, 29637, 29629, 29620, 29611, 29602, 29593, 29584, 29575, 29566, 29557,
29548, 29540, 29531, 29522, 29513, 29504, 29495, 29486, 29477, 29468, 29459, 29450, 29441, 29432, 29424, 29415,
29406, 29397, 29388, 29379, 29370, 29361, 29352, 29343, 29334, 29325, 29316, 29307, 29298, 29289, 29280, 29271,
29262, 29253, 29244, 29235, 29226, 29217, 29208, 29199, 29190, 29181, 29172, 29162, 29153, 29144, 29135, 29126,
29117, 29108, 29099, 29090, 29081, 29071, 29062, 29053, 29044, 29035, 29026, 29016, 29007, 28998, 28989, 28980,
28971, 28961, 28952, 28943, 28934, 28924, 28915, 28906, 28897, 28887, 28878, 28869, 28859, 28850, 28841, 28831,
28822, 28813, 28803, 28794, 28785, 28775, 28766, 28756, 28747, 28738, 28728, 28719, 28709, 28700, 28690, 28681,
28671, 28662, 28652, 28643, 28633, 28623, 28614, 28604, 28595, 28585, 28576, 28566, 28556, 28547, 28537, 28527,
28518, 28508, 28498, 28488, 28479, 28469, 28459, 28449, 28439, 28430, 28420, 28410, 28400, 28390, 28380, 28370,
28360, 28351, 28341, 28331, 28321, 28311, 28301, 28291, 28281, 28270, 28260, 28250, 28240, 28230, 28220, 28210,
28200, 28189, 28179, 28169, 28159, 28148, 28138, 28128, 28117, 28107, 28097, 28086, 28076, 28065, 28055, 28045,
28034, 28023, 28013, 28002, 27992, 27981, 27971, 27960, 27949, 27939, 27928, 27917, 27906, 27896, 27885, 27874,
27863, 27852, 27841, 27830, 27819, 27808, 27797, 27786, 27775, 27764, 27753, 27742, 27731, 27720, 27708, 27697,
27686, 27675, 27663, 27652, 27640, 27629, 27618, 27606, 27595, 27583, 27571, 27560, 27548, 27536, 27525, 27513,
27501, 27489, 27478, 27466, 27454, 27442, 27430, 27418, 27406, 27394, 27382, 27369, 27357, 27345, 27333, 27320,
27308, 27295, 27283, 27271, 27258, 27245, 27233, 27220, 27207, 27195, 27182, 27169, 27156, 27143, 27130, 27117,
27104, 27091, 27078, 27065, 27051, 27038, 27025, 27011, 26998, 26984, 26970, 26957, 26943, 26929, 26916, 26902,
26888, 26874, 26860, 26846, 26831, 26817, 26803, 26788, 26774, 26759, 26745, 26730, 26716, 26701, 26686, 26671,
26656, 26641, 26626, 26611, 26595, 26580, 26564, 26549, 26533, 26518, 26502, 26486, 26470, 26454, 26438, 26422,
26405, 26389, 26372, 26356, 26339, 26322, 26305, 26288, 26271, 26254, 26237, 26219, 26202, 26184, 26166, 26148,
26130, 26112, 26094, 26076, 26057, 26039, 26020, 26001, 25982, 25963, 25943, 25924, 25904, 25884, 25865, 25844,
25824, 25804, 25783, 25762, 25741, 25720, 25699, 25678, 25656, 25634, 25612, 25590, 25567, 25545, 25522, 25498,
25475, 25452, 25428, 25404, 25379, 25355, 25330, 25305, 25279, 25254, 25227, 25201, 25175, 25148, 25120, 25093,
25065, 25036, 25008, 24979, 24949, 24919, 24889, 24858, 24827, 24795, 24763, 24731, 24697, 24664, 24629, 24595,
24559, 24523, 24486, 24449, 24411, 24372, 24332, 24292, 24250, 24208, 24165, 24121, 24076, 24029, 23982, 23933,
23883, 23832, 23779, 23725, 23669, 23611, 23552, 23490, 23426, 23360, 23291, 23220, 23145, 23067, 22985, 22899,
22809, 22713, 22612, 22504, 22388, 22263, 22128, 21980, 21816, 21633, 21424, 21181, 20890, 20523, 20021, 19203
