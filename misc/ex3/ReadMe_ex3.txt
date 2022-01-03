
Build:

make
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ make
make -C /lib/modules/3.13.0-96-generic/build M=/home/alex/aspiration_inspiration/ldd3_examples/ex3 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex3/chr_drv_skel.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex3/chr_drv_skel.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex3/chr_drv_skel.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'


Run:

step 1:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ sudo insmod ./chr_drv_skel.ko 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ dmesg | tail
[ 5540.502737] sample_cdrv:Device Registered Successfully


step 2:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ lsmod
Module                  Size  Used by
chr_drv_skel           16889  0 
ctr                    13049  2 

step 3:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ cat /proc/devices 
Character devices:
  1 mem
  4 /dev/vc/0
  4 tty
  4 ttyS
  5 /dev/tty
  5 /dev/console
  5 /dev/ptmx
  5 ttyprintk
  6 lp
  7 vcs
 10 misc
 13 input
 21 sg
 29 fb
300 sample_cdrv
 81 video4linux
 99 ppdev
108 ppp
116 alsa
128 ptm
136 pts
180 usb
189 usb_device
216 rfcomm
226 drm
251 hidraw
252 bsg
253 watchdog
254 rtc

step 4:
mknod /dev/sample_cdrv c 300 0


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ sudo mknod /dev/sample_cdrv c 300 0
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ ls -l /dev/sample_cdrv 
crw-r--r-- 1 root root 300, 0 Nov 18 20:09 /dev/sample_cdrv

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ sudo chmod 666 /dev/sample_cdrv 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ ls -l /dev/sample_cdrv 
crw-rw-rw- 1 root root 300, 0 Nov 18 20:09 /dev/sample_cdrv



Setp 5:
gcc test_skel.c

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ ./a.out 
read data=Hello world

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex3$ dmesg | tail
[ 6299.400956]  Device open operation invoked with success
[ 6299.400969]  Received data from application=Hello world , number of bytes copied=12
[ 6299.400975]  Write data to application=Hello world , number of bytes copied=12







