#include<linux/device.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/string.h>
#include"lddbus.h"

static struct ldd_driver sample_ldd_driver = {
	
	.driver   = {
		.name = "sample_ldd_driver",
	},
};

static int __init sample_ldd_init_driver(void)
{
	return register_ldd_driver(&sample_ldd_driver);
}

static void __exit sample_ldd_exit_driver(void)
{
	unregister_ldd_driver(&sample_ldd_driver);
}

module_init(sample_ldd_init_driver);
module_exit(sample_ldd_exit_driver);

MODULE_AUTHOR("Aspiration Inspiration");
MODULE_DESCRIPTION("Sample ldd client driver");
MODULE_LICENSE("Dual BSD/GPL");
