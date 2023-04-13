#include "idt.h"
#include "lib.h"
#include "x86_desc.h"
#include "wrapper.h"
#include "keyboard.h"

//FUNCTION HANDLER DEFINITIONS

//CHECK FOR DIVISION BY 0 AND PRINT DIVIDE ERROR
void divide_error(){
    cli();
    clear();
    printf(" divide error");
    while(1);
   
}

//CHECK FOR RESERVED AND PRINT RESERVED
void Reserved(){
    cli();
    clear();
    printf("Reserved");
    while(1);
    
}
//CHECK FOR NMI INTERRUPT AND PRINT NMI INTERRUPT
void NMI_INTERRUPT(){
    cli();
    clear();
    printf("NMI_INTERRUPT");
    while(1);
   
}

//CHECK FOR BREAKPOINT AND PRINT BREAKPOINT
void BREAKPOINT(){
    cli();
    clear();
    printf("BREAKPOINT");
    while(1);
   
}

//CHECK FOR OVERFLOW AND PRINT OVERFLOW
void OVERFLOW(){
    cli();
    clear();
    printf("OVERFLOW");
    while(1);
   
}
//CHECK FOR BOUND AND PRINT BOUND
void BOUND(){
    cli();
    clear();
    printf("BOUND");
    while(1);
   
}
//CHECK FOR INVALID OPCODE AND PRINT INVALID OPCODE
void INVALID_OPCODE(){
    cli();
    clear();
    printf("INVALID_OPCODE");
    while(1);
   
}
//CHECK FOR DEV NOT AVAILABLE AND PRINT DEV NOT AVAILABLE
void DEV_NOT_AVAILABLE(){
    cli();
    clear();
    printf("DEV_NOT_AVAILABLE");
    while(1);
   
}

//CHECK FOR DOUBLE FAULT AND PRINT DOUBLE FAULT
void DOUBLE_FAULT(){
    cli();
    clear();
    printf("DOUBLE_FAULT");
    while(1);
   
}

//CHECK FOR SEGEMENT OVERRUN AND SEGEMENT OVERRUN
void SEGMENT_OVERRUN(){
    cli();
    clear();
    printf("SEGMENT_OVERRUN");
    while(1);
   
}

//CHECK FOR INVALID TSS AND PRINT INVALID TSS
void INVALID_TSS(){
    cli();
    clear();
    printf("INAVLID_TSS");
    while(1);
   
}

//CHECK FOR SEGMENT NOT PRESENT AND PRINT SEGMENT NOT PRESENT
void SEGMENT_NOT_PRESENT(){
    cli();
    clear();

    printf("SEGMENT_NOT_PRESENT");
    while(1);
   
}

//CHECK FOR STACK SEGMENT FAULT AND PRINT STACK SEGMENT FAULT
void STACK_SEGMENT_FAULT(){
    cli();
    clear();
    printf("STACK_sEGMENT_FAULT");
    while(1);
   
}

//CHECK FOR GENERAL PROTECTION AND PRINT GENERAL PROTECTION
void GENERAL_PROTECTION(){
    cli();
    clear();
    printf("GENERAL_PROTECTION");
    while(1);
}

//CHECK FOR PAGE FAULT AND PRINT PAGE FAULT
void PAGE_FAULT(){
    cli();
   
    printf("PAGE_FAULT");
    while(1);
}

//CHECK FOR MATH FAULT AND PRINT MATH FAULT
void MATH_FAULT(){
    cli();
    clear();
    printf("MATH_FAULT");
    while(1);
}

//CHECK FOR ALIGNMENT CHECK AND PRINT ALIGNMENT CHECK
void ALIGNMENT_CHECK(){
    cli();
    clear();
    printf("ALIGNMENT_CHECK");
    while(1);
}

//CHECK FOR MACHINE CHECK AND PRINT MACHINE CHECK
void MACHINE_CHECK(){
    cli();
    clear();
    printf("MACHINE_CHECK");
    while(1);
}

