/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:28 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/08 21:13:23 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_getpid(void)
{
	int		fd;
	int		pid;
	char	*line;
	int		i;

	fd = open("/proc/self/status", O_RDONLY);
	pid = 1;
	i = 0;
	while (pid > 0)
	{
		pid = get_next_line(fd, &line);
		if (!ft_strncmp(line, "Pid:", 4))
		{
			while (line[i] < 0 || line[i] > 9)
				i++;
			pid = ft_atoi(&line[i]);
			free (line);
			/*close(fd);*/
			return (pid);
		}
		free (line);
	}
	close(fd);
	return (-1);
}

void	ft_shelllevelup(char **envp)
{
	int		shlvlint;
	char	*shlvlstr;

	shlvlstr = ft_getenvval(envp, "SHLVL");
	shlvlint = ft_atoi(shlvlstr);
	free(shlvlstr);
	shlvlint++;
	shlvlstr = ft_itoa(shlvlint);
	ft_setenv(envp, "SHLVL", shlvlstr);
	free(shlvlstr);
}

t_shell	*ft_initstruct(char **envp, int debugmode)
{
	t_shell	*shell;
	char	*home;

	ft_seminit("/tmp/minishellprintsem", 1);
	shell = ft_calloc(100, 8);
	shell->starttime = ft_gettimems(envp);
	ft_charpptofd(envp, shell->envpfd);
	shell->envp = ft_fdtocharpp(shell->envpfd);
	ft_shelllevelup(shell->envp);
	ft_charpptofd(shell->envp, shell->envpfd);
	shell->builtins = ft_getbuiltins();
	home = ft_gethome(envp);
	shell->historyfile = ft_strjoin(home, "/.mshhistory");
	free(home);
	shell->oldline = ft_calloc(2, 8);
	shell->pid = ft_getpid();
	shell->alias = ft_parsemshrc(envp);
	shell->code = 256;
	shell->stop = 0;
	shell->debug = debugmode;
	/*dup2(0, shell->stdinfd);*/
	/*dup2(1, shell->stdoutfd);*/
	ft_readhistory(shell->historyfile);
	return (shell);
}
