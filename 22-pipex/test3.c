#include <fcntl.h>

int main(void)
{
	int fd;
	fd = open("junfile", O_CREAT | O_RDONLY, 00666);
}
