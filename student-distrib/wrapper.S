#define ASM 1

#include "wrapper.h"




/* pushal call popal then iret before each function call recommend making functions in here and calling them in the table in idt.c*/

                 
#define pushall \
pushall:
        pushl %eax ;\ 
        pushl %ebp ;\
        pushl %ebx ;\
        pushl %ecx ;\
        pushl %edx ;\
        pushl %edi ;\
        pushl %esi ;\  
        
#define popall \
popall:
        popl %esi ;\
        popl %edi ;\
        popl %edx ;\
        popl %ecx ;\
        popl %ebx ;\
        popl %ebp ;\
        popl %eax ;\
        


#define INTERRUPT_WRAPPER(name,id) \
.globl name                     
name:

INTERRUPT_WRAPPER:                   
        pushall                   ;\
        pushfl                      ;\
        call name                   ;\
        popall                     ;\   
        popfl                       ;\            
        iret         








/*call the functions*/
INTERRUPT_WRAPPER (divide_error, 0x00);
INTERRUPT_WRAPPER (Reserved, 0x01);
INTERRUPT_WRAPPER (NMI_INTERRUPT, 0x02);
INTERRUPT_WRAPPER (BREAKPOINT, 0x03);
INTERRUPT_WRAPPER (OVERFLOW, 0x04);
INTERRUPT_WRAPPER (BOUND, 0x05);
INTERRUPT_WRAPPER (INVALID_OPCODE, 0x06);
INTERRUPT_WRAPPER (DEV_NOT_AVAILABLE, 0x07);
INTERRUPT_WRAPPER (DOUBLE_FAULT, 0x08);
INTERRUPT_WRAPPER (SEGMENT_OVERRUN, 0x09);
INTERRUPT_WRAPPER (INVALID_TSS, 0x0A);
INTERRUPT_WRAPPER (SEGMENT_NOT_PRESENT, 0x0B);
INTERRUPT_WRAPPER (STACK_SEGMENT_FAULT, 0x0C);
INTERRUPT_WRAPPER (GENERAL_PROTECTION, 0x0D);
INTERRUPT_WRAPPER (PAGE_FAULT, 0x0E);
INTERRUPT_WRAPPER (MATH_FAULT, 0x10);
INTERRUPT_WRAPPER (ALIGNMENT_CHECK, 0x11);
INTERRUPT_WRAPPER (MACHINE_CHECK, 0x12);
INTERRUPT_WRAPPER (SIMD_FLOATING_POINT_CHECK, 0x13);
INTERRUPT_WRAPPER(rtc_wrap, rtc_handler);
INTERRUPT_WRAPPER(keyboard_wrap, handler_keyboard);



