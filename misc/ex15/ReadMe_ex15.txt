
Build

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex15$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex15 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex15/lddbus.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex15/lddbus.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex15/lddbus.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'


load the module
Run:

ls -l /sys/bus/ldd
total 0
drwxr-xr-x 2 root root    0 Nov 20 20:56 devices
drwxr-xr-x 2 root root    0 Nov 20 20:56 drivers
-rw-r--r-- 1 root root 4096 Nov 20 20:56 drivers_autoprobe
--w------- 1 root root 4096 Nov 20 20:56 drivers_probe
--w------- 1 root root 4096 Nov 20 20:56 uevent
-r--r--r-- 1 root root 4096 Nov 20 20:56 version
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex15$ ls -l /sys/bus/ldd/devices/
total 0
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex15$ ls -l /sys/bus/ldd/drivers
total 0
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex15$ ls -l /sys/bus/ldd/version 
-r--r--r-- 1 root root 4096 Nov 20 20:56 /sys/bus/ldd/version
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex15$ cat /sys/bus/ldd/version 
$Revision: 1.9 $


