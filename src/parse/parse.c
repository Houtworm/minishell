/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/14 19:51:00 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell ft_parsecmds(t_shell shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell.forks[forknumber].cmds[cmdnumber].envp = shell.envp;
	shell.forks[forknumber].cmds[cmdnumber].debug = shell.debug;
	shell.forks[forknumber].cmds[cmdnumber].forkamount = shell.forkamount;
	ft_parsealiases(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_parsevariable(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_executepriority(&shell.forks[forknumber].cmds[cmdnumber]);
	ft_parseglobs(&shell.forks[forknumber].cmds[cmdnumber]);
	ft_redirection(&shell.forks[forknumber].cmds[cmdnumber]);
	paths = ft_getpaths(shell.envp, 1);
	shell.forks[forknumber].cmds[cmdnumber].arguments = split_not_quote(shell.forks[forknumber].cmds[cmdnumber].pipeline, ' ');
	shell.forks[forknumber].cmds[cmdnumber].arguments = ft_checkarg(shell.forks[forknumber].cmds[cmdnumber].arguments, 0);
	shell.forks[forknumber].cmds[cmdnumber].cmdamount = shell.forks[forknumber].cmdamount;
	shell.forks[forknumber].cmds[cmdnumber].absolute = ft_abspathcmd(paths, shell.forks[forknumber].cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
	return (shell);
}

t_shell	ft_parseline(char *line, t_shell shell)
{
	int	forknumber;
	line = ft_closequote(line);
	line = ft_parsehashtag(line);
	shell = ft_parsepipe(line, shell);
	if (shell.debug)
		ft_printshell(shell);
	forknumber = 0;
	while (shell.forkamount > forknumber)
	{
		shell.forks[forknumber] = ft_parseendcondition(shell.forks[forknumber]);
		shell.forks[forknumber] = ft_parseheredoc(shell.forks[forknumber], shell.forks[forknumber].cmdamount);
		if (shell.debug)
			ft_printforks(shell.forks[forknumber], forknumber);
		forknumber++;
	}
	return (shell);
}
