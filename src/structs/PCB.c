#include "PCB.h"
#include "byteswap.h"
#include "bitmap.h"

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;
    
    for (i = size-1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

void openPCB( char* ruta){
  FILE * fp;
  fp = fopen(ruta, "rb+");
  // tamaño entrada 256 bytes
  // 3*256 = 768
  unsigned int aux=0;
  unsigned int num = 0;
  char name[12];

  //result = fread(&num, sizeof(int), 1, fp);
  //printf("Estado: %ld\n", result);
  for (int k = 0; k < 16; k++){
    num=0;
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
    
    for (int e=0; e < 10 ;e++){
        num=0;
        fseek( fp,  256*k + 14 +21*e , SEEK_SET);
        fread(&num, 1, 1, fp);
        //printf("%d ", bswap_32(num));
        
        //printf("Validez: %d ;",num);
        //printf("Nombre del archivo: ");
        for (int i = 1 ; i < 13; i++){
            fseek( fp, 256*k + 14 + 21*e + i, SEEK_SET);
            fread(&num, 1, 1, fp);
            //printf("%d ", bswap_32(num));
            //printf("%c", num);
        /*
        printf("location %d\n", i);
        printf("result1: %d\n", bswap_32(num));
        printf("result2: %d\n", num);
        printf("-------\n");
        */
        }
        //printf("---Tamano del archivo: ");
        fseek( fp, 256*k + 14 + 21*e + 13, SEEK_SET);
        fread(&num, 4, 1, fp);
        //printf("%d ", bswap_32(num));
        //printf("%d bytes \n", bswap_32(num));

        //printf("---Memoria Virtual: \n ");
        fseek( fp, 256*k + 14 + 21*e + 13  + 4, SEEK_SET);
        fread(&num, 4, 1, fp);
        //printBits(sizeof(num), &num);
        aux = num >> 28;
        //printBits(sizeof(aux), &aux);
        //printf("bits no significativos: %d \n", (aux));

        aux = num;
        for (int a = 28 ; a < 33; a++){
            aux = aux & (~(0x01<<(a))); 
        }
        aux = aux >> 23; // 28 - 23
        //printBits(sizeof(aux), &aux);
        //printf("VPN: %d \n", bswap_32(aux));

         aux = num;
        for (int a = 23 ; a < 33; a++){
            aux = aux & (~(0x01<<(a))); 
        }
        //printBits(sizeof(aux), &aux);
        //printf("OFFSET: %d \n", bswap_32(aux));
        //printf("---Tabla de paginas: ");
        for (int s = 0 ; s < 32; s++){
        fseek( fp, 256*k + 14 + 210 +  s, SEEK_SET);
        fread(&num, 1, 1, fp);
        aux = num;
        //printBits(sizeof(num), &num);
        aux = num >> 7;
        //printBits(sizeof(aux), &aux);
        //printf("Validez Tabla de Paginas: %d \n", (aux));

        aux = num;
        aux = aux & (~(0x01<<(7))); 
        printBits(sizeof(aux), &aux);
        printf("PFN: %d \n", bswap_32(aux));
        }

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
