#ifndef _TERMINAL_H
#define _TERMINAL_H


int terminal_open();
int terminal_close();
int terminal_write(char* buf , int  nbytes);
int terminal_read(unsigned char * buf, int nbytes);





#endif
