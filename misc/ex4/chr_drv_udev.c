/*sample char device driver */

//procedure-steps
/* step 1: need to get the major and minor number, by dynamic
   step 2: alloc_chrdev_region , will taken dev_t * ,minor, count, name
   step 3: fill call back functions using stuct file_operations (open,release, read, write, owner)
   step 4: cdev_alloc and 
   step 5: cdev_init , take arguments file_operations, cdev (nothing but :binding cdev with file opeations) 
   step 6: cdev_add ,take three aguments of cdev, mkdev, count (binding the cdev with major and minor number of count )
   step 7: implementing the file opeations call back functions , let us see
   step 8: int my_dev_open(struct inode *inode,  struct file  *file) , 
         if you impelent this, please consider the retun value as success as 0
   step 9: int my_dev_release(struct inode *inode, struct file *file)
   step 10: step 8 and step 9 are optinal, if you want to implement any extra , Please add , other wise it is dummy 
   step 11: ssize_t my_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos), what is the use of ppos??
   step 12: ssize_t my_dev_read(struct file *file, const char *buf, size_t lbuf, loff_t *ppos), what is the use of ppos??
*/

/* API:functions used
 dev_t mkdev(int,int);
 int alloc_chrdev_region(dev_t, int minor,int count,char *name);
 stuct cdev * cdev_alloc();
 cdev_init(stuct cdev *, struct file_operations *);
 cdev_add(stuct cdev *, dev_t, int count);
 int unregister_chrdev_region(dev_t, int count);
 cdev_del(struct cdev *);
 int copy_to_user(char __user *buffer, char * buffer2 , int len); //return non successfull copy byte count
 int copy_from_user(char *buffer, char __user* buffer2 , int len); //return non successfull copy byte count
 struct file_operations {    };
*/


#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/cdev.h>
#include<linux/slab.h>
#include<linux/device.h> 

#define CHAR_DEV_NAME "sample_cdrv"
#define MAX_LENGTH 4000
#define SUCCESS 0

static char char_device_buf[MAX_LENGTH];
static struct sample_drv {
	struct cdev *sample_cdev;
	dev_t sample_dev;
	int count,inuse;
	struct class *sample_class;
	
}sample_drv;


static int char_dev_open(struct inode *inode, struct file  *file)
{
	if(sample_drv.inuse)
	{
		pr_err("%s: Sample device is busy\n",CHAR_DEV_NAME);
		return -EBUSY;
	}	
	sample_drv.inuse=1;
	pr_info("Device open operation invoked with success\n");
	return SUCCESS;
		
}

static int char_dev_release(struct inode *inode, struct file *file)
{
	sample_drv.inuse=0;
	return SUCCESS;
}

static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf, loff_t *ppos)
{
       int nbytes = lbuf - copy_from_user (char_device_buf, buf, lbuf);
       pr_info("\n Received data from application=%s , number of bytes copied=%d\n",char_device_buf,nbytes);
       return nbytes;

}

static ssize_t char_dev_read(struct file *file, char *buf, size_t lbuf, loff_t *ppos)
{
       int nbytes = lbuf - copy_to_user (buf,char_device_buf,lbuf);
       pr_info("\n Write data to application=%s , number of bytes copied=%d\n",char_device_buf,nbytes);
       return nbytes;

}

static struct file_operations char_dev_fops = {
	.owner = THIS_MODULE,
	.write = char_dev_write,
	.read = char_dev_read,
	.open = char_dev_open,
	.release = char_dev_release
};

static int __init char_dev_init(void)
{
	int ret;
	sample_drv.count=1;
	sample_drv.inuse=0;
	if (alloc_chrdev_region (&sample_drv.sample_dev, 0, sample_drv.count, CHAR_DEV_NAME) < 0) {
            pr_err("failed to reserve major/minor range\n");
            return -1;
        }
   	sample_drv.sample_cdev= cdev_alloc(); 
	cdev_init(sample_drv.sample_cdev,&char_dev_fops);
	ret=cdev_add(sample_drv.sample_cdev,sample_drv.sample_dev,sample_drv.count);
	if( ret < 0 ) {
		pr_err("Error in registering device driver\n");
		return ret;
	}
	pr_info("%s:Device Registered Successfully\n",CHAR_DEV_NAME); 
	
	memset(char_device_buf,'\0',MAX_LENGTH);
        sample_drv.sample_class = class_create (THIS_MODULE, "virtual");
        device_create (sample_drv.sample_class, NULL, sample_drv.sample_dev, NULL, "%s", "sample_cdrv");
	
	pr_info("Major number = %d, Minor number = %d\n", MAJOR (sample_drv.sample_dev),MINOR (sample_drv.sample_dev));
	return 0;
}

static void __exit char_dev_exit(void)
{
	 device_destroy (sample_drv.sample_class, sample_drv.sample_dev);
         class_destroy (sample_drv.sample_class);
	 cdev_del(sample_drv.sample_cdev);
	 unregister_chrdev_region(sample_drv.sample_dev,sample_drv.count);
	 pr_info("%s: Device unregistered Successfully\n",CHAR_DEV_NAME);
}

module_init(char_dev_init);
module_exit(char_dev_exit);

MODULE_AUTHOR("Aspiration Inspiration Team");
MODULE_DESCRIPTION("Sample Linux Kernel char driver development");
MODULE_LICENSE("GPL");
/* End of code */
