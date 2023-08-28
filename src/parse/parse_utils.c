/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/28 21:29:26 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
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

int	check_quote(char *s, int i)
{
	int	j;

	j = 0;
	if (s[i] == '\"' || (s[i] == '\''))
	{
		j++;
		while (s[i + j] != s[i])
			j++;
	}
	return (i + j);
}

int	count_str(char *s, int c)
{
	int	str_count;
	int	i;

	str_count = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		i = check_quote(s, i);
		while (s[i] && s[i] != c)
			i++;
		str_count++;
		if (s[i] == c && s[i + 1] == '|')
			i++;
		else if (s[i] && s[i] == c)
			i++;
	}
	return (str_count);
}

int	count_wd(char *s, int c)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (s[i] == c)
		i++;
	while (s[i + wd])
	{
		wd = check_quote(s, wd);
		if (s[i + wd] == c && s[i + wd + 1] != c && s[i + wd - 1] != c)
			break ;
		wd++;
	}
	return (wd);
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
		ft_errorexit("Error allocating memory", "malloc", 1);
	//this condition is messing up and leaving c in the beginning and the end of str
	if (count_str(s, c) == 1)
	{
		cmd[i] = ft_strdup(s);
		return (cmd);
	}
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
