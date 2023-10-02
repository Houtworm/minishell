/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 09:00:10 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/02 23:05:20 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkoutquote(char *line, char target, int mode)
{
	int		i;
	char	*quotes;

	i = 0;
	quotes = "\'";
	if (mode == 2)
		quotes = "\'\"";
	if (line)
	{
		while (line[i])
		{
			if (line[i] == target)
				return (i);
			if (ft_strchr(quotes, line[i]))
			{
				i++;
				while (!ft_strchr(quotes, line[i]))
					i++;
			}
			i++;
		}
	}
	return (-1);
}

char	**ft_checkarg(char	**cmd, int count)
{
	char	**tmp;

	if (!ft_strncmp(cmd[0], "printf", 6))
	{
		tmp = ft_calloc(3, sizeof(char *));
		tmp[0] = ft_strdup(cmd[0]);
		tmp[1] = ft_strdup(cmd[1]);
		ft_frearr(cmd);
		cmd = tmp;
	}
	cmd = ft_remove_quote(cmd, count);
	if (ft_strchr(cmd[0], ' '))
		ft_errorexit("command not found", cmd[0], 127);
	return (cmd);
}
