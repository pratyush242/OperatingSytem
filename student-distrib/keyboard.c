#include "keyboard.h"
#include "lib.h"
#include "i8259.h"

void init_keyboard()
{
    enable_irq(KEYBOARD_IRQ);
}
// used the scan code given on https://wiki.osdev.org/PS/2_Keyboard for a "US QWERTY" keyboard only
unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8','9', '0', '-', '=', '\b', // 0 isnt mapped--- 27 = esc key---- 0-9 ----- symbols---- backspace
    '\t','q', 'w', 'e', 'r','t', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', // tab---qwerty--- brackets---enter
    0,'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';','\'', '`',   0,  //left control (responds to nothing on the kernel)----qwerty----symbols--- left shift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n','m', ',', '.', '/', 0,'*', //symbol----qwerty----right shift
    0,  // Alt 
    ' ',  // Space bar 
    0,  // Caps lock 
    0,  0,   0,   0,   0,   0,   0,   0,   0,  0,  // F1 - F10 
    0,  // 69 - Num lock
    0,  // Scroll Lock 
    0,  // Home key 
    0,  // Up Arrow 
    0,  // Page Up 
    '-',
    0,  // Left Arrow 
    0,
    0,  // Right Arrow 
    '+',
    0,  // 79 - End key
    0,  // Down Arrow 
    0,  // Page Down 
    0,  // Insert Key 
    0,  // Delete Key 
    0,   0,   0,
    0,  // F11 Key 
    0,  // F12 Key 
    0,  // All other keys are undefined 
    };

void handler_keyboard(){
    unsigned char keydata = 0;
    // mask interrupt
    cli();
    // wait for interrupt
    while(1){
        if (inb(EOI)){
            keydata = inb(EOI);
            break;
        }
    }
    // check if key is valid
    if (keydata < 128){ 
        putc(keyboard_map[keydata]);
    }
    // end interrupt
    send_eoi(KEYBOARD_IRQ);
    // enable interrupt
    sti();
}