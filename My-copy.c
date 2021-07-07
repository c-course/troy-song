#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>

#define SIZE 5
#define BUF_SIZE 10

int My_copy(char *dist, char *src)
{
	int fdd, fds;
	int size;
	char *buf = (char *)malloc(BUF_SIZE * sizeof(char));
	memset(buf, 0, BUF_SIZE * sizeof(char));
	// char buf[10] = {0};
	fdd = open(src, O_RDONLY);
	if (fdd < 0)
		return fdd;
	fds = open(dist, O_RDWR | O_CREAT | O_APPEND, 0622);
	if (fds < 0)
		return fds;
	while (read(fdd, buf, SIZE)) {
		write(fds, buf, SIZE);
		memset(buf, 0, BUF_SIZE * sizeof(char));
	}

	// free(buf);
	close(fdd);
	close(fds);

	return 0;
}
