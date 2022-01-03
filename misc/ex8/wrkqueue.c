
/* Demonstration of WORK-QUEUES*/
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/workqueue.h>
#include<linux/sched.h>

#define DELAY	100


void wq_func(void *arg);
static int counter;
DECLARE_WORK(wq,(work_func_t)wq_func);
//create_workqueue(myqueue);

void wq_func(void *arg)
{
	printk("%ld %d %s \n", jiffies,counter++,current->comm);
        if( counter < 1000 )
                schedule_work(&wq);
}

static int __init my_wq_init(void)
{
	pr_info("\nWQ Module Inserted\n");
	schedule_work(&wq);
	pr_info("current counter %ld\n",jiffies);
	pr_info("current counter %ld\n",jiffies);
	return 0;	
}

static void __exit my_wq_exit(void)
{
	pr_info("\nWQ Module Removed");
}

module_init(my_wq_init);
module_exit(my_wq_exit);
MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("work queue -Test");
MODULE_LICENSE("GPL");
