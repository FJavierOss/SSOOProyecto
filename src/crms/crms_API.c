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
