/*Test for cifft: rand*/
#define NX 512
#define FNAME "t512"
#define MAXERROR 520
#pragma DATA_SECTION (x,".input")
LDATA x[2*NX] ={
43382741, 81551211,
-12698973, 67796034,
84605, 26752518,
29683618, 1040066,
19543793, 18144168,
-54165038, 22948596,
-50454643, -19798850,
19246349, -8760535,
-30552551, 50904370,
-54736585, 33797993,
-12050680, 10181121,
-13341784, -27416672,
-38967000, -16481672,
-37239990, 29107350,
9753346, 12106095,
-64096973, -2696797,
44116303, 25142367,
22324411, -60128475,
-9231313, 40709094,
-772476, -2030848,
-30466635, -13170795,
-35019316, 20453001,
12533106, 21594952,
30250407, 34209453,
42900655, 31354492,
-4310279, 41224383,
20562874, -8371373,
65649853, -23742532,
76045298, -19925442,
-12547970, -8801677,
75096121, 41703037,
-5354621, -51972533,
-23598204, -12977522,
18907152, 9230766,
-1687667, 27721136,
39043691, -32859140,
22105943, -3499620,
-52012345, 4289902,
-101640339, 2098616,
18138794, 12469636,
-33856368, -3488404,
30469008, -23379901,
53093288, -12979617,
-32852749, 541359,
33819581, 45943123,
5318089, 13988082,
-19694008, 2306561,
52817418, 9871289,
-17335868, 15858923,
41198127, 59818649,
53146051, 8743514,
-70093544, 50691612,
98970318, 10635695,
45503999, 26960072,
35234434, 19490884,
-25741957, 59679391,
-8645395, -31476570,
-46031486, -30758421,
-42535468, 12616663,
-30029482, 30527144,
19766544, 5175768,
61828378, -6786856,
45230277, 49952738,
-16483706, -20858734,
-73067055, 27163558,
7952384, 64719561,
-24676306, 13289468,
-59707409, -28903758,
15033402, 81602224,
19502308, -28203092,
28742975, 9410369,
-8934312, 27528594,
-14007973, 41199067,
-6905708, -2132886,
-5849309, 21651496,
7300675, -59435553,
56515551, 2000234,
4010704, -25507318,
21832777, -56737237,
69795260, 37033091,
-11382498, 49073348,
24498519, 7925991,
9863964, -36832383,
-28491366, 81041755,
-85022179, -13492652,
-79824030, 30673144,
-11619089, -4562034,
-20499655, 44096997,
-13696640, 10816645,
-47500028, -15988555,
7620965, 2555556,
6978449, -3528143,
-24149738, 47547079,
25426266, 23753536,
-55134476, 12345268,
-35460761, -20228104,
-8444368, -28592059,
-43568438, 21982258,
41381171, 49331190,
50151281, -27192628,
7916774, -42820734,
-47122468, 57789727,
22105359, 3418444,
-85785714, -26910558,
-17949791, -41971142,
107458893, 41530898,
14737027, 51276696,
-38584287, 59623634,
29754887, 21178468,
-9508872, 2793693,
34740118, 71807941,
-12243269, 42394996,
45029627, -58741904,
33852117, -484271,
7176433, 82815757,
-10041632, -22453230,
8584874, 8721689,
-6403047, -12493248,
-2652829, 44243314,
23483110, -21913766,
-26727452, 2086397,
-26886613, -24691813,
-254967, -6017111,
-24387712, 36395648,
-50026357, 4594091,
29203581, -523725,
-8914574, -31490536,
-52569576, -49596315,
-13241803, 12144386,
-4826966, 16032020,
-78324338, 10795856,
-45551461, -63000946,
-60924397, 22834656,
37192465, 7831538,
-4768580, 41590438,
37337918, 4216482,
18765786, 6030423,
16051425, -20302474,
-22796364, -34790928,
9561895, -9907892,
-44725882, 48859094,
-24292744, 60482704,
-22266734, -44748646,
6658647, 12994195,
-60225788, -765329,
-46562563, 3710991,
6636006, 27273400,
49302457, -33859731,
12297472, -33707843,
-14857079, 9494501,
-1629490, 9722406,
2607466, -8297898,
65696564, -7343868,
-2444370, 30154936,
31501235, -21549102,
-2671209, -6054723,
-26875728, 24089161,
10382549, 10112843,
35293438, 51972292,
-55841663, -1484529,
-36600907, -994913,
-6433416, -12821475,
15549167, -18586779,
-31009226, 31284752,
-21798880, -44152259,
20900828, -10117314,
-44798771, -87227713,
35154604, 26175065,
28968457, 20231341,
-21555746, 31635082,
22146272, -34356825,
43423319, -2275991,
10555522, 2743422,
28842483, -59291581,
4317450, -59769301,
555925, -22157795,
-2442792, 45346018,
-33363502, 71684667,
-25077184, 5596322,
-1033942, -57217938,
33163678, 9278746,
-20099663, 13237634,
49547936, -3306959,
-27306635, 5920676,
21643937, -61668161,
-43953601, -50408526,
-29105957, 27487696,
-15912628, -7870788,
7463089, -54747340,
62791174, -10668253,
3691037, -26719015,
-13802309, 23179408,
17154426, -1409626,
-40235674, 10873019,
-3233325, 16993856,
14959147, -34513738,
-9926232, 3336195,
-5637020, -3904077,
6024474, 23127019,
14130383, 63192751,
56293545, 10919774,
67006487, -3194808,
23386239, 1045947,
-45848179, -20595696,
12181773, -58091395,
-19026855, 16065025,
-35035992, -15026862,
23392109, 12979344,
16241213, 1777001,
-6501203, -16310311,
-12686779, 8203155,
-29741772, 24102453,
-61746769, 5150109,
-54633164, 4489008,
-39385810, -33762265,
-13938876, 43837840,
5874973, 40236363,
7698504, -86481031,
-41637312, -70003612,
23488235, 12956436,
14323610, -28891415,
48815104, -41299051,
-17119008, 88635856,
-223361, -30346748,
-17632725, -41048424,
24081951, 10173868,
36519759, -24498003,
16795748, -38371852,
93005829, -47418885,
-5379084, -19858112,
14411244, 17410980,
-65995443, -50090431,
-18321344, -2908638,
-63364012, -423466,
-3622285, -11605066,
-44162462, 33095104,
-22569779, 21584095,
-30278339, 97977067,
-5194170, -41895559,
31784179, 5271897,
52021957, 26465503,
14396192, -19363691,
-18817143, 17704471,
6016453, 56092746,
-25887543, 26846213,
-31654911, 29654970,
-47230192, -7522403,
-63959138, 9965370,
-2190870, -17482111,
22553572, -5212996,
6917144, -3305056,
-272602, 33459482,
672490, 14578385,
-18738359, -863049,
63286313, -12748474,
-7381138, -8133444,
-47459231, -39094744,
-10160661, 25387453,
-19111728, 39062805,
-4076689, -34341437,
-13091955, 57095869,
-28329574, -16581676,
-58309442, 5795305,
-15083396, 11880328,
-51940011, -8263050,
-3213717, -4890251,
30457842, -39225392,
79510648, -738570,
17440521, 20745958,
13774936, 62608039,
35318894, 2747262,
14387596, 53955343,
43455933, -12773040,
-6242892, -43606941,
4386686, -24292008,
-22066299, -18957702,
-25476789, 20859586,
-19970586, -44810977,
27259607, -4130820,
2333403, -37004327,
-61528328, -92381255,
61316122, 8456283,
21947118, -28794674,
-51833858, 38096475,
-12586568, -9996121,
6968863, 38732911,
-25689761, 35100473,
-3568688, 71366055,
11367214, -22004110,
34677211, -38331513,
-47138020, 31844459,
-34580195, -13576401,
-21587983, -12895946,
5730648, 16173917,
45125314, 14890595,
64970543, 12787600,
24875100, 36988675,
27245514, 28737588,
-4791854, -39544194,
-3350695, 13487862,
-26847958, -19603427,
16550691, -32866102,
41526085, 3862324,
43484908, 2297503,
-9334713, -17780507,
7285580, 18156698,
21163719, 22874727,
-18406237, 18071226,
7705159, -17113950,
11922266, -44362675,
17491393, -20490315,
-20668543, -18968625,
45157668, 2891553,
32712967, 23202936,
-79790220, 71596798,
-36652142, -96097,
-10929000, -3003898,
-67519160, -8555772,
52601956, -29333692,
7829496, 14191107,
21690247, -4476137,
-37896777, 18105250,
6611509, 29365865,
56937497, -41969068,
24361646, 29135667,
26592754, -27004813,
20245287, -25256194,
-1959760, -25025310,
-37200664, -10390254,
71948399, -51066191,
-45393155, 27733778,
15335092, -20568440,
13125649, 32203138,
69558785, 66202475,
-10848764, 9897143,
49262348, -13175197,
-16857703, 19324889,
7032785, -38299676,
25326886, 2049131,
-31815945, 413313,
20574125, -5641100,
59072674, -23063600,
2978368, -33240700,
87092861, -1669726,
-22665005, 24135722,
93509632, -9498032,
-564615, -47813930,
9115091, 15487008,
-30672183, 36624123,
-65477141, -35040724,
-10650786, -95388005,
19741194, 33447868,
27816504, 2568061,
-56198659, -62637293,
-64501465, -20589469,
-14651950, 39236993,
1509082, -19294236,
81087946, -8885043,
-10398242, 158451,
6294242, -1322386,
31799500, -16958159,
-17639658, -38850399,
-37433503, 23837985,
-53429388, 24433399,
39421228, 29087797,
16278728, 81589928,
55213162, 3697821,
-15241537, 887483,
33848643, 32558665,
68766567, -176487,
20200444, 47296374,
599269, 58983678,
-54036922, 29696058,
41565618, 38280976,
22937369, 13529689,
-26196477, 6409185,
17816705, -23274247,
71621858, 370314,
11890371, -37097323,
7774554, 64020964,
43217452, -5550292,
-452594, -24576263,
-44739631, -33243741,
-18667771, 30007906,
25353614, 15039992,
-30596738, 29837229,
46026065, 36015207,
8240301, -3514305,
3987761, 51919409,
12908055, 5698685,
-2353923, 26979382,
-19404847, -57848827,
15747358, 5842934,
43610275, -16243188,
54854720, -24549337,
-23582344, -71534849,
27086914, -60745798,
-34475541, -1756182,
43436081, -2892808,
500980, -39920968,
7338525, -25304780,
57485066, 31785375,
-69753120, -6127977,
3788861, -2223576,
-36456602, 30367357,
-52288227, 48929609,
21387782, -37513319,
-13575324, 60844083,
-13533352, 5058436,
2821137, -9495694,
-14607892, 55368916,
-18878481, 22359945,
29462882, -11621968,
-27335114, -8859774,
-8669220, -21620749,
16552377, -30384890,
-26933934, 24047770,
-279463, -246168,
21057788, -94448992,
5180189, -5017919,
86595085, 19377502,
-43830352, 25270399,
34343839, -5603084,
26098486, -19522505,
-27980518, 12272792,
-19685154, -18418680,
2203312, 19419182,
-414118, -65625727,
-2583240, 17515621,
-52297507, 53725191,
57129998, 24580610,
-15736508, 18647782,
3174882, -27291364,
9632517, -18084984,
30848387, 43885052,
17117326, -16192649,
8235588, -58802363,
-46993617, -31090522,
32533390, 30951934,
53475622, 1375777,
-48248496, 13879701,
-51480228, 20040185,
-2506836, 64567789,
2733325, 23961853,
-28294436, -77589160,
-18946180, 46329123,
-946454, 46664248,
-41731716, -15230487,
24596722, -21082408,
1999168, 34333728,
5004437, -16411831,
53548077, -13502467,
-26080193, 46965556,
52018676, 9414069,
35399978, 63111602,
-5591986, -26832584,
10552325, -18813929,
47632895, 57340314,
10983970, -21636235,
15960267, -47731033,
13379960, -25365031,
-2441758, 5285489,
44116823, 12695192,
32825610, 5994996,
57784562, -20225765,
-13834552, -33333178,
18962719, 39894490,
24825275, 80128295,
7386614, 76018333,
44050494, 77211200,
21110825, -9062257,
-37177884, 16872401,
-14998877, -3999383,
-24360274, -63387,
11879793, -14517291,
-17004446, -6537148,
-70590038, 33062890,
-22303107, 15723489,
48657608, -45798484,
-11066436, 9183476,
90659796, 88807950,
-54859446, -1803677,
-17996086, 15854851,
18361746, -69794362,
50083449, -26927230,
-15275429, -15327436,
-16656945, 6504760,
41448457, 29847521,
1373259, -53407561,
25114395, -10803725,
41297572, -23615527,
10230841, -24974111,
36163997, 12458332,
25674206, 48226969,
-44277762, 15432129,
-17085627, 22170694,
18626596, 37727524,
-65687007, 32863606,
-25516575, -44172094,
-82003220, -778845,
-22124641, 4514638,
-3851354, 80803273,
10068996, 30256185,
-19595640, 2556349,
-103137755, 12138070,
52044321, -69077473,
-13669027, -78250026,
47918926, -12445499,
-45407274, 43140391,
30332200, 18691351,
18175457, -6047479,
-15603489, -1197077,
};


