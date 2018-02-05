/* Test for divQ31byQ15: rand */
#define NX 64
#define FNAME "t4"
#define MAXERROR 3.000000e-004

LDATA x[64] = {
-645934454, 
-585169684, 
-1120161002, 
-955969546, 
-1887536934, 
-1179496919, 
-610136717, 
-230120892, 
-1561000544, 
-1600370736, 
-288614332, 
-1648515010, 
-419034735, 
-196714776, 
-1649494376, 
-1633563813, 
-2040636687, 
-1979155110, 
-771343027, 
-1737557843, 
-335287695, 
-1774035691, 
-1780708856, 
-12250341, 
-1203039963, 
-1417236225, 
-1472707097, 
-1363483769, 
-1303008130, 
-877192937, 
-1890329728, 
-2065602660, 
-1162652028, 
-279457735, 
-141225999, 
-1579583373, 
-1803241273, 
-273041254, 
-1636639561, 
-760571592, 
-71108722, 
-719554737, 
-278354625, 
-2126164903, 
-1853257128, 
-389218895, 
-1223709080, 
-235532303, 
-569280275, 
-671467468, 
-1404213843, 
-1790926744, 
-1813308167, 
-1737064477, 
-1240275892, 
-309289811, 
-1094679807, 
-395277070, 
-1157987958, 
-1165322584, 
-1179636633, 
-1262249943, 
-211291291, 
-2135492209, 
}; 

DATA y[64] = {
-7100, 
-10459, 
-17659, 
-14162, 
-6744, 
-30829, 
-13014, 
-31121, 
-19157, 
-22774, 
-4117, 
-32277, 
-7604, 
-956, 
-325, 
-6919, 
-18395, 
-16440, 
-25757, 
-11683, 
-22282, 
-1308, 
-8958, 
-19270, 
-8371, 
-23988, 
-18353, 
-2184, 
-10377, 
-25803, 
-5268, 
-12164, 
-28385, 
-25981, 
-12872, 
-12128, 
-20629, 
-13922, 
-17976, 
-31330, 
-31878, 
-22522, 
-32347, 
-20187, 
-10384, 
-29726, 
-31611, 
-12702, 
-12828, 
-32252, 
-32233, 
-26540, 
-13536, 
-30882, 
-20724, 
-12077, 
-9253, 
-10071, 
-30013, 
-17880, 
-18291, 
-21193, 
-27735, 
-10629, 
}; 

// Floating point representation of numerator
// -3.007867e-001, 
// -2.724909e-001, 
// -5.216156e-001, 
// -4.451580e-001, 
// -8.789529e-001, 
// -5.492461e-001, 
// -2.841170e-001, 
// -1.071584e-001, 
// -7.268975e-001, 
// -7.452307e-001, 
// -1.343965e-001, 
// -7.676496e-001, 
// -1.951283e-001, 
// -9.160246e-002, 
// -7.681057e-001, 
// -7.606874e-001, 
// -9.502455e-001, 
// -9.216159e-001, 
// -3.591846e-001, 
// -8.091134e-001, 
// -1.561305e-001, 
// -8.260997e-001, 
// -8.292072e-001, 
// -5.704509e-003, 
// -5.602091e-001, 
// -6.599520e-001, 
// -6.857827e-001, 
// -6.349216e-001, 
// -6.067604e-001, 
// -4.084748e-001, 
// -8.802534e-001, 
// -9.618712e-001, 
// -5.414020e-001, 
// -1.301326e-001, 
// -6.576348e-002, 
// -7.355508e-001, 
// -8.396997e-001, 
// -1.271447e-001, 
// -7.621197e-001, 
// -3.541687e-001, 
// -3.311258e-002, 
// -3.350688e-001, 
// -1.296190e-001, 
// -9.900727e-001, 
// -8.629901e-001, 
// -1.812442e-001, 
// -5.698339e-001, 
// -1.096783e-001, 
// -2.650918e-001, 
// -3.126764e-001, 
// -6.538880e-001, 
// -8.339653e-001, 
// -8.443874e-001, 
// -8.088837e-001, 
// -5.775485e-001, 
// -1.440243e-001, 
// -5.097500e-001, 
// -1.840652e-001, 
// -5.392302e-001, 
// -5.426456e-001, 
// -5.493111e-001, 
// -5.877809e-001, 
// -9.839017e-002, 
// -9.944161e-001, 


