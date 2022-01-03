/*
ex1 is basic module based on the chapter 2 of ldd3 book
having module_init and module_exit functions
*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

static int ex1_module_init(void)
{
	pr_debug("welcome to hello world example module\n");
	return 0;
}

static void ex1_module_exit(void)
{
	pr_debug("exit the hello world example module\n");
	return;
}
module_init(ex1_module_init);
module_exit(ex1_module_exit);
MODULE_AUTHOR("Alex");
MODULE_DESCRIPTION("ex1 module");
MODULE_LICENSE("GPL");
