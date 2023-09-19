/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   redirect.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 10:16:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/19 10:38:17 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_parseredirectin(t_cmds *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*begin;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	cmd->infile = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	i = 0;
	k = 0;
	while (cmd->pipeline[i] && ft_checkoutquote(cmd->pipeline, '<', 2) >= 0)
	{
		cmd->infile[k] = ft_calloc(ft_strlen(cmd->pipeline) + 1, 8);
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '<')
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
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\'')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			else
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
			}
		}
		if (cmd->pipeline[i] == '<')
		{
			begin[j] = '\0';
			i++;
			while (cmd->pipeline[i] && cmd->pipeline[i] == ' ')
				i++;
			j = 0;
			while (cmd->pipeline[i] && cmd->pipeline[i] != ' ')
			{
				cmd->infile[k][j] = cmd->pipeline[i];
				i++;
				j++;
			}
			cmd->infile[k][j] = '\0';
			while (cmd->pipeline[i] && cmd->pipeline[i] == ' ')
				i++;
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
		cmd->pipeline = ft_strjoin(begin, rest);
		k++;
		i = 0;
	}
}

void	ft_parseredirectout(t_cmds *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*begin;
	char	*rest;

	begin = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	cmd->outfile = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	rest = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	i = 0;
	k = 0;
	while (cmd->pipeline[i] && ft_checkoutquote(cmd->pipeline, '>', 2) >= 0)
	{
		cmd->outfile[k] = ft_calloc(ft_strlen(cmd->pipeline) + 1, 8);
		j = 0;
		while (cmd->pipeline[i] && cmd->pipeline[i] != '>')
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
				while (cmd->pipeline[i] && cmd->pipeline[i] != '\'')
				{
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			else
			{
				begin[j] = cmd->pipeline[i];
				i++;
				j++;
			}
		}
		if (cmd->pipeline[i] == '>')
		{
			begin[j] = '\0';
			i++;
			if (cmd->pipeline[i] == '>')
			{
				cmd->append[k] = 1;
				i++;
			}
			else
				cmd->append[k] = 0;
			while (cmd->pipeline[i] && cmd->pipeline[i] == ' ')
				i++;
			j = 0;
			while (cmd->pipeline[i] && cmd->pipeline[i] != ' ')
			{
				cmd->outfile[k][j] = cmd->pipeline[i];
				i++;
				j++;
			}
			cmd->outfile[k][j] = '\0';
			while (cmd->pipeline[i] && cmd->pipeline[i] == ' ')
				i++;
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
		cmd->pipeline = ft_strjoin(begin, rest);
		k++;
		i = 0;
	}
}

void	ft_parseredirection(t_cmds *cmds)
{
	cmds->infile = ft_calloc(1000 * 8, 1);
	cmds->outfile = ft_calloc(1000 * 8, 1);
	cmds->append = ft_calloc(1000 * 8, 1);
	if (ft_checkoutquote(cmds->pipeline, '<', 2) >= 0)
		ft_parseredirectin(cmds);
	if (ft_checkoutquote(cmds->pipeline, '>', 2) >= 0)
		ft_parseredirectout(cmds);
}
