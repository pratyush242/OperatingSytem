#ifndef _FILESYS_H
#define _FILESYS_H



#include "types.h"
#include "lib.h"

typedef struct dentry{
    uint8_t filename[32];
    uint32_t filetype;
    uint32_t inode_num;
    uint8_t reserved[24];
}dentry_t;

typedef struct boot_block {
uint32_t dir_count;
uint32_t inode_count;
uint32_t data_count;
uint8_t reserved[52];
dentry_t dentry_start[63];


}boot_block_t;




typedef struct inode {
    uint32_t length;
    uint32_t data_block_num[1023];
}inode_t;

extern uint32_t file_system_base;

boot_block_t* boot_block_A;
uint32_t num_dentry;

uint32_t num_inode;

uint32_t num_data_blocks;


inode_t* inode_start;

uint8_t*  data_block_start;

int init_filesys();
int open();
int close();
uint32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry);
uint32_t read_dentry_by_index(uint32_t index,dentry_t* dentry);
uint32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);
int write();

uint32_t read_file(const uint8_t* fname, uint8_t* buf, uint32_t length);

uint32_t read_directory( uint8_t* buf);

#endif
