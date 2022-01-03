#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include<linux/cdev.h>
#include<linux/sched.h>
#include<linux/errno.h>
#include<asm/current.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/mutex.h>
#include <linux/spinlock.h>
#include <linux/delay.h>
#include"ioctl_const.h"


#define CHAR_DEV_NAME "sample_cdrv"
#define MAX_LENGTH 4000
#define SUCCESS 0

static char char_device_buf[MAX_LENGTH];

static struct sample_drv {
	struct cdev *sample_cdev;
	dev_t sample_dev;
	int count,inuse;
	struct class *sample_class;
	struct mutex sample_lock;
	
}sample_drv;

static int char_dev_open(struct inode *inode, struct file  *file)
{
	static int counter = 0;
	counter++;
	pr_info("Number of times open() was called: %d\n", counter);
	pr_info(" MAJOR number = %d, MINOR number = %d\n",imajor (inode), iminor (inode));
	pr_info("Process id of the current process: %d\n",current->pid );
	pr_info( "ref count=%ld\n", module_refcount(THIS_MODULE));
	return SUCCESS;
}

static int char_dev_release(struct inode *inode, struct file *file)
{
	return SUCCESS;
}

static ssize_t char_dev_read(struct file *file, char *buf,  size_t lbuf,  loff_t *ppos)
{
	int maxbytes; /* number of bytes from ppos to MAX_LENGTH */
	int bytes_to_do; /* number of bytes to read */
	int nbytes; /* number of bytes actually read */

	maxbytes = MAX_LENGTH - *ppos;
	
	if( maxbytes > lbuf ) 
		bytes_to_do = lbuf;
	else 
		bytes_to_do = maxbytes;
	
	if( bytes_to_do == 0 ) {
		pr_err("Reached end of device\n");
		return -ENOSPC; /* Causes read() to return EOF */
	}
	if(mutex_lock_interruptible(&sample_drv.sample_lock)) /*begin of critical region */
		/* something went wrong with wait */
                 return -ERESTARTSYS;
	pr_info("Reader: Acquired  lock : executing code \n");
	nbytes = bytes_to_do - copy_to_user( buf, /* to */
			       char_device_buf + *ppos, /* from */
			       bytes_to_do ); /* how many bytes */

	*ppos += nbytes;
	 pr_info("Reader/read :entering delay routine \n");
 
	ssleep(30);

	pr_info("Reader/Read:  out of delay releasing lock \n");
	mutex_unlock(&sample_drv.sample_lock); /*end of critical region */
	pr_info("number of bytes copied to user space=%d\n",nbytes);
	return nbytes;

}

static ssize_t char_dev_write(struct file *file, const char *buf, size_t lbuf,  loff_t *ppos)
{
	int nbytes; /* Number of bytes written */
	int bytes_to_do; /* Number of bytes to write */
	int maxbytes; /* Maximum number of bytes that can be written */

	maxbytes = MAX_LENGTH - *ppos;

	if( maxbytes > lbuf ) 
		bytes_to_do = lbuf;
	else 
		bytes_to_do = maxbytes;

	if( bytes_to_do == 0 ) {
		pr_err("Reached end of device\n");
		return -ENOSPC; /* Returns EOF at write() */
	}
	if(mutex_lock_interruptible(&sample_drv.sample_lock)) /*begin of critical region */
		/* something went wrong with wait */
                 return -ERESTARTSYS;
	pr_info("WRITER: Acquired Write lock : executing code \n");
	nbytes = bytes_to_do - copy_from_user( char_device_buf + *ppos, /* to */
				 buf, /* from */
				 bytes_to_do ); /* how many bytes */
	*ppos += nbytes;
	 pr_info("Writer/write :entering delay routine \n");
 
	ssleep(30);

	pr_info("Writer/write:  out of delay releasing lock \n");
	mutex_unlock(&sample_drv.sample_lock); /*end of critical region */
        pr_info("number of bytes copied from user space=%d\n",nbytes);
        return nbytes;

}


static long char_dev_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
 /*	step 1: verify args */

        unsigned int i, size;
        char c;
        int retbytes;

        if( _IOC_TYPE(cmd) != SAMPLE_MAGIC ) return -ENOTTY;
        if( _IOC_NR(cmd) > SAMPLE_MAX_CMDS ) return -ENOTTY;

        if( _IOC_DIR(cmd) & _IOC_READ )
                if( !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd) ) )
                        return -EFAULT;
        if( _IOC_DIR(cmd) & _IOC_WRITE )
                if( !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd) ) )
                        return -EFAULT;

	/* implement support of commands using switch/case */

        /* sounds ok lets continue */
        switch(cmd) {

        case SAMPLE_FILL_ZERO:
                for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = 0;
		pr_info("Fill zero config executed\n ");
                break;

        case SAMPLE_FILL_CHAR:
                retbytes = copy_from_user( &c, (char *)arg, sizeof(char) );
                for(i=0; i<MAX_LENGTH; i++) char_device_buf[i] = c;
		pr_info("Fill char config executed \n");
                break;

        	
	case SAMPLE_GET_SIZE:
		if (!capable(CAP_SYS_ADMIN))
                        return -EPERM;

		size = MAX_LENGTH;
                retbytes=copy_to_user( (unsigned int*)arg, &size , sizeof(unsigned int) );
		pr_info("Get size config executed \n");	
                break;

        }

        return SUCCESS;
}	

static loff_t char_dev_lseek (struct file *file, loff_t offset, int orig)
{
    loff_t testpos;

    switch (orig) {

    case 0:                 /* SEEK_SET */
            testpos = offset;
            break;
    case 1:                 /* SEEK_CUR */
            testpos = file->f_pos + offset;
            break;
    case 2:                 /* SEEK_END */
           testpos = MAX_LENGTH + offset;
           break;
    default:
          return -EINVAL;
    }
   
    testpos = testpos < MAX_LENGTH ? testpos : MAX_LENGTH;
    testpos = testpos >= 0 ? testpos : 0;
    file->f_pos = testpos;
    pr_info("Seeking to posotion=%ld\n", (long)testpos);
    return testpos;
}

static struct file_operations char_dev_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = char_dev_ioctl,
	.read = char_dev_read,
	.write = char_dev_write,
	.open = char_dev_open,
	.release = char_dev_release,
	.llseek = char_dev_lseek,
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
	
	mutex_init(&sample_drv.sample_lock);
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
