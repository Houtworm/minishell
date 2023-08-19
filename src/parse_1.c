/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_test.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/19 15:58:10 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
// check the quote close and split command line by semicolon
/////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (*str != '\0')
	{
		a++;
		str++;
	}
	return (a);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;
	char	*t;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	p = malloc(count * size);
	if (p == NULL)
		return (0x0);
	if (p)
	{
		t = p;
		i = 0;
		while (count * size > i)
		{
			t[i] = '\0';
			i++;
		}
	}
	return (p);
}

void	*ft_frenarr(char **s, int n)
{
	while (n > 0)
	{
		n--;
		free(s[n]);
	}
	free(s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*r;
	long unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	if (len > ft_strlen((char *)s) && start < ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	r = ft_calloc(len + 1, 1);
	if (r == NULL)
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		r[i] = '\0';
		return (r);
	}
	while (len > i)
	{
		r[i] = s[i + start];
		i++;
	}
	return (r);
}

/////////////////////////////////////////////////////////////////////////////////

void	ft_putstr_fd(char *s, int fd)
{
	int	count;
	int	i;

	count = ft_strlen(s);
	i = 0;
	while (i <= count && s[i] != '\0')
	{
		write(fd, &(s[i]), 1);
		++i;
	}
}

static void	semicolon_error(char *s)
{
	ft_putstr_fd("bash: syntax error near unexpected token '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("'\n", 2);
	exit(258);
}
/////////////////////////////////////////////////////////////////////////////////

// check whether double & single quote are closed
// ignore the other type of quote mark if it's within a quote
static int	check_quote_closed(char *s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i])
	{
		while (s[i] && !check)
		{
			if (s[i] == '\'')
				check = 1;
			if (s[i] == '\"')
				check = 2;
			i++;
		}
		while (s[i] && check)
		{
			if ((s[i] == '\'' && check == 1) || (s[i] == '\"' && check == 2))
				check = 0;
			i++;
		}
	}
	return (check);
}

static int	count_str(char *s)
{
	int	str_count;
	int	i;
	int	j;

	str_count = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\"' || (s[i] == '\''))
		{
			j++;
			while (s[i + j] != s[i])
				j++;
		}
		i = i + j;
		if (s[i] == ';' && s[i + 1] == ';')
			return (semicolon_error(";;"), 0);
		if (s[i] == ';')
			str_count++;
		i++;
	}
	return (str_count + 1);
}


static int	count_wd(char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\"' || (s[i] == '\''))
		{
			j++;
			while (s[i + j] != s[i])
				j++;
		}
		i = i + j;
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static char	**split_semicolon(char *s, int c)
{
	int		i;
	int		start;
	char	**cmd;

	i = 0;
	start = 0;
	cmd = ft_calloc(count_str(s) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (s[start])
	{
		while (s[start] == c)
			start++;
		// printf("start = %d, word = %d\n", start, count_wd(s + start, c));
		cmd[i] = ft_substr(s, start, count_wd(s + start, c));
		if (!cmd[i])
			return (ft_frenarr(cmd, i));
		start += count_wd(s + start, c);
		i++;
	}
	return (cmd);
}

int	main(void)
{
	char	*s = "cat < file1 | grep a | wc -l > file2 > file3 ;; echo \"hello; world | hey\" | grep e; echo b";
	char	**arr;
	int		i = 0;

	if (s[0] == ';')
		semicolon_error(";");
	printf("%d\n", check_quote_closed(s));
	if (!check_quote_closed(s))
		printf("%d\n", count_str(s));
	arr = split_semicolon(s, ';');
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
