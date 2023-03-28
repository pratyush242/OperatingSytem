#include "filesys.h"

static uint32_t file_position = 0;

static uint32_t directory_file = 0;

/* init_filesys
 * initializes file system 
 * 
 * returns 0
 * Inputs: None
 * 


 */
int init_filesys(){
    boot_block_A = (boot_block_t*) file_system_base;
    num_dentry = boot_block_A -> data_count;
    num_inode = boot_block_A -> inode_count;

    inode_start = (inode_t*)(boot_block_A+1);

    data_block_start = (uint8_t*)(inode_start + num_inode);
    return 0;

}


/* open
 * opens files/directories
 * 
 * returns 0
 * Inputs: None
 * 


 */
int open(){
    return 0;
}
/* close
 * closes files/directories
 * 
 * returns 0
 * Inputs: None
 * 


 */
int close(){
    return 0;

}
/* write
 * writes files/directories
 * 
 * returns 0
 * Inputs: None
 * 


 */

int write(){
    return -1;
}

/* read_dentry_by_name
 * 
 * returns dentry of file based on provided file name
 * Inputs: fname - name of file, dentry - dentry to be written to
 * Outputs: return -1 if fail, 0 if success


 */
uint32_t read_dentry_by_name(const uint8_t* fname, dentry_t* dentry){

int i;

uint32_t fname_length = strlen(fname);

uint8_t* temp_name;

for(i = 0; i<63;i++){

temp_name = boot_block_A->dentry_start[i].filename;

if(fname_length == strlen(temp_name)){
    
    if(strncmp(fname,temp_name,32) == 0){

        read_dentry_by_index(i,dentry);

        return 0;

    }

}
}

return -1;
}

/* read_dentry_by_index
 * 
 * returns dentry of file based on provided index
 * Inputs: index - index of file, dentry - dentry to be written to
 * Outputs: return -1 if fail, 0 if success


 */
uint32_t read_dentry_by_index(uint32_t index,dentry_t* dentry){

if(index < 63){


dentry_t temp = (dentry_t)(boot_block_A->dentry_start[index]);


strncpy((uint8_t*)(dentry->filename),(uint8_t*)(temp.filename),32);

dentry->filetype = temp.filetype;

dentry->inode_num = temp.inode_num;

return 0;
}
return -1;
}



/* read_directory
 * 
 * reads a file in the directory
 * Inputs:buf - character array where file data is written to
 * Outputs: returns 0 if end of directory was reached, number of bytes read if end of file was not reached
 * Side Effect: increment directory_file to move to next file

 */



uint32_t read_directory( uint8_t* buf){

dentry_t file_entry;
read_dentry_by_index(directory_file,&file_entry);

if(directory_file == num_dentry){
    return 0;
}


int i;
int j;
for(i = 0;i<32;i++){
    buf[i] = file_entry.filename[i];
    j++;
}

directory_file++;

return j;

}














/* read_file
 * 
 * reads the given file based on the specified file name
 * Inputs: fname - name of file, buf - character array where file data is written to, length - length of the file
 * Outputs: return -1 if fail, 0 if end of file was reached, number of bytes read if end of file was not reached


 */

uint32_t read_file(const uint8_t* fname, uint8_t* buf, uint32_t length){

dentry_t file_entry;

read_dentry_by_name(fname,&file_entry);

if(buf == NULL){
    return -1;
}



inode_t* file_inode = (inode_t*)(inode_start + file_entry.inode_num);

if(file_inode < 0){
    return -1;
}

uint32_t val = read_data(file_inode,file_position, buf, length);


if(val == 0){

    file_position = file_inode->length;

    return 0;
}else if(val == -1){


    return -1;
}
else{
    file_position +=val;
    return val;
}

return -1;


}
/* read_data
 * 
 * reads the given file based on the specified inode
 * Inputs: inode - file inode, offset - place in file to start reading, buf - character array where file data is written to, length - length of the file
 * Outputs: return -1 if fail, 0 if end of file was reached, number of bytes read if end of file was not reached


 */


uint32_t read_data(uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){


inode_t* node = (inode_t*)inode;
uint32_t file_length = ((inode_t*)inode)->length;
uint32_t current_block_index;
uint32_t current_block;
uint8_t* mem_offset;
uint8_t* block_start;
//uint32_t end_of_file = 0;
if(buf == NULL){
    return -1;
}
int i;
for(i = 0;i<length;i++){

    if(offset== file_length){
        return 0;
    }

    current_block_index = (uint32_t)(offset/4096);


    current_block = node->data_block_num[current_block_index];

   block_start = (uint8_t*) (data_block_start+4096*current_block);

    mem_offset = block_start + offset%4096;
   
    buf[i] = *mem_offset;
    
    offset++;

}


return length;

}