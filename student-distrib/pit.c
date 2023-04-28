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
   
    printf("PITISWORKING \n");
    send_eoi(0x0);
    //scheduler(); /* video memory and context switch */
    
    
    
   
}
