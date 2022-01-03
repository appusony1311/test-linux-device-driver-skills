
Build:

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ make
make -C /lib/modules/3.13.0-96-generic/build SUBDIRS=/home/alex/aspiration_inspiration/ldd3_examples/ex7 modules
make[1]: Entering directory `/usr/src/linux-headers-3.13.0-96-generic'
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_mutex.o
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_spinlock.o
  CC [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_semaphore.o
  Building modules, stage 2.
  MODPOST 3 modules
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_mutex.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_mutex.ko
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_semaphore.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_semaphore.ko
  CC      /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_spinlock.mod.o
  LD [M]  /home/alex/aspiration_inspiration/ldd3_examples/ex7/chr_drv_spinlock.ko
make[1]: Leaving directory `/usr/src/linux-headers-3.13.0-96-generic'



Run:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ gcc test_reader.c -o t1

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ gcc test_writer.c -o t2

mutex:
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ sudo insmod ./chr_drv_mutex.ko 
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ ls -l /dev/sample_cdrv 
crw------- 1 root root 250, 0 Nov 19 18:55 /dev/sample_cdrv
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ chmod 666 /dev/sample_cdrv 
chmod: changing permissions of ‘/dev/sample_cdrv’: Operation not permitted
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ sudo chmod 666 /dev/sample_cdrv 

take two terminals:

1. run ./t2

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ ./t2
[3287] - Opening device sample_chr_driver
PID [3287]

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ dmesg | tail -20
[  762.541841] sample_cdrv:Device Registered Successfully
[  762.541948] Major number = 250, Minor number = 0
[  810.033311] Number of times open() was called: 1
[  810.033318]  MAJOR number = 250, MINOR number = 0
[  810.033321] Process id of the current process: 3287
[  810.033324] ref count=1
[  810.033332] WRITER: Acquired Write lock : executing code 
[  810.033335] Writer/write :entering delay routine 
[  810.967076] Number of times open() was called: 2
[  810.967083]  MAJOR number = 250, MINOR number = 0
[  810.967086] Process id of the current process: 3288
[  810.967089] ref count=2
[  840.039212] Writer/write:  out of delay releasing lock 
[  840.039223] number of bytes copied from user space=4000


2. run ./t1 in other terminal
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ ./t1
[3288] - Opening device sample_chr_driver
 read frm device ****************************************************************************************************
*********************************************************************************************************************
*********************************************************************************************************************
**********************************************************************************************************************
**********************************************************************************************************************
***********************************************************************************************************************
************************************************************************************************************************
**************************************************************************************************************************
******************************************************************************************************************************
************************************************************************************************************************************
*************************************************************************************************************************************
**************************************************************************************************************************************
************************************************************************************************************************************
*******************************************************************************************************************************************
*********************************************************************************************************************************************
*****************************************************************************************************************************************
*********************************************************************************************************************************************
*********************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************************@ 

Number of times open() was called: 2
[  810.967083]  MAJOR number = 250, MINOR number = 0
[  810.967086] Process id of the current process: 3288
[  810.967089] ref count=2
Reader: Acquired  lock : executing code 
[  840.039278] Reader/read :entering delay routine 
[  870.046134] Reader/Read:  out of delay releasing lock 
[  870.046145] number of bytes copied to user space=4000

spinlock with sleep: issue
=========================

alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/ex7$ dmesg | tail -40
[ 1745.422195]  MAJOR number = 250, MINOR number = 0
[ 1745.422197] Process id of the current process: 3407
[ 1745.422199] ref count=1
[ 1745.422206] WRITER: Acquired Write lock : executing code 
[ 1745.422207] Writer/write :entering delay routine 
[ 1747.562613] Number of times open() was called: 2
[ 1747.562620]  MAJOR number = 250, MINOR number = 0
[ 1747.562623] Process id of the current process: 3408
[ 1747.562626] ref count=2
[ 1772.377847] BUG: soft lockup - CPU#2 stuck for 22s! [t1:3408]
[ 1772.377854] Modules linked in: chr_drv_spinlock(OX) rfcomm bnep arc4 brcmsmac cordic brcmutil b43 mac80211 cfg80211 btusb ssb bluetooth snd_hda_codec_idt dell_wmi sparse_keymap bcma uvcvideo videobuf2_vmalloc videobuf2_memops videobuf2_core videodev dell_laptop dcdbas intel_powerclamp coretemp kvm_intel kvm joydev snd_hda_intel snd_hda_codec snd_hwdep snd_pcm snd_page_alloc serio_raw snd_seq_midi snd_seq_midi_event intel_ips snd_rawmidi snd_seq snd_seq_device lpc_ich snd_timer snd shpchp mei_me soundcore mei wmi i915 video drm_kms_helper drm mac_hid i2c_algo_bit parport_pc ppdev lp parport hid_generic usbhid hid ums_realtek usb_storage psmouse ahci libahci atl1c [last unloaded: chr_drv_semaphore]
[ 1772.377931] CPU: 2 PID: 3408 Comm: t1 Tainted: G           OX 3.13.0-96-generic #143-Ubuntu
[ 1772.377934] Hardware name: Dell Inc. Inspiron N4030/0K13WN, BIOS A07 03/23/2011
[ 1772.377938] task: ffff88007038c800 ti: ffff880045a9a000 task.ti: ffff880045a9a000
[ 1772.377941] RIP: 0010:[<ffffffff81731f72>]  [<ffffffff81731f72>] _raw_spin_lock+0x32/0x50
[ 1772.377952] RSP: 0018:ffff880045a9bed8  EFLAGS: 00000202
[ 1772.377955] RAX: 0000000000007d54 RBX: 0002000000000001 RCX: 0000000000000000
[ 1772.377958] RDX: 0000000000000002 RSI: 0000000000000002 RDI: ffffffffa0298380
[ 1772.377961] RBP: ffff880045a9bed8 R08: 0000000000000000 R09: 0000000000000000
[ 1772.377963] R10: 0000000000000011 R11: 0000000000000246 R12: 0000000000000000
[ 1772.377966] R13: 00000000811d218a R14: ffff880045a9bf00 R15: 000000000000d9e0
[ 1772.377970] FS:  00007fcba8371740(0000) GS:ffff880077300000(0000) knlGS:0000000000000000
[ 1772.377973] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[ 1772.377975] CR2: 00007fcba7dfac1c CR3: 0000000045916000 CR4: 00000000000007e0
[ 1772.377978] Stack:
[ 1772.377980]  ffff880045a9bf00 ffffffffa02963e5 ffff880045a9bf50 ffff880045a56300
[ 1772.377985]  00007ffc5dabab60 ffff880045a9bf38 ffffffff811c0f75 ffff880045a56300
[ 1772.377989]  00007ffc5dabab60 0000000000000fa0 0000000000000000 0000000000000000
[ 1772.377994] Call Trace:
[ 1772.378002]  [<ffffffffa02963e5>] char_dev_read+0x55/0xd1 [chr_drv_spinlock]
[ 1772.378010]  [<ffffffff811c0f75>] vfs_read+0x95/0x160
[ 1772.378015]  [<ffffffff811c1a89>] SyS_read+0x49/0xa0
[ 1772.378021]  [<ffffffff8173aadd>] system_call_fastpath+0x1a/0x1f
[ 1772.378023] Code: 89 e5 b8 00 00 02 00 f0 0f c1 07 89 c2 c1 ea 10 66 39 c2 75 02 5d c3 83 e2 fe 0f b7 f2 b8 00 80 00 00 eb 0c 0f 1f 44 00 00 f3 90 <83> e8 01 74 0a 0f b7 0f 66 39 ca 75 f1 5d c3 66 66 66 90 66 66 
[ 1775.426213] Writer/write:  out of delay releasing lock 
[ 1775.426222] number of bytes copied from user space=4000
[ 1775.426224] Reader: Acquired lock : executing code 
[ 1775.426227] Reader/read :entering delay routine 
[ 1805.433185] Reader/Read:  out of delay releasing lock 
[ 1805.433197] number of bytes copied to user space=4000
alex@alex-inspiron-N4030:~/aspiration_inspiration/ldd3_examples/

