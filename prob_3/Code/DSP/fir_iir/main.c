#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "ezdsp5502.h"
#include "dsplib.h"
#include "filtros/firLow.h"
#include "filtros/firHigh.h"
#include "filtros/firBand.h"
#include "samplesIn/samplesHex.h"

#define NX 1000
#define FS 1000
#define NH 199
#define NHHigh 215

/**
 * main.c
 */

//ushort oflag = fir (DATA *x, DATA *h, DATA *output, DATA *dbuffer, ushort nx, ushort nh);

void zerarVetores();
void showOutFIR();
void writeOutFIR();

    ushort nx = NX;
    ushort nh = NH;                 //ordem do filtro
    ushort nh2 = NHHigh;
    DATA dbuffer[NH+2];             //buffer de atraso (cont�m os valores de entrada atrasados)
    DATA dbufferHigh[NHHigh+2];     //buffer de atraso (cont�m os valores de entrada atrasados)
    DATA out[NX];
    ushort oflag;

int main(void){

//    //Filtro FIR passa-baixas
//    zerarVetores();
//    oflag = fir (samplesIn, HLow, out, dbuffer, nx, nh);
//    printf("\n\noflag: %u\n",oflag);
//    printf("Sinal filtrado com passa baixas\n");
//    showOutFIR();
//    writeOutFIR();

//    //Filtro FIR passa-faixa
//    zerarVetores();
//    oflag = fir (samplesIn, HBand, out, dbuffer, nx, nh);
//    printf("\n\noflag: %u\n",oflag);
//    printf("Sinal filtrado com passa faixa\n");
//    showOutFIR();
//    writeOutFIR();

    //Filtro FIR passa-alta
    zerarVetores();
    oflag = fir (samplesIn, HHigh, out, dbufferHigh, nx, nh2);
    printf("\n\noflag: %u\n",oflag);
    printf("Sinal filtrado com passa alta\n");
    showOutFIR();
    writeOutFIR();

    return 0;
}

void showOutFIR(){
    int i;
    for(i=0; i<NX;i++){
        printf("%d ",out[i]);
    }
}

void writeOutFIR(){
    FILE *outFile;
    outFile = fopen("..\\outDSP\\outfirDSPAlta.txt", "w");
    int i;
    for(i=0; i<NX;i++){
        fprintf(outFile,"%d ",out[i]);
        printf("%d ",out[i]);
    }
}

void zerarVetores(){
    int i;
    for(i=0; i<NH+2; i++){
       dbuffer[i] = 0;
   }

   for(i=0; i<NX; i++){
       out[i] = 0;
   }
}
