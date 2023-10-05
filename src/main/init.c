/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:28 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/05 18:01:34 by houtworm     \___)=(___/                 */
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

	shell = ft_calloc(sizeof(shell), 100);
	home = ft_gethome(envp);
	shell->historyfile = ft_strjoin(home, "/.mshhistory");
	free(home);
	shell->oldline = ft_calloc(2, 8);
	shell->pid = ft_getpid();
	shell->alias = ft_parsemshrc(envp);
	ft_charpptofd(envp, shell->envpfd);
	shell->envp = ft_fdtocharpp(shell->envpfd);
	ft_shelllevelup(shell->envp);
	ft_charpptofd(shell->envp, shell->envpfd);
	shell->builtins = ft_getbuiltins();
	shell->starttime = ft_gettimems(shell->envp);
	shell->code = 256;
	shell->stop = 0;
	shell->debug = debugmode;
	ft_readhistory(shell->historyfile);
	return (shell);
}
