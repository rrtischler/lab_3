/*
 * File: distortion.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 26-Nov-2017 14:16:23
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "distortion.h"

/* Function Definitions */

/*
 * Y   = espectro do sinal de saída
 *    X   = espectro do sinal de entrada
 *    FS  = frequencia de amostragem 16000
 * Arguments    : long d
 *                double Y[57]
 * Return Type  : void
 */
void distortion(long d, double Y[57]) {
  int i;
  static const double dv0[57] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.40583429307480412, -0.4273924238397025,
    -0.30785928881425267, -0.12819928123129815, -0.034361469959131467,
    -0.034361469959131467, -0.068641989089834127, -0.025775540244580623,
    0.025775540244580623, 0.07719007632216765, 0.11973697850073878,
    0.17021192528547441, 0.21982673563117316, 0.26035924839480895,
    0.23613585751336014, 0.0, -0.17854694022788065, -0.15347111736265345,
    -0.017185807845897398, 0.21162680876562981, 0.33876126487599517,
    0.33876126487599517, 0.26035924839480895, 0.26035924839480895,
    0.28427404198088607, 0.32339028120066104, 0.30785928881425267, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  (void)d;

    /* %distorcao
	 Y=(atan((0.1+2*d)*X));
	 %normalizacao
	 sx=sum(abs(X));
	 sy=sum(abs(Y));
	 sr=repmat(sx/sy,length(X),1); */
  
  //sr = 0.93607582921947075
  for (i = 0; i < 57; i++) {
    Y[i] = 0.93607582921947075 * dv0[i];
  }
}

/*
 * File trailer for distortion.c
 *
 * [EOF]
 */
