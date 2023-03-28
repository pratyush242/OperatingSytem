#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define KEYBOARD_IRQ 1       //the irq num for keybaord 



volatile unsigned char key_buffer[127];
volatile int keybuffer_ptr;

extern void init_keyboard();
extern void handler_keyboard();

#endif
