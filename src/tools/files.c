/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   files.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/15 05:08:56 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/15 05:56:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_removemshfiles(void)
{
	unlink("/tmp/minishell");
	/*unlink("/tmp/minishelllastcode.tmp");*/
	/*unlink("/tmp/minishelltempz.tmp");*/
	/*unlink("/tmp/minishellenvpfile.tmp");*/
	/*unlink("/tmp/minishellhistory.tmp");*/
	/*unlink("/tmp/minishellprintsem");*/
	return (0);
}

int	ft_rmdir(char *dirname, char **envp)
{
	char	**cmd;
	char	*command;
	char	**paths;
	int		pid;
	int		status;

	paths = ft_getpaths(envp, 0);
	if (!paths)
		return (1);
	command = ft_abspathcmd(paths, "rm");
	cmd = ft_calloc(4, 8);
	cmd[0] = ft_strdup("rm");
	cmd[1] = ft_strdup("-rf");
	cmd[2] = ft_strdup(dirname);
	cmd[3] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(command, cmd, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	free(command);
	ft_frearr(paths);
	ft_frearr(cmd);
	return (WEXITSTATUS(status));
}

int	ft_mkdir(char *dirname, char **envp)
{
	char	**cmd;
	char	*command;
	char	**paths;
	int		pid;
	int		status;

	paths = ft_getpaths(envp, 0);
	if (!paths)
		return (1);
	command = ft_abspathcmd(paths, "mkdir");
	cmd = ft_calloc(3, 8);
	cmd[0] = ft_strdup("mkdir");
	cmd[1] = ft_strdup(dirname);
	cmd[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(command, cmd, envp);
		exit(1);
	}
	waitpid(pid, &status, 0);
	free(command);
	ft_frearr(paths);
	ft_frearr(cmd);
	return (WEXITSTATUS(status));
}
