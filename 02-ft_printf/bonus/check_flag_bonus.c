#include "printf_bonus.h"

void	check_prec_value(t_tool *tool, t_option *option)
{
	tool->precision_value_zero = 1;
	++option->width;
}

void	check_un_sign(t_option *option, t_tool *tool, unsigned int *value)
{
	(void)*value;
	if (option->flag & FLAG_PLUS)
	{
		tool->sign = '+';
		--option->width;
	}
	else if (option->flag & FLAG_SPACE)
	{
		tool->sign = ' ';
		--option->width;
	}
}

void	check_sign(t_option *option, t_tool *tool, long *value)
{
	if (*value < 0)
	{
		tool->sign = '-';
		*value *= -1;
		--option->width;
	}
	else if (option->flag & FLAG_PLUS)
	{
		tool->sign = '+';
		--option->width;
	}
	else if (option->flag & FLAG_SPACE)
	{
		tool->sign = ' ';
		--option->width;
	}
}
