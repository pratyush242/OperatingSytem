#define ASM 1

.globl system_call_linkage

system_call_linkage:

    pushl %ebp          /* save your registers */
    pushl %esi
    pushl %edi

    pushl %edx             /* third arg */
    pushl %ecx             /* second arg */
    pushl %ebx            /* first arg */

    cmp $1, %eax          /* check value of system call is less than 10 and more than 1 to see if it is out of bounds */
    jl invalid
    cmp $10, %eax
    jg invalid

    movl jumptable(, %eax, 4), %eax           
    call *%eax
    jmp pop_registers

invalid:
    movl $-1, %eax



jumptable:
    .long 0x0                             /* there is no system call number 0 */
    .long halt
    .long execute
    .long sys_read
    .long sys_write
    .long sys_open
    .long sys_close

pop_registers:
    popl %ebx
    popl %ecx
    popl %edx
    
    popl %edi
    popl %esi
    popl %ebp

    iret
   