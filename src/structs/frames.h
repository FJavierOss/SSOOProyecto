#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#pragma once


typedef struct frames
{
  Frame frames[128];
} Frames;

typedef struct frame //tiene 8mega bytes de info
{
    int info[8388608]; //número de bytes en 8 mega bytes DUDA DE QUE ES 4GB EN 1GB 
} Frame;