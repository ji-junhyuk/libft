#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define sec 150

void	put_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while (*str && (*str >= '0' && *str <= '9'))
	{
		result *= 10;
		result += (*str - '0');
		++str;
	}
	return (result);
}

void	send_padding_bit(int pid, unsigned char c)
{
	int	len;

	len = 0;
	while (c > 0)
	{
		++len;
		c /= 2;
	}
	len = 8 - len;
	while (--len >= 0)
	{
		if (kill(pid, SIGUSR1) > 0)
			put_error();
//		usleep(sec);
		pause();
	}
}

void	send_bit(int pid, unsigned char c)
{
	if (c == 0)
		return ;
	send_bit(pid, c / 2);
	if (c % 2)
	{
		if (kill(pid, SIGUSR2) > 0)
			put_error();
	}
	else
	{
		if (kill(pid, SIGUSR1) > 0)
			put_error();
	}
//	usleep(sec);
	pause();
}

void	receive(int signum)
{
	(void)signum;
	write(1, "client received...\n", 19);
}

int main(int argc, char *argv[])
{
	int		pid;
	char	*send_message;

	struct sigaction zero_act;
	struct sigaction one_act;
	zero_act.sa_handler = receive;
	one_act.sa_handler = receive;
	if (argc != 3)
		put_error();
	pid = ft_atoi(argv[1]);
	send_message = argv[2];
	sigaction(SIGUSR1, &zero_act, 0);
	sigaction(SIGUSR2, &one_act, 0);
	while (*send_message)
	{
		send_padding_bit(pid, *send_message);
		send_bit(pid, *send_message);
		++send_message;
	}
}
