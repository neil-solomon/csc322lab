#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int printcontent (char* filepath)
{
        int fd;

        fd = open(filepath, O_RDONLY);
        if (fd < 0)
        {
                printf("\n error opening file \n");
		perror("open");
                return -1;
        }

        int fileSize = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

        char c;
	for (int i = 0; i < fileSize; i++)
	{
		read(fd, &c, 1);
		write(1, &c, 1); // fd=1 write to stdout
	}

	close(fd);

        return 0;
}

int main(int argc, char* argv[])
{
        if (argc < 2)
        {
                printf("\n ERROR: no filename \n");
		return -1;
	}

	printcontent(argv[1]);

	return 0;
}
