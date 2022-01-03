******  ADC module in S3C2410 SoC *********************
**Note: it will not work on other boards, platforms : it will work on S3C2410 , (memory map)modify as per your platform inorder to work
Step 1: find the unused/free major number from cat /proc/devices

Step 2: open the ex31.c fill with major and minor number, build, insmod (in case of static) 
 (in case of dynamic major and minor, while insmod, it will display the major and minor, check with dmesg | tail)

Step 3: mknod /dev/sample_drver c major minor , check the test.c node

step 4: change permissons /dev/sample_driver , to run the test app

Step 5: run the app, see the output/observations
