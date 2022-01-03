
This Linux device driver will provide you with all the necessary information about how to write a device driver for Linux operating systems.

Overview /Inputs:

1. Linux has a monolithic kernel. For this reason, writing a device driver for Linux requires performing a combined compilation with the kernel. 

2. At its base, a module is a specifically designed object file. When working with modules, Linux links them to its kernel by loading them to its address space. The Linux kernel was developed using the C programming language and Assembler. C implements the main part of the kernel, and Assembler implements parts that depend on the architecture.


3. We run the module code in the kernel context.This requires a developer to be very attentive, as it entails extra responsibilities: 
if a developer makes a mistake when implementing a user-level application, this will not cause problems outside the user application in most cases; but if a kernel developer makes a mistake when implementing a kernel module, the consequences will be problems at the system level.

4. When the kernel encounters non-critical errors (for example, null pointer dereferencing), you’ll see the oops message (insignificant malfunctions during Linux operation are called oops), after which the malfunctioning module will be unloaded, allowing the kernel and other modules to work as usual. In addition, you’ll be able to find a record in the kernel log that precisely describes this error. But be aware that continuing work after an oops message is not recommended, as doing so may lead to instability and kernel panic.

5. The kernel and its modules essentially represent a single program module – so keep in mind that a single program module uses a single global namespace. In order to minimize it, you must watch what is being exported by the module: exported global characters must be named uniquely (a commonly used workaround is to simply use the name of the module that’s exporting the characters as a prefix) and must be cut to the bare minimum.

6. Loading and Unloading Modules:
The only two things this module does is load and unload itself. To load a Linux driver, we call the driver_init function, and to unload it, we call the driver_exit function. The module_init and module_exit macros notify the kernel about driver loading and unloading. The driver_init and driver_exit functions must have identical signatures.

7. Registering a Character Device:
you can find device files in the /dev folder. They facilitate interaction between the user and the kernel code. If the kernel must receive anything, you can just write it to a device file to pass it to the module serving this file; anything that’s read from a device file originates from the module serving this file. We can divide device files into two groups: character files and block files. Character files are non-buffered, whereas block files are buffered. As their names imply, character files allow you to read and write data character by character, while block files allow you to write only whole blocks of data. We’ll leave the discussion of block files out of the scope of this article, and will get straight to character files.

8. major device numbers,minor device numbers
Linux systems have a way of identifying device files via major device numbers, which identify modules serving device files or a group of devices, and minor device numbers, which identify a specific device among a group of devices that a major device number specifies. In the driver code, we can define these numbers as constants or they can be allocated dynamically. In case a number defined as a constant has already been used, the system will return an error. When a number is allocated dynamically, the function reserves that number to prohibit it from being used by anything else

9. Build System of a Kernel Module
fortunately, these times are long gone and the process is much simpler now. Today, much of the work is done by the makefile: it starts the kernel build system and provides the kernel with the information about the components required to build the module. A module built from a single source file requires a single string in the makefile. After creating this file, you need only to initiate the kernel build system:

obj-m := source_file_name.o

To build the module:

make –C KERNEL_MODULE_BUILD_SYSTEM_FOLDER M=`pwd` modules

10.Loading and Using Module
insmod , modprobe , lsmod , rmmod
cat /proc/modules ==> to get list of modules that are already loaded
