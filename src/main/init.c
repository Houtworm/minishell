/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:28 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/16 12:14:59 by houtworm     \___)=(___/                 */
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
			close(fd);
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
	t_shell	*msh;
	char	*home;

	msh = ft_calloc(10000, 8);
	msh->starttime = ft_gettimems(envp);
	ft_rmdir("/tmp/minishell", envp);
	ft_mkdir("/tmp/minishell", envp);
	ft_seminit("/tmp/minishell/printsem", 1);
	msh->os = ft_getos();
	ft_charpptofd(envp, msh->envpfd);
	msh->envp = ft_fdtocharpp(msh->envpfd);
	ft_shelllevelup(msh->envp);
	ft_charpptofd(msh->envp, msh->envpfd);
	msh->bltn = ft_getbuiltins();
	home = ft_gethome(envp);
	msh->historyfile = ft_strjoin(home, "/.mshhistory");
	free(home);
	msh->oldline = ft_calloc(2, 8);
	msh->alias = ft_parsemshrc(envp);
	msh->pid = ft_getpid();
	msh->code = 256;
	msh->stop = 0;
	msh->debug = debugmode;
	ft_readhistory(msh->historyfile);
	return (msh);
}
