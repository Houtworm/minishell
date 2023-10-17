/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   variable.c                                      |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/27 08:14:18 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/17 16:36:46 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parsevariable(t_commands *cmd, t_shell msh)
{
	int		i;
	int		j;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	while (ft_checkoutquotevar(cmd->line) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->line[i] && cmd->line[i] != '$')
		{
			if (cmd->line[i] == '\'')
			{
				begin[j] = cmd->line[i];
				i++;
				j++;
				while (cmd->line[i] && cmd->line[i] != '\'')
				{
					begin[j] = cmd->line[i];
					i++;
					j++;
				}
			}
			if (cmd->line[i] == '\"')
			{
				begin[j] = cmd->line[i];
				i++;
				j++;
				while (cmd->line[i] && cmd->line[i] != '\"')
				{
					if (cmd->line[i] == '$' && cmd->line[i + 1] != '\'' && cmd->line[i + 1] != '\"' && cmd->line[i + 1] != '(')
						break ;
					begin[j] = cmd->line[i];
					i++;
					j++;
				}
			}
			if (!cmd->line[i] || (cmd->line[i] == '$' && cmd->line[i + 1] != '\'' && cmd->line[i + 1] != '\"' && cmd->line[i + 1] != '('))
				break ;
			begin[j] = cmd->line[i];
			i++;
			j++;
			if (cmd->line[i] == '$' && cmd->line[i + 1] == '(')
			{
				while (cmd->line[i] != ')')
				{
					begin[j] = cmd->line[i];
					j++;
					i++;
				}
				begin[j] = cmd->line[i];
				i++;
				j++;
			}
		}
		if (cmd->line[i] == '$')
		{
			begin[j] = '\0';
			i++;
		}
		if (cmd->line[i] == '?')
		{
			val = ft_itoa(msh.code % 256);
			i++;
		}
		else if (cmd->line[i] == '$')
		{
			val = ft_itoa(msh.pid);
			i++;
		}
		else if (cmd->line[i] == ' ')
		{
			val = ft_strdup("$");
			i++;
		}
		else if (!cmd->line[i])
			val = ft_strdup("$");
		else
		{
			j = 0;
			while ((cmd->line[i] >= 'A' && cmd->line[i] <= 'Z') || (cmd->line[i] >= 'a' && cmd->line[i] <= 'z' ) || cmd->line[i] == '_')
			{
				var[j] = cmd->line[i];
				i++;
				j++;
			}
			var[j] = '\0';
			val = ft_getenvval(msh.envp, var);
		}
		j = 0;
		while (cmd->line[i])
		{
			rest[j] = cmd->line[i];
			i++;
			j++;
		}
		rest[j] = '\0';
		free (cmd->line);
		cmd->line = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
	return (0);
}
