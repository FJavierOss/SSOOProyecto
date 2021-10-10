#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <byteswap.h>
#pragma once



int checkPosStatusFB(int pos_to_check, char* ruta);
void frameBitmapChangeToOne(int pos_to_check, char* ruta);
void frameBitmapChangeToZero(int pos_to_check, char* ruta);
/*
typedef struct frameBitmap
{
  int data[16];
} FrameBitmap;

FrameBitmap frameBitmapInit();
void frameBitmapChangeToOne(FrameBitmap fb, int position);
void frameBitmapChangeToZero(FrameBitmap fb, int position);

*/
