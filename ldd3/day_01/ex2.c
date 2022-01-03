/*
ex2 is basic module based on the chapter 2 of ldd3 book
having module_param along with base functions
*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/stat.h>
#include<linux/moduleparam.h>
long count=0;
module_param(count,long,S_IRUGO);
char *name="naveen";
module_param(name,charp,S_IRUGO);

static int ex2_module_init(void)
{
	pr_debug("welcome to hello world example module\n");
	pr_debug("module param: count = %ld\n",count);
	pr_debug("module param: name = %s\n",name);
	return 0;
}

static void ex2_module_exit(void)
{
	pr_debug("exit the hello world example module\n");
	return;
}
module_init(ex2_module_init);
module_exit(ex2_module_exit);
MODULE_AUTHOR("Alex");
MODULE_DESCRIPTION("ex2 module explain the module params");
MODULE_LICENSE("GPL");
