#include<linux/module.h>
#include<linux/init.h>
#include<linux/errno.h>
#include<linux/types.h>
#include<linux/timer.h>
#include<linux/sched.h>


static struct timer_list my_timer;

static void my_timer_function (unsigned long ptr)
{
    pr_info("In my_timer_fun, jiffies = %ld\n", jiffies);
    pr_info("current task pid is %d\n",(int)current->pid);
    pr_info( "my data is: %d\n", (int)ptr);
}

static __init int my_timer_init(void)
{
	static int len = 100;
	init_timer (&my_timer);     /* intialize */
        my_timer.function = my_timer_function;
        my_timer.expires = jiffies + HZ;    /* one second delay */
        my_timer.data = len;
        pr_info("Adding timer at jiffies = %ld\n", jiffies);
        add_timer (&my_timer);

	return 0;
}

static __exit void  my_timer_exit(void)
{
	pr_info("Deleted time,r rc = %d\n", del_timer_sync (&my_timer));
	pr_info("timer module removed\n");
}
module_init(my_timer_init);
module_exit(my_timer_exit);

MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("Timer -Test");
MODULE_LICENSE("GPL");
