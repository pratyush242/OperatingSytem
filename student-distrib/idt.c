#include "idt.h"
#include "lib.h"
#include "x86_desc.h"
#include "interrupt_wrapper.S"


void divide_error(){
    printf("divide error");
   
}
void Reserved(){
    printf("Reserved");
    
}
void NMI_INTERRUPT(){
    printf("NMI_INTERRUPT");
   
}
void BREAKPOINT(){
    printf("BREAKPOINT");
   
}
void OVERFLOW(){
    printf("OVERFLOW");
   
}






void BOUND(){
    printf("BOUND");
   
}
void INVALID_OPCODE(){
    printf("INVALID_OPCODE");
   
}
void DEV_NOT_AVAILABLE(){
    printf("DEV_NOT_AVAILABLE");
   
}
void DOUBLE_FAULT(){
    printf("DOUBLE_FAULT");
   
}
void SEGMENT_OVERRUN(){
    printf("SEGMENT_OVERRUN");
   
}
void INVALID_TSS(){
    printf("INAVLID_TSS");
   
}
void SEGMENT_NOT_PRESENT(){
    printf("SEGMENT_NOT_PRESENT");
   
}
void STACK_SEGMENT_FAULT(){
    printf("STACK_sEGMENT_FAULT");
   
}
void GENERAL_PROTECTION(){
    printf("GENERAL_PROTECTION");
}

void PAGE_FAULT(){
    printf("PAGE_FAULT");
}
void MATH_FAULT(){
    printf("MATH_FAULT");
}
void ALIGNMENT_CHECK(){
    printf("ALIGNMENT_CHECK");
}
void MACHINE_CHECK(){
    printf("MACHINE_CHECK");
}
void SIMD_FLOATING_POINT_CHECK(){
    printf("SIMD_FLOATING_POINT_CHECK");

}




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

    SET_IDT_ENTRY(idt[0], divide_error());
    SET_IDT_ENTRY(idt[1], Reserved());
    SET_IDT_ENTRY(idt[2], NMI_INTERRUPT() );
    SET_IDT_ENTRY(idt[3], BREAKPOINT());
    SET_IDT_ENTRY(idt[4], OVERFLOW());
    SET_IDT_ENTRY(idt[5], BOUND());
    SET_IDT_ENTRY(idt[6], INVALID_OPCODE());
    SET_IDT_ENTRY(idt[7], DEV_NOT_AVAILABLE());
    SET_IDT_ENTRY(idt[8], DOUBLE_FAULT());
    SET_IDT_ENTRY(idt[9], SEGMENT_OVERRUN());
    SET_IDT_ENTRY(idt[10], INVALID_TSS());
    SET_IDT_ENTRY(idt[11], SEGMENT_NOT_PRESENT() );
    SET_IDT_ENTRY(idt[12], STACK_SEGMENT_FAULT());
    SET_IDT_ENTRY(idt[13], GENERAL_PROTECTION() );
    SET_IDT_ENTRY(idt[14], PAGE_FAULT() );
    SET_IDT_ENTRY(idt[16], MATH_FAULT() );
    SET_IDT_ENTRY(idt[17], ALIGNMENT_CHECK());
    SET_IDT_ENTRY(idt[18], MACHINE_CHECK() );
    SET_IDT_ENTRY(idt[19], SIMD_FLOATING_POINT_CHECK());
    lidt(idt_desc_ptr);



}


// call the functions 
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
