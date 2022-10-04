#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

typedef struct s_cmd_node
{
	char				**cmd;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node	*tail;
	t_cmd_node	*head;
	int		cnt;
}	t_cmd_list;

typedef struct s_path_node
{
	char				*path;
	struct s_path_node	*next;
}	t_path_node;

typedef struct s_path_list
{
	t_path_node	*tail;
	t_path_node	*head;
	int		cnt;
}	t_path_list;

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		++len;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cnt;

	if (n == 0)
		return (0);
	cnt = 0;
	while (*s1 && (*s1 == *s2) && ++cnt < n)
	{
		++s1;
		++s2;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static int	count_word(const char *str, char c)
{
	int	cnt;

	cnt = 0;
	while (*str)
	{
		while (*str && *str == c)
			++str;
		if (*str && *str != c)
		{
			++cnt;
			while (*str && *str != c)
				++str;
		}
	}
	return (cnt);
}

static char	*ft_strlen_dup(const char **str, char c)
{
	int		word_len;
	int		cnt;
	char	*copy;

	word_len = 0;
	while (*(*str) && *(*str) != c)
	{
		++word_len;
		++*str;
	}
	*str -= word_len;
	copy = malloc(sizeof(char) * (word_len + 1));
	if (!copy)
		return (0);
	cnt = 0;
	while (*(*str) && ++cnt <= word_len)
		*copy++ = *(*str)++;
	*copy = '\0';
	copy -= word_len;
	return (copy);
}

static char	**free_copy(char **str, int size)
{
	int	index;

	index = -1;
	while (++index < size)
		free(str[index]);
	free(str);
	return (0);
}

char	**ft_split(char const *str, char c)
{
	char	**copy;
	int		words;
	int		index;

	if (!str)
		return (0);
	words = count_word(str, c);
	copy = malloc(sizeof(char *) * (words + 1));
	if (!copy)
		return (0);
	index = -1;
	while (++index < words)
	{
		while (*str && *str == c)
			++str;
		copy[index] = ft_strlen_dup(&str, c);
		if (!copy[index])
			return (free_copy(copy, index));
	}
	copy[index] = 0;
	return (copy);
}

static void	ft_strcat(char *dest, const char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*copy;
	size_t	s1_size;
	size_t	s2_size;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	size = s1_size + s2_size;
	copy = malloc(sizeof(char) * (size + 2));
	if (!copy)
		return (0);
	copy[0] = 0;
	ft_strcat(copy, s1);
	ft_strcat(copy + s1_size, "/");
	ft_strcat(copy + s1_size + 1, s2);
	return (copy);
}

static void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}

char	*ft_strdup(const char *src)
{
	size_t	src_len;
	char	*copy;

	src_len = ft_strlen(src);
	copy = malloc(sizeof(char) * (src_len + 1));
	if (!copy)
		return (0);
	ft_strcpy(copy, src);
	return (copy);
}

