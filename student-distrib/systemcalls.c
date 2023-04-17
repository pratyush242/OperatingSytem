#include "systemcalls.h"
#include "x86_desc.h"

#define progImage 0x08048000
#define mb_8 0x800000
#define kb_8 0x2000


static fops_table_t fopsarray[6];
int32_t pid = -1;
uint8_t glob_ret = -1; 



/* helper function to get the adress of your pcb
Input: PID number
Output: A pointer to your adress that has that PCB */

pcb_t* pcb_adress(uint32_t in){
    return (pcb_t*) (mb_8 - ((in+1) * kb_8));                  // mb_8 0x800000 kb_8 0x2000


   
}
/* sys_open
 * 
 * will call particulara device's open function according to the file type 
 * Inputs: fname is file name of the file that needs to be opened
 * Outputs: fd index for sucess and -1 if failed
 */
int32_t sys_open(const char* fname){
    //printf("sys_open \n");
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
    file_descriptor_array[fd_id].filetype = dentry.filetype;
    file_descriptor_array[fd_id].offset = 0;
    memcpy(file_descriptor_array[fd_id].filename, dentry.filename, sizeof(dentry.filename));
    if ((file_descriptor_array[fd_id].op->sys_open(fname)) == -1){
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
/* sys_close
 * 
 * will call particulara device's close function according to the file type 
 * Inputs: file discriptor array index of the file to be closed
 * Outputs: 0 for success -1 for fail
 */
int32_t sys_close(int32_t fd){
     //printf("sys_close \n");
    if (fd < 2 || fd > 8 || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0)
        return -1;
    
    if ((file_descriptor_array[fd].op->sys_close(fd)) == 0)// close the file and clear the file descriptor 
    {
        // if successfully closed, clear the file descriptor 
        file_descriptor_array[fd].op = NULL;
        file_descriptor_array[fd].inode = -1;
        file_descriptor_array[fd].fileoffset = 0;
        file_descriptor_array[fd].flags = 0;
    }
    return 0;
}
/* sys_read
 * 
 * will call particular device's read function according to the file type
 * Inputs: fd - file descripor; buf - a buffer that hold the terminal input; nbytes - the number of bytes to read from the keyboard buffer
 * Outputs: the actual number of bytes that are read successfully, if error then ret -1
 */
int32_t sys_read(int32_t fd, void* buf, int32_t nbytes){
    //printf("sys_read \n");
    if (fd < 0 || fd > 8 || buf == NULL || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0 || file_descriptor_array[fd].op == NULL){
        return -1;
    }

    if(file_descriptor_array[fd].filetype == 1){

        int32_t bytesRead = file_descriptor_array[fd].op->sys_read(&file_descriptor_array[fd], buf, nbytes);
        return bytesRead;
    }
    return file_descriptor_array[fd].op->sys_read(fd, buf, nbytes);
}
/* sys_write
 * 
 * will call particular device's write function according to the file type
 * Inputs: fd - file descripor; buf - a buffer that hold the terminal input; nbytes - the number of bytes to write from the  buffer to terminal
 * Outputs: the actual number of bytes that are written successfully, if error then ret -1
 */
int32_t sys_write(int32_t fd, void* buf, int32_t nbytes){
    //printf("sys_write \n");
    if (fd < 0 || fd > 8 || buf == NULL || file_descriptor_array == NULL || file_descriptor_array[fd].flags == 0 || file_descriptor_array[fd].op == NULL){
        return -1;
    }
    return file_descriptor_array[fd].op->sys_write(fd, buf, nbytes);
}

/* halt
 * 
 * The halt system call terminates a process, returning the specified value to its parent process
 * Inputs: status
 * Outputs: 0 for succes, -1 for failure
 */


int32_t halt(uint8_t status){
   
   
    pcb_t* PCB;
    pcb_t* PCB_parent;


    glob_ret = status;
    
    
    PCB = pcb_adress(pid);
    pid = PCB->pid;

    // tss 
    tss.esp0 = PCB->esp0;
    tss.ss0 = PCB->ss0;

   
   
   
    // clear flags 
    int i;
    for (i = 0; i < 8; i++) {
        PCB->file_descriptor[i].flags = 0;
       
    }

    



    if (pid == 0) {
        system_execute((uint8_t *) "shell");
        return -1;
    }
    
    
    
   

   
    PCB_parent = pcb_adress(PCB->parent_id);
    pid = PCB_parent->pid;

    // restore parent paging 
    sysCallPaging(pid);

   
    asm volatile ("                 \n\
        movl    %0, %%esp           \n\
        movl    %1, %%ebp           \n\
        jmp end_of_execute          \n\
        "
        :
        : "a"(PCB->saved_esp), "b"(PCB->saved_ebp)
    );

    return 0;
}
   





int32_t null_open(){
    return -1;
   
}

int32_t null_close(){
    return -1;
   
}

int32_t null_read(){
    return -1;
   
}

int32_t null_write(){
    return -1;
   
}
/* file_op_table_init
 * 
 * initallize the fops table
 * Inputs: none
 * Outputs: none
 */
void file_op_table_init()
{
    // init rtc operation table 
    fopsarray[0].sys_open  = rtc_open;
    fopsarray[0].sys_close = rtc_close;
    fopsarray[0].sys_read  = rtc_read;
    fopsarray[0].sys_write = rtc_write;

    // init dir operation table 
    fopsarray[1].sys_open  = open_directory ;
    fopsarray[1].sys_close = close_directory;
    fopsarray[1].sys_read  = read_directory ;
    fopsarray[1].sys_write = write_directory;

    // init file operation table 
    fopsarray[2].sys_open  = open;
    fopsarray[2].sys_close = close;
    fopsarray[2].sys_read  = read_file;
    fopsarray[2].sys_write = write;

    // stdin
    fopsarray[3].sys_open  = terminal_open;
    fopsarray[3].sys_close = terminal_close;
    fopsarray[3].sys_read  = terminal_read;        // would be 1 cuz read only
    fopsarray[3].sys_write = terminal_write;         // would be 0 cuz read only

    //stdout
    fopsarray[4].sys_open  = terminal_open;
    fopsarray[4].sys_close = terminal_close;
    fopsarray[4].sys_read  = terminal_read;          // would be 1 cuz write only
    fopsarray[4].sys_write = terminal_write;          // would be 1 cuz write only

    //null
    
    fopsarray[5].sys_open  = null_open;
    fopsarray[5].sys_close = null_close;
    fopsarray[5].sys_read  = null_read;         
    fopsarray[5].sys_write = null_write;         
}

/* system_execute
 * 
 * The execute system call attempts to load and execute a new program, handing off the processor to the new program
   until it terminates.
 * Inputs: command -- The command is a space-separated sequence of words. 
 * Outputs: 0 for success, if error then ret -1
 */


int32_t system_execute(const uint8_t* command){
    if(command == NULL){
        return -1;
    } 

    pcb_t* PCB;
    pcb_t* PCB_parent;

    int32_t i;
    int counter = 0;
    dentry_t dentry;
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

    if (read_dentry_by_name(filename, &dentry) == -1){
        return -1;
    } 

    /* parsing arguments */
    int32_t parent_id = pid;
    PCB_parent = pcb_adress(pid); 

    if(pid+1 >5){
        printf("Max number of processes running \n");
        return -1;
    }
    else{
        pid+=1;
    }
    

    

     



    





    /* SET UP PAGING */
    sysCallPaging(pid);
    /* loading file */
    inode_t* file_inode = (inode_t*)(inode_start + dentry.inode_num);
    int32_t errCheck = read_file_2((int32_t)filename,(uint8_t*)progImage, file_inode->length );



    if (errCheck == -1){
        return -1;
    } 
    uint8_t* file = (uint8_t*)progImage;


    /* Checks ELF magic constant */     
    if ((file[0] != 0x7F) || (file[1] != 0x45) || (file[2] != 0x4C) || (file[3] != 0x46)){
        return -1;
    } 

    

    if(errCheck==-1)
    {
        return -1;
    }

    /* SET UP PCB */

    register uint32_t saved_ebp asm("ebp");
    register uint32_t saved_esp asm("esp");
    file_op_table_init();
    
    PCB = pcb_adress(pid);
    
   
    
    PCB->pid = pid;
    
    PCB->parent_id = parent_id;
    PCB->saved_ebp = saved_ebp;
    PCB->saved_esp = saved_esp;
    PCB->active = 1;
    
    for(i = 0; i < 8; i++){
        PCB->file_descriptor[i].op = &fopsarray[5];    // file operator table (in case of null)
        PCB->file_descriptor[i].inode = 0 ;     // inode index 
        PCB->file_descriptor[i].fileoffset = 0; // offset in current file 
        PCB->file_descriptor[i].flags = 0;
               
        if(i==0||i==1){
            PCB->file_descriptor[i].flags = 1;
            PCB->file_descriptor[i].op = &fopsarray[i+3]; //(terminal)
        }
    }

    file_descriptor_array =  PCB->file_descriptor;

    // set TSS values in PCB 

    PCB->ss0 = tss.ss0;
    PCB->esp0 = tss.esp0;

    tss.ss0 = KERNEL_DS;
    tss.esp0 = (mb_8 - ((pid) * kb_8) - 4); // will point to the top of your stack

    uint32_t esp_context = 0x8000000 + 0x400000 - 4;
    

     // store EIP value for context switching
    uint8_t eip_loc[4];
    eip_loc[0]= file[24];
    eip_loc[1]= file[25];
    eip_loc[2]= file[26];
    eip_loc[3]= file[27];

    uint32_t eip_context = *((int*)eip_loc);    

    contextSwitch(eip_context,esp_context);
    

    
  
    asm volatile("end_of_execute:");
    return glob_ret;
    
}





