#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ft_atoi(char *str)
{
	int	result;
	int	sign;
	int	error;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += (*str - '0');
		if (sign > 0 && result == 214748364 && (*(str + 1) >= '8' && *(str + 1) <= '9'))
			return (0);
		if (sign < 0 && result == 214748364 && (*(str + 1) == '9'))
			return (0);
		if (result > 214748364 && (*(str + 1) != '\0'))
			return (0);
		++str;
	}
	if (*str != '\0')
		return (0);
	return (sign * result);
}

int check_real_zero(char *str)
{
	if (*str == '-' || *str == '+')
		++str;
	if (*str == '0')
		return (1);
	return (0);
}

// 일부 인자가 정수가 아니거나, 정수 범위를 초과하거나, 중복이 있는 경우
// 2147483647 -2147483648
int main(int argc, char *argv[])
{
	int	i;
	int element;

	i = 0;
	while (++i < argc)
	{
		element = ft_atoi(argv[i]);
		if (element == 0 && !check_real_zero(argv[i]))
		{
			printf("error\n");
			break ;
		}
		else
			printf("%d\n", element);
	}
	return 0;
}
