int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	cnt;

	if (n == 0)
		return (0);
	cnt = 0;
	while (*s1 && (*s1 == *s2) && ++cnt < n)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
#include <string.h>
#include <stdio.h>
int	main(void)
{
	printf(">>>>YOURS<<<<\n");
	printf("1. %d\n", ft_strncmp("", "", 0));
	printf("1. %d\n", ft_strncmp("a", "b", 0));
	printf("2. %d\n", ft_strncmp("", "", 1));
	printf("3. %d\n", ft_strncmp("abc", "abd", 2));
	printf("4. %d\n", ft_strncmp("abc", "abc", 3));
	printf("5. %d\n", ft_strncmp("abcde", "abcdf", 5));

	printf(">>>>TESTER<<<<\n");
	printf("1. %d\n", strncmp("", "", 0));
	printf("1. %d\n", strncmp("a", "b", 0));
	printf("2. %d\n", strncmp("", "", 1));
	printf("3. %d\n", strncmp("abc", "abd", 2));
	printf("4. %d\n", strncmp("abc", "abc", 3));
	printf("5. %d\n", strncmp("abcde", "abcdf", 5));
}
