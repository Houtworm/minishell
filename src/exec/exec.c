/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/15 16:35:55 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_executecommand(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	status;

	cmds.code = ft_builtincheck(cmds, cmdnbr, forknbr, shell);
	if (cmds.code == -1111)
	{
		status = ft_checkcommand(cmds);
		if (status)
			return (status);
		if ((cmds.condition == 1 && cmds.lastcode != 0) || (cmds.condition == 2 && cmds.lastcode == 0))
			return (cmds.lastcode);
		cmds.pid = fork();
		if (cmds.pid == 0)
		{
			ft_dupmachine(cmds, cmdnbr, forknbr, shell);
			execve(cmds.absolute, cmds.arguments, cmds.envp);
			exit (-1);
		}
		waitpid(cmds.pid, &status, 0);
		cmds.code = WEXITSTATUS(status);
	}
	return (cmds.code);
}

int	ft_executeforks(int forknbr, t_shell *shell)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (shell->forks[forknbr].cmdamount > cmdnbr)
	{
		*shell = ft_parsecmds(*shell, forknbr, cmdnbr);
		if (shell->debug)
			ft_printcmds(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr);
		status = ft_executecommand(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr, shell);
		// if redirection exists write output to files
		// below should be in funciton above somewhere
		// outputfd = open("/tmp/minishelloutputfile.tmp", O_RDONLY); we should use this for output
		// while line from getnextline write it to every outputfile in a while loop for every redirection
		cmdnbr++;
		shell->forks[forknbr].cmds[cmdnbr].lastcode = status;
	}
	return (status);
}
