/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_strct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 17:38:38 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/29 19:21:05 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	symbol_check(char	*s)
{
	int	i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '&' && s[i] != '|' && s[i] != ';')
		return (i + 1);
	ft_errorexit("syntax error near unexpected token", &s[i], 258);
	return (0);
}

int	count_str2(char *s)
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
		i += j;
		if ((s[i] == '&' && s[i + 1] == '&')
			|| (s[i] == '|' && s[i + 1] == '|'))
		{
			str_count++;
			i += symbol_check(s + i + 2);

		}
		else if (s[i] == '&' || s[i] == ';')
		{
			str_count++;
			i += symbol_check(s + i + 1);
		}
		i++;
		// printf("i = %d, %c\n", i, s[i]);
	}
	return (str_count + 1);
}


int	count_wd2(char *s)
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
		if (s[i] == '&' || s[i] == '|' || s[i] == ';')
			break ;
		i++;
	}
	return (i);
}

char	**split_spchr(char *s)
{
	int		i;
	int		start;
	char	**cmd;

	i = 0;
	start = 0;
	cmd = ft_calloc(count_str2(s) + 1, sizeof(char *));
	if (!cmd)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (s[start])
	{
		// printf("start = %d, %d char\n", start, count_wd2(s + start));
		cmd[i] = ft_substr(s, start, count_wd2(s + start));
		if (!cmd[i])
			return (ft_frenarr(cmd, i));
		start += count_wd2(s + start);
		if ((s[start] == '&' && s[start + 1] == '&')
			|| (s[start] == '|' && s[start + 1] == '|'))
			start ++;
		// start++;
		i++;
	}
	return (cmd);
}
