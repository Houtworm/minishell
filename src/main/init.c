/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:28 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/25 09:37:52 by djonker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_getpid(char **envp)
{
	int			pid;
	char		*file;
	char		*line;

	if (!access("/tmp/ft_systemtempfile", R_OK | W_OK))
		ft_errorexit("I think you evaluated enough...", "init", 1);
	file = ft_system("cat /proc/self/status", envp, "/tmp/ft_systemtempfile");
	unlink("/tmp/ft_systemtempfile");
	line = ft_strnstr(file, "Pid:", 2000);
	while (*line < 0 || *line > 9)
		line++;
	pid = ft_atoi(line);
	free (file);
	return (pid);
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

char	*ft_createtempdir(char **envp, int pid)
{
	char	*dir;
	char	*apid;

	apid = ft_itoa(pid);
	dir = ft_vastrjoin(3, "/tmp/minishell", apid, "/");
	free(apid);
	ft_mkdir(dir, envp);
	return (dir);
}

t_shell	*ft_initstruct(char **envp, int debugmode)
{
	t_shell	*msh;
	char	*home;

	msh = ft_calloc(10000, 8);
	msh->os = ft_getos();
	msh->home = ft_gethome(envp);
	msh->pid = ft_getpid(envp);
	msh->tmpdir = ft_createtempdir(envp, msh->pid);
	msh->sysfile = ft_strjoin(msh->tmpdir, "ft_system");
	msh->starttime = ft_gettimemsdate(envp, msh->sysfile);
	ft_charpptofd(envp, msh);
	msh->envp = ft_fdtocharpp(msh);
	ft_shelllevelup(msh->envp);
	ft_charpptofd(msh->envp, msh);
	msh->bltn = ft_getbuiltins();
	home = ft_gethome(envp);
	msh->historyfile = ft_strjoin(home, "/.mshhistory");
	free(home);
	msh->oldline = ft_calloc(2, 8);
	msh->alias = ft_parsemshrc(envp);
	msh->code = 256;
	msh->debug = debugmode;
	ft_readhistory(msh->historyfile);
	return (msh);
}
