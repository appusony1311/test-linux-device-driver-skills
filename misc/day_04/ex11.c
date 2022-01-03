/*
ex11: char drv module with ioctl file operation
dynamic allocation of major and minor number
*/
#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<linux/kdev_t.h>
#include<asm/uaccess.h>
#include<linux/slab.h>
#include<linux/semaphore.h>
#include<linux/ioctl.h>
#include "driver_ioctl_const.h"

int major_num=0,minor_num=0; //dynamic
dev_t char_dev;
struct cdev *char_cdev;
int count=1;
char *buffer=NULL;
int buffer_len=4000;
static struct semaphore sem;

static int char_drv_open(struct inode *inode, struct file *fp)
{
	return 0;
}

static int char_drv_release(struct inode *inode, struct file *fp)
{
	return 0;
}
static ssize_t sample_char_drv_read(struct file *fp, char __user *user_ptr, size_t count, loff_t *off)
{
	size_t len=0,ret_len=0;
	down(&sem);
	if(count > buffer_len)
		len=buffer_len;
	else
		len=count;

	ret_len=copy_to_user(user_ptr,buffer,len);
	up(&sem);
	return (len-ret_len);
}
static ssize_t sample_char_drv_write(struct file *fp, const char __user  *user_ptr, size_t count, loff_t *off)
{
	size_t len=0,ret_len=0;

	down(&sem);
	if(count > buffer_len)
		len=buffer_len;
	else
		len=count;

	ret_len=copy_from_user(buffer,user_ptr,len);
	up(&sem);
	return (len-ret_len);
	
}

static long sample_char_drv_ioctl(struct file *fp, unsigned int cmd ,unsigned long arg)
{
	int num;
	char ch = (char)arg;


	if( _IOC_TYPE(cmd) != MAGIC_NUM ) return -ENOTTY;
        if( _IOC_NR(cmd) > IOCTL_NUMS ) return -ENOTTY;

        if( _IOC_DIR(cmd) & _IOC_READ )
                if( !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd) ) )
                        return -EFAULT;
        if( _IOC_DIR(cmd) & _IOC_WRITE )
                if( !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd) ) )
                        return -EFAULT;

	num = _IOC_NR(cmd);
	switch(num){
		case 1:
			memset(buffer,0,buffer_len);
			break;
		case 2:
			copy_from_user( &ch, (char *)arg, sizeof(char) );
			memset(buffer,ch,buffer_len);
			break;
		default:
			return -ENOTTY;
	}
	return 0;
}

static struct file_operations sample_char_drv_fops = 
{
	.owner = THIS_MODULE,
	.open = char_drv_open,
	.release = char_drv_release,
	.read = sample_char_drv_read,
	.write = sample_char_drv_write,
	.unlocked_ioctl = sample_char_drv_ioctl,
};
static int char_drv_module_init(void)
{
	int ret=0;
	printk("welcome to char drv module\n");
	
	ret=alloc_chrdev_region(&char_dev,0,count,"sample char drv");
	if(ret < 0)
		goto fail0;
	char_cdev=cdev_alloc();
	if(char_cdev==NULL)
		goto fail1;
	cdev_init(char_cdev,&sample_char_drv_fops);
	ret=cdev_add(char_cdev,char_dev,count);
	if(ret < 0)
		goto fail2;

	buffer=kmalloc(GFP_KERNEL,buffer_len);
	if(buffer==NULL)
		goto fail3;

	major_num=MAJOR(char_dev);
	minor_num=MINOR(char_dev);
	sema_init(&sem,1);

	printk("char drv module loaded suceessfully..major=%d minor=%d\n",major_num,minor_num);
	return 0;

fail3:
fail2:
	cdev_del(char_cdev);
fail1:
	unregister_chrdev_region(char_dev,count);
fail0:
	return -1;
}

static void char_drv_module_exit(void)
{
	printk("exit the char drv module\n");
	cdev_del(char_cdev);
	unregister_chrdev_region(char_dev,count);
	kfree(buffer);
	buffer=NULL;
	return;
}
module_init(char_drv_module_init);
module_exit(char_drv_module_exit);
MODULE_AUTHOR("Alex");
MODULE_DESCRIPTION("char drv module with ioctl file operation");
MODULE_LICENSE("GPL");