/* Test for sqrtv: rand */
#define NX 40
#define FNAME "t2"
#define MAXERROR 20

DATA x[NX] ={
20166,
25950,
30205,
24189,
5775,
13294,
30653,
30045,
13443,
29283,
1896,
11562,
26645,
323,
4551,
6644,
6511,
19785,
8919,
6514,
500,
24470,
14584,
30533,
15269,
13718,
27728,
17208,
6640,
22024,
27463,
643,
22324,
12434,
27256,
16476,
23247,
14053,
9981,
6214,
};

DATA rtest[NX] = {
25706,
29160,
31460,
28153,
13757,
20871,
31693,
31377,
20988,
30976,
7884,
19465,
29548,
3253,
12212,
14755,
14607,
25462,
17095,
14610,
4049,
28317,
21861,
31631,
22368,
21201,
30143,
23746,
14750,
26864,
29998,
4592,
27046,
20185,
29885,
23235,
27600,
21459,
18085,
14270,
};

DATA r[NX];