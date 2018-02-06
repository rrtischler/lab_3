/* Test for cfft: rand */
#define NX 256
#define FNAME "t6"
#define MAXERROR 140

#pragma DATA_SECTION (x,".input")

DATA x[2*NX] ={
140,	370,	/* 0 */ 
643,	-171,	/* 1 */ 
-303,	-243,	/* 2 */ 
557,	5,	/* 3 */ 
-572,	92,	/* 4 */ 
-624,	383,	/* 5 */ 
-381,	401,	/* 6 */ 
620,	-23,	/* 7 */ 
-627,	433,	/* 8 */ 
-339,	-42,	/* 9 */ 
716,	-427,	/* 10 */ 
-413,	114,	/* 11 */ 
-3,	238,	/* 12 */ 
-301,	253,	/* 13 */ 
247,	634,	/* 14 */ 
656,	387,	/* 15 */ 
382,	340,	/* 16 */ 
238,	525,	/* 17 */ 
-530,	703,	/* 18 */ 
-581,	5,	/* 19 */ 
-696,	185,	/* 20 */ 
-304,	419,	/* 21 */ 
454,	-74,	/* 22 */ 
695,	34,	/* 23 */ 
-692,	-471,	/* 24 */ 
457,	-530,	/* 25 */ 
173,	-404,	/* 26 */ 
86,	-566,	/* 27 */ 
-367,	-515,	/* 28 */ 
461,	-62,	/* 29 */ 
-340,	413,	/* 30 */ 
363,	-314,	/* 31 */ 
228,	-395,	/* 32 */ 
-410,	586,	/* 33 */ 
146,	-707,	/* 34 */ 
150,	127,	/* 35 */ 
228,	60,	/* 36 */ 
-454,	220,	/* 37 */ 
195,	-268,	/* 38 */ 
-473,	-386,	/* 39 */ 
56,	-121,	/* 40 */ 
176,	-289,	/* 41 */ 
266,	247,	/* 42 */ 
254,	628,	/* 43 */ 
540,	-225,	/* 44 */ 
-699,	90,	/* 45 */ 
-272,	-547,	/* 46 */ 
400,	-475,	/* 47 */ 
-277,	-317,	/* 48 */ 
611,	81,	/* 49 */ 
256,	-21,	/* 50 */ 
-611,	648,	/* 51 */ 
-616,	-385,	/* 52 */ 
-700,	-31,	/* 53 */ 
-392,	38,	/* 54 */ 
23,	419,	/* 55 */ 
-60,	-441,	/* 56 */ 
291,	587,	/* 57 */ 
118,	605,	/* 58 */ 
13,	-698,	/* 59 */ 
-611,	383,	/* 60 */ 
-440,	641,	/* 61 */ 
-173,	449,	/* 62 */ 
-321,	607,	/* 63 */ 
388,	-432,	/* 64 */ 
-267,	249,	/* 65 */ 
198,	612,	/* 66 */ 
697,	-224,	/* 67 */ 
4,	135,	/* 68 */ 
641,	165,	/* 69 */ 
470,	-712,	/* 70 */ 
598,	691,	/* 71 */ 
-555,	572,	/* 72 */ 
447,	276,	/* 73 */ 
585,	-87,	/* 74 */ 
-493,	288,	/* 75 */ 
-542,	157,	/* 76 */ 
376,	-287,	/* 77 */ 
317,	510,	/* 78 */ 
217,	-557,	/* 79 */ 
364,	-299,	/* 80 */ 
233,	-578,	/* 81 */ 
549,	-148,	/* 82 */ 
-327,	-239,	/* 83 */ 
-116,	636,	/* 84 */ 
-412,	485,	/* 85 */ 
-666,	-347,	/* 86 */ 
-601,	-656,	/* 87 */ 
502,	-709,	/* 88 */ 
-230,	106,	/* 89 */ 
-49,	349,	/* 90 */ 
593,	439,	/* 91 */ 
-390,	197,	/* 92 */ 
519,	-357,	/* 93 */ 
224,	-510,	/* 94 */ 
560,	217,	/* 95 */ 
-17,	639,	/* 96 */ 
706,	452,	/* 97 */ 
-182,	616,	/* 98 */ 
44,	-273,	/* 99 */ 
-457,	-332,	/* 100 */ 
2,	52,	/* 101 */ 
-112,	-483,	/* 102 */ 
229,	-415,	/* 103 */ 
248,	-406,	/* 104 */ 
655,	217,	/* 105 */ 
-442,	-642,	/* 106 */ 
-558,	-389,	/* 107 */ 
93,	240,	/* 108 */ 
672,	-272,	/* 109 */ 
-683,	-278,	/* 110 */ 
530,	316,	/* 111 */ 
-679,	651,	/* 112 */ 
27,	-529,	/* 113 */ 
-442,	-619,	/* 114 */ 
309,	-538,	/* 115 */ 
-358,	-479,	/* 116 */ 
621,	589,	/* 117 */ 
-521,	-522,	/* 118 */ 
30,	167,	/* 119 */ 
566,	-332,	/* 120 */ 
634,	-401,	/* 121 */ 
-237,	305,	/* 122 */ 
-90,	70,	/* 123 */ 
-42,	632,	/* 124 */ 
-503,	-244,	/* 125 */ 
-523,	293,	/* 126 */ 
46,	635,	/* 127 */ 
323,	116,	/* 128 */ 
-146,	544,	/* 129 */ 
-203,	357,	/* 130 */ 
-308,	-173,	/* 131 */ 
528,	323,	/* 132 */ 
181,	-484,	/* 133 */ 
-372,	654,	/* 134 */ 
685,	-436,	/* 135 */ 
201,	395,	/* 136 */ 
-388,	162,	/* 137 */ 
259,	-485,	/* 138 */ 
237,	-673,	/* 139 */ 
-524,	-304,	/* 140 */ 
-685,	675,	/* 141 */ 
-341,	645,	/* 142 */ 
-550,	-390,	/* 143 */ 
-618,	657,	/* 144 */ 
505,	257,	/* 145 */ 
-459,	-638,	/* 146 */ 
-671,	143,	/* 147 */ 
335,	-154,	/* 148 */ 
52,	-409,	/* 149 */ 
-322,	-456,	/* 150 */ 
-189,	-607,	/* 151 */ 
-699,	-707,	/* 152 */ 
557,	413,	/* 153 */ 
524,	-692,	/* 154 */ 
-353,	541,	/* 155 */ 
99,	-212,	/* 156 */ 
-489,	318,	/* 157 */ 
135,	671,	/* 158 */ 
-243,	-494,	/* 159 */ 
227,	-484,	/* 160 */ 
521,	-268,	/* 161 */ 
96,	-675,	/* 162 */ 
688,	-205,	/* 163 */ 
418,	-678,	/* 164 */ 
-499,	421,	/* 165 */ 
477,	715,	/* 166 */ 
-442,	-559,	/* 167 */ 
199,	175,	/* 168 */ 
242,	-527,	/* 169 */ 
390,	-273,	/* 170 */ 
-173,	-524,	/* 171 */ 
-84,	-397,	/* 172 */ 
-25,	-149,	/* 173 */ 
154,	-524,	/* 174 */ 
-465,	-372,	/* 175 */ 
-714,	612,	/* 176 */ 
416,	-157,	/* 177 */ 
19,	16,	/* 178 */ 
-412,	-584,	/* 179 */ 
-569,	-686,	/* 180 */ 
-492,	-489,	/* 181 */ 
-133,	493,	/* 182 */ 
-133,	543,	/* 183 */ 
-642,	-449,	/* 184 */ 
633,	704,	/* 185 */ 
-502,	303,	/* 186 */ 
-166,	532,	/* 187 */ 
-271,	-30,	/* 188 */ 
-476,	-6,	/* 189 */ 
568,	-305,	/* 190 */ 
-255,	-630,	/* 191 */ 
335,	-341,	/* 192 */ 
-128,	-450,	/* 193 */ 
-144,	597,	/* 194 */ 
7,	-541,	/* 195 */ 
-475,	-698,	/* 196 */ 
35,	-187,	/* 197 */ 
202,	284,	/* 198 */ 
-694,	558,	/* 199 */ 
482,	134,	/* 200 */ 
435,	-493,	/* 201 */ 
283,	-263,	/* 202 */ 
-55,	-383,	/* 203 */ 
-599,	-705,	/* 204 */ 
459,	-148,	/* 205 */ 
-441,	214,	/* 206 */ 
-79,	-595,	/* 207 */ 
-699,	385,	/* 208 */ 
-275,	673,	/* 209 */ 
538,	307,	/* 210 */ 
480,	404,	/* 211 */ 
-240,	-377,	/* 212 */ 
545,	-437,	/* 213 */ 
-30,	-340,	/* 214 */ 
87,	306,	/* 215 */ 
166,	684,	/* 216 */ 
232,	196,	/* 217 */ 
167,	65,	/* 218 */ 
265,	498,	/* 219 */ 
14,	433,	/* 220 */ 
306,	241,	/* 221 */ 
21,	245,	/* 222 */ 
151,	459,	/* 223 */ 
669,	674,	/* 224 */ 
461,	-19,	/* 225 */ 
-262,	455,	/* 226 */ 
125,	202,	/* 227 */ 
-531,	-278,	/* 228 */ 
-353,	230,	/* 229 */ 
434,	-204,	/* 230 */ 
240,	628,	/* 231 */ 
-698,	-18,	/* 232 */ 
88,	-587,	/* 233 */ 
-66,	249,	/* 234 */ 
580,	21,	/* 235 */ 
-313,	-400,	/* 236 */ 
-624,	322,	/* 237 */ 
-34,	-619,	/* 238 */ 
693,	665,	/* 239 */ 
605,	-420,	/* 240 */ 
87,	-486,	/* 241 */ 
218,	198,	/* 242 */ 
390,	-717,	/* 243 */ 
-565,	-236,	/* 244 */ 
-716,	-323,	/* 245 */ 
59,	-653,	/* 246 */ 
-707,	-583,	/* 247 */ 
-70,	-130,	/* 248 */ 
-437,	454,	/* 249 */ 
411,	531,	/* 250 */ 
169,	-685,	/* 251 */ 
-695,	325,	/* 252 */ 
560,	498,	/* 253 */ 
375,	327,	/* 254 */ 
583,	652,	/* 255 */ 
};

