#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "crms_API.h"

int main(int argc, char **argv)
{
  cr_mount(argv[1]);
  printf("Ruta global: %s\n", ruta);
  printf("Primer print del proyecto 1\n");
  imprimir_desde_otro_archivo();
  FrameBitmap bitmap = frameBitmapInit();
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);

}