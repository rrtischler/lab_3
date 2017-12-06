#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {

  static const double inSamples[57] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.390625000000000,-0.414062500000000,-0.289062500000000,
    -0.117187500000000,-0.0312500000000000, -0.0312500000000000,-0.0625000000000000,-0.0234375000000000,0.0234375000000000,
    0.0703125000000000,0.109375000000000,0.156250000000000,0.203125000000000,0.242187500000000,0.218750000000000,0,
    -0.164062500000000,-0.140625000000000,-0.0156250000000000,0.195312500000000,0.320312500000000,0.320312500000000,
    0.242187500000000,0.242187500000000,0.265625000000000,0.304687500000000,0.289062500000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int FS = 16000;

  double d = 200;
  int att = 0.5;

  double num = (d*FS)/1000;
  int cont = (int)round(num);
  int tam = sizeof(inSamples)/sizeof(double);
  int new_tam = tam + cont;

  int i;
  double maxInput, maxOutput, max, mtmp;
  double outSamples[new_tam];

  // procura o máximo do input e grava em maxInput
  maxInput = inSamples[0];
  for (i = 1; i < tam; i++) {
    mtmp = fabs(inSamples[i]);
    if (mtmp > maxInput)
      maxInput = mtmp;
  }

  // os cont-primeiros termos são zerados, coloca a atenuacao no fim
  for (i = 0; i < new_tam; i++) {
    if(i >= cont)
      outSamples[i] = att * inSamples[i-cont];
    else
      outSamples[i] = 0;
    //printf("%.4f   ", new_input[i]);
  }

  // nao precisa somar os ultimos, ja estao no outSamples, e nao aparece nada no input
  for (i = 0; i < tam; i++) {
    outSamples[i] = outSamples[i] + inSamples[i];
  }


  // procura o máximo de y_1 e grava em maxOutput
  maxOutput = outSamples[0];
  for (i = 1; i < new_tam; i++) {
    mtmp = fabs(outSamples[i]);
    if (mtmp > maxOutput)
      maxOutput = mtmp;
  }

  //printf("%f  %f", maxInput, maxOutput);

  // normalizacao
  max = (maxInput/maxOutput);
  for (i = 0; i < new_tam; i++){
    outSamples[i] = outSamples[i] * max;
    printf("%.4f   ", outSamples[i]);
  }
  // for (i = 0; i < 65; i++) {
  //   outSamples[i] = outSamples[i] * 0.4140625 / maxInput;
  // }

  return 0;
}
