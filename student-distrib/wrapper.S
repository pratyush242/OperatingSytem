#define ASM 1



/* pushal call popal then iret before each function call recommend making functions in here and calling them in the table in idt.c*/
#define EXCEPTION_WRAPPER_ERROR(name, id)     \
    .globl name                     
    name:                           ;\
        pushal                      ;\
        pushl $id                   ;\
        call blue_screen            ;\
        addl $4, %esp               ;\
        popal                       ;\
        addl $4, %esp               ;\
        iret

#define EXCEPTION_WRAPPER(name, id)     \
    .globl name                     
    name:                           ;\
        pushl $0                    ;\
        pushal                      ;\
        pushl $id                   ;\
        call blue_screen            ;\
        addl $4, %esp               ;\
        popal                       ;\
        addl $4, %esp               ;\
        iret


#define INTERRUPT_WRAPPER(name, id)     \
    .globl name                     
    name:                           ;\
        pushal                      ;\
        pushfl                      ;\
        call id                     ;\
        popal                       ;\   
        popfl                       ;\            
        iret







/*call the functions*/
EXCEPTION_WRAPPER (divide_error, 0x00);
EXCEPTION_WRAPPER (Reserved, 0x01);
EXCEPTION_WRAPPER (NMI_INTERRUPT, 0x02);
EXCEPTION_WRAPPER (BREAKPOINT, 0x03);
EXCEPTION_WRAPPER (OVERFLOW, 0x04);
EXCEPTION_WRAPPER (BOUND, 0x05);
EXCEPTION_WRAPPER (INVALID_OPCODE, 0x06);
EXCEPTION_WRAPPER (DEV_NOT_AVAILABLE, 0x07);
EXCEPTION_WRAPPER_ERROR (DOUBLE_FAULT, 0x08);
EXCEPTION_WRAPPER (SEGMENT_OVERRUN, 0x09);
EXCEPTION_WRAPPER_ERROR (INVALID_TSS, 0x0A);
EXCEPTION_WRAPPER_ERROR (SEGMENT_NOT_PRESENT, 0x0B);
EXCEPTION_WRAPPER_ERROR (STACK_SEGMENT_FAULT, 0x0C);
EXCEPTION_WRAPPER_ERROR (GENERAL_PROTECTION, 0x0D);
EXCEPTION_WRAPPER_ERROR (PAGE_FAULT, 0x0E);
EXCEPTION_WRAPPER (MATH_FAULT, 0x10);
EXCEPTION_WRAPPER_ERROR (ALIGNMENT_CHECK, 0x11);
EXCEPTION_WRAPPER (MACHINE_CHECK, 0x12);
EXCEPTION_WRAPPER (SIMD_FLOATING_POINT_CHECK, 0x13);



INTERRUPT_WRAP(rtc_wrap, rtc_handler);
INTERRUPT_WRAP(keyboard_wrap, handler_keyboard);



