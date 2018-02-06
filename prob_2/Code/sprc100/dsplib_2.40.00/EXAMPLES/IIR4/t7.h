/* Test for iircas4 : rand */
#define NX 35
#define NBIQ 4
#define FNAME "t7"
#define MAXERROR 20

DATA x[NX] ={
-113,
-300,
-348,
-253,
-200,
171,
-712,
-864,
-78,
691,
812,
-441,
-636,
697,
-491,
272,
873,
308,
692,
-917,
-680,
596,
-131,
730,
439,
350,
-288,
-625,
-645,
-578,
-146,
665,
-19,
590,
-74,
};

#pragma DATA_SECTION (h,".coeffs")
DATA h[4*NBIQ] ={ /* C54x: a1 b1 a2 b2  ... */
-1677,
5902,
-19442,
-11845,

-1939,
18991,
-7967,
4923,

-3452,
2071,
-17728,
9176,

15791,
-3930,
7596,
-4881,
};

DATA rtest[NX] ={
-113,
-348,
-601,
-802,
-981,
-751,
-1591,
-1825,
-1920,
-1270,
-684,
-1002,
-991,
-257,
-1167,
-11,
122,
644,
1336,
224,
387,
498,
79,
1112,
852,
1570,
883,
723,
-114,
-520,
-815,
-242,
-677,
410,
-270,
};

#pragma DATA_SECTION (dbuffer,".dbuffer")
DATA dbuffer[2*NBIQ];
DATA *dp = dbuffer;

DATA r[NX];
