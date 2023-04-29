#include "pit.h"
#include "lib.h"
#include "systemcalls.h"
#include "i8259.h"


void pit_init()
{   

    

    int divisor = 1193180 / PIT_HZ;       /* Calculate our divisor */
    outb(0x36, 0x43);             /* Set our command byte 0x36 */
    outb(divisor & 0xFF, 0x40);   /* Set low byte of divisor */
    outb(divisor >> 8, 0x40);     /* Set high byte of divisor */
    enable_irq(0x0);
  
    
}

void pit_handler()
{   
     cli();
    //printf("PITISWORKING \n");

     if(multi_terminal[0].pid == -1){
     
     terminal_switch(0);
     runningTerminal =  &(multi_terminal[0]);
     sti();
     send_eoi(0x0);
     system_execute((uint8_t*)"shell");
    
    
    return;

    }

    else if(multi_terminal[1].pid == -1){
     terminal_switch(1);
     runningTerminal =  &(multi_terminal[1]);
     sti();
     send_eoi(0x0);
     system_execute((uint8_t*)"shell");
    
    return;

    }
       else if(multi_terminal[2].pid == -1){
     terminal_switch(2);
     runningTerminal =  &(multi_terminal[2]);
     sti();
     send_eoi(0x0);
     system_execute((uint8_t*)"shell");
    
    return;

    }

    
    
  
    
    //scheduler(); /* video memory and context switch */
    sti();
    
    send_eoi(0x0);
   
}
