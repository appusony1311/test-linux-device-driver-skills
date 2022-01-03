/*
ex21 is basic modulde based on the chapter 11 of ldd3 book
print size of available data types in linux kernel on given platform
*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>

static int ex_module_init(void)
{
	printk("welcome to hello world example module\n");
	printk("size char=%ld\n",sizeof(char));
	printk("size int=%ld\n",sizeof(int));
	printk("size short=%ld\n",sizeof(short));
	printk("size long=%ld\n",sizeof(long));
	printk("size long long=%ld\n",sizeof(long long));
	printk("size size_t=%ld\n",sizeof(size_t));
	printk("size loff_t=%ld\n",sizeof(loff_t));
	printk("size pid_t=%ld\n",sizeof(pid_t));
	return 0;	
}

static void ex_module_exit(void)
{
	printk("exit the hello world example module\n");
	return;
}
module_init(ex_module_init);
module_exit(ex_module_exit);
MODULE_AUTHOR("Alex");
MODULE_DESCRIPTION("Ex1 module");
MODULE_LICENSE("GPL");
