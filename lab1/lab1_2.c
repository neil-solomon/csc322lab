#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int copycontent(char* file_from, char* file_to)
{
	int fd_from;
	fd_from = open(file_from, O_RDONLY);
        if (fd_from < 0)
        {
                printf("\n error opening file %s \n", file_from);
                perror("open");
                return -1;
        }

	int fd_to;
        fd_to = open(file_to, O_WRONLY | O_CREAT, 0700);
        if (fd_to < 0)
        {
                printf("\n error opening file %s \n", file_to);
                perror("open");
                return -1;
        }

	int file_size = lseek(fd_from, 0, SEEK_END);
        lseek(fd_from, 0, SEEK_SET);
        char buffer[file_size];

	int bytes_read = read(fd_from, buffer, file_size);
        if (bytes_read < 0)
        {
                printf("\n error reading file %s \n", file_from);
                perror("read");
                return -1;
        }

	int bytes_written = write(fd_to, buffer, file_size);
        if (bytes_written < 0)
        {
                printf("\n error writing file %s \n", file_to);
                perror("write");
                return -1;
        }

        close(fd_from);
	close(fd_to);

        return 0;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("\n ERROR: must have source and destination file \n");
		return -1;
	}

	copycontent(argv[1], argv[2]);

	return 0;
}
