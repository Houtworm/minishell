/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/12 20:45:23 by yitoh         ########   odam.nl         */
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


void	ft_check_redirect(t_cmds *cmds)
{
	char		**tmp;
	char		**newline;
	
	if (ft_strchr((*cmds).pipeline, '<'))
		(*cmds).redirect = ft_redrc_in((*cmds).redirect, (*cmds).pipeline);
	if (ft_strchr((*cmds).pipeline, '>'))
		(*cmds).redirect = ft_redrc_out((*cmds).redirect, (*cmds).pipeline);
	tmp = split_not_quote((*cmds).pipeline, '>');
	newline = split_not_quote(tmp[0], '<');
	free((*cmds).pipeline);
	(*cmds).pipeline = ft_strdup(newline[0]);
	ft_frearr(tmp);
	ft_frearr(newline);
}

t_redirect *ft_redrc_in(t_redirect *redirect, char *line)
{
	t_redirect	*new;
	char		**file;
	char		**tmp;
	int			i;

	new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	// filename should be search from the beginning (see notion)
	i = ft_strlen(line) - 1;
	tmp = NULL;
	file = NULL;
	while ((int)i > -1)
	{
		if (line[i] == '<')
		{
			i++;
			tmp = split_not_quote(line + i, ' ');
			file = split_not_quote(tmp[0], '>');
			break ;
		}
		i--;
	}
	// if (line[i - 2] == '<')
	// 	// new->hdfd = ft_heredoc(file[0]);
	// else
	// 	new->infilename = ft_strdup(file[0]);
	ft_frearr(tmp);
	ft_frearr(file);
	ft_rdrct_add_back(&redirect, new);
	return (redirect);
}

t_redirect *ft_redrc_out(t_redirect *redirect, char *line)
{
	t_redirect	*new;
	char		**tmp;
	char		**file;
	int			i;

	if (redirect && !redirect->outfilename)
		new = redirect;
	else
		new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	i = (int)ft_strlen(line) - 1;
	tmp = NULL;
	file = NULL;
	while ((int)i > -1)
	{
		if (line[i] == '>')
		{
			i++;
			tmp = split_not_quote(line + i, ' ');
			file = split_not_quote(tmp[0], '<');
			break ;
		}
		i--;
	}
	new->outfilename = ft_strdup(file[0]);
	if (line[i - 2] == '>')
		new->append = 1;
	else
		new->append = 0;
	ft_frearr(tmp);
	ft_frearr(file);
	if (new != redirect)
		ft_rdrct_add_back(&redirect, new);
	return (redirect);
}

void	ft_rdrct_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*l;

	l = *lst;
	if (lst && new)
	{
		if ((*lst)->infilename || (*lst)->outfilename || (*lst)->hdfd)
		{
			while (l)
			{
				if (!l->nxt)
					break ;
				l = l->nxt;
			}
			l->nxt = new;
		}
		else
			*lst = new;
	}
}
