/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirectYukaBackup.c                            |o_o || |                */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/19 10:43:24 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_redrc_in(char	**infile, char *pipeline)
{
	char		**lines;
	char		**file;
	char		**tmp;
	int			i;

	i = 1;
	// tmp = NULL;
	lines = split_not_quote(pipeline, '<');
	while (lines[i])
		i++;
	infile = ft_calloc(i, sizeof(char *));
	i = 1;
	while (lines[i])
	{
		tmp = split_not_quote(lines[i], ' ');
		file = split_not_quote(tmp[0], '>');
		file = ft_remove_quote(file, 0);
		infile[i - 1] = ft_strdup(file[0]);
		// ft_frearr(tmp);
		ft_frearr(file);
		i++;
	}
	infile[i] = ft_calloc(8, 1);
	infile[i] = NULL;
	ft_frearr(lines);
	return (infile);
}

void	ft_append(int **append, int count, char *pipeline)
{
	char		quote;
	int	i;
	int	k;

	i = 0;
	k = 0;
	quote = '\0';
	(*append) = ft_calloc(count, sizeof(int));
	while (pipeline[i])
	{
		if (pipeline[i] == '\'' || pipeline[i] == '\"')
		{
			quote = pipeline[i];
			while (pipeline[i] != quote)
				i++;
			i++;
		}
		if (pipeline[i] && pipeline[i] == '>')
		{
			if (pipeline[i + 1] == '>')
			{
				(*append)[k] = 1;
				i++;
			}
			else
				(*append)[k] = 0;
			k++;
		}
		i++;
	}
}

char	**ft_redrc_out(char **outfile, int	**append, char *pipeline)
{
	char		**lines;
	char		**file;
	char		**tmp;
	int			i;

	i = 1;
	// tmp = NULL;
	lines = split_not_quote(pipeline, '>');
	while (lines[i] && lines[i][0])
		i++;
	outfile = ft_calloc(i - 1, sizeof(char *));
	ft_append(append, i - 1, pipeline);
	i = 1;
	while (lines[i] && lines[i][0])
	{
		tmp = split_not_quote(lines[i], ' ');
		file = split_not_quote(tmp[0], '<');
		file = ft_remove_quote(file, 0);
		outfile[i - 1] = ft_strdup(file[0]);
		// ft_frearr(tmp);
		ft_frearr(file);
		i++;
	}
	outfile[i - 1] = NULL;
	ft_frearr(lines);
	return (outfile);
}

void	ft_check_redirect(char	*line)
{
	char	check;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			check = line[i];
			i++;

			if ((line[i] == '<' || line[i] == '>') && (line[i + 1] == '<' || line[i + 1] == '>'))
				ft_errorexit("syntax error near expected token", &(line[i + 1]), 258);
			if ((check == '>' && line[i] == '<') || (check == '<' && line[i] == '>'))
				ft_errorexit("syntax error near expected token", "<", 258);
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
				if (line[i] == '>' || line[i] == '<')
					ft_errorexit("syntax error near expected token", &(line[i + 1]), 258);
			}
		}
		i++;
	}
}

char	*ft_parserdrct(char *pipeline)
{
	int		i;
	char	check;
	char	*line;

	i = 0;
	while (pipeline[i] && (pipeline[i] != '<') && (pipeline[i] != '>'))
	{
		if ((pipeline[i] == '\'') && (pipeline[i] == '\"'))
		{
			check = pipeline[i];
			i++;
			while (pipeline[i] && pipeline[i] != check)
				i++;
			i++;
		}
		if (pipeline[i] == ' ')
			i++;
		else
			i++;

	}
	line = ft_substr(pipeline, 0, i);
	free(pipeline);
	return (line);
}

void	ft_redirection(t_cmds *cmds)
{
	cmds->infile = ft_calloc(1000 * 8, 1);
	cmds->outfile = ft_calloc(1000 * 8, 1);
	if (ft_checkoutquote((*cmds).pipeline, '<', 2) < 0 
		&& ft_checkoutquote((*cmds).pipeline, '>', 2) < 0)
		return ;
	ft_check_redirect((*cmds).pipeline);
	if (ft_checkoutquote((*cmds).pipeline, '<', 2) >= 0)
		(*cmds).infile = ft_redrc_in((*cmds).infile, (*cmds).pipeline);
	if (ft_checkoutquote((*cmds).pipeline, '>', 2) >= 0)
		(*cmds).outfile = ft_redrc_out((*cmds).outfile, &((*cmds).append), (*cmds).pipeline);
	(*cmds).pipeline = ft_parserdrct((*cmds).pipeline);
}
