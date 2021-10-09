#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "crms_API.h"

int main(int argc, char **argv)
{
  int cr_int;
  cr_mount(argv[1]);
  //printf("Ruta global: %s\n", ruta);
  //openPCB(ruta);
  cr_ls_processes();
  cr_ls_files(27);
  cr_int = cr_exists(27, "grab.mp4");
  printf("cr_exists result con id 27 y filename grab.mp4 %d\n", cr_int);
  cr_int = cr_exists(27, "grub.mp4");
  printf("cr_exists result con id 27 y filename grub.mp4 %d\n", cr_int);
  /*
  printf("Primer print del proyecto 1\n");
  imprimir_desde_otro_archivo();
  FrameBitmap bitmap = frameBitmapInit();
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);
  */



}
