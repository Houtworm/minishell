/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputfile.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 10:16:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/17 18:05:59 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parseredirectout(t_commands *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*begin;
	char	*rest;
	char	quote;

	free(cmd->outfile);
	cmd->outfile = ft_calloc(100, 8);
	if (cmd->outfile == NULL)
		ft_errorexit("Error allocating memory", "ft_parseredirectout", 1);
	k = 0;
	i = 0;
	while (ft_checkoutquote(cmd->line, '>', 2) >= 0)
	{
		begin = ft_calloc((ft_strlen(cmd->line) + 1), 8);
		rest = ft_calloc((ft_strlen(cmd->line) + 1), 8);
		if (begin == NULL || rest == NULL)
			ft_errorexit("Error allocating memory", "ft_parseredirectout", 1);
		i = 0;
		cmd->outfile[k] = ft_calloc(ft_strlen(cmd->line) + 1, 8);
		if (cmd->outfile[k] == NULL)
			ft_errorexit("Error allocating memory", "ft_parseredirectout", 1);
		j = 0;
		while (cmd->line[i] && cmd->line[i] != '>')
		{
			if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
			{
				quote = cmd->line[i];
				begin[j] = cmd->line[i];
				i++;
				j++;
				while (cmd->line[i] && cmd->line[i] != quote)
				{
					begin[j] = cmd->line[i];
					i++;
					j++;
				}
			}
			begin[j] = cmd->line[i];
			i++;
			j++;
		}
		if (cmd->line[i] == '>')
		{
			begin[j] = '\0';
			i++;
			if (cmd->line[i] == '>')
			{
				cmd->append[k] = 1;
				i++;
			}
			else
				cmd->append[k] = 0;
			while (cmd->line[i] && cmd->line[i] == ' ')
				i++;
			j = 0;
			while (cmd->line[i] && cmd->line[i] != ' ' && cmd->line[i] != '>')
			{
				if (cmd->line[i] == '\'' || cmd->line[i] == '\"')
				{
					quote = cmd->line[i];
					i++;
					while (cmd->line[i] != quote)
					{
						cmd->outfile[k][j] = cmd->line[i];
						i++;
						j++;
					}
					i++;
				}
				else
				{
					cmd->outfile[k][j] = cmd->line[i];
					i++;
					j++;
				}
			}
			cmd->outfile[k][j] = '\0';
			while (cmd->line[i] && cmd->line[i] == ' ')
				i++;
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
		cmd->line = ft_strjoin(begin, rest);
		free(begin);
		free(rest);
		k++;
	}
}

int	ft_parseoutputfiles(t_commands *cmd)
{
	int	i;

	cmd->outfile = ft_calloc(1000 * 8, 1);
	cmd->append = ft_calloc(1000 * 8, 1);
	if (ft_checkoutquote(cmd->line, '>', 2) >= 0)
		ft_parseredirectout(cmd);
	i = 0;
	while (cmd->outfile[i + 1])
	{
		if (ft_checkoutputfile(cmd->outfile[i]))
			return (1);
		i++;
	}
	ft_createfdo(*cmd);
	return (0);
}
