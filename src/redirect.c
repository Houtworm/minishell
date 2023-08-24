/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 14:58:24 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/24 15:24:50 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//ex sort < a.txt > b.txt
//problem when there is two redirection 
//ex. wc -l > file 2 > file3 then the file name will be ' file2 > file3'
//split before ft_redrc_in / _out

void	ft_check_redirect(t_exec commands, char *cmd)
{
	char	**tmp;
	int		k;
	t_redirect	*p;

	tmp = split_not_quote(cmd, ' ');
	if (!tmp)
		return ;
	k = 0;
	while (tmp[k])
	{
		if (ft_strnstr(tmp[k], "<<", 2) || ft_strchr(tmp[k], '<'))
			commands.redirect = ft_redrc_in(commands, tmp[k], tmp[k+1]);
		if (ft_strnstr(tmp[k], ">>", 2) || ft_strchr(tmp[k], '>'))
			commands.redirect = ft_redrc_out(commands, tmp[k], tmp[k+1]);
		k++;
	}
	ft_frearr(tmp);
	p = commands.redirect;
	printf("fd in = %d, fd out final = %d\n", p->fd_in, p->fd_out);
	while (commands.redirect && p->nxt)
	{
		p = p->nxt;
		printf("fd in = %d, fd out final = %d\n", p->fd_in, p->fd_out);
	}
}

t_redirect	*ft_redrc_in(t_exec commands, char *meta, char *file)
{
	t_redirect	*new;

	new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	if (ft_strnstr(meta, "<<", 2))
		new->fd_in = open("/tmp/shell_file.tmp", O_RDWR| O_CREAT | O_TRUNC, 0666);
	if (ft_strchr(meta, '<'))
		new->fd_in = open(file, O_RDONLY);
	if (new->fd_in < 0)
		return (NULL);
	ft_rdrct_add_back(&commands.redirect, new);
	return (commands.redirect);
}

t_redirect	*ft_redrc_out(t_exec commands, char *meta, char *file)
{
	t_redirect	*new;

	if (commands.redirect && !commands.redirect->fd_out)
		new = commands.redirect;
	else
		new = ft_calloc(1, sizeof(t_redirect));
	if (!new)
		return (NULL);
	if (ft_strnstr(meta, ">>", 2))
	{
		new->fd_out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		new->trc_apd = 0;
	}
	if (ft_strchr(meta, '>'))
	{
		new->fd_out = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
		new->trc_apd = 1;
	}
	if (new->fd_out < 0)
		return (NULL);
	if (new != commands.redirect)
		ft_rdrct_add_back(&commands.redirect, new);
	return (commands.redirect);
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

