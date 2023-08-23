/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   exec.c                                          |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: djonker <djonker@student.codam.nl>         //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/03/19 04:35:12 by djonker      /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/23 04:35:19 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_builtincheck(t_shell *strct)
{
	int	ret;

	ret = 1;
	if (!ft_strncmp(strct->line, "exit", 4))
		ret = ft_exit(strct);
	if (!ft_strncmp(strct->line, "cd", 2))
		ret = ft_chdir(strct);
	if (!ft_strncmp(strct->line, "unset", 5))
		ret = ft_unset(strct);
	if (!ft_strncmp(strct->line, "export", 6))
		ret = ft_export(strct);
	if (!ft_strncmp(strct->line, "env", 3))
		ret = ft_env(strct);
	if (!ft_strncmp(strct->line, "pwd", 3))
		ret = ft_pwd(strct);
	if (!ft_strncmp(strct->line, "echo", 4))
		ret = ft_echo(strct);
	return (ret);
}

int	ft_executecommands(t_shell *strct)
{
	int	pid;
	int	status;

	strct->starttime = ft_gettimems(strct->envp);
	if (ft_builtincheck(strct))
	{
		pid = fork();
		if (pid == 0)
		{
			execve(strct->absolute, strct->arguments, strct->envp);
			exit (0);
		}
		waitpid(pid, &status, 0);
		strct->code = WEXITSTATUS(status);
	}
	return (0);
}
