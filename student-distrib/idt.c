#include "idt.h"
#include "lib.h"
#include "x86_desc.h"
#include "wrapper.h"

//FUNCTION HANDLER DEFINITIONS

//CHECK FOR DIVISION BY 0 AND PRINT DIVIDE ERROR
void divide_error(){
    clear();
    printf(" divide error");
    while(1);
   
}

//CHECK FOR RESERVED AND PRINT RESERVED
void Reserved(){
    clear();
    printf("Reserved");
    while(1);
    
}
//CHECK FOR NMI INTERRUPT AND PRINT NMI INTERRUPT
void NMI_INTERRUPT(){
    clear();
    printf("NMI_INTERRUPT");
    while(1);
   
}

//CHECK FOR BREAKPOINT AND PRINT BREAKPOINT
void BREAKPOINT(){
    clear();
    printf("BREAKPOINT");
    while(1);
   
}

//CHECK FOR OVERFLOW AND PRINT BREAKPOINT
void OVERFLOW(){
    clear();
    printf("OVERFLOW");
    while(1);
   
}
//CHECK FOR BOUND AND PRINT BREAKPOINT
void BOUND(){
    clear();
    printf("BOUND");
    while(1);
   
}
//CHECK FOR INVALID OPCODE AND PRINT BREAKPOINT
void INVALID_OPCODE(){
    clear();
    printf("INVALID_OPCODE");
    while(1);
   
}
//CHECK FOR DEV NOT AVAILABLE AND PRINT BREAKPOINT
void DEV_NOT_AVAILABLE(){
    clear();
    printf("DEV_NOT_AVAILABLE");
    while(1);
   
}

//CHECK FOR DOUBLE FAULT AND PRINT BREAKPOINT
void DOUBLE_FAULT(){
    clear();
    printf("DOUBLE_FAULT");
    while(1);
   
}

//CHECK FOR SGEMENT OVERRUN AND PRINT BREAKPOINT
void SEGMENT_OVERRUN(){
    clear();
    printf("SEGMENT_OVERRUN");
    while(1);
   
}

//CHECK FOR INVALID TSS AND PRINT BREAKPOINT
void INVALID_TSS(){
    clear();
    printf("INAVLID_TSS");
    while(1);
   
}

//CHECK FOR SEGMENT NOT PRESENT AND PRINT BREAKPOINT
void SEGMENT_NOT_PRESENT(){
    clear();
    printf("SEGMENT_NOT_PRESENT");
    while(1);
   
}

//CHECK FOR STACK SEGMENT FAULT AND PRINT BREAKPOINT
void STACK_SEGMENT_FAULT(){
    clear();
    printf("STACK_sEGMENT_FAULT");
    while(1);
   
}

//CHECK FOR GENERAL PROTECTION AND PRINT BREAKPOINT
void GENERAL_PROTECTION(){
    clear();
    printf("GENERAL_PROTECTION");
    while(1);
}

//CHECK FOR PAGE FAULT AND PRINT BREAKPOINT
void PAGE_FAULT(){
    clear();
    printf("PAGE_FAULT");
    while(1);
}

//CHECK FOR MATH FAULT AND PRINT BREAKPOINT
void MATH_FAULT(){
    clear();
    printf("MATH_FAULT");
    while(1);
}

//CHECK FOR ALIGNMENT CHECK AND PRINT BREAKPOINT
void ALIGNMENT_CHECK(){
    clear();
    printf("ALIGNMENT_CHECK");
    while(1);
}

//CHECK FOR MACHINE CHECK AND PRINT BREAKPOINT
void MACHINE_CHECK(){
    clear();
    printf("MACHINE_CHECK");
    while(1);
}

//CHECK FOR SIMD_FLOATING_POINT_CHECK AND PRINT BREAKPOINT
void SIMD_FLOATING_POINT_CHECK(){
    clear();
    printf("SIMD_FLOATING_POINT_CHECK");
    while(1);

}
//KEYBOARD WRAP DECLARATION
void keyboard_wrap(){
    clear();
    printf("keyboard");
    while(1);

}

//RTC WRAP DECLARATION
void rtc_wrap(){
    clear();
    printf("rtc");
    while(1);

}

//SYSTEM CALL DECLARATION
void systemcall(){
    printf("System Call");

}


// IDT INITIALIZER
void idt_init(){
    idt_desc_t desc;

    // Setting specific bits for interrupt gate
    desc.present = 0x1;
    desc.dpl = 0x0;
    desc.reserved0 = 0x0;
    desc.size = 0x1;
    desc.reserved1 = 0x1;
    desc.reserved2 = 0x1;
    desc.reserved3 = 0x0;
    desc.reserved4 = 0x0;
    desc.seg_selector = KERNEL_CS;
    int i = 0;
    for(i = 0;i<20;i++){
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
    
    /* Interrupts */
    SET_IDT_ENTRY(desc, keyboard_wrap);
    idt[33] = desc;

    SET_IDT_ENTRY(desc, rtc_wrap);
    idt[40] = desc;

    // System Call 
    desc.dpl = 3;
    SET_IDT_ENTRY(desc, systemcall);
    idt[0x80] = desc;

    // Load IDT 
    lidt(idt_desc_ptr);


}



