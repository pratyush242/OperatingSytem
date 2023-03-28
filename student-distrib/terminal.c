#include "terminal.h"
#include "keyboard.h"
#include "lib.h"

int terminal_read(unsigned char * buf, int nbytes){

		return 0;
	}


int terminal_write(char* buf , int  nbytes){

    int i;
    int j = 0;

    for(i = 0;i<nbytes;i++){
        if(buf){
        if(buf[i] != 0){
            putc(buf[i]);
            j+=1;
        }
        }
    }
    return j;
   // return 0;

}

int terminal_open(){
    return 0;

}
int terminal_close(){
    return 0;
}

