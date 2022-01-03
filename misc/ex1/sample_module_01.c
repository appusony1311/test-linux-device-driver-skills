/*
This is sample linux kernel module. It has init and exit functions. 
*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int __init sample_module_init(void)
{
	printk("sample module init function\n");
	pr_info("sample module init function invoked\n");
	return 0;
}
static void __exit sample_module_exit(void)
{
	printk("sample module exit function\n");
	pr_info("sample module exit function invoked\n");
}

module_init(sample_module_init);
module_exit(sample_module_exit);
MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("Sample Linux Kernel module development");
MODULE_LICENSE("GPL");
