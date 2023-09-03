/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/03 14:36:26 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//ex sort < a.txt > b.txt
//problem when there is two redirection 
//ex. wc -l > file 2 > file3 then the file name will be ' file2 > file3'
//split before ft_redrc_in / _out



void	ft_check_redirect(t_cmds *cmds)
{
	char		**tmp;
	char		*newline;
	int			k;
	// t_redirect	*p;

	k = 0;
	if (ft_strnstr((*cmds).pipeline, "<<", 2))
	{
		(*cmds).redirect = ft_redrc_in((*cmds).redirect, "<<", (*cmds).pipeline);
		tmp = split_not_quote((*cmds).pipeline, '<');
		while (tmp[k])
		{
			newline = ft_strjoin(newline, tmp[k]);
		}
	}
	else if (ft_strchr((*cmds).pipeline, '<'))
	{
		(*cmds).redirect = ft_redrc_in((*cmds).redirect, "<", (*cmds).pipeline);
	}
	if (ft_strnstr((*cmds).pipeline, ">>", 2))
	{
		(*cmds).redirect = ft_redrc_out((*cmds).redirect, ">>", (*cmds).pipeline);
	}
	else if (ft_strchr((*cmds).pipeline, '>'))
	{
		(*cmds).redirect = ft_redrc_out((*cmds).redirect, ">", (*cmds).pipeline);
	}
}


t_redirect *ft_redrc_in(t_redirect *redirect, char *meta, char *line)
{
	t_redirect	*new;
	char		*file;

	new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	if (!ft_strncmp(meta, "<<", 2))
	{
		line = NULL;
		new->delimiter = ft_strdup(file);
	}
	if (!ft_strncmp(meta, "<", 1))
		new->infilename = ft_strdup(file);
	ft_rdrct_add_back(&redirect, new);
	return (redirect);
}

t_redirect *ft_redrc_out(t_redirect *redirect, char *meta, char *line)
{
	t_redirect	*new;

	if (redirect && !redirect->outfilename)
		new = redirect;
	else
		new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->outfilename = ft_strdup(line);
	if (ft_strnstr(meta, ">>", 2))
		new->append = 0;
	if (ft_strchr(meta, '>'))
		new->append = 1;
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
		if ((*lst)->infilename || (*lst)->outfilename || (*lst)->delimiter)
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

	// tmp = split_not_quote((*cmds).pipeline, ' ');
	// if (!tmp)
	// 	return ;
	// k = 0;
	// newline = NULL;
	// while (tmp[k])
	// {
	// 	if (ft_strnstr(tmp[k], "<<", 2) || ft_strchr(tmp[k], '<'))
	// 		(*cmds).redirect = ft_redrc_in((*cmds).redirect, tmp[k], tmp[k + 1]);
	// 	if (ft_strnstr(tmp[k], ">>", 2) || ft_strchr(tmp[k], '>'))
	// 		(*cmds).redirect = ft_redrc_out((*cmds).redirect, tmp[k], tmp[k + 1]);
	// 	while (tmp[k])
		

	// 	k++;
		
	// }

	// ft_frearr(tmp);

		// p = (*cmds).redirect;
		// printf("1: fd in = %s, fd out= %s\n", p->infilename, p->outfilename);
		// while ((*cmds).redirect && p->nxt)
		// {
		// 	p = p->nxt;
		// 	printf("fd in = %s, fd out final = %s\n", p->infilename, p->outfilename);
		// }
// }
