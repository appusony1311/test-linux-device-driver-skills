
Build:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex12$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex12 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex12/chr_drv_complete.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex12/chr_drv_complete.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex12/chr_drv_complete.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'

run:

load the module

chmod 666 /dev/sample_cdrv

gcc reader.c -o reader

gcc writer.c -o writer

run the reader app first in one terminal

it will wait for data

run the writet app in another terminal
it will write the data, then wakeup the reader process, reader process will display the data
