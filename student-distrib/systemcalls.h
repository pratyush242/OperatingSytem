#ifndef _SYSTEMCALLS_H
#define _SYSTEMCALLS_H

#include "types.h"
#include "filesys.h"
#include "terminal.h"
#include "rtc.h"

int32_t sys_open(const char* fname);

int32_t sys_close(int32_t fd);

int32_t sys_read(int32_t fd, void* buf, int32_t nbytes);

int32_t sys_write(int32_t fd, void* buf, int32_t nbytes);

int32_t execute(const uint8_t* cmd);

int32_t halt(uint8_t status);
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

static fops_table_t fopsarray[4];
void file_op_table_init()
{
    // init rtc operation table 
    fopsarray[0].open  = rtc_open;
    fopsarray[0].close = rtc_close;
    fopsarray[0].read  = rtc_read;
    fopsarray[0].write = rtc_write;

    // init dir operation table 
    //fopsarray[1].open  = opem_directory ;
    //fopsarray[1].close = close_directory;
    fopsarray[1].read  = read_directory ;
    //fopsarray[1].write = write_directory;

    // init file operation table 
    fopsarray[2].open  = open;
    fopsarray[2].close = close;
    fopsarray[2].read  = read_file;
    fopsarray[2].write = write;

    // init stdin/out (terminal) operation table 
    fopsarray[3].open  = terminal_open;
    fopsarray[3].close = terminal_close;
    fopsarray[3].read  = terminal_read;
    fopsarray[3].write = terminal_write;
}


#endif
