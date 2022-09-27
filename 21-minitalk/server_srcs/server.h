#ifndef SERVER
# define SERVER
# include "signal.h"

typedef struct s_sig_tool
{
	struct sigaction	zero_act;
	struct sigaction	one_act;
	int					count;
	pid_t				pid;
} t_sig_tool;

#endif
