#include "rtc.h"
#include "lib.h"


uint32_t rtc_counter = 0;

void rtc_init(){
    
    disable_irq(RTC_IRQ);			// disable interrupts
    outb(0x8B, 0x70);		// select register B, and disable NMI
    char prev = inb(0x71);	// read the current value of register B
    outb(0x8B, 0x70);		// set the index again (a read will reset the index to register D)
    outb(prev | 0x40, 0x71);	// write the previous value ORed with 0x40. This turns on bit 6 of register B
    enable_irq(RTC_IRQ);
    
}



void rtc_handler(){
    
    outb(0x0C, 0x70);	// select register C
    inb(0x71);		// just throw away contents
    
    // end interrupt
    send_eoi(RTC_IRQ);
}
    
    





