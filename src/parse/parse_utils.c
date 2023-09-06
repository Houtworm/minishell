/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/03 12:44:05 by yitoh         ########   odam.nl         */
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

int	ft_skipquote(char *s, int i)
{
	int	k;

	k = 0;
	if (s[i] == '\"' || (s[i] == '\''))
	{
		k++;
		while (s[i + k] != s[i] && s[i + k])
			k++;
		if (!s[i + k])
			return (-1);
	}
	return (i + k);
}

int	count_str(char *s, int c)
{
	int	str_count;
	int	i;

	str_count = 0;
	i = 0;
	while (s && s[i] && s[i] == c)
		i++;
	while (s && s[i])
	{
		while (s[i] && s[i] != c)
		{
			i = ft_skipquote(s, i);
			i++;    
		}
		if (s[i] == c && s[i + 1] == '|')
			i += 2;
		while (s[i] && s[i] != c)
		{
			i = ft_skipquote(s, i);
			i++;    
		}
		str_count++;
		if (s[i] && s[i] == c)
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
		wd = ft_skipquote(s, wd);
		if (s[i + wd] == c)
		{
			if ((c == '|' && s[i + wd + 1] != c && s[i + wd - 1] != c)
				|| (c != '|' && s[i + wd - 1] != c))
				break ;	
		}
		wd++;
	}
	return (wd);
}

char	**split_not_quote(char *s, int c)
{
	int		i;
	int		start;
	char	**cmd;
	char	k;

	i = 0;
	start = 0;
	cmd = ft_calloc(count_str(s, c) + 1, sizeof(char *));
	if (!cmd)
		ft_errorexit("Error allocating memory", "malloc", 1);
	if (count_str(s, c) == 1)
	{
		k = (char)c;
		cmd[i] = ft_strtrim(s, &k);
		return (cmd);
	}
	while (i < count_str(s, c))
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
