/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7  */
uint8_t slave_mask;  /* IRQs 8-15 */

/* Initialize the 8259 PIC */
void i8259_init(void) {
    //magic numbers - 0xff is master and slave mask & port + 1 = data
    // mask out all interrupts on the PIC 
    outb(0xff, (MASTER_8259_PORT + 1)); 
    outb(0xff, (SLAVE_8259_PORT + 1)); 
    // initialize the PIC with ICW1
    outb(ICW1, MASTER_8259_PORT);
    outb(ICW1, SLAVE_8259_PORT);
    // initialize the PIC with ICW2
    outb(ICW2_MASTER, (MASTER_8259_PORT + 1)); 
    outb(ICW2_SLAVE, (SLAVE_8259_PORT + 1));
    // initialize the PIC with ICW3
    outb(ICW3_MASTER, (MASTER_8259_PORT + 1));
    outb(ICW3_SLAVE, (SLAVE_8259_PORT + 1));
    // initialize the PIC with ICW4
    outb(ICW4, (MASTER_8259_PORT + 1));
    outb(ICW4, (SLAVE_8259_PORT + 1));
    // Mask all interrupts
    outb(0xff, (MASTER_8259_PORT + 1));
    outb(0xff, (SLAVE_8259_PORT + 1));
}

/* Enable (unmask) the specified IRQ */
void enable_irq(uint32_t irq_num) {

}

/* Disable (mask) the specified IRQ */
void disable_irq(uint32_t irq_num) {
}

/* Send end-of-interrupt signal for the specified IRQ */
void send_eoi(uint32_t irq_num) {
}
