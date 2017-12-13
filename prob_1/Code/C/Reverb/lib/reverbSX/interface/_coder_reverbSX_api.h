/*
 * File: _coder_reverbSX_api.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 26-Nov-2017 14:57:15
 */

#ifndef ___CODER_REVERBSX_API_H__
#define ___CODER_REVERBSX_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_reverbSX_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void reverbSX(real_T unusedU0[57], int32_T unusedU1, int32_T unusedU2,
                     real_T att, real_T Y[57]);
extern void reverbSX_api(const mxArray *prhs[4], const mxArray *plhs[1]);
extern void reverbSX_atexit(void);
extern void reverbSX_initialize(void);
extern void reverbSX_terminate(void);
extern void reverbSX_xil_terminate(void);

#endif

/*
 * File trailer for _coder_reverbSX_api.h
 *
 * [EOF]
 */
