
Build:

make
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex2$ make
make -C /lib/modules/3.13.0-96-generic/build M=/home/alex/aspiration_inspiration/ldd3_examples/ex2 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex2/sample_module_02.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex2/sample_module_02.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex2/sample_module_02.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic


Run:

sudo insmod ./sample_module_02.ko  var=10 str="fun,to,code"
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex2$ dmesg | tail
[ 3564.253616] sample module init function invoked...with var=10 str=fun,to,code
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex2$ 



alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex2$ lsmod
Module                  Size  Used by
sample_module_02       12641  0 
ctr                    13049  2 


sudo rmmod sample_module_02 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex2$ dmesg | tail
[ 2799.791591] sample module exit function
[ 2799.791597] sample module exit function invoked




