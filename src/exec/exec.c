/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/11 07:32:04 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtincheck(t_cmds cmds)
{
	int	ret;

	ret = -1111;
	if (!ft_strncmp(cmds.arguments[0], "exit\0", 5))
		ret = ft_exit(cmds);
	if (!ft_strncmp(cmds.arguments[0], "cd\0", 3))
		ret = ft_chdir(cmds);
	if (!ft_strncmp(cmds.arguments[0], "unset\0", 6))
		ret = ft_unset(cmds);
	if (!ft_strncmp(cmds.arguments[0], "export\0", 7))
		ret = ft_export(cmds);
	if (!ft_strncmp(cmds.arguments[0], "env\0", 4))
		ret = ft_env();
	if (!ft_strncmp(cmds.arguments[0], "pwd\0", 4))
		ret = ft_pwd(cmds);
	if (!ft_strncmp(cmds.arguments[0], "echo\0", 5))
		ret = ft_echo(cmds);
	return (ret);
}

int	ft_executecommand(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	status;

	ft_dupmachine(cmds, cmdnbr, forknbr, shell);
	cmds.code = ft_builtincheck(cmds);
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
		cmdnbr++;
		shell->forks[forknbr].cmds[cmdnbr].lastcode = status;
	}
	return (status);
}
