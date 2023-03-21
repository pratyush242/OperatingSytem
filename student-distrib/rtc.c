#include "rtc.h"
#include "lib.h"


int rtc_counter = 0;

void rtc_init(){
    disable_irq(RTC_IRQ);		// important that no interrupts happen (perform a CLI)
    outb(0x70, 0x8A);	// select Status Register A, and disable NMI (by setting the 0x80 bit)
    outb(0x71, 0x20);	// write to CMOS/RTC RAM
    enable_ints(RTC_IRQ);		// (perform an STI) and reenable NMI if you wish
    
}



void rtc_handler(){
    
    outb(0x70, 0x0C);	// select register C
    inb(0x71);		// just throw away contents
    
    rtc_counter--;
    if(rtc_counter==0){
        rtc_counter = 512
    }
    
    // end interrupt
    send_eoi(RTC_IRQ);
}
    
    





