/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 22:22:12 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/19 00:11:15 by djonker       ########   odam.nl         */
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

void	ft_executedollarsign(t_commands *cmd, char **envp, char *sysfile)
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
	while (ft_checkoutsinglequote(cmd->line, '$') >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->line[i] && (cmd->line[i] != '$' || cmd->line[i + 1] != '('))
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
			else if (cmd->line[i] == '\"')
			{
				begin[j] = cmd->line[i];
				i++;
				j++;
				while (cmd->line[i] && cmd->line[i] != '\"')
				{
					if (cmd->line[i] == '$' && cmd->line[i + 1] == '(')
						break ;
					begin[j] = cmd->line[i];
					i++;
					j++;
				}
				if (cmd->line[i] == '$' && cmd->line[i + 1] == '(')
					break ;
			}
			begin[j] = cmd->line[i];
			i++;
			j++;
		}
		if (cmd->line[i] == '$' && cmd->line[i + 1] == '(')
		{
			begin[j] = '\0';
			i++;
			i++;
			j = 0;
			while (cmd->line[i] && cmd->line[i] != ')')
			{
				var[j] = cmd->line[i];
				i++;
				j++;
			}
			var[j] = '\0';
			i++;
		}
		if (j == 0)
			val = ft_strdup("");
		else
			val = ft_system(var, envp, sysfile);
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
}

void	ft_executebacktick(t_commands *cmd, char **envp, char *sysfile)
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
	while (ft_checkoutquote(cmd->line, '`', 1) >= 0)
	{
		i = 0;
		j = 0;
		while (cmd->line[i] && cmd->line[i] != '`')
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
			else if (cmd->line[i] == '\"')
			{
				begin[j] = cmd->line[i];
				i++;
				j++;
				while (cmd->line[i] && cmd->line[i] != '\"')
				{
					if (cmd->line[i] == '`')
						break ;
					begin[j] = cmd->line[i];
					i++;
					j++;
				}
				if (cmd->line[i] == '`')
					break ;
			}
			begin[j] = cmd->line[i];
			i++;
			j++;
		}
		if (cmd->line[i] == '`')
		{
			begin[j] = '\0';
			i++;
			j = 0;
			while (cmd->line[i] && cmd->line[i] != '`')
			{
				var[j] = cmd->line[i];
				i++;
				j++;
			}
			var[j] = '\0';
			i++;
		}
		if (j == 0)
			val = ft_strdup("");
		else
			val = ft_system(var, envp, sysfile);
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
}

void	ft_executepriority(t_commands *cmd, char **envp, char *sysfile)
{
	ft_executedollarsign(cmd, envp, sysfile);
	ft_executebacktick(cmd, envp, sysfile);
}