// Floating point representation of denominator
// -2.166713e-001 
// -3.191542e-001 
// -5.389049e-001 
// -4.321713e-001 
// -2.057893e-001 
// -9.408174e-001 
// -3.971309e-001 
// -9.497312e-001 
// -5.846251e-001 
// -6.950013e-001 
// -1.256328e-001 
// -9.849905e-001 
// -2.320496e-001 
// -2.915506e-002 
// -9.917407e-003 
// -2.111383e-001 
// -5.613415e-001 
// -5.016887e-001 
// -7.860367e-001 
// -3.565077e-001 
// -6.799644e-001 
// -3.990140e-002 
// -2.733682e-001 
// -5.880468e-001 
// -2.554342e-001 
// -7.320527e-001 
// -5.600757e-001 
// -6.661989e-002 
// -3.166677e-001 
// -7.874401e-001 
// -1.607618e-001 
// -3.712154e-001 
// -8.662272e-001 
// -7.928673e-001 
// -3.928011e-001 
// -3.701121e-001 
// -6.295232e-001 
// -4.248522e-001 
// -5.485752e-001 
// -9.561047e-001 
// -9.728149e-001 
// -6.873149e-001 
// -9.871374e-001 
// -6.160327e-001 
// -3.168840e-001 
// -9.071575e-001 
// -9.646617e-001 
// -3.876045e-001 
// -3.914596e-001 
// -9.842402e-001 
// -9.836451e-001 
// -8.099254e-001 
// -4.130815e-001 
// -9.424189e-001 
// -6.324320e-001 
// -3.685488e-001 
// -2.823656e-001 
// -3.073306e-001 
// -9.159209e-001 
// -5.456448e-001 
// -5.581717e-001 
// -6.467495e-001 
// -8.463936e-001 
// -3.243553e-001 


float rtest[64] = {
1.388194e+000, 
8.537127e-001, 
9.679087e-001, 
1.030005e+000, 
4.270689e+000, 
5.837911e-001, 
7.153794e-001, 
1.128295e-001, 
1.243356e+000, 
1.072263e+000, 
1.069688e+000, 
7.793272e-001, 
8.408683e-001, 
3.139780e+000, 
7.744396e+001, 
3.602573e+000, 
1.692723e+000, 
1.836953e+000, 
4.569539e-001, 
2.269368e+000, 
2.296061e-001, 
2.069544e+001, 
3.033206e+000, 
9.700331e-003, 
2.192920e+000, 
9.015053e-001, 
1.224417e+000, 
9.526150e+000, 
1.915999e+000, 
5.187343e-001, 
5.475350e+000, 
2.591137e+000, 
6.250013e-001, 
1.641271e-001, 
1.674128e-001, 
1.987346e+000, 
1.333815e+000, 
2.992586e-001, 
1.389249e+000, 
3.704246e-001, 
3.403705e-002, 
4.875026e-001, 
1.313060e-001, 
1.607109e+000, 
2.723272e+000, 
1.997917e-001, 
5.906905e-001, 
2.829427e-001, 
6.771537e-001, 
3.176789e-001, 
6.647412e-001, 
1.029667e+000, 
2.044096e+000, 
8.582832e-001, 
9.131977e-001, 
3.907749e-001, 
1.805197e+000, 
5.988928e-001, 
5.887280e-001, 
9.944861e-001, 
9.840811e-001, 
9.088098e-001, 
1.162448e-001, 
3.065672e+000, 
}; 

DATA r[64];
DATA rexp[64];
