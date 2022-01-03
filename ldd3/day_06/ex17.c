/*
ex17: work queue example
*/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/time.h>
#include<linux/delay.h>
#include<linux/wait.h>
#include<linux/workqueue.h>


/* declare a wait queue*/
static wait_queue_head_t my_wait_queue;

/* declare a work queue*/
struct workqueue_struct *wq;
struct work_struct workq;

void my_workqueue_handler(struct work_struct *work)
{
	printk("WORK QUEUE: I'm just a timer to wake up the sleeping moudlue. \n");
	msleep(10000);  /* sleep */
	printk("WORK QUEUE: time up MODULE !! wake up !!!! \n");
	wake_up_interruptible(&my_wait_queue);
}

static int work_queue_init_module(void)
{
	printk("work queue example ....\n");
	wq = create_workqueue("wq_test");
	// -- initialize the work queue
	INIT_WORK(&workq, my_workqueue_handler);
	//schedule_work(&workq);
	queue_work(wq, &workq);

	// -- initialize the WAIT QUEUE head
	init_waitqueue_head(& my_wait_queue);

	printk("MODULE: This moudle is goint to sleep....\n");
	interruptible_sleep_on(&my_wait_queue);
	printk("MODULE: Wakeup Wakeup I am Waked up........\n");
	return 0;
}

void work_queue_exit_module(void)
{
	printk("work queue exit module \n");
	flush_workqueue(wq);
    	destroy_workqueue(wq);

}
module_init(work_queue_init_module);
module_exit(work_queue_exit_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ALEX");
MODULE_DESCRIPTION("A Work queue example");
