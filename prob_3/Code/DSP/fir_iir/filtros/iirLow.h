#include "dsplib.h"

#define FILENAME "..\\outDSP\\dspIirLow.txt"
#define NBIQ 1
#define NBUFF 4*NBIQ+1

DATA dbuffer[NBUFF];

DATA coef[5*NBIQ] = { 4480, 4480, 0, -23807, 0 };

void filter(){
    oflag = iircas51 (samplesIn, coef, out, dbuffer, NBIQ, NX);
    printf("\n\noflag: %u\n", oflag);
    printf("IIR Passa-Baixa: \n");
}
