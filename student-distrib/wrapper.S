#define ASM 1

#include "wrapper.h"






/* pushal call popal then iret before each function call recommend making functions in here and calling them in the table in idt.c*/

                 
#define pushall     \
        pushl %eax ;\
        pushl %ebp ;\
        pushl %ebx ;\
        pushl %ecx ;\
        pushl %edx ;\
        pushl %edi ;\
        pushl %esi ;
        
#define popall     \
        popl %esi ;\
        popl %edi ;\
        popl %edx ;\
        popl %ecx ;\
        popl %ebx ;\
        popl %ebp ;\
        popl %eax ;
   
#define INTERRUPT_WRAPPER(name,function) \
        .globl name               ;\               
        name:                     ;\    
                pushall           ;\
                pushfl            ;\
                cli               ;\
                call function         ;\
                sti               ;\
                popall            ;\
                popfl             ;\      
                iret         


/*call the functions*/
INTERRUPT_WRAPPER(keyboard_wrap,handler_keyboard)
INTERRUPT_WRAPPER(rtc_wrap,rtc_handler)



