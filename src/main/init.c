/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:28 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/29 18:53:54 by houtworm     \___)=(___/                 */
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
			return (pid);
		}
		free (line);
	}
	return (-1);
}

t_shell	*ft_initstruct(char **envp, int debugmode)
{
	t_shell	*shell;
	int		shlvlint;
	char	*shlvlstr;

	shell = ft_calloc(sizeof(shell), 10);
	shell->pid = ft_getpid();
	shell->envp = envp;
	shell->alias = ft_parsemshrc(envp);
	shlvlint = ft_atoi(ft_getenvval(shell->envp, "SHLVL"));
	shlvlint++;
	shlvlstr = ft_itoa(shlvlint);
	ft_setenv(shell->envp, "SHLVL", shlvlstr);
	shell->envpfd = open("/tmp/minishellenvpfile.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_charpptofd(envp, shell->envpfd);
	shell->starttime = ft_gettimems(shell->envp);
	shell->code = 0; // should be 0 but we use the 256 value in different places
	shell->fdout = 1;
	shell->fdin = 0;
	shell->stop = 0;
	dup2(1, shell->fdout);
	dup2(0, shell->fdin);
	shell->debug = 0;
	if (debugmode)
		shell->debug = 1;
	close(shell->envpfd);
	return (shell);
}
