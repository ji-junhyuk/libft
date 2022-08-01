#include "printf_bonus.h"

int	print_percent(t_option *option, t_tool *tool)
{
	(void) *option;
	if (write(1, "%", 1) == -1)
		return (-1);
	++tool->printed;
	return (0);
}
