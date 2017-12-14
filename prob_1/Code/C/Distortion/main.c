#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned char wavHd[44];

void distortion(double inSamples[], int tam);

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
  distortion(inSamples, dataSize);

  fclose(inFile);
}

void distortion(double X[], int tam){
	
	FILE *outFile;
	outFile = fopen("distortionC.wav", "wb");
	char buff[1];

	//setando o novo tamanho no header
	unsigned char *p = (unsigned char*)&tam;
	wavHd[40] = p[3];
	wavHd[41] = p[2];
	wavHd[42] = p[1];
	wavHd[43] = p[0];

	fwrite(wavHd, sizeof(unsigned char), 44, outFile);
  
	int i;
	double d = 200;
	double Y[tam];
	double Y_atan[tam];

	// calculo do arco tangente para cada amostra
	printf("###### Calculo do arco tangente:\n");
	for (i = 0; i < tam; i++) {
		Y_atan[i] = atan((0.1 + 2 * d )* X[i]);
		printf("%.4f | ", Y_atan[i]);
	}
	printf("\n -------------------------------- \n\n");

	// normaliza��o
	double sx = 0;
	printf("###### Calculo do 'sx':\n");
	for (i = 0; i < tam; i++) {
		if(X[i] < 0){
			sx = sx + (X[i] * -1);
		}else{
			sx = sx + X[i];
		}
	}
	printf("sx: %.4f", sx);
	printf("\n -------------------------------- \n\n");

	double sy = 0;
	printf("###### Calculo do 'sy':\n");
	for (i = 0; i < tam; i++) {
		if(Y_atan[i] < 0){
			sy = sy + (Y_atan[i] * -1);
		}else{
			sy = sy + Y_atan[i];
		}
	}
	printf("sy: %.4f", sy);
	printf("\n -------------------------------- \n\n");

	// calculo do sr:
	double sr = sx / sy;
	printf("###### Calculo do 'sr':\n");
	printf("sr: %.4f", sr);
	printf("\n -------------------------------- \n\n");

	// Calculo para obten��o do resultado
	printf("###### Resultado:\n");
	for (i = 0; i < tam; i++) {
		Y[i] = sr * Y_atan[i];
		printf("%.4f | ", Y[i]);
		buff[0] = (char)(((char)(Y[i]*128)) ^ 0x80);
		fwrite(buff, sizeof(char), 1, outFile);
	}
	
	fclose(outFile);
}






