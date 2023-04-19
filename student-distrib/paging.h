#ifndef PAGING_H
#define PAGING_H


#ifndef ASM

#include "x86_desc.h"

PageDirectoryEntry PageDir[1024] __attribute__((aligned (4096))); 
PageTableEntry PageTable[1024] __attribute__((aligned (4096))); 
PageTableEntry video_page_table[1024] __attribute__((aligned(4096)));

void initializeTable();

void initializeDirectory();
extern void sysCallPaging(uint32_t pid);
extern void enablePaging();

extern void loadDirectory(PageDirectoryEntry* pg_dir);
extern void flush();
#endif
#endif
