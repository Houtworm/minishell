/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substitution2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/21 23:51:54 by yitoh         #+#    #+#                 */
/*   Updated: 2023/10/22 01:10:24 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_checkoutsinglequote(char *line, char target, int i)
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
	return (-1);
}

void	ft_begin_dollar(char *line, char **begin, int *i, int j)
{
	while (line[*i] && (line[*i] != '$' || line[*i + 1] != '('))
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
				if (line[*i] == '$' && line[*i + 1] == '(')
					break ;
				(*begin)[j] = line[*i];
				(*i)++;
				j++;
			}
			if (line[*i] == '$' && line[*i + 1] == '(')
				break ;
		}
		(*begin)[j] = line[*i];
		(*i)++;
		j++;
	}
	(*begin)[j] = '\0';
}

int	ft_varval_dollar(char *line, char **var, char **val, int *i)
{
	int	j;

	j = 0;
	if (line[*i] == '$' && line[*i + 1] == '(')
	{
		(*i) += 2;
		while (line[*i] && line[*i] != ')')
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

void	ft_executedollarsign(t_commands *cmd, char **envp, char *sysfile)
{
	int		i;
	char	*begin;
	char	*var;
	char	*val;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	var = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->line) + 1) * 8, 1);
	while (cmd->line && ft_checkoutsinglequote(cmd->line, '$', 0) >= 0)
	{
		i = 0;
		ft_begin_dollar(cmd->line, &begin, &i, 0);
		if (ft_varval_dollar(cmd->line, &var, &val, &i))
			val = ft_system(var, envp, sysfile);
		rest = ft_parsevar_rest(cmd->line, rest, &i, 1);
		free (cmd->line);
		cmd->line = ft_vastrjoin(3, begin, val, rest);
		free (val);
	}
	ft_vafree(3, begin, var, rest);
}
