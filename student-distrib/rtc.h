#ifndef _RTC_H
#define _RTC_H

#define RTC_IRQ 8       //the irq num for keybaord 

extern void rtc_init();
extern void rtc_handler();

#endif