//CHECK FOR SIMD_FLOATING_POINT_CHECK AND PRINT SIMD_FLOATING_POINT_CHECK
void SIMD_FLOATING_POINT_CHECK(){
    cli();
    clear();
    printf("SIMD_FLOATING_POINT_CHECK");
    while(1);

}


//SYSTEM CALL DECLARATION
void systemcall(){
    printf("System Call");

}


// IDT INITIALIZER
void idt_init(){
    // looping and setting idt entries fir errors
    int i;
    for(i = 0;i<256;i++){
    if(i!=15)
{
    idt[i].present = 0x1;
    idt[i].dpl = 0x0;
    idt[i].reserved0 = 0x0;
    idt[i].size = 0x1;
    idt[i].reserved1 = 0x1;
    idt[i].reserved2 = 0x1;
    idt[i].reserved3 = 0x0;
    idt[i].reserved4 = 0x0;
    idt[i].seg_selector = KERNEL_CS;
}
    
    }

    // Sets IDT entries in the interrupt descriptor table 
    SET_IDT_ENTRY(idt[0x00], divide_error);
    SET_IDT_ENTRY(idt[1], Reserved);
    SET_IDT_ENTRY(idt[2], NMI_INTERRUPT);
    SET_IDT_ENTRY(idt[3], BREAKPOINT);
    SET_IDT_ENTRY(idt[4], OVERFLOW);
    SET_IDT_ENTRY(idt[5], BOUND);
    SET_IDT_ENTRY(idt[6], INVALID_OPCODE);
    SET_IDT_ENTRY(idt[7], DEV_NOT_AVAILABLE);
    SET_IDT_ENTRY(idt[8], DOUBLE_FAULT);
    SET_IDT_ENTRY(idt[9], SEGMENT_OVERRUN);
    SET_IDT_ENTRY(idt[10], INVALID_TSS);
    SET_IDT_ENTRY(idt[11], SEGMENT_NOT_PRESENT);
    SET_IDT_ENTRY(idt[12], STACK_SEGMENT_FAULT);
    SET_IDT_ENTRY(idt[13], GENERAL_PROTECTION);
    SET_IDT_ENTRY(idt[14], PAGE_FAULT);
    SET_IDT_ENTRY(idt[16], MATH_FAULT);
    SET_IDT_ENTRY(idt[17], ALIGNMENT_CHECK);
    SET_IDT_ENTRY(idt[18], MACHINE_CHECK);
    SET_IDT_ENTRY(idt[19], SIMD_FLOATING_POINT_CHECK);


    idt[33].present = 0x1;
    idt[33].dpl = 0x0;
    idt[33].reserved0 = 0x0;
    idt[33].size = 0x1;
    idt[33].reserved1 = 0x1;
    idt[33].reserved2 = 0x1;
    idt[33].reserved3 = 0x1;
    idt[33].reserved4 = 0x0;
    idt[33].seg_selector = KERNEL_CS;  

    idt[40].present = 0x1;
    idt[40].dpl = 0x0;
    idt[40].reserved0 = 0x0;
    idt[40].size = 0x1;
    idt[40].reserved1 = 0x1;
    idt[40].reserved2 = 0x1;
    idt[40].reserved3 = 0x1;
    idt[40].reserved4 = 0x0;
    idt[40].seg_selector = KERNEL_CS; 
    /* Interrupts */
    SET_IDT_ENTRY(idt[33], keyboard_wrap);
    SET_IDT_ENTRY(idt[40], rtc_wrap);

    idt[0x80].present = 0x1;
    idt[0x80].dpl = 3;
    idt[0x80].reserved0 = 0x0;
    idt[0x80].size = 0x1;
    idt[0x80].reserved1 = 0x1;
    idt[0x80].reserved2 = 0x1;
    idt[0x80].reserved3 = 0x0;
    idt[0x80].reserved4 = 0x0;
    idt[0x80].seg_selector = KERNEL_CS;
    // System Call 
   SET_IDT_ENTRY(idt[0x80] ,system_call_linkage);

    // Load IDT 
    lidt(idt_desc_ptr);


}



