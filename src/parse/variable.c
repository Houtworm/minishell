/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/14 06:54:55 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parsevariable(t_cmds *cmd, t_shell shell)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	while (ft_checkoutquotevar(cmd->pipeline) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '$')
		{
			if (cmd->pipeline[i] == '\'')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\'')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			if (cmd->pipeline[i] == '\"')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\"')
				{
					if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] != '\'' && cmd->pipeline[i + 1] != '\"' && cmd->pipeline[i + 1] != '(')
						break ;
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			if (!cmd->pipeline[i] || (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] != '\'' && cmd->pipeline[i + 1] != '\"' && cmd->pipeline[i + 1] != '('))
				break ;
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
			if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] == '(')
			{
				while (cmd->pipeline[i] != ')')
				{
					begin[j] = cmd->pipeline[i];
					j++;
					i++;
				}
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
			}
		}
		if (cmd->pipeline[i] == '$')
		{
			begin[j] = '\0';
			i++;
		}
		if (cmd->pipeline[i] == '?')
		{
			val = ft_itoa(shell.code % 256);
			i++;
		}
		else if (cmd->pipeline[i] == '$')
		{
			val = ft_itoa(shell.pid);
			i++;
		}
		else if (cmd->pipeline[i] == ' ')
		{
			val = ft_strdup("$");
			i++;
		}
		else if (!cmd->pipeline[i])
			val = ft_strdup("$");
		else
		{
			j = 0;
			while ((cmd->pipeline[i] >= 'A' && cmd->pipeline[i] <= 'Z') || (cmd->pipeline[i] >= 'a' && cmd->pipeline[i] <= 'z' ) || cmd->pipeline[i] == '_')
			{
				var[j] = cmd->pipeline[i];
				i++;
				j++;
			}
			var[j] = '\0';
			val = ft_getenvval(shell.envp, var);
		}
		j = 0;
		while (cmd->pipeline[i])
		{
			rest[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		rest[j] = '\0';
		free (cmd->pipeline);
		cmd->pipeline = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (0);
}
