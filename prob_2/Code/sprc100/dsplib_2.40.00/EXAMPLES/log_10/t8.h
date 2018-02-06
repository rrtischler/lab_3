/* Test for logn: rand */
#define NX 600
#define FNAME "t8"
#define MAXERROR 20

DATA x[NX] ={
11299,
23954,
4464,
19222,
5458,
23283,
8742,
15263,
24584,
14267,
22455,
21397,
12070,
11721,
18725,
13583,
19412,
15249,
21990,
19111,
12946,
13458,
23779,
16662,
6453,
15626,
12128,
15939,
27556,
11095,
21896,
14577,
14512,
12279,
24045,
17138,
16010,
8417,
6064,
3189,
23067,
13914,
25784,
16392,
17063,
17909,
15076,
17112,
19094,
14864,
15807,
31488,
18261,
5540,
22967,
21136,
17071,
8001,
24582,
23124,
15558,
29263,
15314,
24446,
21105,
18529,
16642,
12443,
9623,
19476,
5986,
7729,
16249,
11208,
31719,
17574,
5162,
25512,
23284,
9521,
23233,
18041,
14915,
25161,
20279,
4887,
7028,
17761,
12509,
26641,
17415,
23954,
12046,
18301,
9731,
27516,
30422,
11105,
4957,
16327,
13319,
30881,
11310,
20203,
3957,
28901,
21325,
8480,
16816,
19953,
10369,
8375,
25989,
13616,
17595,
5845,
7505,
24384,
15726,
14120,
12543,
11202,
21902,
11318,
18301,
18312,
16332,
25850,
23266,
19474,
15385,
18896,
7045,
20719,
22605,
21740,
21031,
22539,
29655,
13664,
22645,
9604,
15998,
1754,
11823,
9849,
19946,
24505,
9297,
15375,
7533,
6353,
15254,
22032,
9761,
27639,
17647,
15941,
9769,
30732,
23126,
9606,
17278,
25790,
21752,
12812,
14017,
20592,
8894,
21046,
8840,
6140,
7085,
19616,
23129,
20409,
22343,
17849,
16452,
16469,
17056,
16673,
29654,
20454,
15484,
27152,
5972,
10440,
8926,
21928,
20846,
8491,
13782,
10542,
16218,
19512,
5653,
24290,
12360,
17156,
7483,
19065,
21712,
17972,
15009,
4159,
13141,
26727,
14779,
12921,
17805,
16545,
10277,
18809,
14848,
19744,
8821,
24187,
14021,
5585,
18086,
16650,
18064,
11588,
19853,
20793,
29712,
23039,
31909,
16094,
15456,
10480,
18497,
18592,
18390,
18208,
26544,
11089,
11987,
17160,
10687,
6361,
21076,
13320,
19621,
4686,
22480,
21043,
13705,
13399,
22790,
21490,
23098,
15556,
8691,
7894,
18918,
23355,
22299,
15127,
19100,
11508,
16866,
23443,
17510,
5388,
14425,
6592,
20680,
21144,
27906,
7570,
22132,
18045,
10212,
4887,
18278,
9328,
7461,
21061,
21819,
25182,
11378,
12819,
8830,
18507,
18729,
17891,
15003,
8345,
19020,
21864,
17549,
12407,
13525,
12255,
21522,
12884,
18421,
4622,
16830,
12180,
28561,
14951,
11145,
16504,
16704,
15237,
26699,
21995,
18721,
16266,
14873,
23428,
14889,
21213,
15569,
29368,
13599,
19101,
10617,
22990,
23367,
21059,
6112,
15230,
7031,
11379,
19112,
11495,
20083,
8650,
8791,
18376,
14926,
19754,
24791,
19275,
19216,
15609,
17769,
19063,
4945,
16562,
27041,
11316,
9946,
25075,
9262,
13746,
17110,
20600,
20048,
17241,
4656,
18553,
27596,
5066,
29883,
14518,
15484,
22036,
27125,
25389,
22522,
12728,
17573,
20626,
2466,
16421,
19662,
23407,
3850,
11928,
7280,
22335,
15297,
7481,
15060,
15918,
21650,
14085,
18760,
4700,
11570,
10174,
19821,
12236,
16276,
19988,
1653,
25503,
17905,
7303,
13870,
2447,
12408,
17682,
1146,
18915,
28569,
24977,
13094,
13928,
14631,
7913,
14273,
15215,
12499,
11137,
24351,
7842,
10183,
13843,
20679,
14984,
12680,
6703,
28274,
9168,
20899,
14891,
25129,
31273,
16790,
25506,
23608,
19105,
6533,
9980,
18785,
14562,
22692,
22058,
17592,
22220,
19286,
11013,
12696,
10303,
24388,
26780,
19964,
18505,
23351,
20594,
17970,
9840,
20499,
17020,
15360,
7628,
14311,
14805,
18809,
4070,
14020,
19705,
28492,
13114,
17744,
21909,
18342,
27297,
1630,
11089,
16294,
13551,
23769,
15740,
18878,
18013,
22926,
9220,
20571,
16195,
11157,
19552,
14332,
10112,
17817,
11366,
15658,
8269,
10602,
4382,
28153,
23470,
26448,
10306,
18383,
10695,
21829,
31030,
9976,
19451,
16657,
21769,
17965,
23906,
24780,
18038,
18354,
15196,
25015,
18210,
21473,
13413,
13488,
27826,
11707,
19010,
24586,
17875,
26706,
14628,
15804,
12034,
8758,
11493,
17219,
11705,
26091,
10173,
3944,
2099,
13528,
18884,
10293,
11143,
12569,
19717,
23971,
11247,
22748,
9972,
7129,
23270,
22477,
22988,
27264,
18744,
325,
15253,
17154,
17318,
19053,
24566,
29681,
13042,
5469,
21293,
26295,
16151,
15457,
15168,
14939,
30352,
19692,
21670,
12822,
7280,
9380,
16332,
10676,
17603,
10765,
27041,
10183,
29999,
8518,
13667,
26417,
24296,
21244,
22907,
3849,
13522,
29145,
27405,
15171,
18891,
22761,
10902,
5004,
12760,
25306,
23829,
17345,
6785,
24606,
10434,
17829,
10788,
22288,
8345,
20862,
1768,
13795,
2580,
};

