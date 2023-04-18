#include "terminal.h"
#include "keyboard.h"
#include "lib.h"

/* terminal_read
 * 
 * read the keyboard buffer input and store it into the terminal buffer
 * Inputs: fd - file descripor; buf - a buffer that hold the terminal input; nbytes - the number of bytes to read from the keyboard buffer
 * Outputs: the actual number of bytes that are read successfully, if error then ret -1
 */
int32_t terminal_read(int32_t fd, void* buf, int32_t nbytes){
    if(NULL == buf || 0 == nbytes){
        return 0;
    }
    int i;
    int j = 0;
    int k = 0; 
    while(1)
    {
        sti();
        if (read_the_terminal == 1){
            cli();
            break;
        }   
    }
    for (i = 0; (i < nbytes) && (i < 127); i++)
    {
        ((char*)buf)[i] = key_buffer[i];
        if (key_buffer[i] == '\n')
        {
            k = 1;
            ((char*)buf)[i] = '\0';
        }
        if (k == 0){
            j++;
        }
    }
    clear_buffer();
    return j;
	}

/* terminal_write
 * 
 * write the corresponding number of bytes of a buffer to the terminal
 * Inputs: fd - file descripor; buf - a buffer that hold the terminal input; nbytes - the number of bytes to write from the  buffer to terminal
 * Outputs: the actual number of bytes that are written successfully, if error then ret -1
 */
int32_t terminal_write(int32_t fd, void* buf, int32_t nbytes){
    if(NULL == buf){
        return -1;
    }
    int i;
    int j = 0;
    for(i = 0;i<nbytes;i++){
        putc(((char*)buf)[i]);
        if(((char*)buf)[i] != '\0'){
            j+=1;
        }
    }
    return j;
   // return 0;

}
/* terminal_open
 * 
 * open the terminal
 * Inputs: fname is file name not being used
 * Outputs: none
 */
int32_t terminal_open(const char* fname){
    return 0;

}
/* terminal_close
 * 
 * closes the terminal
 * Inputs: file directory not being used
 * Outputs: none
 */
int32_t terminal_close(int32_t fd){
    return 0;
}

