/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_2.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: yitoh <yitoh@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/19 16:18:01 by yitoh         #+#    #+#                 */
/*   Updated: 2023/08/23 12:59:19 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
cmd1: cat '< file1 | grep a' | wc -l > file2 > file3
command[1] cat < file1
command[2] grep a 
command[3] wc -l > file2 > file3
*/

void	ft_strct_per_cmd(char **cmd, t_shell *shell)
{
	t_exec	*commands;
	char	**paths;
	int		i;

	commands = ft_calloc(count_str(shell->line, '|') + 1, sizeof(t_exec));
	if (!commands)
		exit(0);	//ft_error()?;
	i = 0;
	paths = ft_getpaths(shell->envp, 1);
	while (cmd[i])
	{
		commands[i].arguments = split_not_quote(cmd[i], ' ');
		commands[i].absolute = ft_abspathcmd(paths, commands[i].arguments[0]);
		printf("%s\n", commands[i].absolute);
		i++;
	}
	shell->forks->commands = commands;
	ft_frearr(paths);
	ft_check_redirect(shell->forks->commands, i);
}

//ex sort < a.txt > b.txt

void	ft_check_redirect(t_exec *commands, int strnum)
{
	int	i;
	int	k;
	// t_redirect	*p;

	i = 0;
	while (i < strnum)
	{
		k = 0;
		while (commands[i].arguments[k])
		{
			printf("argument[%d] = %s\n", k, commands[i].arguments[k]);
			if (ft_strnstr(commands[i].arguments[k], "<<", 2) 
				|| ft_strchr(commands[i].arguments[k], '<'))
				commands[i].redirect = ft_redrc_in(commands[i], commands[i].arguments[k], commands[i].arguments[k+1]);
			if (ft_strnstr(commands[i].arguments[k], ">>", 2) 
				|| ft_strchr(commands[i].arguments[k], '>'))
				commands[i].redirect = ft_redrc_out(commands[i], commands[i].arguments[k], commands[i].arguments[k+1]);
			k++;
		}
		i++;
	}
	// p = commands[0].redirect;
	// printf("fd in = %d, fd out final = %d\n", p->fd_in, p->fd_out);
	// while (commands[0].redirect && p->nxt)
	// {
	// 	p = p->nxt;
	// 	printf("fd in = %d, fd out final = %d\n", p->fd_in, p->fd_out);
	// }
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
