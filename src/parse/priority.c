/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   priority.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/26 21:31:26 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/16 10:53:12 by houtworm     \___)=(___/                 */
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
	while (cmd[cmdnbr].pipeline[i + k])
	{
		while (cmd[cmdnbr].pipeline[i + k] == '(')
		{
			k++;
			prio = 1;
		}
		while (cmd[cmdnbr].pipeline[i + k] == ')')
		{
			k++;
			prio = 2;
		}
		while (cmd[cmdnbr].pipeline[i + k] == '$')
		{
			while (cmd[cmdnbr].pipeline[i + k] && cmd[cmdnbr].pipeline[i + k] != ')')
			{
				while (cmd[cmdnbr].pipeline[i + k] == '\"' || cmd[cmdnbr].pipeline[i + k] == '\'')
				{
					ft_copyquote(&(cmd[cmdnbr].pipeline), cmd[cmdnbr].pipeline, i, i + k);
					i = ft_skipquote(cmd[cmdnbr].pipeline, i + k) + 1;
				}
				cmd[cmdnbr].pipeline[i] = cmd[cmdnbr].pipeline[i + k];
				i++;
			}
		}
		while (cmd[cmdnbr].pipeline[i + k] == '\"' || cmd[cmdnbr].pipeline[i + k] == '\'')
		{
			ft_copyquote(&(cmd[cmdnbr].pipeline), cmd[cmdnbr].pipeline, i, i + k);
			i = ft_skipquote(cmd[cmdnbr].pipeline, i + k) + 1;
		}
		cmd[cmdnbr].pipeline[i] = cmd[cmdnbr].pipeline[i + k];
		i++;
	}
	cmd[cmdnbr].pipeline[i + k] = '\0';
	if (cmdnbr > 0 && prio != 2 && cmd[cmdnbr - 1].prio)
		prio = 1;
	return (prio);
}
