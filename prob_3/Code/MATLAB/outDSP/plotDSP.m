function [ outfirDSP ] = plotDSP(x, t, fs)

% Low
% outfirDSP = [-25 -44 -65 -85 -103 -117 -126 -127 -115 -89 -50 3 67 139 215 288 350 390 401 377 315 221 101 -38 -185 -328 -453 -547 -594 -587 -520 -397 -224 -13 219 449 653 806 885 875 774 585 323 10 -325 -650 -931 -1133 -1228 -1200 -1041 -760 -379 70 544 994 1368 1618 1707 1613 1335 894 328 -310 -955 -1539 -1994 -2260 -2293 -2073 -1607 -930 -103 794 1668 2420 2954 3192 3082 2611 1802 721 -531 -1826 -3025 -3981 -4562 -4664 -4219 -3216 -1696 241 2446 4733 6891 8705 9974 10536 10282 9176 7261 4656 1553 -1805 -5137 -8155 -10581 -12184 -12795 -12331 -10805 -8328 -5098 -1389 2474 6146 9288 11602 12864 12943 11819 9585 6439 2666 -1386 -5340 -8819 -11487 -13083 -13445 -12527 -10405 -7272 -3418 792 4958 8676 11581 13386 13908 13087 10997 7831 3889 -451 -4772 -8654 -11714 -13652 -14269 -13499 -11410 -8199 -4171 286 4738 8750 11924 13946 14612 13851 11735 8466 4360 -187 -4729 -8824 -12067 -14136 -14824 -14061 -11915 -8592 -4413 216 4843 9013 12313 14415 15111 14329 12141 8761 4516 -183 -4877 -9107 -12459 -14603 -15326 -14556 -12366 -8969 -4693 46 4785 9061 12453 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 14618 12431 9028 4742 -6 -4752 -9032 -12427 -14608 -15359 -14608 -12427 -9032 -4752 -6 4742 9028 12431 14618 15371 ];

% Alta
% outfirDSP = [21263 -27139 -30991 -16522 19350 32584 18088 -15100 22720 -13265 23143 31502 10413 1946 1872 1790 12022 -27837 24129 -26088 23618 -13743 23118 -29327 21535 -22282 18444 -10035 11923 -8684 9689 -21192 10415 5025 12212 -29553 18284 -5224 10380 -21345 20612 -4020 -17115 16402 14024 -26987 -983 13423 9990 -19383 8328 -8297 17389 -20175 20464 -23646 12634 7982 5227 -29092 8099 10620 5183 -6684 10135 -32728 26636 -16157 30456 -26581 16081 -19192 12154 -17524 -32614 -21280 15219 -20682 6896 -6908 19089 -11688 15823 -25458 10334 -3827 11674 -14696 22195 -15126 -4889 -4368 25030 -26299 25078 -25679 23288 -20597 12832 -7521 11386 -17678 23117 -24127 24257 -21551 3167 8128 2018 -1542 -4498 -2084 128 3374 2623 1054 -2883 -2671 -1603 1249 3062 2389 -774 -2079 -3382 -131 1655 3462 978 -640 -3466 -1873 -46 2871 2662 892 -2431 -2719 -1561 1219 2376 2872 -356 -2404 -3248 -315 1606 2837 2248 -963 -3603 -2281 378 2633 2559 1122 -2068 -2788 -2222 1409 2378 2969 127 -2567 -3589 -661 1969 3238 1831 -844 -3673 -1990 -413 3228 2440 1464 -2353 -2966 -2231 1660 2516 3004 -488 -2374 -3211 -609 1635 3525 1315 -645 -3164 -2381 -251 3066 2549 953 -1831 -2756 -2428 1514 2391 3105 -463 -2141 -3198 -805 1452 3616 1381 -338 -3567 -2350 52 2534 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 957 2975 2536 7 -2525 -2971 -961 1845 3135 1845 -961 -2971 -2525 7 2536 2975 957 -1856 -3149 -1856 95];

% Banda
% outfirDSP = [12 2 -2 4 18 30 28 1 -47 -101 -133 -115 -37 83 202 264 227 87 -114 -298 -379 -310 -102 169 387 454 330 62 -237 -434 -441 -260 24 275 379 296 81 -149 -275 -236 -60 155 289 271 104 -128 -311 -361 -262 -68 132 257 281 228 151 84 26 -57 -191 -355 -473 -443 -204 207 642 900 818 375 -277 -865 -1122 -920 -345 335 804 861 525 31 -314 -304 30 428 541 153 -647 -1463 -1764 -1181 242 1974 3188 3148 1609 -967 -3534 -4888 -4232 -1612 2007 5101 6240 4758 1116 -3226 -6414 -7003 -4623 -190 4457 7329 7156 3952 -971 -5552 -7855 -6898 -3063 2062 6359 8064 6491 2298 -2807 -6773 -8039 -6140 -1862 3100 6826 7909 5976 1801 -3017 -6670 -7812 -6041 -2035 2714 6451 7798 6258 2396 -2365 -6258 -7827 -6472 -2680 2135 6162 7863 6576 2770 -2112 -6200 -7911 -6572 -2686 2250 6323 7949 6493 2520 -2427 -6426 -7930 -6364 -2347 2560 6460 7857 6229 2219 -2625 -6444 -7786 -6152 -2180 2607 6388 7731 6136 2220 -2524 -6296 -7671 -6137 -2284 2421 6194 7605 6123 2316 -2366 -6144 -7577 -6123 -2334 2341 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 7592 6143 2351 -2335 -6126 -7574 -6129 -2346 2330 6112 7557 6112 2330 -2346 -6129 -7574 -6126 -2335 2351 6143 0];

outfirDSP = importdata('dspIirLow.txt');

outfirDSP = outfirDSP / ( 2^15 );

subplot(221); 
plot(t,x);
subplot(222);
plot(outfirDSP);

subplot(223); 
periodogram(x, rectwin(length(x)), length(x), fs);
subplot(224); 
periodogram(outfirDSP, rectwin(length(outfirDSP)), length(outfirDSP), fs);
end
