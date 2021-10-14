#include "crms_API.h"


void cr_mount(char* memory_path)
{
  ruta = memory_path;
}


void cr_ls_processes(){
  int num = 0;
  char name[12];
  FILE * fp;
  fp = fopen(ruta, "rb+");
  printf("      Running Processes      \n");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    if(num == 1){
      printf("\n| Status %d", num);
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);
      printf("| ID %*d", 4,num);
      printf("| Name <");

      for (int j = 2; j < 14; j++){
        fseek( fp, j+256*k, SEEK_SET);
        fread(&num, 1, 1, fp);
        name[j-2] = num;
        printf("%c", num);
      }
      printf(">");
    }
  }
  printf("\n");
  fclose(fp);
}

void cr_ls_files(int process_id){
  int num = 0;
  int process_exists = 0;
  FILE * fp;
  fp = fopen(ruta, "rb+");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    // Aqui podriamos chequear esta vivo o no. (num  == 1)
    // Hay que preguntar al ayudante si procesos con
    // status 0 se incluyen dentro de la operacion
    if( 1 ){
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      if( num == process_id){
        process_exists = 1;
        printf("\n      Process %d Files      \n", process_id);

        // Hay 10 entradas cada 1 con 21 bytes
        for (int j = 0; j < 10; j++){

          fseek( fp, 21*j+14+256*k, SEEK_SET);
          fread(&num, 1, 1, fp);
          if (num == 1){
            printf("\nFile Name | ");
            for (int i = 1; i<13; i++){
              fseek( fp, 21*j+i+14+256*k, SEEK_SET);
              fread(&num, 1, 1, fp);
              printf("%c", num);
            }
          }

        }
      }
    }
  }
  printf("\n");
  fclose(fp);

  if (!process_exists){
    printf("No hay procesos con ese id\n");
  }
}


int cr_exists(int process_id, char* file_name){
  int num = 0;
  char name[12];
  int check_existence = 0;
  int process_exists = 0;
  FILE * fp;
  fp = fopen(ruta, "rb+");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    // Aqui podriamos chequear esta vivo o no. (num  == 1)
    // Hay que preguntar al ayudante si procesos con
    // status 0 se incluyen dentro de la operacion
    if( 1 ){
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      if( num == process_id){
        process_exists = 1;

        // Hay 10 entradas cada 1 con 21 bytes
        for (int j = 0; j < 10; j++){
          fseek( fp, 21*j+14+256*k, SEEK_SET);
          fread(&num, 1, 1, fp);

          if ((num == 1) && (check_existence != 1) ){
            check_existence = 1;

            for (int i = 1; i<13; i++){
              fseek( fp, 21*j+i+14+256*k, SEEK_SET);
              fread(&num, 1, 1, fp);
              
              if (num && check_existence){
                if(num != file_name[i-1]){
                  check_existence = 0;
                }
              }

            }
          }

        }
      }
    }
  }
  printf("\n");
  fclose(fp);

  if (!process_exists){
    printf("No hay procesos con ese id\n");
    return 0;
  }
  return check_existence;
}

