#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int find_len(unsigned char c)
{
	int len;
	printf("c:%d %c\n", c, c);

//	char d = c;
//	len = 0;
//	printf("d:%d %c\n", d, d);
	while (c != 0)
	{
		++len;
		printf("%d ", c % 2);
		c /= 2;
	}
	return (len);
}
//int find_len(char c) // (c + 256)
//{
//	int len;
//	printf("c:%d %c\n", c, c);
//
//	len = 0;
//	while (c != 0)
//	{
//		++len;
//		printf("%d ", c % 2);
//		c /= 2;
//	}
//	return (len);
//}

int main(void)
{
	char c = 97;

	// 부족한 갯수만큼 0 신호를 보낸다.
	printf("len: %d\n", find_len(c));

	write(1, &c, 1);
	return (0);
}
