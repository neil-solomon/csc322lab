#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int copycontentmodified(char* file_from, char* file_to)
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

        char buffer[50];
	int bytes_read;
	int bytes_written;

	while (1)
	{
	        bytes_read = read(fd_from, buffer, 50);
        	if (bytes_read < 0)
        	{
                	printf("\n error reading file %s \n", file_from);
                	perror("read");
                	return -1;
        	}
		else if (bytes_read == 0)
		{
			break;
		}

		for (int i = 0; i < bytes_read; i++)
		{
			if (buffer[i] == '5')
			{
				buffer[i] = 'A';
			}
		}

		bytes_written = write(fd_to, buffer, bytes_read);
	        if (bytes_written < 0)
        	{
                	printf("\n error writing file %s \n", file_to);
                	perror("write");
                	return -1;
        	}

		bytes_written = write(fd_to, "XYZ", 3);
                if (bytes_written < 0)
                {
                        printf("\n error writing file %s \n", file_to);
                        perror("write");
                        return -1;
                }
	}
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("\n ERROR: must have source and destination file \n");
		return -1;
	}

	copycontentmodified(argv[1], argv[2]);

	return 0;
}
