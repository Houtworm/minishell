/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/14 20:46:27 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//ex sort < a.txt > b.txt
//problem when there is two redirection 
//ex. wc -l > file 2 > file3 then the file name will be ' file2 > file3'
//split before ft_redrc_in / _out

//wc-l>file1>file2
//cat < r1 < r2 > r3 will copy the content from r2 to r3 while skipping r1 (r1 is empty)
//ls > r2 > r3 will copy the result of ls to file3, while skipping r2
//cat < r3 << EOF > r1 will copy the content of heredoc to r1 while skipping r3


void	ft_redirection(t_cmds *cmds)
{
	char		**tmp;
	char		**newline;

	cmds->infile = ft_calloc(1000 * 8, 1);
	cmds->outfile = ft_calloc(1000 * 8, 1);
	if (ft_checkoutquote((*cmds).pipeline, '<', 2) < 0 
		&& ft_checkoutquote((*cmds).pipeline, '>', 2) < 0)
		return ;
	if (ft_check_redirect((*cmds).pipeline) != 0)
		exit(0);
	 // need to do sth for <> cmd case ^
	if (ft_checkoutquote((*cmds).pipeline, '<', 2) >= 0)
		(*cmds).infile = ft_redrc_in((*cmds).infile, (*cmds).pipeline);
	if (ft_checkoutquote((*cmds).pipeline, '>', 2) >= 0)
		(*cmds).outfile = ft_redrc_out((*cmds).outfile, &((*cmds).append), (*cmds).pipeline);
	tmp = split_not_quote((*cmds).pipeline, '>');
	newline = split_not_quote(tmp[0], '<');
	free((*cmds).pipeline);
	(*cmds).pipeline = ft_strdup(newline[0]);
	ft_frearr(tmp);
	ft_frearr(newline);
}

int	ft_check_redirect(char	*line)
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
			if (check == '>' && line[i] == '<')
				ft_errorexit("syntax error near expected token", "<", 258);
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
				if (line[i] == '>' || line[i] == '<')
					ft_errorexit("syntax error near expected token", &(line[i + 1]), 258);
				// if (line[i] == '\'' || line[i] == "\"" )
				// {
					
				// }
			}

			//if (check == '<' && line[i] == '>')
				// -> parse file name but we don't use it
				// return (1);
		}
		i++;
	}
	return (0);
}

char	**ft_redrc_in(char	**infile, char *pipeline)
{
	char		**lines;
	char		**file;
	char		**tmp;
	int			i;

	i = 1;
	tmp = NULL;
	lines = split_not_quote(pipeline, '<');
	while (lines[i])
		i++;
	infile = ft_calloc(i, sizeof(char *));
	i = 1;
	while (lines[i])
	{
		tmp = split_not_quote(lines[i], ' ');
		file = split_not_quote(tmp[0], '>');
		infile[i - 1] = ft_strdup(file[0]);
		ft_frearr(tmp);
		ft_frearr(file);
		i++;
	}
	infile[i] = ft_calloc(8, 1);
	infile[i] = NULL;
	ft_frearr(lines);
	return (infile);
}

char	**ft_redrc_out(char **outfile, int	**append, char *pipeline)
{
	char		**lines;
	char		**file;
	char		**tmp;
	int			i;
	int			k;
	char		quote;

	i = 1;
	tmp = NULL;
	lines = split_not_quote(pipeline, '>');
	while (lines[i] && lines[i][0])
		i++;
	outfile = ft_calloc(i - 1, sizeof(char *));
	(*append) = ft_calloc(i - 1, sizeof(int));
	i = 1;
	quote = '\0';
	while (lines[i] && lines[i][0])
	{
		tmp = split_not_quote(lines[i], ' ');
		file = split_not_quote(tmp[0], '>');
		outfile[0] = ft_strdup(file[0]);
		outfile[1] = ft_calloc(8, 1);
		ft_frearr(tmp);
		ft_frearr(file);
		i++;
	}
	ft_frearr(lines);
	i = 0;
	k = 0;
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
		}
		i++;
	}
	return (outfile);
}
