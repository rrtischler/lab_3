#define NX 128
#define NH 64
#define FNAME "t2"
#define MAXERROR 15

DATA x[2*NX] ={
32767, 32767, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
};

#pragma DATA_SECTION(h,".coeffs")
DATA h[2*NH] ={ /* b0 b1 b2 ... b(NH-1) */
-191, -172, 
-592, -460, 
-410, -671, 
-222, -317, 
-84, -483, 
-279, -591, 
-877, -326, 
-633, -404, 
-69, -219, 
-89, -46, 
-628, -509, 
-114, -128, 
-1003, -881, 
-689, -22, 
-199, -776, 
-1054, -796, 
-917, -133, 
-849, -280, 
-853, -920, 
-422, -1052, 
-775, -113, 
-853, -853, 
-1049, -747, 
-270, -361, 
-591, -762, 
-73, -565, 
-569, -996, 
-619, -13, 
-164, -445, 
-506, -614, 
-849, -516, 
-349, -709, 
-173, -604, 
-1044, -824, 
-340, -448, 
-661, -256, 
-180, -501, 
-530, -383, 
-310, -842, 
-608, -661, 
-741, -231, 
-863, -340, 
-859, -574, 
-339, -461, 
-743, -220, 
-488, -1002, 
-904, -423, 
-322, -1011, 
-662, -623, 
-150, -740, 
-156, -134, 
-433, -1049, 
-536, -247, 
-107, -32, 
-190, -11, 
-378, -225, 
-194, -598, 
-362, -535, 
-701, -837, 
-757, -380, 
-702, -724, 
-496, -43, 
-291, -291, 
-736, -626, 
};

#pragma DATA_SECTION(db,".dbuffer")
DATA db[2*NH + 2] ;

DATA rtest[2*NX] ={
-18, -362, 
-131, -1051, 
261, -1079, 
95, -538, 
399, -566, 
312, -870, 
-552, -1202, 
-229, -1036, 
150, -287, 
-43, -134, 
-120, -1136, 
14, -241, 
-122, -1883, 
-667, -710, 
577, -974, 
-258, -1850, 
-784, -1049, 
-569, -1128, 
66, -1772, 
630, -1474, 
-662, -888, 
0, -1705, 
-302, -1795, 
91, -630, 
171, -1352, 
492, -638, 
427, -1564, 
-606, -631, 
280, -608, 
108, -1119, 
-333, -1364, 
360, -1058, 
431, -776, 
-220, -1867, 
108, -787, 
-405, -916, 
321, -680, 
-147, -912, 
533, -1151, 
52, -1268, 
-510, -971, 
-523, -1202, 
-285, -1432, 
122, -798, 
-523, -961, 
514, -1489, 
-481, -1327, 
689, -1332, 
-39, -1284, 
591, -889, 
-22, -289, 
616, -1481, 
-289, -783, 
-76, -138, 
-179, -200, 
-153, -603, 
404, -791, 
172, -896, 
136, -1537, 
-377, -1136, 
23, -1425, 
-453, -538, 
1, -581, 
-109, -1361, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
0, 0, 
};

