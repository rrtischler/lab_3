/* This is a test for power: rand */
#define NX 256
#define FNAME "t8"
#define MAXERROR 10

DATA x[NX] ={
59,
-20,
118,
-110,
13,
-54,
91,
-43,
46,
-115,
-37,
-1,
-17,
15,
29,
-99,
101,
65,
74,
80,
43,
-77,
-59,
32,
9,
-113,
-106,
-59,
-24,
-7,
104,
24,
-44,
-6,
24,
-87,
84,
116,
24,
-121,
79,
28,
51,
-105,
-20,
-32,
-86,
85,
86,
-13,
116,
-91,
94,
68,
-15,
30,
115,
35,
-65,
-38,
-80,
-3,
-24,
-10,
28,
-110,
-48,
27,
-84,
30,
-66,
22,
1,
-10,
10,
113,
-41,
-26,
-50,
-23,
-55,
-28,
0,
56,
-50,
-100,
-15,
-9,
-125,
41,
57,
-56,
-61,
53,
72,
124,
-7,
103,
-13,
77,
84,
-86,
-28,
5,
55,
17,
-11,
-15,
-106,
-15,
-35,
-51,
90,
66,
115,
14,
-125,
24,
80,
122,
-72,
52,
5,
110,
54,
-70,
-13,
-84,
120,
-37,
-116,
65,
101,
-55,
-64,
110,
-95,
112,
51,
89,
-75,
-12,
-108,
89,
15,
-47,
-33,
94,
-33,
-110,
-77,
-116,
17,
-97,
5,
-99,
69,
-32,
82,
-117,
25,
114,
-55,
99,
-102,
-112,
-69,
110,
-112,
-61,
127,
-74,
-1,
-54,
44,
117,
68,
42,
-95,
-104,
-125,
-55,
81,
124,
-124,
81,
31,
15,
-66,
82,
-61,
64,
40,
-74,
26,
26,
40,
-82,
34,
-85,
10,
31,
47,
45,
96,
-125,
-49,
71,
-50,
109,
45,
-109,
-110,
-125,
-70,
4,
-11,
52,
21,
2,
-109,
-79,
-31,
-58,
69,
-48,
35,
124,
0,
114,
83,
106,
-100,
79,
104,
-88,
-97,
67,
56,
38,
65,
41,
98,
-59,
-21,
-74,
-119,
-108,
89,
-41,
-9,
105,
-70,
92,
40,
100,
};

LDATA rtest = 2732146;
LDATA r;