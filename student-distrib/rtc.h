#ifndef _RTC_H
#define _RTC_H

#define RTC_IRQ 8  
#define SLAVE_IRQ 2

extern void rtc_init();
extern void rtc_handler();

#endif 
