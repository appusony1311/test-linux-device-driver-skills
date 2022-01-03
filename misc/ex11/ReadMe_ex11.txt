
Build:
make:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex11$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex11 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex11/chr_drv_mmap.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex11/chr_drv_mmap.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex11/chr_drv_mmap.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'

