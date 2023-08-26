/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:12 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/26 05:59:41 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_builtincheck(t_cmds cmds)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(cmds.arguments[0], "exit", 4))
		ret = ft_exit(cmds);
	if (!ft_strncmp(cmds.arguments[0], "cd", 2))
		ret = ft_chdir(cmds);
	if (!ft_strncmp(cmds.arguments[0], "unset", 5))
		ret = ft_unset(cmds);
	if (!ft_strncmp(cmds.arguments[0], "export", 6))
		ret = ft_export(cmds);
	if (!ft_strncmp(cmds.arguments[0], "env", 3))
		ret = ft_env(cmds);
	if (!ft_strncmp(cmds.arguments[0], "pwd", 3))
		ret = ft_pwd(cmds);
	if (!ft_strncmp(cmds.arguments[0], "echo", 4))
		ret = ft_echo(cmds);
	return (ret);
}

int	ft_executecommand(t_cmds cmds)
{
	int	status;

	status = ft_checkcommand(cmds);
	if (status)
		return (status);
	if ((cmds.condition == 1 && cmds.lastcode != 0) || (cmds.condition == 2 && cmds.lastcode == 0))
		return (-1);
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
	return (cmds.code);
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
		forks.cmds[cmdnbr].lastcode = status;
	}
	return (status);
}

