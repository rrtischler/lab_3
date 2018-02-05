/* Test for cfft: rand */
#define NX 32
#define FNAME "t3"
#define MAXERROR 10

#pragma DATA_SECTION (x,".input")

LDATA x[2*NX] ={
-759715774,	1146367113,	/* 0 */ 
-1206734394,	1776366550,	/* 1 */ 
-1192046512,	87839150,	/* 2 */ 
708547403,	1478125392,	/* 3 */ 
-766920752,	-1271660507,	/* 4 */ 
162042468,	1865423139,	/* 5 */ 
-1357527550,	-888692716,	/* 6 */ 
769498270,	-963029820,	/* 7 */ 
-472928165,	1461015463,	/* 8 */ 
1399850593,	922728390,	/* 9 */ 
1375134406,	-1413341814,	/* 10 */ 
363805213,	-1898460167,	/* 11 */ 
-13405278,	1531612578,	/* 12 */ 
1554441883,	-1169856054,	/* 13 */ 
1250606273,	-782635080,	/* 14 */ 
563462079,	627745004,	/* 15 */ 
1236395060,	-838294543,	/* 16 */ 
623020583,	-119666706,	/* 17 */ 
-614473314,	-1692282680,	/* 18 */ 
-817619004,	1898816438,	/* 19 */ 
-617494751,	321922913,	/* 20 */ 
132511098,	-297473218,	/* 21 */ 
883095342,	60315098,	/* 22 */ 
-741546327,	-645654519,	/* 23 */ 
1316190598,	-260882539,	/* 24 */ 
264689453,	-1065602427,	/* 25 */ 
-503877257,	310316938,	/* 26 */ 
788323443,	1012389902,	/* 27 */ 
181084869,	115962671,	/* 28 */ 
-214324976,	546416005,	/* 29 */ 
756545242,	-1131239554,	/* 30 */ 
471696068,	-467308063,	/* 31 */ 
};

#pragma DATA_SECTION (rtest,".test")

LDATA rtest[2*NX] ={
172572697,	8040073,	 /* 0 */ 
-185525506,	135860670,	 /* 1 */ 
64250770,	332904282,	 /* 2 */ 
-52006049,	-29165753,	 /* 3 */ 
168186218,	40667059,	 /* 4 */ 
84899676,	92401131,	 /* 5 */ 
2028156,	121963320,	 /* 6 */ 
34041927,	239625788,	 /* 7 */ 
28795646,	220201070,	 /* 8 */ 
251660347,	-26017060,	 /* 9 */ 
-168885142,	25221128,	 /* 10 */ 
-190644282,	109167750,	 /* 11 */ 
189602689,	35343846,	 /* 12 */ 
14416216,	276409217,	 /* 13 */ 
277588663,	-247729088,	 /* 14 */ 
-71822982,	-278525299,	 /* 15 */ 
-128781295,	-210769918,	 /* 16 */ 
-101308003,	106274090,	 /* 17 */ 
-232352009,	-133770855,	 /* 18 */ 
208864128,	175258503,	 /* 19 */ 
-7469877,	164229804,	 /* 20 */ 
-121570771,	267916556,	 /* 21 */ 
171875909,	23423074,	 /* 22 */ 
-199563334,	-453903512,	 /* 23 */ 
-59686324,	258284167,	 /* 24 */ 
-10847548,	20021870,	 /* 25 */ 
-33500620,	-141850214,	 /* 26 */ 
-450675298,	65561702,	 /* 27 */ 
-33234328,	-138944731,	 /* 28 */ 
-277623,	70578628,	 /* 29 */ 
-172651517,	-203176739,	 /* 30 */ 
-207696322,	220866541,	 /* 31 */ 
};

LDATA error;

