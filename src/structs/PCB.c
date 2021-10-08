#include "PCB.h"


PageTable pagetable_init(){
    PageTable pt;
    pt.data=0;
    return pt;
};

SubEntrada subentrada_init(){
    SubEntrada se;

    se.validez = 0;

    for (int largo = 0; largo < 12; largo ++){
        se.file_name[largo] = 'x';
    }

    se.file_size = 0;
    se.virtual_adress = 0;
    return se;
};

Entrada entrada_init(){
    Entrada e;
    e.estado = 0;
    e.id = 0;
    for (int largo = 0; largo < 12; largo ++){
        e.name[largo] = 'x';
    }
    for (int largo = 0; largo < 10; largo ++){
        e.subentradas[largo] = subentrada_init();
    }
    for (int largo = 0; largo < 32; largo ++){
        e.pageTable[largo] = pagetable_init();
    }
    return e;
};



TablePCB tablepcb_init(){
    TablePCB tpcb;
    
    for (int largo = 0; largo < 16; largo ++){
        tpcb.entradas[largo] = entrada_init();
    }

    return tpcb;
};
