/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputfile.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 10:16:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/23 19:16:43 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parsestart_out(t_commands *cmd, char **start, int k, int i)
{
	int		j;

	j = 0;
	while (cmd->line[i] && cmd->line[i] != '>')
		(*start) = ft_cpwithquote(cmd->line, *start, &i, &j);
	(*start)[j] = '\0';
	if (cmd->line[i] == '>')
	{
		i++;
		cmd->app[k] = 0;
		if (cmd->line[i] == '>')
		{
			cmd->app[k] = 1;
			i++;
		}
		while (cmd->line[i] && cmd->line[i] == ' ')
			i++;
		j = 0;
		while (cmd->line[i] && cmd->line[i] != ' ' && cmd->line[i] != '>')
			cmd->ofi[k] = ft_cpnonquote(cmd->line, cmd->ofi[k], &i, &j);
		cmd->ofi[k][j] = '\0';
		while (cmd->line[i] && cmd->line[i] == ' ')
			i++;
	}
	return (i);
}

void	ft_parseredirectout(t_commands *cmd)
{
	int		i;
	int		k;
	char	*start;
	char	*rest;

	k = 0;
	while (ft_checkoutquote(cmd->line, '>', 2) >= 0)
	{
		start = ft_calloc((ft_strlen(cmd->line) + 1), 8);
		rest = ft_calloc((ft_strlen(cmd->line) + 1), 8);
		cmd->ofi[k] = ft_calloc(ft_strlen(cmd->line) + 1, 8);
		if (start == NULL || rest == NULL || cmd->ofi[k] == NULL)
			ft_errorexit("Error allocating memory", "ft_parseredirectout", 1);
		i = ft_parsestart_out(cmd, &start, k, 0);
		rest = ft_parsevar_rest(cmd->line, rest, &i, 1);
		free (cmd->line);
		cmd->line = ft_strjoin(start, rest);
		ft_vafree(2, start, rest);
		k++;
	}
}

int	ft_parseoutputfiles(t_commands *cmd)
{
	int	i;

	cmd->ofi = ft_calloc(1000 * 8, 1);
	cmd->app = ft_calloc(1000 * 8, 1);
	if (ft_checkoutquote(cmd->line, '>', 2) >= 0)
	{
		free(cmd->ofi);
		cmd->ofi = ft_calloc(100, 8);
		if (cmd->ofi == NULL)
			ft_errorexit("Error allocating memory", "ft_parseredirectout", 1);
		ft_parseredirectout(cmd);
	}
	i = 0;
	ft_createfdo(*cmd);
	while (cmd->ofi[i])
	{
		if (ft_checkoutputfile(cmd->ofi[i]))
			return (1);
		i++;
	}
	return (0);
}
