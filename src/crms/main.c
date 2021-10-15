#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "crms_API.h"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Número de argumentos inválidos\n");
    return 1;
  }
  int cr_int;
  cr_mount(argv[1]);



  // cr_int = checkPosStatusFB(0, ruta);
  // cr_int = checkPosStatusFB(1, ruta);
  // cr_int = checkPosStatusFB(2, ruta);
  // cr_int = checkPosStatusFB(3, ruta);
  // cr_int = checkPosStatusFB(4, ruta);
  // cr_int = checkPosStatusFB(5, ruta);
  // cr_int = checkPosStatusFB(6, ruta);
  // cr_int = checkPosStatusFB(7, ruta);

  // frameBitmapChangeToZero(0, ruta);

  // cr_int = checkPosStatusFB(0, ruta);
  // cr_int = checkPosStatusFB(1, ruta);
  // cr_int = checkPosStatusFB(2, ruta);
  // cr_int = checkPosStatusFB(3, ruta);
  // cr_int = checkPosStatusFB(4, ruta);
  // cr_int = checkPosStatusFB(5, ruta);
  // cr_int = checkPosStatusFB(6, ruta);
  // cr_int = checkPosStatusFB(7, ruta);

  // frameBitmapChangeToOne(0, ruta);

  // cr_int = checkPosStatusFB(0, ruta);
  // cr_int = checkPosStatusFB(1, ruta);
  // cr_int = checkPosStatusFB(2, ruta);
  // cr_int = checkPosStatusFB(3, ruta);
  // cr_int = checkPosStatusFB(4, ruta);
  // cr_int = checkPosStatusFB(5, ruta);
  // cr_int = checkPosStatusFB(6, ruta);
  // cr_int = checkPosStatusFB(7, ruta);

  // openPCB(ruta);
  // printf("Ruta global: %s\n", ruta);
  // openPCB(ruta);

  // cr_ls_processes();
  
  // cr_start_process(4,"mi pro");

  //cr_ls_processes();
  // cr_finish_process(4);
  // cr_ls_processes();
  // cr_ls_files(27);
  // cr_int = cr_exists(27, "grab.mp4");
  // printf("cr_exists result con id 27 y filename grab.mp4 %d\n", cr_int);
  // cr_int = cr_exists(27, "grub.mp4");
  // printf("cr_exists result con id 27 y filename grub.mp4 %d\n", cr_int);
  char nombre[12] = "info2.txt";
  unsigned char buffer[64];

  CrmsFile* crms_w = cr_open(0, "info.txt", 'w');
  printf("NOmbre: %s\n", crms_w -> file_name);
  FILE* fp;
  fp = fopen("info.txt", "rb+");
  fseek(fp, 0, SEEK_SET);
  fread(buffer, 1, 32, fp);
  fclose(fp);
  int bytes_escritos = cr_write_file(crms_w, buffer, 32);

  printf("\n\n###############################################\n\n");
  
  CrmsFile* crms_w2 = cr_open(0, nombre, 'w');
  printf("NOmbre: %s\n", crms_w2 -> file_name);
  FILE* fp2;
  fp2 = fopen("info.txt", "rb+");
  fseek(fp2, 0, SEEK_SET);
  fread(buffer, 1, 64, fp);
  fclose(fp2);
  int bytes_escritos2 = cr_write_file(crms_w2, buffer, 64);
  

  CrmsFile* crms_r = cr_open(0, "info.txt", 'r');
  int bytes_r = cr_read(crms_r, buffer, 32);
  printf("Pointer: %p\n", buffer);
  printf("info: %s\n", buffer);
  // cr_ls_files(0);
  cr_delete_file(crms_r);
  cr_close(crms_r);
  if (!cr_exists(0, "info.txt"))
  {
    printf("Archivo %s ya no existe\n", "info.txt");
    
  }

  CrmsFile* crms_r2 = cr_open(0, "info2.txt", 'r');
  int bytes_r2 = cr_read(crms_r2, buffer, 32);
  printf("Pointer: %p\n", buffer);
  printf("info: %s\n", buffer);
  // cr_ls_files(0);
  cr_delete_file(crms_r2);
  cr_close(crms_r2);
  if (!cr_exists(0, "info2.txt"))
  {
    printf("Archivo %s ya no existe\n", "info2.txt");
    
  }


  return 0;
}
