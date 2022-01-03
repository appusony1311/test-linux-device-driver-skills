
Build:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex6 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex6/chr_drv_ioctl.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex6/chr_drv_ioctl.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex6/chr_drv_ioctl.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'


Run:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ gcc test_ioctl.c 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ sudo insmod ./chr_drv_ioctl.ko 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ dmesg | tail
[  504.582216] sample_cdrv:Device Registered Successfully
[  504.582314] Major number = 250, Minor number = 0

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ sudo chmod 666 /dev/sample_cdrv 

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ ./a.out 
[2938] - Opening device sample_cdrv
Device opened with ID [3]
Present size of the buffer is 0
New contents of buffer: ======================================================================
New contents of buffer: welcome to hello world=

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ dmesg | tail
[  529.192267] Number of times open() was called: 1
[  529.192274]  MAJOR number = 250, MINOR number = 0
[  529.192277] Process id of the current process: 2938
[  529.192280] ref count=1
[  529.192303] Fill char config executed 
[  529.192307] number of bytes copied to user space=70
[  529.192316] Seeking to posotion=60
[  529.192319] number of bytes copied from user space=22
[  529.192322] Seeking to posotion=60
[  529.192324] number of bytes copied to user space=23

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ sudo rmmod chr_drv_ioctl 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex6$ dmesg | tail

[  542.177850] sample_cdrv: Device unregistered Successfully






