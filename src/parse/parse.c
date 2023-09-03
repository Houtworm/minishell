/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/03 09:05:01 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_setcmddefaults(t_shell shell, int forknumber, int cmdnumber)
{
	shell.forks[forknumber].cmds[cmdnumber].envp = shell.envp;
	shell.forks[forknumber].cmds[cmdnumber].detatch = 0;
	shell.forks[forknumber].cmds[cmdnumber].forkamount = shell.forkamount;
	shell.forks[forknumber].cmds[cmdnumber].redirect = ft_calloc(10 * sizeof(t_redirect), 1);
}

void	ft_finalparsing(t_forks forks, int cmdnumber)
{
	char	**paths;

	paths = ft_getpaths(forks.cmds[0].envp, 1);
	printf("test0\n");
	forks.cmds[cmdnumber].arguments = split_not_quote(forks.cmds[cmdnumber].pipeline, ' ');
	printf("test1\n");
	forks.cmds[cmdnumber].arguments = ft_remove_quote(forks.cmds[cmdnumber].arguments);
	printf("test2\n");
	forks.cmds[cmdnumber].cmdamount = forks.cmdamount;
	printf("test3\n");
	forks.cmds[cmdnumber].absolute = ft_abspathcmd(paths, forks.cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
}


t_shell ft_parsecmds(t_shell shell, int forknumber, int cmdnumber)
{
	ft_setcmddefaults(shell, forknumber, cmdnumber);
	ft_parsealiases(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_parsevariable(&shell.forks[forknumber].cmds[cmdnumber], shell);
	ft_parseglobs(&shell.forks[forknumber].cmds[cmdnumber]);
	ft_finalparsing(shell.forks[forknumber], cmdnumber);
	return (shell);
}

t_shell	ft_parseline(char *line, t_shell shell)
{
	int	forknumber;
	int	cmdnumber;
	line = ft_closequote(line);
	shell = ft_parsepipe(line, shell);
	ft_printshell(shell); // printing contents of shellstruct*/
	forknumber = 0;
	while (shell.forkamount > forknumber)
	{
		shell.forks[forknumber] = ft_parseendcondition(shell.forks[forknumber]);
		ft_printforks(shell.forks[forknumber], forknumber); //printing contents of forkstruct*/
		cmdnumber = 0;
		while (shell.forks[forknumber].cmdamount > cmdnumber)
		{
			shell = ft_parsecmds(shell, forknumber, cmdnumber);
			ft_printcmds(shell.forks[forknumber].cmds[cmdnumber], cmdnumber); // printing content of cmdstruct*/
			cmdnumber++;
		}
		forknumber++;
	}
	return (shell);
}
