
Build:

make
make -C /lib/modules/3.13.0-96-generic/build M=/home/alex/aspiration_inspiration/ldd3_examples/ex1 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex1/sample_module_01.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex1/sample_module_01.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex1/sample_module_01.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'


Run:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex1$ sudo insmod ./sample_module_01.ko 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex1$ dmesg | tail
[ 2625.741661] sample module init function
[ 2625.741667] sample module init function invoked


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex1$ lsmod
Module                  Size  Used by
sample_module_01       12433  0 
ctr                    13049  2 


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex1$ dmesg | tail
[ 2799.791591] sample module exit function
[ 2799.791597] sample module exit function invoked



