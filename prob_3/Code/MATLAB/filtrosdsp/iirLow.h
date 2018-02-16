/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.0 and the Signal Processing Toolbox 7.2.
 * Generated on: 15-Feb-2018 14:57:25
 */

/*
 * Discrete-Time IIR Filter (real)
 * -------------------------------
 * Filter Structure    : Direct-Form II, Second-Order Sections
 * Number of Sections  : 21
 * Stable              : Yes
 * Linear Phase        : No
 */

/* General type conversion for MATLAB generated C-code  */
#include "tmwtypes.h"
/* 
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2016a\extern\include\tmwtypes.h 
 */
/*
 * Warning - Filter coefficients were truncated to fit specified data type.  
 *   The resulting response may not match generated theoretical response.
 *   Use the Filter Design & Analysis Tool to design accurate
 *   int16 filter coefficients.
 */
#define MWSPT_NSEC 43
const int NL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
3,1,3,1,3,1,2,1 };
const int16_T NUM[MWSPT_NSEC][3] = {
  {
      818,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      799,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      781,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      764,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      749,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      734,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      720,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      707,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      696,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      685,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      675,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      667,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      659,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      652,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      646,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      641,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      637,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      634,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      632,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
      631,      0,      0 
  },
  {
    32767,  32767,  32767 
  },
  {
     4544,      0,      0 
  },
  {
    32767,  32767,      0 
  },
  {
    32767,      0,      0 
  }
};
const int DL[MWSPT_NSEC] = { 1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,
3,1,3,1,3,1,2,1 };
const int16_T DEN[MWSPT_NSEC][3] = {
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  31989 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  30491 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  29072 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  27736 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  26482 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  25310 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  24222 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  23216 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  22291 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  21446 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  20680 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  19991 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  19379 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  18843 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  18380 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  17990 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  17673 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  17427 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  17251 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -32768,  17146 
  },
  {
    32767,      0,      0 
  },
  {
    32767, -23679,      0 
  },
  {
    32767,      0,      0 
  }
};
