
Build:

make
 make
make -C /lib/modules/3.13.0-96-generic/build M=/home/alex/aspiration_inspiration/ldd3_examples/ex9 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex9/chr_drv_udev.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex9/chr_drv_udev.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex9/chr_drv_udev.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'




Run:

isnmod the module
then:

cat  /sys/devices/virtual/virtual/sample_cdrv/sample_drv.sample_class 
sample driver example sysfs demo








