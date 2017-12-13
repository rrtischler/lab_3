#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char wavHd[44];

void delay(double inSamples[], int tam);

void main()
{
  FILE *inFile;

  char buffer;
  double sample;
  int i;

  inFile = fopen("dspafsx_mono.wav", "rb");

  if (inFile == NULL)
  {
    printf("Can't open dspafsx_mono.wav");
    return;
  }

  // Read input wav file header
  fread(wavHd, sizeof(char), 44, inFile);

  int dataSize = wavHd[40] |
                 (wavHd[41] << 8) |
                 (wavHd[42] << 16) |
                 (wavHd[43] << 24 );

  double inSamples[dataSize];
  while( (fread(&buffer, sizeof(char), 1, inFile) == 1) )
  {

    inSamples[i] = ((char)(buffer ^ 0x80 & 255))/128.;

    i++;
  }
  delay(inSamples, dataSize);

  fclose(inFile);
}

void delay(double inSamples[], int tam){
  int FS = 16000;
  double d = 200;
  double att = 0.5;

  double num = (d*FS)/1000;
  int cont = (int)round(num);
  int new_tam = tam + cont;

  int i;
  double maxInput, maxOutput, max, mtmp;
  double outSamples[new_tam];

  FILE *outFile;
  outFile = fopen("delayC.wav", "wb");
  char buff[1];

  //setando o novo tamanho no header
  unsigned char *p = (unsigned char*)&tam;
  wavHd[40] = p[3];
  wavHd[41] = p[2];
  wavHd[42] = p[1];
  wavHd[43] = p[0];

  fwrite(wavHd, sizeof(unsigned char), 44, outFile);

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

  // normalizacao
  max = (maxInput/maxOutput);
  for (i = 0; i < new_tam; i++){
    outSamples[i] = outSamples[i] * max;
    // printf("%f ", outSamples[i]);
    buff[0] = (char)(((char)(outSamples[i]*128)) ^ 0x80);
    fwrite(buff, sizeof(char), 1, outFile);
    // printf("%d ", buff[0]);
  }

  fclose(outFile);
}