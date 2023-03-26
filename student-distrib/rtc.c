#include "rtc.h"
#include "lib.h"
#include "i8259.h"


//rtc initializer
void rtc_init()
{
    cli();	
    outb(0x8B, 0x70);		// select register B, and disable NMI
    char prev = inb(0x71);	// read the current value of register B
    outb(0x8B, 0x70);		// set the index again (a read will reset the index to register D)
    outb(prev  | 0x40, 0x71);	// write the previous value ORed with 0x40. This turns on bit 6 of register B
    enable_irq(RTC_IRQ);
    enable_irq(SLAVE_IRQ); 
    sti();
    
}
//rtc handler
void rtc_handler() {
    /* mask the interrupts*/
    cli();
    //test_interrupts();
    outb(0x0C, 0x70); // select register C
    inb(0x71); // just throw away contents
    // end interrupt
    send_eoi(RTC_IRQ);
    
    sti();
}
