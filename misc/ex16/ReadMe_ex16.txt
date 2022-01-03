
Build:
**Imp:
copy Module.symvers from ldd3_examples/ex15  to ldd3_examples/ex16

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex16 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex16/ldd-driver.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex16/ldd-driver.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'

Run:


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ sudo insmod ./ldd-driver.ko 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ ls -l /sys/b
block/ bus/   
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ ls -l /sys/bus/ldd/drivers
total 0
drwxr-xr-x 2 root root 0 Nov 20 21:29 sample_ldd_driver
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ ls -l /sys/bus/ldd/drivers/sample_ldd_driver/
total 0
--w------- 1 root root 4096 Nov 20 21:30 bind
--w------- 1 root root 4096 Nov 20 21:29 uevent
--w------- 1 root root 4096 Nov 20 21:30 unbind
-r--r--r-- 1 root root 4096 Nov 20 21:30 version
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ ls -l /sys/bus/ldd/drivers/sample_ldd_driver/version 
-r--r--r-- 1 root root 4096 Nov 20 21:30 /sys/bus/ldd/drivers/sample_ldd_driver/version
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex16$ cat  /sys/bus/ldd/drivers/sample_ldd_driver/version 
(null)

