
Build:

make
make
make -C /lib/modules/3.13.0-96-generic/build M=/home/alex/aspiration_inspiration/ldd3_examples/ex4 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex4/chr_drv_udev.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex4/chr_drv_udev.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex4/chr_drv_udev.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'



Run:


gcc test_skel.c

 sudo ./a.out
read data=Hello world
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex4$ dmesg | tail
[ 7630.605246] sample_cdrv:Device Registered Successfully
[ 7630.605469] Major number = 250, Minor number = 0
[ 7729.933063] Device open operation invoked with success
[ 7729.933072] Received data from application=Hello world , number of bytes copied=12
[ 7729.933077] Write data to application=Hello world , number of bytes copied=12
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex4$ 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex4$ 








