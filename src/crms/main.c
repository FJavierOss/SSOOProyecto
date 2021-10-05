#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include "../imprimir/imprimir.h"
#include "../structs/bitmap.h"

int main(int argc, char **argv)
{
  printf("Primer print del proyecto 1\n");
  imprimir_desde_otro_archivo();
  FrameBitmap bitmap = frameBitmapInit();
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToOne(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);
  frameBitmapChangeToZero(bitmap, 127);

}