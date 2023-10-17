/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 21:31:26 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/17 16:36:20 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_priority(t_commands *cmd, int cmdnbr)
{
	int prio;
	int i;
	int k;

	i = 0;
	k = 0;
	prio = 0;
	while (cmd[cmdnbr].line[i + k])
	{
		while (cmd[cmdnbr].line[i + k] == '(')
		{
			k++;
			prio = 1;
		}
		while (cmd[cmdnbr].line[i + k] == ')')
		{
			k++;
			prio = 2;
		}
		while (cmd[cmdnbr].line[i + k] == '$')
		{
			while (cmd[cmdnbr].line[i + k] && cmd[cmdnbr].line[i + k] != ')')
			{
				while (cmd[cmdnbr].line[i + k] == '\"' || cmd[cmdnbr].line[i + k] == '\'')
				{
					ft_copyquote(&(cmd[cmdnbr].line), cmd[cmdnbr].line, i, i + k);
					i = ft_skipquote(cmd[cmdnbr].line, i + k) + 1;
				}
				cmd[cmdnbr].line[i] = cmd[cmdnbr].line[i + k];
				i++;
			}
		}
		while (cmd[cmdnbr].line[i + k] == '\"' || cmd[cmdnbr].line[i + k] == '\'')
		{
			ft_copyquote(&(cmd[cmdnbr].line), cmd[cmdnbr].line, i, i + k);
			i = ft_skipquote(cmd[cmdnbr].line, i + k) + 1;
		}
		cmd[cmdnbr].line[i] = cmd[cmdnbr].line[i + k];
		i++;
	}
	cmd[cmdnbr].line[i + k] = '\0';
	if (cmdnbr > 0 && prio != 2 && cmd[cmdnbr - 1].prio)
		prio = 1;
	return (prio);
}
