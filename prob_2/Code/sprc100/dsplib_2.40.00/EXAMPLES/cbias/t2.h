#define NA 64
#define NB 64  // NB <= NA 
#define FNAME "t2"
#define MAXERROR 10  // max absolute error 

DATA a[NA] ={
3567,
3415,
-736,
3224,
-3622,
-1206,
2565,
-4016,
-2959,
-2435,
-2469,
850,
-1867,
-2468,
-3971,
2021,
-450,
3537,
-279,
-667,
2836,
206,
-2436,
1410,
2769,
-3936,
1485,
-988,
2718,
23,
1715,
-583,
-1601,
-2543,
-2512,
1492,
-1616,
341,
-2861,
1621,
-997,
2949,
2897,
766,
-29,
3274,
2634,
1187,
2604,
1312,
-1295,
-1723,
-1301,
279,
1860,
-1563,
2772,
557,
-1062,
1660,
381,
-452,
1593,
993,
};

DATA b[NB] ={
2415,
3742,
185,
3114,
-2680,
3930,
-1873,
-2029,
3078,
1944,
-2978,
-4000,
3226,
-2465,
-1649,
1322,
-1767,
-253,
-3566,
4000,
678,
-627,
127,
-1361,
-550,
-2246,
653,
2132,
244,
1151,
-2384,
-985,
2321,
1481,
-319,
555,
2410,
-3612,
842,
-3685,
-694,
-1598,
3066,
-3974,
2195,
3857,
4014,
2366,
-503,
-14,
-2344,
1175,
-1475,
3769,
1856,
-722,
2003,
-1901,
-493,
3550,
1501,
-2355,
2779,
1055,
};

DATA rtest[NA+NB-1] ={
2,
6,
0,
-1,
12,
-5,
1,
6,
-15,
-2,
17,
-10,
-4,
-2,
-22,
4,
2,
-7,
13,
3,
3,
4,
-5,
-25,
7,
-18,
-38,
20,
0,
-11,
1,
3,
-8,
19,
12,
-13,
21,
-6,
15,
-16,
5,
-29,
17,
-28,
-6,
26,
4,
24,
-20,
22,
-32,
19,
-11,
-11,
13,
0,
-3,
26,
22,
5,
38,
14,
-7,
35,
29,
-15,
31,
-23,
-25,
-32,
-18,
1,
5,
-10,
-4,
22,
-26,
9,
20,
12,
-19,
14,
-9,
8,
11,
-2,
11,
-19,
-4,
-2,
26,
-8,
-3,
4,
-27,
-15,
-9,
9,
-22,
0,
6,
-9,
0,
16,
10,
5,
-3,
13,
10,
-3,
6,
8,
-8,
-11,
8,
-10,
2,
8,
1,
3,
2,
1,
4,
1,
2,
4,
1,
};
