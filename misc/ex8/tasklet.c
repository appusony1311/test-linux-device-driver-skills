#include <linux/module.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/init.h>

static void tasklet_fun (unsigned long t_arg);

static struct simp
{
    int i;
    int j;
} t_data;


static struct tasklet_struct tasklet_name = { NULL, 0, ATOMIC_INIT(0), tasklet_fun, &t_data};

static void tasklet_fun (unsigned long t_arg)
{
    struct simp *datum;
    datum = (struct simp *)t_arg;
    pr_info( "Entering tasklet_fun, datum->i = %d, jiffies = %ld\n",
            datum->i, jiffies);
    pr_info("Entering t_fun, datum->j = %d, jiffies = %ld\n",
            datum->j, jiffies);
}

static int __init my_tasklet_init (void)
{
    pr_info("\nHello: init_module loaded at address 0x%p\n",init_module);
    t_data.i = 100;
    t_data.j = 200;
    pr_info(" scheduling my tasklet, jiffies= %ld \n", jiffies);
    tasklet_schedule (&tasklet_name);
    return 0;
}

static void __exit my_tasklet_exit (void)
{
    tasklet_disable(&tasklet_name);
    pr_info("\nHello: cleanup_module loaded at address 0x%p\n", cleanup_module);
}



module_init (my_tasklet_init);
module_exit (my_tasklet_exit);
MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("tasklet -Test");
MODULE_LICENSE("GPL");
