#include "terminal.h"

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

        if(curr_terminal_ID == runningTerminal->id){


        adjustVIDMEM(0xB8000);


    }
    else{

    adjustVIDMEM(multi_terminal[runningTerminal->id].vidmem);


    }
    int i;
    int j = 0;
    int k = 0; 
    while(1)
    {
        sti();
        if (multi_terminal[curr_terminal_ID].read_the_terminal == 1){
            cli();
            break;
        }   
    }
    for (i = 0; (i < nbytes) && (i < 127); i++)
    {
        ((char*)buf)[i] = multi_terminal[curr_terminal_ID].terminal_buffer[i];
        if (multi_terminal[curr_terminal_ID].terminal_buffer[i] == '\n')
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

    if(curr_terminal_ID == runningTerminal->id){


        adjustVIDMEM(0xB8000);


    }
    else{

    adjustVIDMEM(multi_terminal[runningTerminal->id].vidmem);


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
/* terminal_init
 *
 * initialize all terminals 
 * Inputs: none
 * Outputs: 0
 * Return: 0 if success, 1 if fail
 */
int32_t terminal_init()
{
    init_vidmem();
    int i,j;
    for(i = 0; i < 3; i++){
        // set inital values of multiterminal 
        multi_terminal[i].id = i;
        multi_terminal[i].pid = -1;
        multi_terminal[i].x = 0;
        multi_terminal[i].y = 0;


        // init terminal buffer
        for(j = 0; j < 128; j++)
            multi_terminal[i].terminal_buffer[j] = '\0';
    }
    curr_terminal_ID = -1;
    
    runningTerminal = &(multi_terminal[0]);

    multi_terminal[0].vidmem = 0xB9000;   
    multi_terminal[1].vidmem = 0xBA000; 
    multi_terminal[2].vidmem = 0xBB000; 

    return 0;
  
}

int32_t terminal_switch(uint32_t terminal_ID)
{
   
    cli();
    // if it is the current terminal, do nothing 
    if(curr_terminal_ID == terminal_ID){
        sti();
        return 0;
    }
    // save terminal  
    terminal_save(curr_terminal_ID);
    
     remap_vidmem(terminal_ID);
    // restore terminal  
    terminal_return(terminal_ID);
    //it is the new terminal, run shell for this terminal 
   
    
   
    sti();

    
    return 0;
}

int32_t terminal_save(uint32_t terminal_ID)
{
    if(terminal_ID >= 3){
        return -1;
    }
    // save current cursor position 
    multi_terminal[terminal_ID].x = get_x();
    multi_terminal[terminal_ID].y = get_y();
    return 0;
}

int32_t terminal_return(uint32_t terminal_ID)
{
    if(terminal_ID >= 3) {
        return -1;
    }
    // set current terminal id 
    curr_terminal_ID = terminal_ID;
    // restore current cursor position 
    set_xy(multi_terminal[terminal_ID].x, multi_terminal[terminal_ID].y);

    return 0;
}
