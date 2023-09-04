/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/05 00:42:07 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell ft_parsecmds(t_shell shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell.forks[forknumber].cmds[cmdnumber].envp = shell.envp;
	shell.forks[forknumber].cmds[cmdnumber].detatch = 0;
	shell.forks[forknumber].cmds[cmdnumber].forkamount = shell.forkamount;
	shell.forks[forknumber].cmds[cmdnumber].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
	ft_executepriority(&shell.forks[forknumber].cmds[cmdnumber]);
	ft_parsealiases(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_parsevariable(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_parseglobs(&shell.forks[forknumber].cmds[cmdnumber]);
	//ft_check_redirect(&shell.forks[forknumber].cmds[cmdnumber]);
	paths = ft_getpaths(shell.envp, 1);
	shell.forks[forknumber].cmds[cmdnumber].arguments = split_not_quote(shell.forks[forknumber].cmds[cmdnumber].pipeline, ' ');
	shell.forks[forknumber].cmds[cmdnumber].arguments = ft_remove_quote(shell.forks[forknumber].cmds[cmdnumber].arguments, 0);
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
	ft_printshell(shell); // printing contents of shellstruct
	forknumber = 0;
	while (shell.forkamount > forknumber)
	{
		shell.forks[forknumber] = ft_parseendcondition(shell.forks[forknumber]);
		ft_printforks(shell.forks[forknumber], forknumber); //printing contents of forkstruct
		forknumber++;
	}
	return (shell);
}
