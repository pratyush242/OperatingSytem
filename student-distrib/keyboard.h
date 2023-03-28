#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#define KEYBOARD_IRQ 1       //the irq num for keybaord 


//declaration of variables
volatile unsigned char key_buffer[127];
volatile int keybuffer_ptr;
//declaration of functions
extern void init_keyboard();
extern void handler_keyboard();
volatile int read_terminal;

#endif
