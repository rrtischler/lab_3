/*Test for cfft: rand*/
#define NX 128
#define FNAME "t128"
#define MAXERROR 128
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
49723516, 11061145,
1098443, 20083820,
62761982, 4938387,
-40566990, -3403728,
-26260768, -88415285,
-25746266, 941316,
-3597039, -29404089,
-32784582, -8907945,
-32346074, -10991691,
-79831777, -38864337,
-28124919, 19463356,
8635087, 8044867,
-6168445, -11773744,
-5624236, 29933858,
-3925496, 52958921,
5653525, -37184147,
-16817693, -870102,
-23658439, -37266482,
17051177, 25193814,
-14123783, 16782821,
7688440, -17356395,
-32195378, -18763957,
-4900376, -25278923,
24982551, 31065119,
-29880089, -8338958,
4666142, -5027612,
-7923688, -42225413,
-2531988, 10489782,
-12031677, 90270715,
-69713857, 9720595,
-4816595, -47741347,
46752782, 8280755,
21870916, -48176544,
-12654502, 4985287,
-22194346, -56810088,
8353643, 24131961,
-12868667, 38311539,
-17732840, 52074340,
1858525, 46426923,
42069492, -25437355,
-84557291, 14853297,
19624515, 30571373,
-33825029, -36040333,
31684941, 6770006,
-81334505, 25597442,
-7510536, -43224390,
1948502, -31976093,
-14247682, 26111203,
-6808796, -212435,
-50770439, 17598857,
-37794097, 45777365,
-27346934, 16174556,
12301534, -26409547,
-19666479, 25232908,
51586887, -5599829,
4700021, -27388071,
-62504077, 70265168,
-15240191, 2689473,
-21879976, -31450404,
3466773, 21331854,
-7403169, 56439494,
-9363142, 19919057,
-24617612, 26513131,
-2165388, 3531733,
-48452736, -5321014,
20546731, 29222805,
-44409390, -6535025,
-22198830, 2532503,
-4902789, -17670933,
8324350, -23001039,
-2571362, -9005595,
58323306, -39874274,
54424346, 8340926,
21019701, 3437706,
3080753, -1375962,
-27098796, -75416348,
-15479904, -17138815,
-47176498, 8363195,
-12567129, 12388186,
-15801159, 6012841,
58763730, -1251024,
25274024, -53798152,
2180680, 11387436,
-9823538, -4400154,
2779074, 16280268,
25709120, 20090740,
75056227, -2886718,
10968498, 10914990,
28967673, -11245541,
22796432, -10819600,
18614577, -12830347,
33609140, -31989820,
42257282, 7837497,
1481464, 41447933,
-10540711, -19412299,
7607046, -16828802,
33443432, 24255275,
40799227, 1325349,
-18210071, 51716734,
30609304, -57077862,
-5776098, -34686602,
-11272767, -25625776,
18169281, 73028737,
31276462, 14482499,
-19134504, -14890289,
-50284852, 1006494,
-1689319, -10592157,
18556432, 32811057,
2801724, 613874,
52932905, 27446278,
-11098941, 23566657,
26680969, -7760152,
-26333523, -3814789,
-42383324, 4292971,
22369229, -26823738,
-46728983, -8006489,
-43639635, -3001888,
-20301175, -34335048,
-49947936, 31458552,
18741592, -37974198,
-9306466, -23847205,
-43408857, -39241937,
-29810938, 35750138,
-33102121, -22830226,
-2403089, -57907321,
-81020227, 27286451,
-23298487, 48381015,
-46687268, 22557712,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
-706273171, -20983326,
-233881864, 452536688,
-965700121, -598186534,
263961627, -208576874,
25274292, 113376221,
229589861, -147122725,
-165994994, 144635706,
432503139, 397283282,
-222003943, 11186841,
16073464, 72830496,
-368606388, 393419123,
565670929, -194508763,
-123268181, -238244941,
-118501392, -370647032,
399003006, 396089593,
28923806, -77272763,
13610200, 124646845,
-363485335, -273056054,
-138727403, 91756427,
455587368, 287107938,
294875398, -190398816,
168419901, 670228008,
-7665416, -376772564,
-313426053, -55741502,
786587458, -645234863,
195523877, -165288535,
-728343361, -283638340,
-305115217, -360223752,
581636422, 186499381,
265948051, -370339844,
207525118, -318809273,
-749480449, -653815055,
73833097, 346591776,
428720259, 56865450,
-85606627, -642718755,
-147194635, -87893431,
195455920, 50171211,
265840054, 175755602,
-271098502, -147926819,
462042146, 130323993,
-235100647, -99631886,
-102252570, 471212256,
228766283, -179919000,
-318869548, -4563442,
-245953423, 88691842,
-90418767, -198323139,
108036662, 159831947,
269081281, 462319889,
-135237177, 176745477,
-67641733, 539781814,
12103570, 814241090,
88512314, -37800240,
-56403907, -661586066,
-122343305, -296378145,
160862852, -127723441,
-30536610, 614899580,
337537224, 29024302,
187896642, -498802744,
338848476, -255348999,
987995496, 163115939,
-18434897, -575849497,
271333913, -17640143,
289381494, 517245932,
741712636, -251681065,
-18634759, 168518346,
46586905, 118849014,
423996051, -320400452,
449099710, -182555679,
-62999239, 105617809,
207732441, -282832779,
-676029660, -456850744,
391673403, 87732529,
279732699, -329665841,
-150802045, 115891865,
229402011, 188120236,
304035873, 68170410,
-176582053, 89856583,
-74275287, 583530344,
-147783919, 485916551,
106310868, -502849723,
-238371020, 186087221,
155873109, 168516764,
129006037, -166760439,
946243655, 21312411,
-272895110, 51123489,
326192988, 109590020,
-557534176, -336239646,
-326247892, 335933989,
436806935, 40405911,
-826074200, -133566287,
-392846317, 207586457,
-73642269, -293711885,
276646640, -107855440,
2284498, -108533280,
-94674925, 112619638,
-17866910, -660022022,
-306478479, -650900724,
241665885, -527297796,
94254036, -305377900,
-212541329, 149702273,
-309981805, 218631934,
529007747, -58152556,
407433745, 181044026,
127793889, 378286380,
148721264, 187878610,
-520526722, 277096492,
-119520289, -145025643,
712375025, 466153401,
111199821, 321552907,
106733320, -364395263,
-177168663, 607065237,
281852601, -31220403,
605970221, -332175863,
-275104829, 412681968,
35825222, 10088181,
383094447, 937612144,
332755964, 287926425,
-278894638, 556682021,
-36125784, 486727645,
758791102, 82063515,
225521634, 418235367,
648402452, -43213816,
472949298, 465333251,
-248415429, 24269300,
213176720, 67962349,
-245800821, -31909064,
-333361493, 349142307,
-554466702, -849941797,
};