#pragma DATA_SECTION (rtest,".test")

DATA rtest[2*NX] ={
-1526,	-2112,	 /* 0 */ 
-2322,	10505,	 /* 1 */ 
4616,	-4300,	 /* 2 */ 
5737,	-5704,	 /* 3 */ 
-15165,	11017,	 /* 4 */ 
-11712,	2715,	 /* 5 */ 
-10422,	-3534,	 /* 6 */ 
-1242,	591,	 /* 7 */ 
11030,	16681,	 /* 8 */ 
-6609,	-10897,	 /* 9 */ 
143,	-4694,	 /* 10 */ 
10052,	5528,	 /* 11 */ 
8194,	4652,	 /* 12 */ 
8008,	873,	 /* 13 */ 
3500,	14284,	 /* 14 */ 
6607,	-6205,	 /* 15 */ 
8554,	3131,	 /* 16 */ 
4505,	-5273,	 /* 17 */ 
3977,	2995,	 /* 18 */ 
15693,	-13079,	 /* 19 */ 
-5910,	-6766,	 /* 20 */ 
-2186,	-4223,	 /* 21 */ 
3276,	-4194,	 /* 22 */ 
18213,	7426,	 /* 23 */ 
2867,	-7966,	 /* 24 */ 
-13927,	-5573,	 /* 25 */ 
-3516,	2479,	 /* 26 */ 
-2797,	-1502,	 /* 27 */ 
1209,	3592,	 /* 28 */ 
779,	-3910,	 /* 29 */ 
7475,	-7207,	 /* 30 */ 
-5694,	-1689,	 /* 31 */ 
17362,	13699,	 /* 32 */ 
11039,	270,	 /* 33 */ 
8441,	1642,	 /* 34 */ 
7710,	-2167,	 /* 35 */ 
8266,	3337,	 /* 36 */ 
-4371,	10297,	 /* 37 */ 
-7663,	4032,	 /* 38 */ 
3340,	3674,	 /* 39 */ 
-1539,	1307,	 /* 40 */ 
5372,	-5366,	 /* 41 */ 
4593,	5267,	 /* 42 */ 
-4235,	1606,	 /* 43 */ 
-10079,	-10386,	 /* 44 */ 
8784,	13896,	 /* 45 */ 
7737,	-417,	 /* 46 */ 
5018,	-8851,	 /* 47 */ 
959,	-3575,	 /* 48 */ 
2706,	4913,	 /* 49 */ 
11331,	5932,	 /* 50 */ 
-5496,	-8117,	 /* 51 */ 
7703,	-4928,	 /* 52 */ 
-1912,	-7810,	 /* 53 */ 
-11740,	3881,	 /* 54 */ 
-4215,	1223,	 /* 55 */ 
2706,	-7220,	 /* 56 */ 
-2469,	2399,	 /* 57 */ 
668,	340,	 /* 58 */ 
733,	1530,	 /* 59 */ 
1608,	406,	 /* 60 */ 
-6019,	-1613,	 /* 61 */ 
-1607,	6964,	 /* 62 */ 
-4342,	-10527,	 /* 63 */ 
-15059,	-2401,	 /* 64 */ 
-4833,	-10048,	 /* 65 */ 
7488,	-6419,	 /* 66 */ 
-13026,	2408,	 /* 67 */ 
-4054,	-8651,	 /* 68 */ 
-7834,	4629,	 /* 69 */ 
4072,	2910,	 /* 70 */ 
-2146,	22545,	 /* 71 */ 
4832,	-6195,	 /* 72 */ 
-3326,	4297,	 /* 73 */ 
8061,	3245,	 /* 74 */ 
-5024,	-5391,	 /* 75 */ 
3303,	8025,	 /* 76 */ 
2540,	2601,	 /* 77 */ 
10907,	4370,	 /* 78 */ 
689,	-2479,	 /* 79 */ 
6510,	-516,	 /* 80 */ 
8003,	-3095,	 /* 81 */ 
-1789,	2316,	 /* 82 */ 
15342,	4415,	 /* 83 */ 
-965,	-654,	 /* 84 */ 
5404,	13062,	 /* 85 */ 
-19842,	3174,	 /* 86 */ 
7397,	788,	 /* 87 */ 
13880,	2521,	 /* 88 */ 
-1297,	6305,	 /* 89 */ 
-187,	6874,	 /* 90 */ 
-5757,	2687,	 /* 91 */ 
2718,	-980,	 /* 92 */ 
670,	2913,	 /* 93 */ 
2039,	15868,	 /* 94 */ 
-3289,	-367,	 /* 95 */ 
687,	4767,	 /* 96 */ 
20818,	2903,	 /* 97 */ 
-7411,	-23075,	 /* 98 */ 
2574,	3104,	 /* 99 */ 
12755,	-15181,	 /* 100 */ 
-2092,	1775,	 /* 101 */ 
-3170,	-6643,	 /* 102 */ 
-14478,	-6495,	 /* 103 */ 
459,	-2268,	 /* 104 */ 
10031,	6453,	 /* 105 */ 
-5165,	-14661,	 /* 106 */ 
-2130,	7213,	 /* 107 */ 
7938,	304,	 /* 108 */ 
3374,	7562,	 /* 109 */ 
-5115,	-3437,	 /* 110 */ 
-2713,	-573,	 /* 111 */ 
-4743,	5862,	 /* 112 */ 
902,	-8847,	 /* 113 */ 
-1064,	378,	 /* 114 */ 
-1172,	1060,	 /* 115 */ 
255,	7030,	 /* 116 */ 
-16590,	-2770,	 /* 117 */ 
-12419,	-1831,	 /* 118 */ 
-10374,	9327,	 /* 119 */ 
6237,	-3780,	 /* 120 */ 
-12063,	-7007,	 /* 121 */ 
7326,	9718,	 /* 122 */ 
-2433,	1522,	 /* 123 */ 
4782,	4701,	 /* 124 */ 
4798,	9943,	 /* 125 */ 
-8385,	-6789,	 /* 126 */ 
-2725,	356,	 /* 127 */ 
-13660,	-2469,	 /* 128 */ 
4061,	-5423,	 /* 129 */ 
-3580,	11639,	 /* 130 */ 
-776,	-3613,	 /* 131 */ 
-4519,	6813,	 /* 132 */ 
-1988,	-10662,	 /* 133 */ 
4723,	4128,	 /* 134 */ 
-1606,	1947,	 /* 135 */ 
-2495,	3079,	 /* 136 */ 
2087,	41,	 /* 137 */ 
-7596,	-2733,	 /* 138 */ 
-12254,	-8551,	 /* 139 */ 
4439,	-6124,	 /* 140 */ 
-1792,	3286,	 /* 141 */ 
-9075,	-7754,	 /* 142 */ 
553,	-6717,	 /* 143 */ 
-831,	5378,	 /* 144 */ 
-959,	1273,	 /* 145 */ 
1259,	-5014,	 /* 146 */ 
-9196,	-161,	 /* 147 */ 
76,	-2047,	 /* 148 */ 
-1035,	4818,	 /* 149 */ 
-2942,	-6222,	 /* 150 */ 
2953,	5681,	 /* 151 */ 
12988,	-9348,	 /* 152 */ 
2690,	7438,	 /* 153 */ 
5912,	11526,	 /* 154 */ 
7891,	5795,	 /* 155 */ 
4795,	-14569,	 /* 156 */ 
376,	-5100,	 /* 157 */ 
-2666,	1107,	 /* 158 */ 
-3538,	3364,	 /* 159 */ 
-4643,	128,	 /* 160 */ 
-3170,	-4440,	 /* 161 */ 
-2139,	2499,	 /* 162 */ 
-3434,	-3280,	 /* 163 */ 
-9126,	6001,	 /* 164 */ 
861,	21,	 /* 165 */ 
10341,	1304,	 /* 166 */ 
1038,	-365,	 /* 167 */ 
-1363,	-11372,	 /* 168 */ 
3374,	1718,	 /* 169 */ 
-6167,	7505,	 /* 170 */ 
-6687,	505,	 /* 171 */ 
-15017,	-7905,	 /* 172 */ 
2271,	-4266,	 /* 173 */ 
-2416,	-10136,	 /* 174 */ 
5415,	-257,	 /* 175 */ 
5138,	-759,	 /* 176 */ 
12468,	2154,	 /* 177 */ 
-1708,	904,	 /* 178 */ 
-4410,	-8064,	 /* 179 */ 
8636,	7631,	 /* 180 */ 
-4531,	8313,	 /* 181 */ 
-4377,	-12506,	 /* 182 */ 
6368,	525,	 /* 183 */ 
10028,	275,	 /* 184 */ 
-2233,	7093,	 /* 185 */ 
4470,	4322,	 /* 186 */ 
4003,	1102,	 /* 187 */ 
-1577,	-695,	 /* 188 */ 
-6826,	-1998,	 /* 189 */ 
2750,	7203,	 /* 190 */ 
-4757,	1985,	 /* 191 */ 
-3006,	-3646,	 /* 192 */ 
-15454,	9135,	 /* 193 */ 
10704,	14099,	 /* 194 */ 
-7,	1112,	 /* 195 */ 
-456,	-1836,	 /* 196 */ 
2825,	-4771,	 /* 197 */ 
-250,	4246,	 /* 198 */ 
-501,	-112,	 /* 199 */ 
-2263,	-2827,	 /* 200 */ 
577,	-5339,	 /* 201 */ 
-13201,	-3802,	 /* 202 */ 
-8629,	-810,	 /* 203 */ 
-4738,	-4094,	 /* 204 */ 
639,	4808,	 /* 205 */ 
-3787,	-1786,	 /* 206 */ 
4573,	-482,	 /* 207 */ 
5639,	4646,	 /* 208 */ 
3524,	-12565,	 /* 209 */ 
-255,	6515,	 /* 210 */ 
-13354,	3542,	 /* 211 */ 
4326,	-1197,	 /* 212 */ 
-3099,	-1429,	 /* 213 */ 
-786,	11660,	 /* 214 */ 
-13597,	2722,	 /* 215 */ 
4675,	8196,	 /* 216 */ 
-16934,	1688,	 /* 217 */ 
4191,	-16117,	 /* 218 */ 
6309,	2657,	 /* 219 */ 
1714,	7449,	 /* 220 */ 
7969,	-3509,	 /* 221 */ 
-10474,	9279,	 /* 222 */ 
-1809,	-3755,	 /* 223 */ 
12233,	-4909,	 /* 224 */ 
8617,	7460,	 /* 225 */ 
1275,	-3101,	 /* 226 */ 
-8240,	-70,	 /* 227 */ 
-1925,	1967,	 /* 228 */ 
-5152,	-10952,	 /* 229 */ 
-5297,	2208,	 /* 230 */ 
6733,	7620,	 /* 231 */ 
-6980,	-8199,	 /* 232 */ 
-10773,	-5376,	 /* 233 */ 
11740,	-2853,	 /* 234 */ 
-3376,	7694,	 /* 235 */ 
-1775,	-8772,	 /* 236 */ 
13219,	-2838,	 /* 237 */ 
-1967,	12108,	 /* 238 */ 
13200,	1929,	 /* 239 */ 
-2999,	10998,	 /* 240 */ 
4953,	8046,	 /* 241 */ 
228,	10334,	 /* 242 */ 
1464,	4426,	 /* 243 */ 
-7527,	-6177,	 /* 244 */ 
518,	-291,	 /* 245 */ 
-5259,	1819,	 /* 246 */ 
-4576,	-2299,	 /* 247 */ 
7787,	3737,	 /* 248 */ 
2014,	2258,	 /* 249 */ 
19163,	10270,	 /* 250 */ 
9355,	-9274,	 /* 251 */ 
2647,	4961,	 /* 252 */ 
-3210,	-2882,	 /* 253 */ 
-5624,	8473,	 /* 254 */ 
7483,	4170,	 /* 255 */ 
};

DATA error;
