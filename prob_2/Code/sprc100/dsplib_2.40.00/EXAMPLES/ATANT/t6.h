/* Test for maxval: rand */
#define NX 100
#define FNAME "t6"
#define MAXERROR 40

DATA x[NX] ={
-29554,
16733,
25874,
-14015,
-16306,
28359,
-24184,
28889,
13228,
22785,
-19054,
-2944,
-27455,
23011,
4066,
-11843,
-8199,
24103,
-8378,
-27939,
-19672,
-29525,
4371,
-24778,
1449,
-25097,
17689,
-8189,
21193,
-29712,
6416,
29435,
-13842,
25482,
-26111,
-28488,
-17413,
28383,
-28631,
-15453,
32737,
-18876,
-105,
-13731,
11321,
30014,
17468,
10887,
-24187,
-26516,
-31794,
-13881,
20757,
31816,
-31631,
20931,
7938,
3946,
-16776,
21103,
-15519,
16622,
10462,
-18740,
6692,
6877,
10453,
-20752,
8948,
-21607,
2595,
8086,
12182,
11622,
24695,
-31924,
-12426,
18289,
-12630,
27962,
11712,
-27898,
-28137,
-31987,
-17882,
1065,
-2740,
13317,
5405,
603,
-27900,
-20105,
-7891,
-14652,
17752,
-12195,
9056,
31887,
188,
29340,
};

DATA rtest[NX] ={
-24048,
15471,
21901,
-13244,
-15130,
23376,
-20834,
23677,
12572,
19909,
-17259,
-2936,
-22853,
20061,
4045,
-11364,
-8034,
20781,
-8202,
-23135,
-17717,
-24032,
4346,
-21215,
1448,
-21417,
16220,
-8025,
18812,
-24135,
6336,
23982,
-13097,
21658,
-22047,
-23450,
-16006,
23390,
-23532,
-14439,
25720,
-17125,
-105,
-13003,
10900,
24299,
16049,
10511,
-20836,
-22293,
-25242,
-13130,
18502,
25253,
-25157,
18627,
7788,
3927,
-15505,
18748,
-14493,
15382,
10127,
-17023,
6601,
6778,
10118,
-18499,
8735,
-19102,
2589,
7928,
11663,
11168,
21162,
-25309,
-11877,
16681,
-12055,
23148,
11248,
-23111,
-23249,
-25341,
-16369,
1064,
-2733,
12649,
5357,
603,
-23112,
-18033,
-7743,
-13778,
16269,
-11674,
8836,
25289,
188,
23929,
};

DATA r[NX];
