#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <signal.h>
#include <errno.h>
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
	copy = malloc(sizeof(char) * (size + 1));
	if (!copy)
		return (0);
	copy[0] = '\0';
	ft_strcat(copy, s1);
	ft_strcat(copy + s1_size, s2);
	return (copy);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	int	idx;
	char **PATH;

	char *pwd;
	idx = -1;
	while (envp[++idx])
	{
		if (ft_strncmp(envp[idx], "PATH", 4) == 0)
		{
			char *all_path;

			all_path = ft_strjoin(envp[idx], pwd);
			printf("all_path:%s\n", all_path);
			int jdx = -1;
			while (++jdx < 5)
				;
			PATH = ft_split(&all_path[jdx], ':');
		}
		if (ft_strncmp(envp[idx], "PWD", 3) == 0)
		{
			int jdx = -1;
			while (++jdx < 4)
				;
			pwd = &envp[idx][jdx];
			pwd = ft_strjoin(":", pwd);
			printf("pwd:%s\n", pwd);
		}
	}
	for (int idx = 0; PATH[idx]; ++idx)
		printf("%s\n", PATH[idx]);
}
