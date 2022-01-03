/*
This is sample linux kernel module. It has init and exit functions,with module parameters.
*/
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/moduleparam.h>
#include<linux/stat.h>
static int var=1;
static char *str="Hello world";

static int __init sample_module_init(void)
{
	printk("sample module init function\n");
	pr_info("sample module init function invoked...with var=%d str=%s\n",var,str);
	return 0;
}
static void __exit sample_module_exit(void)
{
	printk("sample module exit function\n");
	pr_info("sample module exit function invoked\n");
}

module_init(sample_module_init);
module_exit(sample_module_exit);
module_param(var,int,S_IRUGO);
module_param(str,charp,S_IRUGO);
MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("Sample Linux Kernel module development");
MODULE_LICENSE("GPL");
