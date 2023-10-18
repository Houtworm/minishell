/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 21:31:26 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/18 21:34:31 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_foundparenthesis(char *line, int i, int k, int *prio)
{
	while (line[i + k] == '(')
	{
		k++;
		*prio = 1;
	}
	while (line[i + k] == ')')
	{
		k++;
		*prio = 2;
	}
	return (k);
}

int	ft_founddollar(char *line, int i, int k)
{
	while (line[i + k] == '$')
	{
		while (line[i + k] && line[i + k] != ')')
		{
			while (line[i + k] == '\"' || line[i + k] == '\'')
				i = ft_cpquote(&line, line, &i, i + k);
			line[i] = line[i + k];
			i++;
		}
	}
	return (i);
}

int	ft_priority(t_commands *cmd, int cmdnbr, int i, int k)
{
	int	prio;

	prio = 0;
	while (cmd[cmdnbr].line[i + k])
	{
		k = ft_foundparenthesis(cmd[cmdnbr].line, i, k, &prio);
		i = ft_founddollar(cmd[cmdnbr].line, i, k);
		while (cmd[cmdnbr].line[i + k] == '\"'
			|| cmd[cmdnbr].line[i + k] == '\'')
			i = ft_cpquote(&(cmd[cmdnbr].line), cmd[cmdnbr].line, &i, i + k);
		cmd[cmdnbr].line[i] = cmd[cmdnbr].line[i + k];
		i++;
	}
	cmd[cmdnbr].line[i + k] = '\0';
	if (cmdnbr > 0 && prio != 2 && cmd[cmdnbr - 1].prio)
		prio = 1;
	return (prio);
}