long rtest[] ={
-15152,
-4459,
-28369,
-7591,
-25508,
-4863,
-18804,
-10873,
-4089,
-11833,
-5379,
-6065,
-14212,
-14631,
-7963,
-12532,
-7451,
-10886,
-5676,
-7673,
-13216,
-12664,
-4563,
-9625,
-23123,
-10539,
-14145,
-10256,
-2465,
-15411,
-5737,
-11527,
-11591,
-13968,
-4405,
-9224,
-10193,
-19343,
-24010,
-33156,
-4996,
-12189,
-3411,
-9857,
-9286,
-8598,
-11048,
-9246,
-7686,
-11249,
-10375,
-567,
-8321,
-25295,
-5058,
-6240,
-9280,
-20065,
-4090,
-4961,
-10600,
-1610,
-10825,
-4170,
-6261,
-8113,
-9642,
-13780,
-17437,
-7404,
-24194,
-20557,
-9982,
-15267,
-463,
-8866,
-26300,
-3562,
-4863,
-17589,
-4894,
-8493,
-11201,
-3759,
-6829,
-27078,
-21910,
-8716,
-13705,
-2946,
-8995,
-4459,
-14241,
-8289,
-17278,
-2486,
-1057,
-15399,
-26877,
-9914,
-12812,
-844,
-15138,
-6882,
-30084,
-1787,
-6113,
-19237,
-9494,
-7060,
-16375,
-19413,
-3299,
-12498,
-8850,
-24533,
-20974,
-4206,
-10448,
-11981,
-13666,
-15274,
-5733,
-15128,
-8290,
-8281,
-9909,
-3375,
-4873,
-7406,
-10759,
-7834,
-21875,
-6523,
-5284,
-5839,
-6311,
-5325,
-1421,
-12448,
-5258,
-17466,
-10204,
-41664,
-14507,
-17106,
-7065,
-4135,
-17927,
-10769,
-20921,
-23347,
-10881,
-5649,
-17234,
-2423,
-8807,
-10254,
-17223,
-913,
-4959,
-17462,
-9108,
-3408,
-5831,
-13364,
-12084,
-6611,
-18558,
-6301,
-18644,
-23832,
-21795,
-7302,
-4958,
-6738,
-5450,
-8646,
-9805,
-9791,
-9292,
-9615,
-1421,
-6707,
-10668,
-2675,
-24226,
-16277,
-18507,
-5717,
-6437,
-19218,
-12326,
-16139,
-10009,
-7378,
-25007,
-4260,
-13875,
-9209,
-21016,
-7708,
-5857,
-8548,
-11111,
-29374,
-13003,
-2900,
-11332,
-13244,
-8681,
-9725,
-16502,
-7900,
-11265,
-7209,
-18676,
-4321,
-12081,
-25180,
-8457,
-9635,
-8475,
-14792,
-7131,
-6473,
-1393,
-5013,
-378,
-10118,
-10694,
-16222,
-8138,
-8065,
-8220,
-8362,
-2998,
-15420,
-14312,
-9205,
-15945,
-23328,
-6280,
-12810,
-7298,
-27679,
-5362,
-6303,
-12405,
-12726,
-5168,
-6004,
-4977,
-10602,
-18887,
-20255,
-7818,
-4819,
-5478,
-11001,
-7682,
-14891,
-9452,
-4765,
-8918,
-25691,
-11676,
-22822,
-6550,
-6235,
-2286,
-20852,
-5585,
-8490,
-16592,
-27080,
-8307,
-17881,
-21058,
-6290,
-5787,
-3747,
-15053,
-13356,
-18662,
-8130,
-7960,
-8612,
-11118,
-19465,
-7741,
-5758,
-8887,
-13820,
-12593,
-13997,
-5982,
-13284,
-8197,
-27874,
-9482,
-14084,
-1955,
-11167,
-15348,
-9760,
-9589,
-10897,
-2915,
-5673,
-7967,
-9967,
-11241,
-4775,
-11226,
-6188,
-10590,
-1559,
-12515,
-7681,
-16038,
-5043,
-4812,
-6292,
-23896,
-10904,
-21903,
-15052,
-7672,
-14907,
-6967,
-18955,
-18723,
-8231,
-11190,
-7202,
-3970,
-7552,
-7595,
-10554,
-8710,
-7709,
-26911,
-9711,
-2734,
-15131,
-16968,
-3808,
-17982,
-12362,
-9247,
-6605,
-6992,
-9138,
-27770,
-8095,
-2444,
-26567,
-1311,
-11585,
-10669,
-5647,
-2689,
-3631,
-5336,
-13458,
-8867,
-6587,
-36812,
-9832,
-7269,
-4787,
-30472,
-14381,
-21407,
-5455,
-10841,
-21019,
-11063,
-10274,
-5898,
-12016,
-7937,
-27635,
-14815,
-16644,
-7154,
-14019,
-9959,
-7034,
-42506,
-3567,
-8601,
-21362,
-12235,
-36922,
-13820,
-8779,
-47723,
-7820,
-1952,
-3864,
-13053,
-12176,
-11474,
-20221,
-11827,
-10918,
-13716,
-15358,
-4225,
-20349,
-16632,
-12262,
-6551,
-11136,
-13512,
-22584,
-2099,
-18126,
-6400,
-11224,
-3777,
-665,
-9516,
-3566,
-4666,
-7678,
-22949,
-16919,
-7918,
-11542,
-5229,
-5632,
-8851,
-5528,
-7544,
-15517,
-13493,
-16466,
-4204,
-2872,
-7051,
-8132,
-4822,
-6610,
-8549,
-17120,
-6675,
-9322,
-10783,
-20743,
-11789,
-11306,
-7900,
-29681,
-12081,
-7237,
-1990,
-13032,
-8730,
-5729,
-8257,
-2600,
-42710,
-15420,
-9943,
-12566,
-4569,
-10435,
-7847,
-8515,
-5083,
-18045,
-6625,
-10029,
-15332,
-7348,
-11769,
-16731,
-8671,
-15068,
-10509,
-19596,
-16058,
-28631,
-2160,
-4749,
-3049,
-16462,
-8226,
-15934,
-5781,
-776,
-16925,
-7422,
-9629,
-5820,
-8553,
-4488,
-3977,
-8496,
-8248,
-10935,
-3842,
-8360,
-6015,
-12711,
-12633,
-2327,
-14647,
-7749,
-4088,
-8625,
-2911,
-11477,
-10377,
-14255,
-18777,
-14910,
-9157,
-14649,
-3243,
-16646,
-30130,
-39107,
-12590,
-7843,
-16480,
-15351,
-13636,
-7229,
-4449,
-15218,
-5194,
-16931,
-21707,
-4871,
-5365,
-5045,
-2617,
-7949,
-65664,
-10882,
-9211,
-9075,
-7716,
-4100,
-1408,
-13111,
-25478,
-6135,
-3132,
-10068,
-10693,
-10961,
-11178,
-1090,
-7247,
-5885,
-13352,
-21409,
-17801,
-9910,
-15960,
-8843,
-15841,
-2734,
-16632,
-1257,
-19172,
-12445,
-3066,
-4257,
-6168,
-5095,
-30477,
-12596,
-1668,
-2543,
-10959,
-7838,
-5186,
-15662,
-26742,
-13422,
-3677,
-4533,
-9053,
-22411,
-4076,
-16286,
-8661,
-15810,
-5485,
-19466,
-6426,
-41549,
-12312,
-36172,
};

long r[NX];
