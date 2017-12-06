/*
 * File: _coder_distortion_api.h
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 26-Nov-2017 14:16:23
 */

#ifndef ___CODER_DISTORTION_API_H__
#define ___CODER_DISTORTION_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_distortion_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void distortion(int32_T d, real_T Y[57]);
extern void distortion_api(const mxArray * const prhs[2], const mxArray *plhs[1]);
extern void distortion_atexit(void);
extern void distortion_initialize(void);
extern void distortion_terminate(void);
extern void distortion_xil_terminate(void);

#endif

/*
 * File trailer for _coder_distortion_api.h
 *
 * [EOF]
 */
