#include "../bonus_includes/checker.h"
#include "../bonus_includes/get_next_line.h"
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;

	fd = 0;
	while (1)
	{
		line = get_next_line(fd);
		printf("line:%ld\n", ft_strlen(line));
		write(1, line, ft_strlen(line));
		if (!line)
			break ;
	}
	return (0);
}
