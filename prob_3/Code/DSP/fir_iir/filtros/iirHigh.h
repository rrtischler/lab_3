#include "dsplib.h"

#define FILENAME "..\\outDSP\\dspIirHigh.txt"
#define NBIQ 1
#define NBUFF 4*NBIQ+1

DATA dbuffer[NBUFF];

DATA coef[5*NBIQ] = { 21707, -21707, 0, -10647, 0 };

void filter(){
    oflag = iircas51 (samplesIn, coef, out, dbuffer, NBIQ, NX);
    printf("\n\noflag: %u\n", oflag);
    printf("IIR Passa-Alta: \n");
}
