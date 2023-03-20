#define ASM 1



/* pushal call popal then iret before each function call recommend making functions in here and calling them in the table in idt.c*/
#define WRAPPER(name, id)     \
    .globl name                     ;\
    name:                           ;\
        pushl $0                    ;\
        pushal                      ;\
        pushl $id                   ;\
        call exception_handler_real ;\
        addl $4, %esp               ;\
        popal                       ;\
        addl $4, %esp               ;\
        iret


#define WRAPPER_ERROR(name, id) \
    .globl name                     ;\
    name:                           ;\
        pushal                      ;\
        pushl $id                   ;\
        call exception_handler_real ;\
        addl $4, %esp               ;\
        popal                       ;\
        addl $4, %esp               ;\
        iret



