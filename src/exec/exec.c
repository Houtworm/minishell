/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:12 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 04:16:42 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtincheck(t_cmds cmds)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(cmds.arguments[0], "exit", 4))
		ret = ft_exit(cmds);
	/*if (!ft_strncmp(cmds.arguments[0], "cd", 2))*/
		/*ret = ft_chdir(cmds);*/
	/*if (!ft_strncmp(cmds.arguments[0], "unset", 5))*/
		/*ret = ft_unset(cmds);*/
	/*if (!ft_strncmp(cmds.arguments[0], "export", 6))*/
		/*ret = ft_export(cmds);*/
	/*if (!ft_strncmp(cmds.arguments[0], "env", 3))*/
		/*ret = ft_env(cmds);*/
	/*if (!ft_strncmp(cmds.arguments[0], "pwd", 3))*/
		/*ret = ft_pwd(cmds);*/
	/*if (!ft_strncmp(cmds.arguments[0], "echo", 4))*/
		/*ret = ft_echo(cmds);*/
	return (ret);
}

int	ft_executecommand(t_cmds cmds)
{
	int	status;

	ft_dupmachine(cmds);
	cmds.pid = fork();
	if (cmds.pid == 0)
	{
		if (ft_builtincheck(cmds))
			execve(cmds.absolute, cmds.arguments, cmds.envp);
		exit (0);
	}
	waitpid(cmds.pid, &status, 0);
	cmds.code = WEXITSTATUS(status);
	return (status);
}

int	ft_executeforks(t_forks forks)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (forks.cmdamount > cmdnbr)
	{
		status = ft_executecommand(forks.cmds[cmdnbr]);
		cmdnbr++;
	}
	return (status);
}

int	ft_forktheforks(t_shell *shell)
{
	int	status;
	int forknumber;

	forknumber = 0;
	status = 1;
	shell->starttime = ft_gettimems(shell->envp);
	while (shell->forkamount > forknumber)
	{
		shell->forks[forknumber].pid = fork();
		if (shell->forks[forknumber].pid == 0)
		{
			status = ft_executeforks(shell->forks[forknumber]);
			exit(0);
		}
		forknumber++;
	}
	return (status);
}
