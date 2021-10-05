#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#pragma once

typedef struct frameBitmap
{
  int data[16];
} FrameBitmap;

FrameBitmap frameBitmapInit();
void frameBitmapChangeToOne(FrameBitmap fb, int position);
void frameBitmapChangeToZero(FrameBitmap fb, int position);