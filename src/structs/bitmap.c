#include "bitmap.h"

FrameBitmap frameBitmapInit(){

    FrameBitmap fB;
    for (int largo = 0; largo < 16; largo ++){
        fB.data[largo] = 0;
    }
    return fB;
}

void frameBitmapChangeToOne(FrameBitmap fb, int pos)
{   
    int row = pos / 8;
    int col = pos % 8;
    int numero = 1;
    numero = numero << col;
    fb.data[row] = fb.data[row] | numero;
    printf("------- Changing to One -------\n");
    printf("col: %i\n",col);
    printf("row: %i\n",row);
    printf("numero: %i\n",numero);
    printf("to one: %d\n", fb.data[row]);
    
}

void frameBitmapChangeToZero(FrameBitmap fb, int pos)
{
    int row = pos / 8;
    int col = pos % 8;
    int numero;
    numero = fb.data[row] & (~(0x01<<(8-col)));
    fb.data[row] = numero;
    printf("------- Changing to Zero -------\n");
    printf("col: %i\n",col);
    printf("row: %i\n",row);
    printf("numero: %i\n",numero);
    printf("to zero: %d\n", fb.data[row]);

    /*
    numero = pow(2, col);
    fb.data[row] = fb.data[row] ~ numero;
    
    */
    /*
    fb.data[pos] = 0;
    */
}
