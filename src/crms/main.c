#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "crms_API.h"

int main(int argc, char **argv)
{
  int cr_int;



  //Inputs para tests
  int testInteger;
  int processId;
  char filename[12];

  
  printf("1 para revisar cr_mount y cr_ls_processes \n");
  printf("2 para revisar cr_ls_files y cr_exists \n ");
  printf("3 para revisar cr_start_process y cr_finish_process\n ");
  printf("4 para revisar cr_open \n ");
  printf("Ingresa un integer: ");
  scanf("%d", &testInteger);  

  if(testInteger==1){
    cr_ls_processes();
    printf("===========Ahora se montará la memoria=============\n");
    cr_mount(argv[1]);
    cr_ls_processes();
    return 1;
  } else if(testInteger==2){
    cr_mount(argv[1]);
    cr_ls_processes();
    printf("Ingresa un ProcessId: ");
    scanf("%d", &processId);  
    cr_ls_files(processId);
    printf("Ingresa un FileName: ");
    gets(filename);
    scanf("%s", &filename); 
    printf("Retorno de cr_exists: %i\n",cr_exists(processId,filename));
    return 1;
  } else if(testInteger==3){
    cr_mount(argv[1]);
    cr_ls_processes();
    printf("Ingresa un ProcessId para iniciar un proceso: ");
    scanf("%d", &processId); 
    printf("Ingresa un nombre para este proceso: ");
    gets(filename);
    scanf("%s", &filename); 
    cr_start_process(processId,filename);
    cr_ls_processes();
    printf("Ingresa un ProcessId para finalizar un proceso: ");
    scanf("%d", &processId); 
    cr_finish_process(processId);
    cr_ls_processes();
    return 1;
  }
  
  printf("----\n");


  cr_int = checkPosStatusFB(0, ruta);
  cr_int = checkPosStatusFB(1, ruta);
  cr_int = checkPosStatusFB(2, ruta);
  cr_int = checkPosStatusFB(3, ruta);
  cr_int = checkPosStatusFB(4, ruta);
  cr_int = checkPosStatusFB(5, ruta);
  cr_int = checkPosStatusFB(6, ruta);
  cr_int = checkPosStatusFB(7, ruta);

  frameBitmapChangeToZero(0, ruta);

  cr_int = checkPosStatusFB(0, ruta);
  cr_int = checkPosStatusFB(1, ruta);
  cr_int = checkPosStatusFB(2, ruta);
  cr_int = checkPosStatusFB(3, ruta);
  cr_int = checkPosStatusFB(4, ruta);
  cr_int = checkPosStatusFB(5, ruta);
  cr_int = checkPosStatusFB(6, ruta);
  cr_int = checkPosStatusFB(7, ruta);

  frameBitmapChangeToOne(0, ruta);

  cr_int = checkPosStatusFB(0, ruta);
  cr_int = checkPosStatusFB(1, ruta);
  cr_int = checkPosStatusFB(2, ruta);
  cr_int = checkPosStatusFB(3, ruta);
  cr_int = checkPosStatusFB(4, ruta);
  cr_int = checkPosStatusFB(5, ruta);
  cr_int = checkPosStatusFB(6, ruta);
  cr_int = checkPosStatusFB(7, ruta);

  openPCB(ruta);
  printf("Ruta global: %s\n", ruta);
  openPCB(ruta);

  cr_ls_processes();
  
  cr_start_process(4,"mi pro");

  cr_ls_processes();
  cr_finish_process(200);
  cr_ls_processes();
  cr_ls_files(27);
  cr_int = cr_exists(27, "grab.mp4");
  printf("cr_exists result con id 27 y filename grab.mp4 %d\n", cr_int);
  cr_int = cr_exists(27, "grub.mp4");
  printf("cr_exists result con id 27 y filename grub.mp4 %d\n", cr_int);

  
  // printf("Primer print del proyecto 1\n");
  // imprimir_desde_otro_archivo();
  // FrameBitmap bitmap = frameBitmapInit();
  // frameBitmapChangeToOne(bitmap, 127);
  // frameBitmapChangeToOne(bitmap, 127);
  // frameBitmapChangeToZero(bitmap, 127);
  // frameBitmapChangeToZero(bitmap, 127);
  



}
