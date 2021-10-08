#include <stdio.h>  // FILE, fopen, fclose, etc.
#include <string.h> // strtok, strcpy, etc.
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#pragma once

typedef struct pageTable
{
  int data; //1 bit de validez y 7 bits de PFN
  
} PageTable;

typedef struct subentrada
{
  int validez; // 1 byte
  char file_name[12]; // 12 bytes
  int file_size; //4 bytes
  int virtual_adress; //4 bytes (4bits no significativos + 5 bits VPN +23 offset) 
} SubEntrada;

typedef struct entrada
{
  int estado; //1 byte
  int id; // 1 byte
  char name[12]; //12 bytes
  SubEntrada subentradas[10];
  PageTable pageTable[32];
} Entrada;

typedef struct tablepcb
{
  Entrada entradas[16];
} TablePCB;

TablePCB tablepcb_init();
Entrada entrada_init();
SubEntrada subentrada_init();
PageTable pagetable_init();
