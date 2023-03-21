#include "idt.h"
#include "lib.h"
#include "x86_desc.h"
#include "wrapper.S"






void idt_init(){

    int i ;



    for(i = 0;i<NUM_VEC;i++){


        if(i<= 19 && i!=15){
            idt[i].present = 1;
        }
        else{
            idt[i].present = 0;

        }
        idt[i].seg_selector = KERNEL_CS;
        idt[i].dpl = 0; // change to 3 for system call handler
        idt[i].reserved0 = 0;
        idt[i].reserved1 = 1;
        idt[i].reserved2 = 1;
        idt[i].reserved3 = 0; // change to 1 for interrupt
        idt[i].reserved4 = 0;
        idt[i].size = 1;


        






    }
//have to add a wrapper not sure how to 
//made a new file interrupt_wrapper

    SET_IDT_ENTRY(idt[0], divide_error);
    SET_IDT_ENTRY(idt[1], Reserved);
    SET_IDT_ENTRY(idt[2], NMI_INTERRUPT );
    SET_IDT_ENTRY(idt[3], BREAKPOINT);
    SET_IDT_ENTRY(idt[4], OVERFLOW);
    SET_IDT_ENTRY(idt[5], BOUND);
    SET_IDT_ENTRY(idt[6], INVALID_OPCODE);
    SET_IDT_ENTRY(idt[7], DEV_NOT_AVAILABLE);
    SET_IDT_ENTRY(idt[8], DOUBLE_FAULT);
    SET_IDT_ENTRY(idt[9], SEGMENT_OVERRUN);
    SET_IDT_ENTRY(idt[10], INVALID_TSS);
    SET_IDT_ENTRY(idt[11], SEGMENT_NOT_PRESENT );
    SET_IDT_ENTRY(idt[12], STACK_SEGMENT_FAULT);
    SET_IDT_ENTRY(idt[13], GENERAL_PROTECTION );
    SET_IDT_ENTRY(idt[14], PAGE_FAULT );
    SET_IDT_ENTRY(idt[16], MATH_FAULT );
    SET_IDT_ENTRY(idt[17], ALIGNMENT_CHECK);
    SET_IDT_ENTRY(idt[18], MACHINE_CHECK );
    SET_IDT_ENTRY(idt[19], SIMD_FLOATING_POINT_CHECK);

    
    idt[0x21].reserved3 = 1;

    
    idt[0x28].reserved3 = 1;

    SET_IDT_ENTRY(idt[0x21], rtc_wrap);
    SET_IDT_ENTRY(idt[0x28], keyboard_wrap);

    lidt(idt_desc_ptr);



}

char* array_of_names[] = {
    "divide_error",
    "Reserved",
    "NMI_INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND",
    "INVALID_OPCODE",
    "DEV_NOT_AVAILABLE",
    "DOUBLE_FAULT",
    "SEGMENT_OVERRUN",
    "INVALID_TSS",
    "SEGMENT_NOT_PRESENT",
    "STACK_SEGMENT_FAULT",
    "GENERAL_PROTECTION",
    "PAGE_FAULT",
    "MATH_FAULT",
    "ALIGNMENT_CHECK",
    "MACHINE_CHECK",
    "SIMD_FLOATING_POINT_CHECK"













}


void blue_screen(uint32_t id){
    char* name = array_of_names[id];
    printf("%s at adress", name);

    
}