void	insert_path_list(t_path_list *list, char *path)
{
	t_path_node *node;
	node = malloc(sizeof(t_path_node));
	if (!node)
		return ;
	node->path = ft_strdup(path);
	++list->cnt;
	if (list->tail == NULL)
	{	
		list->tail = node;
		list->head = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

void	insert_cmd_list(t_cmd_list *list, char *cmd)
{
	t_cmd_node *node;
	node = malloc(sizeof(t_path_node));
	if (!node)
		return ;
	node->cmd = ft_split(cmd, ' ');
	++list->cnt;
	if (list->tail == NULL)
	{
		list->tail = node;
		list->head = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
}

void	init_path_list(t_path_list *list)
{
	list->cnt = 0;
	list->tail = NULL;
	list->head = NULL;
}

void	init_cmd_list(t_cmd_list *list)
{
	list->cnt = 0;
	list->tail = NULL;
	list->head = NULL;
}

void	free_arr(char **arr)
{
	int	idx;

	idx = -1;
	while (arr[++idx])
	{
		arr[idx] = 0;
		free(arr[idx]);
	}
	arr = 0;
	free(arr);
}

void	iterate_path_list(t_path_list *list)
{
	t_path_node	*cur;
	int			cnt;

	cnt = list->cnt;
	cur = list->head;
	while (--cnt >= 0)
		cur = cur->next;
}

void	iterate_cmd_list(t_cmd_list *list)
{
	t_cmd_node	*cur;
	int			cnt;
	if (list->cnt <= 0)
		return ;

	cnt = list->cnt;
	cur = list->head;
	while (--cnt >= 0)
		cur = cur->next;
}

int	check_valid_cmd(t_path_list *path_list, t_cmd_list *cmd_list, int cnt)
{
	t_path_node *p_node;
	t_cmd_node *c_node;
	char	*all_path;
	int		p_count;

	p_count = path_list->cnt;
	p_node = path_list->head;
	c_node = cmd_list->head;
	while (--cnt >= 0)
		c_node = c_node->next;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, c_node->cmd[0]);
		if (access(all_path, F_OK) == 0)
			return (0);
		free(all_path);
		p_node = p_node->next;
	}
	return (1);
}

char	*get_cmd(t_path_list *path_list, t_cmd_list *cmd_list, int cnt)
{
	t_path_node *p_node;
	t_cmd_node *c_node;
	char	*all_path;
	int		p_count;

	p_count = path_list->cnt;
	p_node = path_list->head;
	c_node = cmd_list->head;
	while (--cnt >= 0)
		c_node = c_node->next;
	while (--p_count >= 0)
	{
		all_path = ft_strjoin(p_node->path, c_node->cmd[0]);
		if (access(all_path, F_OK) == 0)
			return (all_path);
		free(all_path);
		p_node = p_node->next;
	}
	return (0);
}

void	parse_path(char *envp[], t_path_list *path_list)
{
	int		idx;
	char	**path;

	idx = -1;
	init_path_list(path_list);
	while (envp[++idx])
	{
		if (ft_strncmp(envp[idx], "PATH", 4) == 0)
		{
			path = ft_split(&envp[idx][5], ':');
			int jdx = -1;
			while (path[++jdx])
				insert_path_list(path_list, path[jdx]);
			free_arr(path);
		}
		if (ft_strncmp(envp[idx], "PWD", 3) == 0)
		{
			path = ft_split(&envp[idx][4], ':');
			int jdx = -1;
			while (path[++jdx])
				insert_path_list(path_list, path[jdx]);
			free_arr(path);
		}
	}
}

void	parse_cmd(int argc, char *argv[], t_path_list *path_list, t_cmd_list *cmd_list)
{
	int	i;

	i = 1;
	init_cmd_list(cmd_list);
	while (++i < argc - 1)
	{
		if (check_valid_cmd(path_list, cmd_list, i - 2) == 1)
			exit(1);
		insert_cmd_list(cmd_list, argv[i]);
	}
}

typedef struct s_pipe
{
	int			argc;
	char		**argv;
	int			i;
	int			fdin;
	int			fdout;
	int			fdpipe[2];
	int			idx;
	pid_t		pid;
	char		*cmd;
	t_cmd_node	*c_node;
}	t_pipe;

void	init_pipe_tool(t_pipe *pipe_tool, int argc, char *argv[])
{
	pipe_tool->argc = argc;
	pipe_tool->argv = argv;
	pipe_tool->i	= 1;
	pipe_tool->fdin = open(argv[1], O_CREAT | O_RDONLY, 00666);
}

void	communicate_pipe(t_pipe *pipe_tool, t_path_list *path_list, t_cmd_list *cmd_list)
{
	pipe_tool->c_node = cmd_list->head;
	pipe_tool->idx = pipe_tool->i - 2;
	while (--(pipe_tool->idx) >= 0)
		pipe_tool->c_node = pipe_tool->c_node->next;
	pipe_tool->cmd = get_cmd(path_list, cmd_list, pipe_tool->i - 2);
	execve(pipe_tool->cmd, pipe_tool->c_node->cmd, 0);
}

void	pipex(t_pipe *pipe_tool, t_path_list *path_list, t_cmd_list *cmd_list)
{
	while (++pipe_tool->i < (pipe_tool->argc - 1))
	{
		dup2(pipe_tool->fdin, 0);
		close(pipe_tool->fdin);
		if (pipe_tool->i == (pipe_tool->argc - 2))
			pipe_tool->fdout = open(pipe_tool->argv[pipe_tool->argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 00666);
		else
		{
			pipe(pipe_tool->fdpipe);
			pipe_tool->fdin = pipe_tool->fdpipe[0];
			pipe_tool->fdout = pipe_tool->fdpipe[1];
		}
		dup2(pipe_tool->fdout, 1);
		close(pipe_tool->fdout);
		pipe_tool->pid = fork();
		if (pipe_tool->pid == -1)
			exit(1);
		if (pipe_tool->pid == 0)
			communicate_pipe(pipe_tool, path_list, cmd_list);
	}
	waitpid(pipe_tool->pid, NULL, 0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_path_list	path_list;
	t_cmd_list	cmd_list;
	t_pipe		pipe_tool;

	parse_path(envp, &path_list);
	parse_cmd(argc, argv, &path_list, &cmd_list);
	iterate_path_list(&path_list);
	iterate_cmd_list(&cmd_list);
//	init_pipe_tool(&pipe_tool, argc, argv);
//	pipex(&pipe_tool, &path_list, &cmd_list);
	return (0);
}
