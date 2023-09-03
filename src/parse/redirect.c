/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/09/03 11:04:50 by yitoh         ########   odam.nl         */
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
	int			k;
	t_redirect	*p;

	tmp = split_not_quote((*cmds).pipeline, ' ');
	if (!tmp)
		return ;
	k = 0;
	while (tmp[k])
	{
		if (ft_strnstr(tmp[k], "<<", 2) || ft_strchr(tmp[k], '<'))
			(*cmds).redirect = ft_redrc_in(*cmds, tmp[k], tmp[k + 1]);
		if (ft_strnstr(tmp[k], ">>", 2) || ft_strchr(tmp[k], '>'))
			(*cmds).redirect = ft_redrc_out(*cmds, tmp[k], tmp[k + 1]);
		k++;
	}
	ft_frearr(tmp);
		p = (*cmds).redirect;
		printf("1: fd in = %s, fd out= %s\n", p->infilename, p->outfilename);
		while ((*cmds).redirect && p->nxt)
		{
			p = p->nxt;
			printf("fd in = %s, fd out final = %s\n", p->infilename, p->outfilename);
		}
}

t_redirect	*ft_redrc_in(t_cmds cmds, char *meta, char *file)
{
	t_redirect	*new;

	new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	if (ft_strnstr(meta, "<<", 2))
		new->delimiter = file;
	if (ft_strchr(meta, '<'))
		new->infilename = file;
	ft_rdrct_add_back(&cmds.redirect, new);
	return (cmds.redirect);
}

t_redirect	*ft_redrc_out(t_cmds cmds, char *meta, char *file)
{
	t_redirect	*new;

	if (cmds.redirect && !cmds.redirect->outfilename)
		new = cmds.redirect;
	else
		new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	new->outfilename = file;
	if (ft_strnstr(meta, ">>", 2))
		new->append = 0;
	if (ft_strchr(meta, '>'))
		new->append = 1;
	if (new != cmds.redirect)
		ft_rdrct_add_back(&cmds.redirect, new);
	return (cmds.redirect);
}

void	ft_rdrct_add_back(t_redirect **lst, t_redirect *new)
{
	t_redirect	*l;

	l = *lst;
	if (lst && new)
	{
		if (*lst)
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

