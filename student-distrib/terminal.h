#ifndef _TERMINAL_H
#define _TERMINAL_H


#include "keyboard.h"
#include "lib.h"
#include "types.h"

extern int32_t terminal_open(const char* fname);
extern int32_t terminal_close(int32_t fd);
extern int32_t terminal_write(int32_t fd, void* buf, int32_t nbytes);
extern int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes);





#endif


