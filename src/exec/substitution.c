/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   substitution.c                                  |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/04 22:22:12 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 10:49:02 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkoutsinglequote(char *line, char target)
{
	int		i;

	i = 0;
	if (line)
	{
		while (line[i])
		{
			if (line[i] == target && line[i + 1] == '(')
				return (i);
			if (line[i] == '\"')
			{
				i++;
				while (line[i] != '\"')
				{
					if (line[i] == '$' && line[i + 1] == '(')
						return (i);
					i++;
				}
			}
			if (line[i] == '\'')
			{
				i++;
				while (line[i] != '\'')
					i++;
			}
			i++;
		}
	}
	return (-1);
}

void	ft_executedollarsign(t_commands *cmd, char **envp)
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
	while (ft_checkoutsinglequote(cmd->pipeline, '$') >= 0)
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
			else if (cmd->pipeline[i] == '\"')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\"')
				{
					if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] == '(')
						break ;
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
				if (cmd->pipeline[i] == '$' && cmd->pipeline[i + 1] == '(')
					break ;
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
		if (j == 0)
			val = ft_strdup("");
		else
			val = ft_system(var, envp);
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

void	ft_executebacktick(t_commands *cmd, char **envp)
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
	while (ft_checkoutquote(cmd->pipeline, '`', 1) >= 0)
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
			else if (cmd->pipeline[i] == '\"')
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\"')
				{
					if (cmd->pipeline[i] == '`')
						break ;
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
				if (cmd->pipeline[i] == '`')
					break ;
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
		if (j == 0)
			val = ft_strdup("");
		else
			val = ft_system(var, envp);
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

void	ft_executepriority(t_commands *cmd, char **envp)
{
	ft_executedollarsign(cmd, envp);
	ft_executebacktick(cmd, envp);
}
