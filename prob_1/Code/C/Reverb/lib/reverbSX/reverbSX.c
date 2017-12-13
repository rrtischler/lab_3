/*
 * File: reverbSX.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 26-Nov-2017 14:57:15
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "reverbSX.h"

/* Function Definitions */

/*
 * Y   = espectro do sinal de saída
 *    X   = espectro do sinal de entrada
 *    FS  = frequencia de amostragem
 *    att = atenuacao (0,1)
 *    d   = offset em ms
 * Arguments    : const double unusedU0[57]
 *                long unusedU1
 *                long unusedU2
 *                double att
 *                double Y[57]
 * Return Type  : void
 */
void reverbSX(const double unusedU0[57], long unusedU1, long unusedU2, double
              att, double Y[57])
{
  double b[32];
  double dbuffer[32];
  int j;
  int k;
  static const double x[57] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.390625, -0.4140625, -0.2890625, -0.1171875,
    -0.03125, -0.03125, -0.0625, -0.0234375, 0.0234375, 0.0703125, 0.109375,
    0.15625, 0.203125, 0.2421875, 0.21875, 0.0, -0.1640625, -0.140625, -0.015625,
    0.1953125, 0.3203125, 0.3203125, 0.2421875, 0.2421875, 0.265625, 0.3046875,
    0.2890625, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0 };

  (void)unusedU0;
  (void)unusedU1;
  (void)unusedU2;

  /*  criacao do filtro */
  memset(&b[0L], 0, sizeof(double) << 5U);
  b[0] = 1.0;
  b[31] = att;
  b[23] = att + 0.07;
  b[15] = att + 0.07;
  b[7] = att + 0.08;

  /*  filtragem */
  memset(&dbuffer[1], 0, 31U * sizeof(double));
  for (j = 0; j < 57; j++) {
    for (k = 0; k < 31; k++) {
      dbuffer[k] = dbuffer[k + 1];
    }

    dbuffer[31] = 0.0;
    for (k = 0; k < 32; k++) {
      dbuffer[k] += x[j] * b[k];
    }

    Y[j] = dbuffer[0];
  }
}

/*
 * File trailer for reverbSX.c
 *
 * [EOF]
 */
