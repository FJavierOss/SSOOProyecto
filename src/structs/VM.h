#pragma once

typedef struct virtualMemory
{
  Page pages[256*1048576]; //tiene 256 MB 
} VirtualMemory;

typedef struct page //tiene 8mega bytes de info
{
    int info[8388608]; //número de bytes en 8 mega bytes DUDA DE QUE ES 4GB EN 1GB 
} Page;