Module -------   Explanation
1.ex1           - sample module to start writing the kernel modules. It(code) contain init and exit functions
2.ex2           - sample module , with module parameters.
3.ex3           - sample char driver with file operation, with static allocation of major and minor number. test app is provided
4.ex4           - sample char driver with file operation, with dynamic allocation of major and minor number,dev node is auto generated.
                   test app is provided.
5.ex5           - extension of ex4 + ioctl fops is added
6.ex6           - extension of ex5 + lseek fops is added
7.ex7           - extension of ex6 + mutex locking mechanisam is added in read and write operations   
		- extension of ex6 + semaphore locking mechanisam is added in read and write operations
		- extension of ex6 + spinlock locking mechanisam is added in read and write operations

8.ex8           - tasklet example module
                - work queue example module
                - timer example module

9.ex9           - extension of ex4 + sysfs entry created using device_create_file/device_remove_file

10.ex10         - interrupt sample/example module

11.ex11         - extension of ex4 + mmap file operation is added, to map the kernel memory to user space

12.ex12         - extension of ex6 + complete and wait_for_completion lock mechanisam

13.ex13         - extension of ex6 + wake_up_interruptible and wait_event_interruptible/wait_event_killable  lock mechanisam

14.ex14		- proc fs file creation ( using the API: proc_create and remove_proc_entry)

15.ex15		- ldd bus is sample bus, with export functions

16.ex16		- ldd driver is sample client driver to register with ldd bus, using the exported functions


