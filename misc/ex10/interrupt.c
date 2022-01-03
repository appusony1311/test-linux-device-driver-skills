#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

/*
 cat /proc/interrupts
19:          0          0          0          0   IO-APIC-fasteoi   my_interrupt
*/
#define SHARED_IRQ 19
static int irq = SHARED_IRQ, my_dev_id, irq_counter = 0;
module_param (irq, int, S_IRUGO);

static irqreturn_t my_interrupt (int irq, void *dev_id)
{
    irq_counter++;
    pr_info("In the ISR: counter = %d\n", irq_counter);
    return IRQ_NONE;            /* we return IRQ_NONE because we are just observing */
}

static int __init my_interrupt_init (void)
{
    if (request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id))
        return -1;
    pr_info("Successfully loaded the module with ISR handler\n");
    return 0;
}

static void __exit my_interrupt_exit (void)
{
    synchronize_irq (irq);
    free_irq (irq, &my_dev_id);
    pr_info("Successfully unloaded the module \n");
}

module_init (my_interrupt_init);
module_exit (my_interrupt_exit);

MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION ("Interrupt Handler Test");
MODULE_LICENSE("GPL");

