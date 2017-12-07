#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define  SAMPLE_SIZE 57

int main(int argc, char const *argv[]) {

	
	static const double X[SAMPLE_SIZE] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.390625000000000,-0.414062500000000,-0.289062500000000,
	-0.117187500000000,-0.0312500000000000, -0.0312500000000000,-0.0625000000000000,-0.0234375000000000,0.0234375000000000,
	0.0703125000000000,0.109375000000000,0.156250000000000,0.203125000000000,0.242187500000000,0.218750000000000,0,
	-0.164062500000000,-0.140625000000000,-0.0156250000000000,0.195312500000000,0.320312500000000,0.320312500000000,
	0.242187500000000,0.242187500000000,0.265625000000000,0.304687500000000,0.289062500000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	int i;
	double d = 200;
	double Y[SAMPLE_SIZE];
	double Y_atan[SAMPLE_SIZE];		
	
	// calculo do arco tangente para cada amostra
	printf("###### Calculo do arco tangente:\n");
	for (i = 0; i < SAMPLE_SIZE; i++) {
		Y_atan[i] = atan((0.1 + 2 * d )* X[i]);
		printf("%.4f | ", Y_atan[i]);
	}
	printf("\n -------------------------------- \n\n");
	
	// normalização
	double sx = 0;
	printf("###### Calculo do 'sx':\n");
	for (i = 0; i < SAMPLE_SIZE; i++) {
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
	for (i = 0; i < SAMPLE_SIZE; i++) {
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
	
	// Calculo para obtenção do resultado
	printf("###### Resultado:\n");
	for (i = 0; i < SAMPLE_SIZE; i++) {
		Y[i] = sr * Y_atan[i];	
		printf("%.4f | ", Y[i]);
	}	
	
	return 0;
}


