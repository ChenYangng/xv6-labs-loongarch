#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "loongarch.h"
#include "defs.h"

void extioi_init(void)
{
    printf("extioi_init\n");

    // *(volatile uint32*)(LIOINTC_INTENCLR) = 0xffffffff;
    // 
    // *(volatile uint32*)(LIOINTC_INTENSET) = 1 << LIOINTC_UART0; 
    // // *(volatile uint64*)(LIOINTC_INTEDGE) = 0 << LIOINTC_UART0; 
    // *(volatile uint32*)(LIOINTC_ROUTE_ENTRY10) = 0x21; 
    
    iocsr_writel(1 << LIOINTC_UART0, 0x1428);

    iocsr_writeb(0x21, 0x140a);


    /* qemu
     * The uart device is implemented as a mixture of 3A5000 and LS7A1000, its physical address is from 3A5000 uart0, which is 0x1fe001e0; but its interrupts go through 7A1000 interrupt controller.
     * It should be fixed. On real hardware, 3A5000 has two uart devices and LS7A1000 has another 4 uart devices(configurable).
     */
    // iocsr_writeq(0x1UL << UART0_IRQ, LOONGARCH_IOCSR_EXTIOI_EN_BASE);  
    //
    // iocsr_writeq(0x01UL,LOONGARCH_IOCSR_EXTIOI_MAP_BASE);
    //
    // iocsr_writeq(0x10000UL,LOONGARCH_IOCSR_EXTIOI_ROUTE_BASE);
    //
    // iocsr_writeq(0x1,LOONGARCH_IOCSR_EXRIOI_NODETYPE_BASE);
}

// ask the extioi what interrupt we should serve.
uint32
extioi_claim(void)
{
    return *(volatile uint32*)(LIOINTC_INTISR);
    // return iocsr_readq(LOONGARCH_IOCSR_EXTIOI_ISR_BASE);
}

void extioi_complete(uint64 irq)
{
    *(volatile uint32*)(LIOINTC_INTENCLR) = 1 << LIOINTC_UART0;
    *(volatile uint32*)(LIOINTC_INTENSET) = 1 << LIOINTC_UART0; 
    // iocsr_writeq(irq, LOONGARCH_IOCSR_EXTIOI_ISR_BASE);
}
