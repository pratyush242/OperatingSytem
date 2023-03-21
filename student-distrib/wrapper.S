#define ASM 1



/* pushal call popal then iret before each function call recommend making functions in here and calling them in the table in idt.c*/
#define WRAPPER(name, id)     \
    .globl name                     
    name:                           ;\
        pushal                      ;\
        pushfl                      ;\
        call id                     ;\
        popal                       ;\   
        popfl                       ;\            
        iret





/*call the functions*/
WRAPPER (divide_error, 0x00);
WRAPPER (Reserved, 0x01);
WRAPPER (NMI_INTERRUPT, 0x02);
WRAPPER (BREAKPOINT, 0x03);
WRAPPER (OVERFLOW, 0x04);
WRAPPER (BOUND, 0x05);
WRAPPER (INVALID_OPCODE, 0x06);
WRAPPER (DEV_NOT_AVAILABLE, 0x07);
WRAPPER_ERR0R (DOUBLE_FAULT, 0x08);
WRAPPER (SEGMENT_OVERRUN, 0x09);
WRAPPER_ERR0R (INVALID_TSS, 0x0A);
WRAPPER_ERR0R (SEGMENT_NOT_PRESENT, 0x0B);
WRAPPER_ERR0R (STACK_SEGMENT_FAULT, 0x0C);
WRAPPER_ERR0R (GENERAL_PROTECTION, 0x0D);
WRAPPER_ERR0R (PAGE_FAULTt, 0x0E);
WRAPPER (MATH_FAULT, 0x10);
WRAPPER_ERR0R (ALIGNMENT_CHECK, 0x11);
WRAPPER (MACHINE_CHECK, 0x12);
WRAPPER (SIMD_FLOATING_POINT_CHECK, 0x13);

