

#include "paging.h"



//function to initialize tables

void initializeTable() {

    int i; 
   
    for (i=0; i < 1024; i++) {
       PageTable[i].Present = 0;
       PageTable[i].ReadWrite = 1;
       PageTable[i].UserSupervisor = 0;
       PageTable[i].WriteThrough= 0;
       PageTable[i].CacheDisabled = 0;
       PageTable[i].Accessed = 0;
       PageTable[i].Dirty= 0;
       PageTable[i].PageTableAttr = 0;
       PageTable[i].GlobalPage = 1;
       PageTable[i].ProgUse = 0;
       PageTable[i].PageBaseAddr = 0x2;
    }
    PageTable[0xB8].PageBaseAddr = 0xB8;
    PageTable[0xB8].Present = 1;

}

//function to initialize directories

void initializeDirectory(){
    int i;
    for (i=0; i < 1024; i++) {
        PageDir[i].FourMB.Present = 0;
        PageDir[i].FourMB.ReadWrite = 1;
        PageDir[i].FourMB.UserSupervisor = 0;
        PageDir[i].FourMB.WriteThrough  = 0;
        PageDir[i].FourMB.CacheDisabled  = 0;
        PageDir[i].FourMB.Accessed  = 0;
        PageDir[i].FourMB.Dirty   = 0;
        PageDir[i].FourMB.PageSize  = 0;
        PageDir[i].FourMB.GlobalPage  = 0;
        PageDir[i].FourMB.ProgUse  = 0;
        PageDir[i].FourMB.PageTableAttr = 0;
        PageDir[i].FourMB.Reserved  = 0;

        PageDir[i].FourMB.PageBaseAddr  = 0x0; 
    }

    //initialize video memory

    PageDir[0].FourKB.Present = 1;
    PageDir[0].FourKB.ReadWrite = 0;
    PageDir[0].FourKB.UserSupervisor = 0;
    PageDir[0].FourKB.WriteThrough = 0;
    PageDir[0].FourKB.CacheDisabled = 0;
    PageDir[0].FourKB.Accessed= 0;
    PageDir[0].FourKB.Reserved = 0;
    PageDir[0].FourKB.PageSize = 0;
    PageDir[0].FourKB.GlobalPage = 0;
    PageDir[0].FourKB.ProgUse = 0;
    PageDir[0].FourKB.PageBaseAddr = (uint32_t)PageTable>>12;



    

    //map kernel
    PageDir[1].FourMB.Present = 1;
    PageDir[1].FourMB.ReadWrite = 1;
    PageDir[1].FourMB.UserSupervisor = 0;
    PageDir[1].FourMB.WriteThrough  = 0;
    PageDir[1].FourMB.CacheDisabled  = 0;
    PageDir[1].FourMB.Accessed  = 0;
    PageDir[1].FourMB.Dirty   = 0;
    PageDir[1].FourMB.PageSize    = 1;
    PageDir[1].FourMB.GlobalPage  = 1;
    PageDir[1].FourMB.ProgUse   = 0;
    PageDir[1].FourMB.PageTableAttr = 0;
    PageDir[1].FourMB.Reserved  = 0;

    PageDir[1].FourMB.PageBaseAddr  = 0x400000 >>22;
    
    loadDirectory(PageDir); 
    enablePaging();
    return; 

}


