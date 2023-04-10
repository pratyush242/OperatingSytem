#include "systemcalls.h"


int32_t prog_count = 0;
int32_t pid = 0;

int32_t sys_open(const char* fname){
    dentry_t dentry;
    int fd_id;
    if(fname == NULL || file_descriptor_array == NULL)
        return -1;
    // find unused file descriptor 
    for(fd_id = 2; fd_id < 8; fd_id++){
        if(file_descriptor_array[fd_id].flags == 0)
            break;
    }
    // fail if reach the max file number or could not find the file 
    if (fd_id >= 8 || read_dentry_by_name((uint8_t*)fname, &dentry) != 0)
        return -1;
    //if there are no errors call the fop
    file_descriptor_array[fd_id].op = &fopsarray[dentry.filetype];
    if ((file_descriptor_array[fd_id].op->open(fname)) == -1){
        return -1;
    }
    //set the file descriptor
    if(dentry.filetype == 2){
        file_descriptor_array[fd_id].inode =  dentry.inode_num;
    }
    else{
        file_descriptor_array[fd_id].inode = -1;
    }
    file_descriptor_array[fd_id].fileoffset = 0;
    file_descriptor_array[fd_id].flags = 1;

    return fd_id;
}

int32_t sys_close(int32_t fd){
    if (fd < 2 || fd > 8 || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0)
        return -1;
    
    if ((file_descriptor_array[fd].op->close(fd)) == 0)// close the file and clear the file descriptor 
    {
        // if successfully closed, clear the file descriptor 
        file_descriptor_array[fd].op = NULL;
        file_descriptor_array[fd].inode = -1;
        file_descriptor_array[fd].fileoffset = 0;
        file_descriptor_array[fd].flags = 0;
    }
    return 0;
}

int32_t sys_read(int32_t fd, void* buf, int32_t nbytes){
    if (fd < 0 || fd > 8 || fd == 1 || buf == NULL || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0 || file_descriptor_array[fd].op == NULL){
        return -1;
    }
    return file_descriptor_array[fd].op->read(fd, buf, nbytes);
}

int32_t sys_write(int32_t fd, void* buf, int32_t nbytes){
    if (fd < 0 || fd > 8 || fd == 1 || buf == NULL || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0 || file_descriptor_array[fd].op == NULL){
        return -1;
    }
    return file_descriptor_array[fd].op->write(fd, buf, nbytes);
}

int32_t halt(uint8_t status){
    return 0;
}

int32_t execute(const uint8_t* command){
   
    if(command == NULL){
        return -1;
    } 
   
    if(prog_count >= 8){
        return 0;
    } 

    

    
    if(strncmp((int8_t*) command, (int8_t*) "shell", 5) == 0){
        pid = prog_count = 0;
    }
    
    

    /* parsing arguments */

    uint8_t argv[16][128];    
    uint8_t cmd[10];
    int32_t cases;

    int32_t i,j, command_length;
    int32_t start = 0;
    int32_t end = 0;

    
    for(i = 0; i < 10; i++){
        cmd[i] = '\0';
    }

    for(i = 0; i < 16; i++){
        for(j = 0; j < 128; j++){
            argv[i][j] = '\0';
        }
    }

    
    while (command[start] == ' '){
        start++; 
        end++;
    }

   
    while (command[end] != ' ' && command[end] != '\0' && command[end] != 0x0A){ 
        end++; 
    } 

    for (i = 0; i < (end - start); i++){
        cmd[i] = command[i + start];
    } 
        

    command_length = strlen((int8_t*) command);

    
    for(j = 0 ; end <= command_length ; end++, j++){
        start = end;
        
        while (command[start] == ' '){
            start++;
            end++;
        }

        while (command[end] != ' ' && command[end] != '\0' && command[end] != 0x0A){
            end++;
        }

        for (i = 0; i < (end - start); i++){
            argv[j][i] = command[i + start];
        }
        
        argv[j][end - start] = '\0';
    }

    if (strncmp("exit", (int8_t*) cmd, 4) == 0){
        cases = 1;
    }

    else{
        cases = 0;
    }
    
    
    sti();
    
    switch(cases){
        case 0:
            break;
        case 1:
            asm volatile(
                "pushl  $0;"
                "pushl  $0;"
                "pushl  %%eax;"
                "call halt;"
                :
                );
            break;
        case -1:
            break;
    }

    /* executable check */
    dentry_t dentry;
    uint8_t  buf[4];
    uint32_t entry_point;

        
    if (read_dentry_by_name(cmd, &dentry) == -1){
        return -1;
    } 

        

    if (read_data(dentry.inode_num, 0, buf, 4) <=0){
        return -1;
    } 

        
    if ((buf[0] != 0x7F) || (buf[1] != 0x45) || (buf[2] != 0x4C) || (buf[3] != 0x46)){
        return -1;
    } 

    read_data(dentry.inode_num, 24, buf, 4);

    entry_point = *((uint32_t*) buf);

    
    
    /* paging */
    
    initializeProgram(pid);   // still need to do
  

    return 0;
    
}

