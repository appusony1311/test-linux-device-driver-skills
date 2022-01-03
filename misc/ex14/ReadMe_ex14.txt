
Build:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex14$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex14 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex14/proc_ex.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex14/proc_ex.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex14/proc_ex.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'


load the Module:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex14$ sudo insmod ./proc_ex.ko 
[sudo] password for alex: 



Run:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex14$ cat /proc/hello_proc 
Hello proc!

