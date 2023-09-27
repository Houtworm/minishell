/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:36:04 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/27 20:34:25 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_shell *ft_parsecmds(t_shell *shell, int forknumber, int cmdnumber)
{
	char	**paths;

	shell->forks[forknumber].cmds[cmdnumber].envp = shell->envp;
	shell->forks[forknumber].cmds[cmdnumber].debug = shell->debug;
	shell->forks[forknumber].cmds[cmdnumber].forkamount = shell->forkamount;
	shell->forks[forknumber].cmds[cmdnumber].prio = ft_priority(shell->forks[forknumber].cmds, cmdnumber); //0;
	ft_parsealiases(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_parsevariable(&shell->forks[forknumber].cmds[cmdnumber], *shell);
	ft_executepriority(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseredirection(&shell->forks[forknumber].cmds[cmdnumber]);
	ft_parseglobs(&shell->forks[forknumber].cmds[cmdnumber]); //should be moved to ft_parseline()
	paths = ft_getpaths(shell->envp, 1);
	shell->forks[forknumber].cmds[cmdnumber].arguments = split_not_quote(shell->forks[forknumber].cmds[cmdnumber].pipeline, ' ');
	shell->forks[forknumber].cmds[cmdnumber].arguments = ft_checkarg(shell->forks[forknumber].cmds[cmdnumber].arguments, 0);
	if (!shell->forks[forknumber].cmds[cmdnumber].arguments[0])
	{
		shell->stop = 1;
		ft_frearr(paths);
		return (shell);
	}
	shell->forks[forknumber].cmds[cmdnumber].cmdamount = shell->forks[forknumber].cmdamount;
	shell->forks[forknumber].cmds[cmdnumber].absolute = ft_abspathcmd(paths, shell->forks[forknumber].cmds[cmdnumber].arguments[0]);
	ft_frearr(paths);
	return (shell);
}
int	ft_parseline(char *line, t_shell *shell)
{
	int	forknumber;

	if (ft_startsyntax(shell, line))
		return (2);
	line = ft_closeline(line);
	line = ft_completeline(line, 0);
	while (check_quote_closed(line))
	{
		line = ft_closeline(line);
		line = ft_completeline(line, 0);
	}
	line = ft_parsehashtag(line);
	if (line[0] == '\0')
		return (1);
	if (ft_checksyntax(shell, line))
		return (2);
	*shell = ft_parsepipe(line, *shell);
	if (shell->debug)
		ft_printshell(*shell);
	forknumber = 0;
	while (shell->forkamount > forknumber)
	{
		shell->forks[forknumber] = ft_parseendcondition(shell->forks[forknumber]);
		shell->forks[forknumber] = ft_parseheredoc(shell->forks[forknumber], shell->forks[forknumber].cmdamount);
		if (shell->debug)
			ft_printforks(shell->forks[forknumber], forknumber);
		forknumber++;
	}
	return (0);
}