void cr_start_process(int process_id, char* process_name){

   FILE * fp;
  fp = fopen(ruta, "rb+");
 
  unsigned int aux=0;
  unsigned int num = 0;
  printf("%i \n",strlen(process_name));
  char name[12];
  

  for(int k=0;k<16;k++){
    
    fseek(fp, 1+256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    
    if (num==process_id){
      printf("YA EXISTE ESTE ID \n");
      return; 
    }
  };

  for(int k=0;k<16;k++){
    
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
   
    if(num==0){ //No se está ejecutando el proceso asignado a ese espacio (si es que hay proceso)
      
      num=1;
      //seteamos estado
      fseek( fp, 256*k, SEEK_SET);
      fwrite(&num, 1, 1, fp);
      //seteamos id 
      fseek( fp, 1+256*k, SEEK_SET);
      fwrite(&process_id, 1, 1, fp);
      //seteamos nombre
      for (int j = 2; j < strlen(process_name)+2; j++){
        fseek( fp, j+256*k, SEEK_SET);
        fwrite(&process_name[j-2], 1, 1, fp);
      }
     
      break;
    }
  };
  fclose(fp);

  printf("NO SE ENCONTRÖ UN ESPACIO PARA INICAR PROCESO\n");
  return;  
};


void cr_finish_process(int process_id){

   FILE * fp;
  fp = fopen(ruta, "rb+");
 
  unsigned int aux=0;
  unsigned int num = 0;
  char name[12];
  
  

  for(int k=0;k<16;k++){
    
    fseek(fp, 1+256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    
    if (num==process_id){
      num=0;
      
      for(int m=0;m<256;m++){
        fseek( fp, m+256*k, SEEK_SET);
        fwrite(&num, 1, 1, fp);
      }
      printf("El proceso termino\n");
      return; 
    }
  };
  fclose(fp);
  printf("No se encontró un proceso con ese id\n");
  
  return;  
};

CrmsFile* cr_open(int process_id, char* file_name, char mode)
{
  FILE* fp;
  CrmsFile* crms_file = malloc(sizeof(CrmsFile));
  char name[12];
  int num = 0;
  int direccion_virtual;
  int tamano;
  if (mode == 'r')
  {
    fp = fopen(ruta, "rb+");

    for (int k = 0; k < 16; k++)
    {
      fseek( fp, 256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      // Aqui podriamos chequear esta vivo o no. (num  == 1)
      // Hay que preguntar al ayudante si procesos con
      // status 0 se incluyen dentro de la operacion
      if( 1 )
      {
        fseek( fp, 1+256*k, SEEK_SET);
        fread(&num, 1, 1, fp);
        if(num == process_id)
        {

          // Hay 10 entradas cada 1 con 21 bytes
          for (int j = 0; j < 10; j++)
          {
            fseek( fp, 21*j+14+256*k, SEEK_SET);
            fread(&num, 1, 1, fp);
            if (num == 1)
            {

              for (int i = 1; i<13; i++){
                fseek( fp, 21*j+i+14+256*k, SEEK_SET);
                fread(&num, 1, 1, fp);
                name[i-1] = num;
              }
              if (!strcmp(name, file_name))
              {
                printf("%s\n", name);
                fseek(fp, 21*j+13+14+256*k, SEEK_SET);
                fread(&num, 4, 1, fp);
                
                tamano = bswap_32(num);
                fseek(fp, 21*j+17+14+256*k, SEEK_SET);
                fread(&num, 4, 1, fp);
                
                direccion_virtual = bswap_32(num);
                
                int offset = (direccion_virtual << 9) >> 9;
                int VPN = direccion_virtual >> 23;
                printf("Tamaño: %i\n", tamano);
                printf("Dirección virtual: %i\n", direccion_virtual);                
                printf("Offset: %i\n", offset);
                printf("VPN: %i\n", VPN);
                fseek(fp, 256-32+256*k+VPN, SEEK_SET);
                fread(&num, 1, 1, fp);
                printf("Nume 1 bite: %i\n", num);
                unsigned int pagina = num;
                unsigned int bit_validez_pagina = pagina >> 7;
                unsigned int PFN = (pagina & ~(0x01 << 7));
                printf("Página: %d\n", pagina);
                printf("Bit de validez de la página: %d\n", bit_validez_pagina);
                printf("PFN: %d\n", PFN);


              }
              
            }

          }
        }
      }
    }
    

    


    return crms_file;
  }
  else if (mode == 'w')
  {
    if (!cr_exists(process_id, file_name))
    {
      crms_file -> file_name = file_name;
      crms_file -> proces_id = process_id;
      // fatla ver qué atributos faltan
      return crms_file;
    }
    else 
    {
      printf("El archivo ya existe\n");
      free(crms_file);
      return NULL;
      
    }
  }
  else
  {
    printf("Modo inválido\n");
    free(crms_file);
    return NULL;
  }
}