#pragma DATA_SECTION (rtest,".test")
LDATA rtest[2*NX] ={
404699852, 1462728451,
-126490022, 139128768,
-931574323, 565844584,
583713506, -437125534,
-625414788, 519133171,
-424512635, -608062671,
-1068633900, 294633917,
-1211606331, 704492569,
269973374, 694903777,
172487831, -717759549,
-502148781, 1406760047,
-876865426, 1044893354,
528524950, -1024393761,
-812866169, -1701454306,
64463403, 972925168,
478154871, 230877711,
-417712251, 202295588,
1059592003, -276671338,
1059909925, -1004671258,
1232542368, 141216251,
-65224214, -1003890348,
-1927698223, 1490626869,
257105891, -1311859180,
-140134443, 1358153845,
-1784633457, 1288302151,
-122070010, 268611234,
378269837, -387337959,
315507563, -1329513628,
-353980610, -103030398,
-1613132531, 855150611,
753807910, -687766907,
-1155893511, -64772015,
-295002320, 230061648,
255579401, -9098710,
947834923, 390999681,
-531649272, 233535199,
508598886, -584616126,
-180589975, 855131908,
1274180008, -346872833,
40089857, 815812652,
96980571, -715593224,
337570861, 203872005,
-796066012, 1002454080,
-106137794, 1694480205,
-2095825684, 75389702,
908819089, 1188371462,
702056729, 1046194020,
-228746382, -560853862,
-506673255, 454958049,
617308977, 834516435,
329970902, 38160360,
197271995, -385116912,
319526655, 1256848385,
-146493964, -1160886176,
-390939766, 657868690,
-1593105555, -454350337,
-182231652, -1247878176,
1957067483, 803286942,
-479825585, -234754989,
597550263, 1113022705,
1227545776, 250752786,
729590352, 490822000,
-132785808, 764139584,
557343537, 900971351,
983954102, -685948100,
-737966655, 183942175,
1195792727, -50713514,
-581980870, -313611081,
-58292668, -59879827,
589147721, 968822911,
-949940385, 674256736,
-94724949, -1025847083,
-1146862499, 617049450,
912912266, -547611268,
219694515, -1081789197,
-554615544, -684639099,
-147215305, -220953921,
310305938, 783548179,
-1112780258, -62050096,
-1434454870, 777528551,
-2086188972, 484525584,
-74761772, -438669291,
-402910143, 88938064,
960282276, -962382638,
-316499651, 256998414,
-1010850022, 571812058,
-222888526, -1367045861,
1513766185, -534065284,
-662457829, -40057462,
-371818441, 289363489,
376205422, -383654042,
-907780954, 1051681327,
206011897, 54405305,
-278475172, 386862783,
316318078, -467810924,
702614368, 1942049207,
-995815978, -562955016,
-236054745, -981259246,
514010261, -808252444,
-1105886572, -519984690,
-348690351, -73480480,
757436034, 4998831,
-163460943, 820356226,
559639878, 513351479,
533815468, 1187967784,
722881707, 561689905,
-275361109, -786412339,
428567790, 312520874,
-283404919, -953888431,
83474154, -1307480638,
-1678126383, -419587823,
-374690157, 435053350,
106832266, 525551989,
-438995451, -505559804,
-639136518, -970639956,
374702714, -738691079,
-837214016, 1112769373,
-719438014, 665212198,
531885768, -54739042,
524136385, 377018135,
-522355870, 480161025,
-660248013, 862857195,
-1626090898, -224514715,
-1242877536, -388389804,
-1162940562, 1379367561,
1299207612, -167957970,
879200935, -679823155,
-1165584299, -210639491,
-815321608, 488102407,
-903145067, -347102982,
-689296587, 211826722,
92140161, 1916050915,
423073964, -230921141,
1070217691, -837601758,
604754130, 126865740,
748271995, -381008883,
-789777861, 43246101,
-791352038, 1336893519,
-94399894, 721197130,
-151269590, 406991430,
1053848594, 981023087,
-97055332, 124574573,
-265957848, -435483522,
-98246969, 1658409310,
-59225298, -705043157,
-640496391, -883273990,
571283042, -363817699,
2142556665, 994575761,
494664201, -115262594,
650982765, -1355549894,
-390986793, 165106103,
1297194285, -152897350,
-937880317, -248707864,
-539758334, 202140803,
-162527765, -281393988,
717105803, -597099129,
1925675814, 772324467,
162422485, 1419543857,
-228635134, 631175878,
145450858, 1152771512,
359301795, -180862452,
218695234, 720220008,
643271676, 468901419,
373657472, -1188509184,
247004717, -634985121,
250717661, -1210090049,
328031963, 2111487230,
707182943, 370961735,
-858260939, -169221255,
-894487228, -734786482,
-774330522, -1509436312,
745559188, 927229085,
-434956175, -159746588,
-316396255, 1027278339,
-1266670626, -489871335,
395101984, 563032972,
-910922713, 3627015,
-606646132, 759863482,
-463033236, 1131468270,
655346455, -989411672,
-624938670, -1309646280,
342897917, -385578589,
206691919, 53006436,
-593327048, -992899676,
523055957, -798886835,
483238845, -175989642,
564225053, -276221614,
837103317, 1204517499,
76618965, 1316502496,
1303192625, 712466684,
-519859093, 854558691,
-1008096344, -39986767,
470891111, 663733366,
615151175, 299169349,
118695403, -864997665,
885410571, -844731836,
358992297, -330279248,
-966885181, 406773904,
137318750, 816677894,
-1172855135, 1060024434,
361409632, 462393112,
-1762288749, 499969081,
-244270089, 321847579,
478132136, 473796622,
-277607872, 100584832,
45397184, 1013313574,
696780918, 207083828,
680724574, -211695447,
809399721, -442702829,
534543394, -88401428,
-589637793, 463226481,
1524308434, 474727550,
-879072120, -509975139,
-357012610, -1592772230,
-502942893, 43736280,
603467237, 93532505,
1576880826, -834510121,
451912350, 141947333,
515138647, -1815836284,
-520087383, -1233496847,
1307189247, 1051994411,
830001325, 1688149330,
522375679, -126297697,
-507113013, 1417104617,
1633627560, 199262690,
-266130423, -856768158,
772172830, 47868443,
500142490, -897784889,
499043927, 385440920,
-326708186, -497194436,
-1163496947, 509854669,
-916152166, -1161324769,
841258936, -472170845,
-416705203, -973396995,
-1048695048, 466941305,
-529878745, -529475170,
385982313, -447388794,
-637706831, -362398242,
76851810, 23333946,
937412177, 1051290713,
615833883, 799881301,
-853162304, -644106432,
-691842079, 947509088,
242838432, 448020891,
-876804851, -708664624,
27043869, -1157574849,
824940788, -1636373845,
-395032542, -345277822,
-39346317, 1694655888,
-615632045, -993962563,
-316354120, -157543301,
1210081139, 742683794,
-130835506, -345244238,
-820755777, -442440785,
555869248, 657552129,
708996319, 396778595,
675050196, -197608841,
649105111, 616490650,
-283644925, -908958576,
-573077379, 725757041,
-171115618, 74240624,
-658342012, -158954358,
49646855, -219508220,
-384731299, 497914080,
-752403702, -164362776,
-729600404, 213250581,
-546305701, 147227510,
56324173, 390127482,
-1333188253, 796850266,
1436760163, -208307192,
-277172350, 685806773,
-511682226, -20962810,
-919586576, 643668598,
-470425772, 540273153,
98886872, 105462689,
-219219849, -1249173692,
1232506229, 525493845,
515622045, 1011154504,
1128725077, -526819947,
-403316607, 1287888147,
-956265164, -463055280,
-360574960, -3220109,
662928665, 431139464,
-103735302, 261272580,
-359261818, 118869757,
685402971, 686448562,
97550852, 512117537,
1896765583, 598211219,
200627574, 243978105,
306915819, -370550899,
177584826, 912528321,
1232378847, 221757037,
-49592413, -572992305,
787855017, 495563753,
1349434766, -104604216,
80956501, -301536485,
-507891903, -818560911,
427353507, -109143500,
247661482, 280125849,
-881154868, 287453851,
676114727, 243694101,
702239059, -1372118684,
-646383794, -604439496,
518815006, 277014747,
1266655875, -65526404,
-558480593, 491676419,
203014823, -1136603819,
434487569, 437151023,
-200611754, 697447237,
141931065, 739466591,
-446141777, -407841652,
298588800, 256324208,
104310467, -700523733,
402422732, -526712244,
-762364107, -505818237,
-317108400, 27665193,
-160313399, 483973428,
1025251877, 1393455016,
-137742738, 977352853,
149895023, -296765925,
-1277541368, -651331196,
-218031117, 644397523,
339111157, -880630838,
-262552916, 120032714,
1109137582, -339955763,
-662079734, -535932116,
-370398310, 434241491,
1052630301, 2.249173e+009,
669376228, -762139426,
744268891, 254362942,
662053148, -185684584,
-536657158, -350125480,
64228285, 1311933158,
-1117166085, -60562519,
-1604845055, -639242064,
236125029, -686626443,
1240527928, -1151028031,
1422292141, 503698341,
303365886, -1479277761,
-500642515, -764165041,
-1475286876, -833508103,
263044397, 1450231055,
-1020723805, 248467155,
538465819, -492936945,
1173857885, 331074805,
-579251297, 777396925,
-162222036, 108701126,
685209199, 162305597,
-1371360207, -700895014,
-443477054, -417396071,
596478847, 402349547,
-585498131, -179742875,
745605262, -8203378,
1514068701, -305945359,
-25623697, -1352146895,
-618029014, 389974928,
828116992, -858243710,
2006818182, -540858208,
206087483, 305446035,
-628677437, -924432120,
14040817, 460453317,
696452640, -1383447330,
214065792, -64959712,
472842881, 753849648,
-114037189, -1232694900,
-699941621, 1181012359,
1184183046, -910241763,
-630788348, 400550229,
725714436, -1604560658,
1042357039, 556433950,
120597201, -144388378,
-449802852, 576867128,
-348261422, 1484250604,
-436819638, 448131580,
-305526350, 34904988,
799648983, -1056684352,
1369959728, -406133092,
-718990644, -249527989,
-1368906519, 2009464334,
284814379, -687106953,
602048628, 150060203,
707017872, 553472260,
-435257668, 1164929146,
343260909, 394019452,
259535548, -200122717,
858125396, 564846808,
583444899, 6657663,
431187926, 998600786,
101565673, 309493089,
395851701, 164267580,
933049867, 1186605081,
-470362869, 427420826,
-914575261, -823470790,
-850936712, -879229175,
-75332539, -631414798,
1245410315, -36237272,
-1207898358, 2.235529e+009,
-358179265, 583217980,
-98883752, -588967855,
-872734452, 1254555702,
-70438969, 1674599717,
2126838978, 1248342140,
-671727441, 203480671,
-679689906, 118961203,
1175655583, -936890425,
445368089, 1464221876,
-1162184000, 1034830484,
774975713, -104293816,
-578645368, 948991616,
-523470412, -242984830,
-709680057, 266819098,
-1075139805, 5210258,
147492807, 1060914566,
-180479624, 485532352,
88016121, -207982141,
159379947, -240386876,
682167464, 579365164,
576037740, 51411344,
420081745, 173573801,
783202444, 353956120,
1537203376, -467552261,
183813365, -350511907,
779828141, -489400097,
760011209, -2.558766e+009,
931571220, -349432217,
-2544813, 140148269,
-154323787, -118621502,
162193115, 437063843,
170015387, 280212225,
376949803, 858197112,
277942927, -12869398,
-1255950224, 145818932,
-628417170, 971502058,
810930214, -1117012066,
-78021676, 165401876,
1110566026, -1351208181,
1100345813, -125160738,
-1240937214, -1624417526,
773228298, -538212627,
1215659180, -931535950,
14381266, 630825753,
-928075175, -212350866,
-1026167594, -373057760,
-36858456, 370992797,
468230344, -1802733776,
44546723, 1367084316,
-830712304, -659463065,
-607180142, 516020964,
-226176969, -53996914,
-997454006, -369996991,
-806638866, 579431765,
510312169, 749191612,
-734278558, -1654814558,
1012177416, 430606970,
87051792, 499364808,
368903401, 1900137520,
314186584, 559928352,
-1923432036, 1124922431,
304876881, -714917336,
-521686242, -868690031,
-171808622, -295248703,
823611005, 1284548617,
-485151680, 216537239,
1659756813, 978902553,
-994633959, -209521759,
-481976895, 177046278,
362711377, 852212042,
517774129, -86135634,
303260019, 756347388,
-82297760, 478060171,
513948683, -874469029,
-983460972, -904321519,
1179764019, 155643319,
-906600601, -1177213462,
-463042950, 486520355,
-1394368214, 428300587,
-342630616, 1563276081,
-481202315, -1127145268,
1263611689, 1181515826,
1569786655, -1524448,
700028436, 1394349328,
299416875, -264591620,
464248274, 657688531,
-1352513178, 1449029697,
23053219, 356533456,
1769916677, -651493055,
-385538479, 269903276,
-74240583, 747133538,
931886566, 519596656,
1489056869, 913704591,
676353656, -26503669,
1506631135, -887520378,
2039227759, 472728174,
916448504, 33404185,
1510177904, 693604308,
-317694001, -286292272,
-1195418418, -1754204085,
-450478890, 630343264,
440977712, -234308388,
287306777, 1099784254,
-1008042074, 456695724,
971037658, 135273324,
93364551, 649375810,
476844708, 198678374,
-856280286, 860454229,
-220409571, -2103767,
-554473545, -683874309,
-926040186, -200061682,
-1443596701, 189369057,
402782586, -727371124,
455240395, -120918853,
315342922, 2.531483e+009,
};
