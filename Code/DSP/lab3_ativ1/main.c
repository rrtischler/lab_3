#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "ezdsp5502.h"

#define UPPERLIMIT 0x7FFF
#define LOWERLIMIT 0x8000
#define BUFFERSIZE    1
#define FS  16000
#define OFFSET 200
#define ATT 0x4000 //0.5 em q15
#define NUMNEWSAMPLES 3200

#define Q 15
#define K (1 << (Q - 1))


    Int16 samples[NUMNEWSAMPLES];
    Int16 preSample[NUMNEWSAMPLES];
    Int16 outSample[NUMNEWSAMPLES];

//#pragma DATA_SECTION(samples, "Buffer1");
//    Uint8 samples[60000];
//#pragma DATA_SECTION(samples2, "Buffer2");
//    Uint8 samples2[60000];

    Uint8 buffer[BUFFERSIZE];
    Uint8 wavHd[44];

    Uint16 maxIn = 0;
    Uint16 maxOut = 0;




/*    Int8 samples[200] = { 1, 4, 8, -8, -30, -19, 20, 38, 25, -5, -24, -27, -23, -4, 21, 35, 13, -21, -34,
                         -24, 14, 36, 34, 22, 0, -18, -26, -22, -16, -20, -8, 17, 29, 7, -25, -36, -35,
                         -24, 3, 32, 30, 19, -3, -24, -30, -20, 17, 39, 39, 27, 29, 22, -2, -15, -15, 12,
                         41, 48, 40, 27, 2, -14, -17, 9, 15, -21, -25, -23, -25, -30, -34, -38, -33, 0, -8,
                         -43, -57, -46, -10, 21, 4, -31, -46, -25, 26, 35, 24, 9, -18, -28, -22, -13, -15,
                         -18, -22, -24, -27, -29, -31, -32, -31, -7, 25, 26, 18, 22, 30, 37, 44, 49, 56, 61,
                         66, 66, 40, 17, 15, 31, 63, 82, 74, 62, 63, 66, 69, 69, 41, 11, 10, 18, 14, 6, -2,
                         -9, -16, -23, -28, -34, -38, -42, -29, -6, 6, 2, -3, 1, 6, 11, 14, 22, 25, 29, 16,
                         -15, -27, -20, 4, 31, 38, 28, 21, 25, 27, 32, 20, -14, -29, -19, -16, -22, -29, -36,
                         -41, -47, -51, -56, -59, -62, -49, -25, -12, -12, -16, -12, -6, 1, 5, 12, 18, 23, 23,
                         -4, -27, -26, -10, 18, 36, 35, 25, 25 } ;
*/



void delay();
void wavReader();
void zerarBuffers();
Int16 soma(Int16 a, Int16 b);
Int16 q_mul(Int16 a, Int16 b);
Int16 sat16(Int32 r);


int main(void)
{
    //DMA_open();

    //delay();

    zerarBuffers();

    wavReader();

    printf("Efeito Delay finalizado!\n");
    //DMA_close();
    return 0;
}

/*
//int[] delay(int[] inSamples, int numSamples){
void delay(){
    double inSamples[57] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0.390625000000000,-0.414062500000000,-0.289062500000000,
      -0.117187500000000,-0.0312500000000000, -0.0312500000000000,-0.0625000000000000,-0.0234375000000000,0.0234375000000000,
      0.0703125000000000,0.109375000000000,0.156250000000000,0.203125000000000,0.242187500000000,0.218750000000000,0,
      -0.164062500000000,-0.140625000000000,-0.0156250000000000,0.195312500000000,0.320312500000000,0.320312500000000,
      0.242187500000000,0.242187500000000,0.265625000000000,0.304687500000000,0.289062500000000,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int FS = 16000;

    double d = 200;
    double  att = 0.5;

    double num = (d*FS)/1000;
    int cont = (int)round(num);
    int tam = sizeof(inSamples)/sizeof(double);
    int new_tam = tam + cont;

    int i;
    double maxInput, maxOutput, max, mtmp;
    double outSamples[3257];    // <<<<<<< não aceitou new_tam

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
        //printf("%.4f   ", outSamples[i]);
    }
    // for (i = 0; i < 65; i++) {
    //   outSamples[i] = outSamples[i] * 0.4140625 / maxInput;
    // }

    return;

}*/


