#ifndef PAGING_H
#define PAGING_H


#ifndef ASM

#include "x86_desc.h"

void initializeTable();

void initializeDirectory();

extern void enablePaging();

extern void loadDirectory(PageDirectoryEntry* pg_dir);

#endif
#endif

