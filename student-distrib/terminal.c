#include "terminal.h"
#include "keyboard.h"
#include "lib.h"

int terminal_read(unsigned char * buf, int nbytes){
    int i;
    int j = 0;
    int k = 0; 
    while(1)
    {
        if (read_the_terminal == 1){
            break;
        }   
    }
    for (i = 0; (i < nbytes) && (i < 127); i++)
    {
        buf[i] = key_buffer[i];
        if (key_buffer[i] == '\n')
        {
            k = 1;
            buf[i] = '\0';
        }
        if (k == 0){
            j++;
        }
    }
    clear_buffer();
    return j;
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

