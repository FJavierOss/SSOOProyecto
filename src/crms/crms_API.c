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
  unsigned int pagina;
  unsigned int bit_validez_pagina;
  unsigned int PFN;
  int memoria_fisica;
  int memoria_fisica_abosluta;
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

                fseek(fp, 224+256*k+VPN, SEEK_SET);
                num = 0;
                fread(&num, 1, 1, fp);
                pagina = num;
                bit_validez_pagina = pagina >> 7;
                PFN = (pagina & ~(0x01 << 7));
                memoria_fisica = (PFN << 23) | offset;
                memoria_fisica_abosluta = memoria_fisica + pow(2, 12) + pow(2, 4);

                
                crms_file -> size = tamano;
                crms_file -> virtual_address = direccion_virtual;
                crms_file -> offset = offset;
                crms_file -> VPN = VPN;
                crms_file -> PFN = PFN;
                crms_file -> fisic_address = memoria_fisica;
                crms_file -> proces_id = process_id;
                crms_file -> file_name = file_name;
                crms_file -> page_table = pagina;
                crms_file -> content = calloc(sizeof(char), crms_file -> size);
                for (int z = 0; z< crms_file -> size; z++)
                {
                  fseek(fp, memoria_fisica_abosluta + z, SEEK_SET);
                  num = 0;
                  fread(&num, 1, 1, fp);
                  crms_file -> content[z] = num;
                  
                }
                printf("Contenido gigante: %s\n", crms_file->content);


              }
              
            }

          }
        }
      }
    }
    fclose(fp);
    return crms_file;
  }
  else if (mode == 'w')
  {
    if (!cr_exists(process_id, file_name))
    {
      crms_file -> file_name = file_name;
      crms_file -> proces_id = process_id;
      crms_file -> size = NULL;
      crms_file -> virtual_address = NULL;
      crms_file -> offset = NULL;
      crms_file -> VPN = NULL;
      crms_file -> PFN = NULL;
      crms_file -> fisic_address = NULL;
      crms_file -> proces_id = NULL;
      crms_file -> file_name = NULL;
      crms_file -> page_table = NULL;
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

int cr_write_file(CrmsFile* file_desc, void* buffer, int n_bytes)
{
  FILE* fp;
  fopen(fp, "wb+");;
  int PFN;
  
}


void cr_close(CrmsFile* file_desc)
{
  free(file_desc -> content);
  free(file_desc);
}