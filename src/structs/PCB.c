#include "PCB.h"



void openPCB( char* ruta){
  FILE * fp;
  fp = fopen(ruta, "rb+");
  // tamaño entrada 256 bytes
  // 3*256 = 768


  int num = 0;
  char name[12];

  //result = fread(&num, sizeof(int), 1, fp);
  //printf("Estado: %ld\n", result);
  for (int k = 0; k < 16; k++){
    printf("\n Numero de entrada %d", k);

    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    printf("\n Estado proceso %d", num);

    fseek( fp, 1+256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    printf("\n ID proceso %d", num);


    printf("\n Nombre del proceso <");

    for (int j = 2; j < 14; j++){
      fseek( fp, j+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);
      name[j-2] = num;
      printf("%c", num);
    }
    printf(">\n");





    for (int i = 14; i < 256; i++){
      fseek( fp, i + 256*k, SEEK_SET);
      fread(&num, 1, 1, fp);
      //printf("%d ", bswap_32(num));
      printf("%c ", num);
      /*
      printf("location %d\n", i);
      printf("result1: %d\n", bswap_32(num));
      printf("result2: %d\n", num);
      printf("-------\n");
      */
    }
    printf("\n");
  }



  fclose(fp);
}


/*
PageTable pagetable_init(){
    PageTable pt;
    pt.data=0;
    return pt;
};

SubEntrada subentrada_init(){
    SubEntrada se;

    se.validez = 0;

    for (int largo = 0; largo < 12; largo ++){
        se.file_name[largo] = 'x';
    }

    se.file_size = 0;
    se.virtual_adress = 0;
    return se;
};

Entrada entrada_init(){
    Entrada e;
    e.estado = 0;
    e.id = 0;
    for (int largo = 0; largo < 12; largo ++){
        e.name[largo] = 'x';
    }
    for (int largo = 0; largo < 10; largo ++){
        e.subentradas[largo] = subentrada_init();
    }
    for (int largo = 0; largo < 32; largo ++){
        e.pageTable[largo] = pagetable_init();
    }
    return e;
};



TablePCB tablepcb_init(){
    TablePCB tpcb;

    for (int largo = 0; largo < 16; largo ++){
        tpcb.entradas[largo] = entrada_init();
    }

    return tpcb;
};
*/
