#ifndef _PIT_H
#define _PIT_H




/*Constants to set the PIT frequency*/
#define PIT_HZ        50       // frequency in Hz


void pit_init();
void pit_handler();

#endif
