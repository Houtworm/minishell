/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   redirect.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/19 10:16:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/04 12:20:03 by djonker      \___)=(___/                 */
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
	char	quote;

	free(cmd->infile);
	cmd->infile = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
	i = 0;
	k = 0;
	while (cmd->pipeline[i] && ft_checkoutquote(cmd->pipeline, '<', 2) >= 0)
	{
		begin = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
		rest = ft_calloc((ft_strlen(cmd->pipeline) + 1) * 8, 1);
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
			while (cmd->pipeline[i] && cmd->pipeline[i] != ' ' && cmd->pipeline[i] != '<')
			{
				if (cmd->pipeline[i] == '\'' || cmd->pipeline[i] == '\"')
				{
					quote = cmd->pipeline[i];
					i++;
					while (cmd->pipeline[i] != quote)
					{
						cmd->infile[k][j] = cmd->pipeline[i];
						i++;
						j++;
					}
					i++;
				}
				else
				{
					cmd->infile[k][j] = cmd->pipeline[i];
					i++;
					j++;
				}
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
		free(begin);
		free(rest);
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
	char	quote;

	free(cmd->outfile);
	cmd->outfile = ft_calloc(100, 8);
	k = 0;
	i = 0;
	while (ft_checkoutquote(cmd->pipeline, '>', 2) >= 0)
	{
		begin = ft_calloc((ft_strlen(cmd->pipeline) + 1), 8);
		rest = ft_calloc((ft_strlen(cmd->pipeline) + 1), 8);
		i = 0;
		/*printf("%s\n", cmd->pipeline);*/
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
					/*printf("looping in \' \n");*/
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
					/*printf("looping in \" \n");*/
					begin[j] = cmd->pipeline[i];
					i++;
					j++;
				}
			}
			/*printf("looping in nothing \n");*/
			begin[j] = cmd->pipeline[i];
			i++;
			j++;
		}
		if (cmd->pipeline[i] == '>')
		{
			begin[j] = '\0';
			/*printf("begin: %s\n", begin);*/
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
			while (cmd->pipeline[i] && cmd->pipeline[i] != ' ' && cmd->pipeline[i] != '>')
			{
				if (cmd->pipeline[i] == '\'' || cmd->pipeline[i] == '\"')
				{
					quote = cmd->pipeline[i];
					i++;
					while (cmd->pipeline[i] != quote)
					{
						cmd->outfile[k][j] = cmd->pipeline[i];
						i++;
						j++;
					}
					i++;
				}
				else
				{
					cmd->outfile[k][j] = cmd->pipeline[i];
					i++;
					j++;
				}
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
		/*printf("rest: %s\n", rest);*/
		free (cmd->pipeline);
		cmd->pipeline = ft_strjoin(begin, rest);
		free(begin);
		free(rest);
		k++;
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
