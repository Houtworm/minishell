/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/04 22:22:12 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/22 01:30:37 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_begin_backtick(char *line, char **begin, int *i, int j)
{
	while (line[*i] && line[*i] != '`')
	{
		if (line[*i] == '\'')
			(*begin) = ft_quoteinvariable(line, *begin, i, &j);
		else if (line[*i] == '\"')
		{
			(*begin)[j] = line[*i];
			(*i)++;
			j++;
			while (line[*i] && line[*i] != '\"')
			{
				if (line[*i] == '`')
					break ;
				(*begin)[j] = line[*i];
				(*i)++;
				j++;
			}
			if (line[*i] == '`')
				break ;
		}
		(*begin)[j] = line[*i];
		(*i)++;
		j++;
	}
	(*begin)[j] = '\0';
}

int	ft_varval_backtick(char *line, char **var, char **val, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '`')
	{
		(*i)++;
		while (line[*i] && line[*i] != '`')
		{
			(*var)[j] = line[*i];
			(*i)++;
			j++;
		}
		(*var)[j] = '\0';
		(*i)++;
	}
	if (j == 0)
		*val = ft_strdup("");
	return (j);
}

void	ft_executebacktick(t_commands *cmd, char **envp, char *sysfile)
{
	int		i;
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
		ft_begin_backtick(cmd->line, &begin, &i, 0);
		if (ft_varval_backtick(cmd->line, &var, &val, &i))
			val = ft_system(var, envp, sysfile);
		rest = ft_parsevar_rest(cmd->line, rest, &i, 1);
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
