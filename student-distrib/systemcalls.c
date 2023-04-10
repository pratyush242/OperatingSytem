#include "systemcalls.h"

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

int32_t execute(const uint8_t* cmd){
    return 0;
}

