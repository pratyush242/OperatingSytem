#include "systemcalls.h"


int32_t pid = -1


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

int32_t system_execute(const uint8_t* command){
   
    if(command == NULL){
        return -1;
    } 
   
   
    
    
    /* parsing arguments */

     


    if(pid+1 >5){
        printf("Max number of processes running \n");
        return -1;
    }

    else{
        pid+=1;
    }
   
    int32_t i;
    int counter = 0;
  
   

    for (i = 0; i < 32; i++){
        if (command[i] == ' '  || command[i] == '\n'){
            break;
        } 
     
        counter++;
    }
    uint8_t filename[counter];   

    for (i = 0; i < counter; i++){
       
        filename[i] = command[i];
        
    }



    // printf("______________ \n");

    // printf("%s",filename);
    
    // printf("\n______________ \n");


    
    /* executable check */
    dentry_t dentry;
    uint8_t  buf[4];
    uint32_t entry_point;


        
    if (read_dentry_by_name(filename, &dentry) == -1){
        return -1;
    } 


    if (read_file(filename, buf, 4) == -1){
        return -1;
    } 

    /* Checks ELF magic constant */     
    if ((buf[0] != 0x7F) || (buf[1] != 0x45) || (buf[2] != 0x4C) || (buf[3] != 0x46)){
        return -1;
    } 


    /* get entry point */
    if(read_data(dentry.inode_num, 24, buf, 4)==-1)
    {
        return -1;
    }


    

    


    
    
    // /* paging */
    
    // initializeProgram();   /* still need to figure out */  
    

    // /* flush tlb */
  

    return 0;
    
}

