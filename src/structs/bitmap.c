#include "bitmap.h"

int checkPosStatusFB(int pos_to_check, char* ruta){
  // Aqui podriamos hacer uso del bonus lanzando un error
  if ((pos_to_check < 0) && (pos_to_check > 127)){
    printf("Posicion fuera de rango\n");
    return 0;
  }

  int row = pos_to_check / 8;
  int col = pos_to_check % 8;

  FILE * fp;
  int num = 0;
  fp = fopen(ruta, "rb+");

  /*
  for (int i = 0; i < 16; i++){
    fseek( fp, 4096+i, SEEK_SET);
    fread(&num, 1, 1, fp);
    printf("%i\n", num);
    //num = bswap_32(num);
    for (int bit = 0; bit<8; bit++){

      printf("%i ", num & 0x01);
      num = num >> 1;
    }
    printf("\n");

  }
  */

  fseek( fp, 4096 + row, SEEK_SET);
  fread(&num, 1, 1, fp);
  num = num >> col;

  printf("pos %i |row %i |col %i |status %i\n", pos_to_check, row, col, num & 0x01 );
  fclose(fp);

  return(num);
}

void frameBitmapChangeToOne(int pos_to_check, char* ruta){
  if ((pos_to_check < 0) && (pos_to_check > 127)){
    printf("Posicion fuera de rango\n");
    return ;
  }

  int row = pos_to_check / 8;
  int col = 7 - pos_to_check % 8;
  FILE * fp;
  int num = 0;
  int bit = 1;
  fp = fopen(ruta, "rb+");

  fseek( fp, 4096 + row, SEEK_SET);
  fread(&num, 1, 1, fp);
  bit = bit << col;
  num = num | bit;
  fseek( fp, 4096 + row, SEEK_SET);
  fwrite(&num, 1, 1, fp);

  //num = num >> col;

  for (int i = 0; i < 8; i++) {
    //printf("%i ", num & 0x01);
    num = num >> 1;
  }
  //printf("\n");


  //printf("pos %i status %i\n", pos_to_check, num & 0x01);
  fclose(fp);
  /*
  fb.data[row] = fb.data[row] | numero;
  printf("------- Changing to One -------\n");
  printf("col: %i\n",col);
  printf("row: %i\n",row);
  printf("numero: %i\n",numero);
  printf("to one: %d\n", fb.data[row]);
  */
}

void frameBitmapChangeToZero(int pos_to_check, char* ruta){
  if ((pos_to_check < 0) || (pos_to_check > 127)){
    printf("Posicion fuera de rango\n");
    return ;
  }

  int row = pos_to_check / 8;
  int col = 7 - pos_to_check % 8;
  FILE * fp;
  int num = 0;
  int bit = 1;
  fp = fopen(ruta, "rb+");

  fseek( fp, 4096 + row, SEEK_SET);           
  fread(&num, 1, 1, fp);
  bit = ~(bit << col);                    
  num = num & bit;
  fseek( fp, 4096 + row, SEEK_SET);
  fwrite(&num, 1, 1, fp);

  //num = num >> col;

  for (int i = 0; i < 8; i++) {
    //printf("%i ", num & 0x01);
    num = num >> 1;
  }
  //printf("\n");


  //printf("pos %i status %i\n", pos_to_check, num & 0x01);
  fclose(fp);
}
/*
FrameBitmap frameBitmapInit(){

    FrameBitmap fB;
    for (int largo = 0; largo < 16; largo ++){
        fB.data[largo] = 0;
    }
    return fB;
}

void frameBitmapChangeToOne(FrameBitmap fb, int pos)
{
    if (pos > 127 || pos < 0){
        return;
    }
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


    numero = pow(2, col);
    fb.data[row] = fb.data[row] ~ numero;



    fb.data[pos] = 0;

}
*/
