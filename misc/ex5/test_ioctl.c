#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include"ioctl_const.h"

int main()
{
	int fd, i;
	char my_buf[4000];
	unsigned int size;
	char c;
	
	printf("[%d] - Opening device sample_cdrv\n", getpid());
	fd = open("/dev/sample_cdrv", O_RDWR);
	if( fd < 0 ) {
		printf("\n\nDevice could not be opened\n\n");
		return 1;
	}
	printf("Device opened with ID [%d]\n", fd);
	
	ioctl(fd, SAMPLE_GET_SIZE, &size );
	printf("Present size of the buffer is %d\n", size);
		
	/* lets fill the buffer with character '=' */
	c = '=';
	ioctl(fd, SAMPLE_FILL_CHAR, &c);

      	/* test if it worked */
	read(fd, my_buf, 70 );
	printf("New contents of buffer: %s\n", my_buf);
	
	close(fd);
	exit(0);
}


