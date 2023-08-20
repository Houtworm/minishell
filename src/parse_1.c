/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_1.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/20 18:29:29 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// check the quote close and split command line by pipe

// check whether double & single quote are closed
// ignore the other type of quote mark if it's within a quote
// return 0 when the quote is properly closed
int	check_quote_closed(char *s)
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

int	count_str(char *s, int c)
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
		if (s[i] == c)
			str_count++;
		i++;
	}
	return (str_count + 1);
}


int	count_wd(char *s, int c)
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

char	**split_not_quote(char *s, int c)
{
	int		i;
	int		start;
	char	**cmd;

	i = 0;
	start = 0;
	cmd = ft_calloc(count_str(s, c) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (s[start])
	{
		while (s[start] == c)
			start++;
		cmd[i] = ft_substr(s, start, count_wd(s + start, c));
		if (!cmd[i])
			return (ft_frenarr(cmd, i));
		start += count_wd(s + start, c);
		i++;
	}
	return (cmd);
}
