/* 
Shows how to use mmap sys call
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <assert.h>

int main(){
	int fd,i;
	unsigned char *filedata=NULL,*temp="welcome to hello world\n";
	unsigned int size=100;

	fd = open("/dev/veda_cdrv",0666);
	if(fd<0){
		printf("file open failed\n");
		return 0;
	}
	filedata = (char *) mmap((void*)0,size,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);	
	perror("\n MMAP STATUS: ");
	if(filedata == NULL){
		perror("Maping Failed");
		close(fd);
		exit(1);
	}
	write(fd,temp,strlen(temp));
	//write(1,(char *)filedata,strlen((char *)filedata));
	
 
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	//temp = filedata;
	write(1,filedata,strlen(temp));
	//for(i=0;i<100;i++,filedata++)
	//	putchar(*filedata);
	i = munmap(filedata,size);
	assert(i == 0);
	if( i != 0)
		printf(" failed to unmap\n");
	close(fd);
}