void wavReader(){
    FILE *inFile; // File pointer of input signal
    FILE *outFile; // File pointer of output signal
    inFile = fopen("..\\Data\\dspafsx_mono.wav", "rb");
    if (inFile == NULL){
      printf("Can't open dspafsx_mono.wav");
      return;
    }
    outFile = fopen("..\\Data\\outGuitar.wav", "wb");
    if (outFile == NULL){
          printf("Can't open outGuitar.wav");
          return;
    }

    //pular 44 bytes reservados pro header
//    fseek(outFile, 44, SEEK_SET);
    wavHd[40] = (Uint8) 0xE0;
    wavHd[41] = (Uint8) 0xF6;
    fwrite(wavHd, sizeof(Uint8), 44, outFile);


    // Skip input wav file header
    fread(wavHd, sizeof(Uint8), 44, inFile); //estava sizeof int

     Uint32 dataSize = wavHd[40] |
                  (wavHd[41] << 8);// |
      //            (wavHd[42] << 16) |
      //            (wavHd[43] << 24 );
     printf("%ld\n", dataSize);

    // Add wav header output file
//    fwrite(wavHd, sizeof(Uint8), 44, outFile);

     Uint32 i = 0, j;
    // Read  input and write to output
    while( (fread(buffer, sizeof(Int8), BUFFERSIZE, inFile) == BUFFERSIZE ) ) {
      //fwrite(buffer, sizeof(int), 1024, outFile);
      //sample = buffer[0];
      //printf("%d ", buffer[0]);

        // alterna o bit de sinal (no wav está ao contrario), elimina qq coisa maior que 8 bits, e desloca 8 para esquerda
        // samples em q15
        samples[i++] = (Int16)((Int8)((buffer[0] ^ 0x80) & 0xFF)) << 8 ;
        if (i%3200 == 0){
            //printf("passada: %ld\n", i/3200);

            delay();
            i = 0;

            //escrever as amostras com efeito no arquivo de saida
            for (j = 0; j < NUMNEWSAMPLES; j++){
                // desloca 8 bits pra direita e alterna o bit de sinal, que no wav tá ao contrario
                buffer[0] = (Int8)(outSample[j] >> 8) ^ 0x80;
                fwrite(buffer, sizeof(Int8), 1, outFile);
            }
        }
    }

    //escrever ultimos samples, que estao só atenuados
    for (j = 0; j < NUMNEWSAMPLES; j++){
        // desloca 8 bits pra direita e alterna o bit de sinal, que no wav tá ao contrario
        buffer[0] = (Int8)(preSample[j] >> 8) ^ 0x80;
        fwrite(buffer, sizeof(Int8), 1, outFile);
    }

    // for(i = 0; i < dataSize; i++)
      // printf("%f\n", samples[i]);


    //alterar o header com o novo tamanho;
//    wavHd[40] = (Uint8) 0xE0;
//    wavHd[41] = (Uint8) 0xF6;
//
//    rewind(outFile);
//    fwrite(wavHd, sizeof(Uint8), 44, outFile);
//    for (j = 0; j < 44; j++){
//        // desloca 8 bits pra direita e alterna o bit de sinal, que no wav tá ao contrario
//        buffer[0] = (Uint8)(wavHd[j]<<8);
//        fwrite(buffer, sizeof(Int8), 1, outFile);
//    }

    fclose(inFile);
    //fclose(outFile);
}

void zerarBuffers(){
    int i;
    for (i= 0; i < 3200; i++){
        samples[i] = 0;
        preSample[i] = 0;
        outSample[i] = 0;
    }
}

// samples tem as amostras lidas
// preSample tem as atenuacoes das ultimas amostras lidas
// presamples[i] = atenuacao * samples[i]
// outSamples = samples[i] + preSamples[i]
void delay(){
    Int32  i;

    for(i = 0; i < NUMNEWSAMPLES; i++){
        outSample[i] = soma(samples[i], preSample[i]);

        //tmp = (Int32) samples[i] * ATT;
        //preSample[i] = (Int16) (tmp >> 15);
        preSample[i] = q_mul(samples[i], ATT);

        // procurando os máximos
//        if (samples[i] > maxIn)
//            maxIn = samples[i];
//        if (outSample[i] > maxOut)
//            maxOut = outSample[i];
    }
    //copiando as amostrar lidas para o buffer de amostrar anteriores
    //memcpy(preSample, samples, BUFFERSIZE * sizeof(Int8));
}

Int16 soma(Int16 a, Int16 b){
    long r;
    r = (Int32)a + (Int32)b;

    return sat16(r);
}

Int16 sat16(Int32 r){
    if ( r > UPPERLIMIT)
        r = UPPERLIMIT;
    else if (r < (Int16)-0x8000)
        r = (Int16)-0x8000;

    return (Int16)r;
}

Int16 q_mul(Int16 a, Int16 b){
    Int16 result;
    Int32 temp;

    temp = (Int32)a * (Int32)b; // result type is operand's type
    // Rounding; mid values are rounded up
    temp += K;
    // Correct by dividing by base and saturate result
    result = sat16(temp >> Q);

    return result;
}
