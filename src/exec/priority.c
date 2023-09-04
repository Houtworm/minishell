/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   priority.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 22:22:12 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/05 01:18:31 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executedollarsign(t_cmds *cmd)
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
	if (ft_checkoutquote(cmd->pipeline, '$', 1) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->pipeline[i] && (cmd->pipeline[i] != '$' || cmd->pipeline[i + 1] != '('))
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
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] == '(')
		{
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (cmd->pipeline[i] && cmd->pipeline[i] != ')')
			{
				var[j] = cmd->pipeline[i];
				i++;
				j++;
			}
			var[j] = '\0';
			i++;
		}
		val = ft_system(var, cmd->envp);
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
}

void	ft_executebacktick(t_cmds *cmd)
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
	if (ft_checkoutquote(cmd->pipeline, '`', 1) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '`')
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
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		if (cmd->pipeline[i] == '`')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (cmd->pipeline[i] && cmd->pipeline[i] != '`')
			{
				var[j] = cmd->pipeline[i];
				i++;
				j++;
			}
			var[j] = '\0';
			i++;
		}
		val = ft_system(var, cmd->envp);
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
}

void	ft_executepriority(t_cmds *cmd)
{
	ft_executedollarsign(cmd);
	ft_executebacktick(cmd);

}
