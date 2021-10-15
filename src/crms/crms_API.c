#include "crms_API.h"


void cr_mount(char* memory_path)
{
  ruta = memory_path;
}


void cr_ls_processes(){
  int num = 0;
  char name[12];
  FILE * fp;
  fp = fopen(ruta, "rb+");
  printf("      Running Processes      \n");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    if(num == 1){
      printf("\n| Status %d", num);
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);
      printf("| ID %*d", 4,num);
      printf("| Name <");

      for (int j = 2; j < 14; j++){
        fseek( fp, j+256*k, SEEK_SET);
        fread(&num, 1, 1, fp);
        name[j-2] = num;
        printf("%c", num);
      }
      printf(">");
    }
  }
  printf("\n");
  fclose(fp);
}

void cr_ls_files(int process_id){
  int num = 0;
  int process_exists = 0;
  FILE * fp;
  fp = fopen(ruta, "rb+");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    // Aqui podriamos chequear esta vivo o no. (num  == 1)
    // Hay que preguntar al ayudante si procesos con
    // status 0 se incluyen dentro de la operacion
    if( 1 ){
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      if( num == process_id){
        process_exists = 1;
        printf("\n      Process %d Files      \n", process_id);

        // Hay 10 entradas cada 1 con 21 bytes
        for (int j = 0; j < 10; j++){

          fseek( fp, 21*j+14+256*k, SEEK_SET);
          fread(&num, 1, 1, fp);
          if (num == 1){
            printf("\nFile Name | ");
            for (int i = 1; i<13; i++){
              fseek( fp, 21*j+i+14+256*k, SEEK_SET);
              fread(&num, 1, 1, fp);
              printf("%c", num);
            }
          }

        }
      }
    }
  }
  printf("\n");
  fclose(fp);

  if (!process_exists){
    printf("No hay procesos con ese id\n");
  }
}


int cr_exists(int process_id, char* file_name){
  int num = 0;
  char name[12];
  int check_existence = 0;
  int process_exists = 0;
  FILE * fp;
  fp = fopen(ruta, "rb+");

  for (int k = 0; k < 16; k++){
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);

    // Aqui podriamos chequear esta vivo o no. (num  == 1)
    // Hay que preguntar al ayudante si procesos con
    // status 0 se incluyen dentro de la operacion
    if( 1 ){
      fseek( fp, 1+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      if( num == process_id){
        process_exists = 1;

        // Hay 10 entradas cada 1 con 21 bytes
        for (int j = 0; j < 10; j++){
          fseek( fp, 21*j+14+256*k, SEEK_SET);
          fread(&num, 1, 1, fp);

          if ((num == 1) && (check_existence != 1) ){
            check_existence = 1;

            for (int i = 1; i<13; i++){
              fseek( fp, 21*j+i+14+256*k, SEEK_SET);
              fread(&num, 1, 1, fp);
              
              if (num && check_existence){
                if(num != file_name[i-1]){
                  check_existence = 0;
                }
              }

            }
          }

        }
      }
    }
  }
  printf("\n");
  fclose(fp);

  if (!process_exists){
    printf("No hay procesos con ese id\n");
    return 0;
  }
  return check_existence;
}

