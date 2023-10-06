/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                   |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 18:48:20 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/30 02:26:39 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		while (s[i] && s[i] == c)
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
