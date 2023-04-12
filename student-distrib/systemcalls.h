#ifndef _SYSTEMCALLS_H
#define _SYSTEMCALLS_H

#include "types.h"
#include "filesys.h"
#include "terminal.h"
#include "rtc.h"

//pcb_t* pcb_adress(uint32_t pid);

int32_t sys_open(const char* fname);

int32_t sys_close(int32_t fd);

int32_t sys_read(int32_t fd, void* buf, int32_t nbytes);

int32_t sys_write(int32_t fd, void* buf, int32_t nbytes);

int32_t system_execute(const uint8_t* cmd);

int32_t halt(uint8_t status);

uint32_t null_open();

uint32_t null_read();

uint32_t null_write();

uint32_t null_close();




/* struct for fops */
typedef struct fops_table_t {
    int32_t (*read)(int32_t fd, void* buf, int32_t nbytes);
    int32_t (*write)(int32_t fd, void* buf, int32_t nbytes);
    int32_t (*open)(const char* fname);
    int32_t (*close)(int32_t fd);
} fops_table_t;

typedef struct file_descriptor_t {
    fops_table_t* op;    // file operator table 
    uint32_t inode;     // inode index 
    uint32_t fileoffset;   // offset in current file 
    uint32_t flags;        
} file_descriptor_t;

// pointer pointing to fd array
file_descriptor_t* file_descriptor_array;

static fops_table_t fopsarray[6];
void file_op_table_init()
{
    // init rtc operation table 
    fopsarray[0].open  = rtc_open;
    fopsarray[0].close = rtc_close;
    fopsarray[0].read  = rtc_read;
    fopsarray[0].write = rtc_write;

    // init dir operation table 
    // fopsarray[1].open  = open_directory ;
    // fopsarray[1].close = close_directory;
    fopsarray[1].read  = read_directory ;
    // fopsarray[1].write = write_directory;

    // init file operation table 
    fopsarray[2].open  = open;
    fopsarray[2].close = close;
    fopsarray[2].read  = read_file;
    fopsarray[2].write = write;

    // stdin
    fopsarray[3].open  = terminal_open;
    fopsarray[3].close = terminal_close;
    fopsarray[3].read  = terminal_read;        // would be 1 cuz read only
    fopsarray[3].write = terminal_write;         // would be 0 cuz read only

    //stdout
    fopsarray[4].open  = terminal_open;
    fopsarray[4].close = terminal_close;
    fopsarray[4].read  = terminal_read;          // would be 1 cuz write only
    fopsarray[4].write = terminal_write;          // would be 1 cuz write only

    //null
    
    fopsarray[5].open  = -1;
    fopsarray[5].close = -1;
    fopsarray[5].read  = -1;         
    fopsarray[5].write = -1;         
}

typedef struct pcb_t {
    uint32_t pid;    // file operator table 
    file_descriptor_t file_descriptor[8];   // inode index 
    uint32_t saved_ebp; 
    uint32_t saved_esp;   
    uint32_t parent_id;
    uint32_t ss0;   
    uint32_t esp0;
    int active;

} pcb_t;
#endif
