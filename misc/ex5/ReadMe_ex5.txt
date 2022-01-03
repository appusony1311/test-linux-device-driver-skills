
Build:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex5 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex5/chr_drv_ioctl.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex5/chr_drv_ioctl.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex5/chr_drv_ioctl.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ 



Run:


 gcc test_ioctl.c 

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ sudo insmod ./chr_drv_ioctl.ko 
[sudo] password for alex: 


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ ls -l /dev/sample_cdrv 
crw------- 1 root root 250, 0 Nov 19 18:46 /dev/sample_cdrv
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ sudo chmod 666 /dev/sample_cdrv 


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ ./a.out 
[2607] - Opening device sample_cdrv
Device opened with ID [3]
Present size of the buffer is 0
New contents of buffer: ======================================================================

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ dmesg | tail
[   67.320732] systemd-hostnamed[2177]: Warning: nss-myhostname is not installed. Changing the local hostname might make it unresolveable. Please install nss-myhostname!
[  206.695115] chr_drv_ioctl: module verification failed: signature and/or  required key missing - tainting kernel
[  206.695544] sample_cdrv:Device Registered Successfully
[  206.695649] Major number = 250, Minor number = 0
[  233.024719] Number of times open() was called: 1
[  233.024730]  MAJOR number = 250, MINOR number = 0
[  233.024733] Process id of the current process: 2607
[  233.024736] ref count=1
[  233.024757] Fill char config executed 
[  233.024779] 


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ sudo rmmod chr_drv_ioctl 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex5$ dmesg | tail
[  206.695115] chr_drv_ioctl: module verification failed: signature and/or  required key missing - tainting kernel
[  206.695544] sample_cdrv:Device Registered Successfully
[  206.695649] Major number = 250, Minor number = 0
[  233.024719] Number of times open() was called: 1
[  233.024730]  MAJOR number = 250, MINOR number = 0
[  233.024733] Process id of the current process: 2607
[  233.024736] ref count=1
[  233.024757] Fill char config executed 
[  233.024779] 
[  309.256564] sample_cdrv: Device unregistered Successfully








