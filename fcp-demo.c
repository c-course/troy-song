#include <stdio.h>
#include <unistd.h>

void My_copy(char *dist, char *src);

int main(int argc, char **argv)
{
	My_copy("../dist.txt", "../src.txt");
	return 0;
}
