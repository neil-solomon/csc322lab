#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	errno = 0;
	int fd;
	fd = open("destination.txt", O_CREAT|O_RDONLY);
	if (fd < 0){
		printf("\n open() failed \n");
		perror("open");
		return -1;
	} else {
		printf("\n open() success \n");
	}
	close(fd);
	return 0;
}