void cr_start_process(int process_id, char* process_name){

   FILE * fp;
  fp = fopen(ruta, "rb+");
 
  unsigned int aux=0;
  unsigned int num = 0;
  printf("%i \n",strlen(process_name));
  char name[12];
  

  for(int k=0;k<16;k++){
    
    fseek(fp, 1+256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    
    if (num==process_id){
      printf("YA EXISTE ESTE ID \n");
      return; 
    }
  };

  for(int k=0;k<16;k++){
    
    fseek( fp, 256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
   
    if(num==0){ //No se está ejecutando el proceso asignado a ese espacio (si es que hay proceso)
      
      num=1;
      //seteamos estado
      fseek( fp, 256*k, SEEK_SET);
      fwrite(&num, 1, 1, fp);
      //seteamos id 
      fseek( fp, 1+256*k, SEEK_SET);
      fwrite(&process_id, 1, 1, fp);
      //seteamos nombre
      for (int j = 2; j < strlen(process_name)+2; j++){
        fseek( fp, j+256*k, SEEK_SET);
        fwrite(&process_name[j-2], 1, 1, fp);
      }
     
      break;
    }
  };
  fclose(fp);

  printf("NO SE ENCONTRÖ UN ESPACIO PARA INICAR PROCESO\n");
  return;  
};


void cr_finish_process(int process_id){

   FILE * fp;
  fp = fopen(ruta, "rb+");
 
  unsigned int aux=0;
  unsigned int num = 0;
  char name[12];
  
  

  for(int k=0;k<16;k++){
    
    fseek(fp, 1+256*k, SEEK_SET);
    fread(&num, 1, 1, fp);
    
    if (num==process_id){
      num=0;
      
      for(int m=0;m<256;m++){
        fseek( fp, m+256*k, SEEK_SET);
        fwrite(&num, 1, 1, fp);
      }
      printf("El proceso termino\n");
      return; 
    }
  };
  fclose(fp);
  printf("No se encontró un proceso con ese id\n");
  
  return;  
};

CrmsFile* cr_open(int process_id, char* file_name, char mode)
{
  FILE* fp;
  CrmsFile* crms_file = malloc(sizeof(CrmsFile));
  crms_file -> pointer = 0;
  char name[12];
  int num = 0;
  int direccion_virtual;
  int tamano;
  unsigned int pagina;
  unsigned int bit_validez_pagina;
  unsigned int PFN;
  int memoria_fisica;
  int memoria_fisica_abosluta;
  if (mode == 'r')
  {
    fp = fopen(ruta, "rb+");

    for (int k = 0; k < 16; k++)
    {
      fseek( fp, 256*k, SEEK_SET);
      fread(&num, 1, 1, fp);

      // Aqui podriamos chequear esta vivo o no. (num  == 1)
      // Hay que preguntar al ayudante si procesos con
      // status 0 se incluyen dentro de la operacion
      if( 1 )
      {
        fseek( fp, 1+256*k, SEEK_SET);
        fread(&num, 1, 1, fp);
        if(num == process_id)
        {
          // Hay 10 entradas cada 1 con 21 bytes
          for (int j = 0; j < 10; j++)
          {
            fseek( fp, 21*j+14+256*k, SEEK_SET);
            fread(&num, 1, 1, fp);
            if (num == 1)
            {

              for (int i = 1; i<13; i++){
                fseek( fp, 21*j+i+14+256*k, SEEK_SET);
                fread(&num, 1, 1, fp);
                name[i-1] = num;
              }
              // printf("NOMBRE: %s\n", name);
              if (!strcmp(name, file_name))
              {
                // printf("HOLAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
                // printf("%s\n", name);
                fseek(fp, 21*j+13+14+256*k, SEEK_SET);
                fread(&num, 4, 1, fp);
                
                tamano = bswap_32(num);
                // printf("tamano archivo: %i\n", tamano);
                fseek(fp, 21*j+17+14+256*k, SEEK_SET);
                fread(&num, 4, 1, fp);
                
                direccion_virtual = bswap_32(num);
                int offset = (direccion_virtual << 9) >> 9;
                int VPN = direccion_virtual >> 23;

                fseek(fp, 224+256*k+VPN, SEEK_SET);
                num = 0;
                fread(&num, 1, 1, fp);
                pagina = num;
                bit_validez_pagina = pagina >> 7;
                PFN = (pagina & ~(0x01 << 7));
                memoria_fisica = (PFN << 23) | offset;
                memoria_fisica_abosluta = memoria_fisica + pow(2, 12) + pow(2, 4);

                crms_file -> size = tamano;
                crms_file -> virtual_address = direccion_virtual;
                crms_file -> offset = offset;
                crms_file -> VPN = VPN;
                crms_file -> PFN = PFN;
                crms_file -> fisic_address = memoria_fisica;
                crms_file -> proces_id = process_id;
                crms_file -> file_name = file_name;
                crms_file -> page_table = pagina;
                crms_file -> content = calloc(sizeof(char), crms_file -> size);
                crms_file -> pointer = 0;
                for (int z = 0; z< crms_file -> size; z++)
                {
                  fseek(fp, memoria_fisica_abosluta + z, SEEK_SET);
                  num = 0;
                  fread(&num, 1, 1, fp);
                  crms_file -> content[z] = num;
                  
                }

                // printf("Contenido gigante: %s\n", crms_file->content);


              }
              
            }
          }
        }
      }
    }
    fclose(fp);
    return crms_file;
  }
  else if (mode == 'w')
  {
    if (!cr_exists(process_id, file_name))
    {
      crms_file -> file_name = file_name;
      crms_file -> proces_id = process_id;
      crms_file -> size = 0;
      crms_file -> virtual_address = NULL;
      crms_file -> offset = NULL;
      crms_file -> VPN = NULL;
      crms_file -> PFN = NULL;
      crms_file -> fisic_address = NULL;
      crms_file -> page_table = NULL;
      crms_file -> pointer = 0;
      return crms_file;
    }
    else 
    {
      // printf("El archivo ya existe\n");
      free(crms_file);
      return NULL;
      
    }
  }
  else
  {
    // printf("Modo inválido\n");
    free(crms_file);
    return NULL;
  }
}

int cr_write_file(CrmsFile* file_desc, void* buffer, int n_bytes)
{
  FILE* fp;
  fp = fopen(ruta, "rb+");
  int num = 0;
  int bitmap = pow(2, 12);
  int memoria_fisica_inicio = pow(2, 12) + pow(2, 4);
  int frame;
  bool encontrado = false;
  bool encontre_espacio = false;
  
  for (int k = 0; k < 16; k++)
    {
      fseek(fp, 256*k+1, SEEK_SET);
      fread(&num, 1, 1, fp);
      if (num == file_desc -> proces_id)
      {
        for (int i = 0; i < 10; i++)
        {
          fseek(fp, 256*k + 14 + 21*i, SEEK_SET);
          fread(&num, 1, 1, fp);
          // byte de validez
          if (num == 0 && !encontre_espacio) // Encontré el lugar
          {
            
            encontre_espacio = true;
            const char escribir = 0x01;
            fseek(fp, 256*k + 14 + 21*i, SEEK_SET);
            fwrite(&escribir, 1, 1, fp); // Se cambia a 1
            fseek(fp, 256*k + 14 + 21*i+1, SEEK_SET); // Se escribe el nombre del archivo
            for(int q = 0; q < 12; q++)
            {
              fwrite(&file_desc -> file_name[q], 1, 1, fp);
            }
            
            
            fseek(fp, 256*k + 14 + 21*i+1, SEEK_SET);
            char arr[12];
            for(int q = 0; q < 12; q++)
            {
              fread(&arr[q], 1, 1, fp);
            }
            
            // printf("Nombre archivo: %s\n", arr);
            // printf("Nombre archivo: %s\n", file_desc -> file_name);
            int offset;
            int direccion_virtual_anterior;
            int VPN;
            int offset_anterior;
            int VPN_anterior;
            int pagina;
            int bit_validez_pagina;
            int PFN;
            int memoria_fisica;
            int memoria_fisica_absoluta;
            bool encontre_libre = false;
            if (i == 0) // primero de la página
            {
              offset = 0;
              // printf("Estoy al inicio \n");
              for (int j = 0; j < 16; j++)
              {
                fseek(fp, bitmap + j, SEEK_SET);
                num = 0;
                fread(&num, 1, 1, fp);
                for (int bit = 0; bit < 8; bit++)
                {
                  int valor_bit = (num >> (7 - bit)) & 0x01;
                  if (valor_bit == 0) // está libre
                  {
                    frame = bit + (8 * j);
                    encontrado = true;
                    break;
                  }
                }
                if (encontrado)
                {
                  break;
                }
              }
              memoria_fisica = (frame << 23) | offset;
              memoria_fisica_absoluta = memoria_fisica + pow(2, 12) + pow(2, 4);
              file_desc -> fisic_address = memoria_fisica;
              fseek(fp, memoria_fisica_absoluta, SEEK_SET);
              for (int r = 0;r < n_bytes; r++)
              {
                fwrite(&buffer[r], 1, 1, fp);
              }
              
              for (int w = 0; w < 32; w++)
              {
                fseek(fp, 224+256*k + w, SEEK_SET);
                fread(&num, 1, 1, fp);
                pagina = num;
                PFN = (pagina & ~(0x01 << 7));
                int validez = (pagina >> 7) & 0x01;
                // printf("PFN: %i\n", PFN);
                // printBits(sizeof(pagina), &pagina);
                // printBits(sizeof(PFN), &PFN);
                // printBits(sizeof(frame), &frame);
                // printf("----------------------------------\n");
                if (PFN == frame)
                {
                  file_desc -> VPN = w;
                  file_desc -> virtual_address = w << 23 | offset;
                  fseek(fp, 224+256*k + w, SEEK_SET);
                  int entrada = 0x01 << 7 | frame;
                  fwrite(&entrada, 1, 1, fp);
                  encontre_libre = true;
                }
              }
              for (int w = 0; w < 32; w++)
              {
                fseek(fp, 224+256*k + w, SEEK_SET);
                fread(&num, 1, 1, fp);
                pagina = num;
                PFN = (pagina & ~(0x01 << 7));
                int validez = (pagina >> 7) & 0x01;
                
                if (validez == 0 && !encontre_libre) // busco una tabla vacía
                {  
                  file_desc -> VPN = w;
                  file_desc -> virtual_address = w << 23 | offset;
                  encontre_libre = true;
                  fseek(fp, 224+256*k + w, SEEK_SET);
                  int entrada = 0x01 << 7 | frame;
                  // printBits(sizeof(entrada), &entrada);
                  // printBits(sizeof(frame), &frame);
                  // printBits(sizeof(file_desc -> VPN), &file_desc -> VPN);
                  fwrite(&entrada, 1, 1, fp);
                  break;
                }
              }
              if(!encontre_libre)
              {
                printf("No hay tablas de página disponibles");
                return 0;
              }
              fseek(fp, 256*k + 14 + 21*i+17, SEEK_SET); // Se escribe el nombre del archivo
              int memoria_v = bswap_32(file_desc -> virtual_address);
              fwrite(&memoria_v, 4, 1, fp);
              file_desc -> size = n_bytes;
              fseek(fp, 256*k + 14 + 21*i+13, SEEK_SET);
              int n = bswap_32(n_bytes);
              fwrite(&n, 4, 1, fp);
              num = 0;
              fseek(fp, 256*k + 14 + 21*i+13, SEEK_SET);
              fread(&num, 4, 1, fp);
              // printf("Memoria virtual: %i\n", memoria_v);
              // printf("Memoria virtual: %i\n", file_desc -> virtual_address);
              // printf("Memoria física: %i\n", memoria_fisica);
              // printf("Memoria física absoluta: %f\n", memoria_fisica + pow(2, 12) + pow(2, 4));
              // printf("TAMAÑO ARCHIVO %i\n", bswap_32(num));
            }
            else // nos encontramos en otro lugar que no sea en la primera página
            {
            
              num = 0;
              fseek(fp, 256*k + 14 + 21*i - 4, SEEK_SET);
              fread(&num, 4, 1, fp);
              printf("\n");
              direccion_virtual_anterior = bswap_32(num);
              // printf("DIRECCION VIRTUAL ANTERIOR: %i\n", direccion_virtual_anterior);
              VPN_anterior = direccion_virtual_anterior;
              offset_anterior = direccion_virtual_anterior;
              fseek(fp, 256*k + 21*i - 8 + 14, SEEK_SET);
              fread(&num, 4, 1, fp);
              int espacio_anterior = bswap_32(num);
              unsigned int memoria_virtual;
              for (int u = 23; u <= 27; u++)
              {
                offset_anterior = offset_anterior & (~(0x01 << u));
              }
              VPN_anterior = VPN_anterior >> 23;

              
              memoria_virtual = direccion_virtual_anterior + espacio_anterior;
              // printf("MEMORIA VIRTUAL: %i\n", memoria_virtual);
              fseek(fp, 224+256*k + VPN_anterior, SEEK_SET);
              fread(&num, 1, 1, fp);
              int PFN_anterior = (num & ~(0x01 << 7));
              int memoria_fisica_anterior = PFN_anterior << 23 | offset_anterior;
              int memoria_fisica = memoria_fisica_anterior + espacio_anterior;
              int PFN = memoria_fisica >> 23;


              fseek(fp, 224+256*k + VPN, SEEK_SET);
              fread(&num, 1, 1, fp);
              pagina = num;
              int validez = (pagina >> 7) & 0x01;
              if (validez == 0)
              {
                int entrada = 0x01 << 7 | PFN;
              }

              file_desc -> virtual_address = memoria_virtual;
              fseek(fp, 256*k + 14 + 21*i+17, SEEK_SET);
              fwrite(&memoria_virtual, 4, 1, fp);
              fseek(fp, 224+256*k+VPN, SEEK_SET);
              num = 0;
              fread(&num, 1, 1, fp);
              pagina = num;
              bit_validez_pagina = pagina >> 7;
              PFN = (pagina & ~(0x01 << 7));
              // memoria_fisica = (PFN << 23) | offset;
              memoria_fisica_absoluta = memoria_fisica + pow(2, 12) + pow(2, 4);
              file_desc -> fisic_address = memoria_fisica;
              fseek(fp, memoria_fisica_absoluta, SEEK_SET);
              for (int r = 0;r < n_bytes; r++)
              {
                fwrite(&buffer[r], 1, 1, fp);
              }
              int n = bswap_32(n_bytes);
              file_desc -> size = n_bytes;
              fseek(fp, 256*k + 14 + 21*i+13, SEEK_SET);
              fwrite(&n, 4, 1, fp);
              fseek(fp, 256*k + 14 + 21*i+13, SEEK_SET);
              num = 0;
              fread(&num, 4, 1, fp);

              // printf("MEMORIA VIRTUAL ANTERIOR: %i\n", direccion_virtual_anterior);
              // printf("MEMORIA VIRTUAL: %i\n", memoria_virtual);
              // printf("MEMORIA FISICA ABSOLUTA: %i\n", memoria_fisica_absoluta);
              // printf("TAMAÑO ARCHIVO %i\n", file_desc -> size);
              // printf("TAMAÑO ARCHIVO %i\n", bswap_32(num));

            }
            
          }

        }
        if (encontre_espacio)
        {
          break;
        }
      }
      if (encontre_espacio)
      {
        break;
      }
    }
  fclose(fp);
  return 0;
}

int cr_read(CrmsFile* file_desc, void* buffer, int n_bytes)
{
  
  FILE* fp;
  fp = fopen(ruta, "rb+");
  
  
  int memoria_fisica_abosluta = file_desc -> fisic_address + pow(2, 12) + pow(2, 4);
  int leo;
  
  // printf("Fisic address: %d\n", file_desc -> fisic_address);
  // printf("Pointer: %i\n", file_desc -> pointer);
  // printf("Tamano archivo: %i\n", file_desc -> size);
  if (file_desc -> pointer + n_bytes > file_desc -> size)
  {
    leo = file_desc -> size - file_desc -> pointer;
  }
  else
  {
    leo = n_bytes;
  }
  if (leo == 0)
  {
    // printf("LEO MESSI\n");
    return leo;
  }
  
  fseek(fp, memoria_fisica_abosluta  + file_desc -> pointer, SEEK_SET);
  // char arreglo[leo];
  // for (int i = 0; i < leo; i++)
  // {
  //   arreglo[i] = file_desc -> content[file_desc -> pointer + leo + i];
  // }
  

  // buffer = arreglo;
  file_desc -> pointer += leo;
  fread(buffer, 1, leo, fp);
  
  
  // printf("\n");
  
  //fclose(fp);
  //printf("HOLAAAAAAAAAAAAAA\n");
  // printf("LEO: %i\n", leo);
  return leo;
} 

void cr_delete_file(CrmsFile* file_desc)
{
  FILE* fp;
  fp = fopen(ruta, "rb+");
  int num = 0;
  char name[12];
  int memoria = file_desc -> fisic_address;
  int memoria_virtual = file_desc -> virtual_address;
  int VPN = memoria_virtual >> 23;
  int PFN = memoria >> 23;
  int proceso;
  int bitmap = pow(2, 12);
  for (int k = 0; k < 16; k++)
  {
    fseek( fp, 256*k+1, SEEK_SET);
    fread(&num, 1, 1, fp);
    if (num == file_desc -> proces_id)
    {
      proceso = k;
      for (int j = 0; j < 10; j++)
      {
        fseek( fp, 21*j+14+256*k, SEEK_SET);
        fread(&num, 1, 1, fp);
        if (num == 1)
        {
          for (int i = 1; i<13; i++)
          {
            fseek( fp, 21*j+i+14+256*k, SEEK_SET);
            fread(&num, 1, 1, fp);
            name[i-1] = num;
          }
          // printf("NOMBRE: %s\n", name);
          if (!strcmp(name, file_desc -> file_name))
          {
            for (int r = 0; r < 21; r++) // borro toda la página
            {
              fseek( fp, r+14+256*k+21*j, SEEK_SET);
              int cero = 0;
              fwrite(&cero, 1, 1, fp);
            }
            
          }
        }

      }
    }
  }
  int memoria_fisica = file_desc ->fisic_address + pow(2, 12) + pow(2, 4);
  for (int i = 0; i < file_desc -> size; i++)
  {
    fseek(fp, memoria_fisica, SEEK_SET);
    int cero = 0;
    fwrite(&cero, 1, 1, fp);
    // ver que ninún archivo del proceso usa el frame
    // 
  }
  bool borrar = true;
  for (int k = 0; k < 16; k++)
  {
    for (int j = 0; j < 10; j++)
    {
      fseek( fp, 21*j+14+256*k, SEEK_SET);
      fread(&num, 1, 1, fp);
      if (num == 1)
      {
        
        fseek(fp, 224+256*k+VPN, SEEK_SET);
        num = 0;
        fread(&num, 1, 1, fp);
        int pagina = num;
        int bit_validez_pagina = pagina >> 7;
        int PFN_nuevo = (pagina & ~(0x01 << 7));
        if (bit_validez_pagina == 1 && PFN == PFN_nuevo)
        {
          borrar = false;
        }

      }
    }
  }
  if (borrar)
  {
    int cero = 0;
    fseek(fp, 224+256*proceso+VPN, SEEK_SET);
    fwrite(&cero, 1, 1, fp); // Borro entrada tabla de páginas
    VPN = memoria_virtual >> 23;
    PFN = memoria >> 23;
    int byte = PFN / 8;
    int bit = PFN % 8;
    fseek(fp, bitmap + byte, SEEK_SET);
    num = 0;
    fread(&num, 1, 1, fp);
    int final = (num & ( ~( 0x01 << bit)));
    fseek(fp, bitmap + byte, SEEK_SET);
    fwrite(&final, 1, 1, fp);

  }
  
  fclose(fp);
}

void cr_close(CrmsFile* file_desc)
{
  if (file_desc -> content)
  {
    free(file_desc -> content);
  }
  free(file_desc);
}