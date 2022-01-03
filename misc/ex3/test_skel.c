
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

int main()
{
	int fd, i;
	ssize_t ret;
	char my_buf[20]="Hello world";
	
	fd = open( "/dev/sample_cdrv", O_RDWR );
	if(fd<0) {
		printf("failed acquiring file descriptor return status %d\n",fd);
		return 0;
        }
	
	/* write the contents of my buffer into the device */
	ret = write( fd, my_buf, 12 );
	if(ret<0)
		printf("write operation failed with return status %d\n",ret);

	memset(my_buf,'\0',20);

	/* read the contents of my buffer into the device */
	ret = read( fd, my_buf, 12 );
	if(ret<0)
		printf("read operation failed with return status %d\n",ret);
	printf("read data=%s\n",my_buf);

	close(fd);
}
	
