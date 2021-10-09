#include "../imprimir/imprimir.h"
#include "../structs/bitmap.h"
#pragma once

typedef struct crmsFile CrmsFile;

char* ruta;

void cr_mount(char* memory_path);
void cr_ls_processes();
int cr_exists(int process_id, char* file_name);
void cr_ls_files(int process_id);