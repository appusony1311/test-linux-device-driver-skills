
Build:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex10$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex10 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex10/interrupt.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex10/interrupt.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex10/interrupt.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic




Run:

isnmod the module

[ 1367.072109] Successfully loaded the module with ISR handler 


alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex10$ cat /proc/interrupts 
           CPU0       CPU1       CPU2       CPU3       
  0:         44          0          0          0   IO-APIC-edge      timer
  1:        698        769        600        440   IO-APIC-edge      i8042
  8:          1          0          0          0   IO-APIC-edge      rtc0
  9:          0          1          1          1   IO-APIC-fasteoi   acpi
 12:       3686       3634       3197       3467   IO-APIC-edge      i8042
 16:        138        132        133        131   IO-APIC-fasteoi   ehci_hcd:usb1
 17:          0          1          0      33280   IO-APIC-fasteoi   brcmsmac
 18:          0          0          0          0   IO-APIC-fasteoi   ips
 19:          0          0          0          0   IO-APIC-fasteoi   my_interrupt


rmmod the module
[ 1411.723009] Successfully unloaded the module 








