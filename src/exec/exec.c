/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/09/15 16:35:55 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_executecommand(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	status;

	cmds.code = ft_builtincheck(cmds, cmdnbr, forknbr, shell);
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
			ft_dupmachine(cmds, cmdnbr, forknbr, shell);
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
		if (shell->forks[forknbr].cmds[cmdnbr].outfile[0])
			ft_executeredirect(shell->forks[forknbr].cmds[cmdnbr].outfile, shell->forks[forknbr].cmds[cmdnbr].append, forknbr);
		// if redirection exists write output to files
		// below should be in funciton above somewhere
		// outputfd = open("/tmp/minishelloutputfile.tmp", O_RDONLY); we should use this for output
		// while line from getnextline write it to every outputfile in a while loop for every redirection
		cmdnbr++;
		shell->forks[forknbr].cmds[cmdnbr].lastcode = status;
	}
	return (status);
}



void	ft_executeredirect(char **outfile, int *append, int forknbr)
{
	int		fdread;
	int		fdo;
	int		i;
	char	*line;
	char	*outtmp;

	outtmp = ft_vastrjoin(3, "/tmp/minishelloutputfile", ft_itoa(forknbr), ".tmp");
//	printf("exec:outtmp = %s\n", outtmp);
	fdread = open(outtmp, O_RDONLY);
	i = 0;
	while (outfile[i])
	{
		if (append[i])
			fdo = open(outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			fdo = open(outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
		get_next_line(fdread, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
		while (line)
		{
			ft_putendl_fd(line, fdo);
			free(line);
			get_next_line(fdread, &line);
			if (!line)
				ft_errorexit("Error allocating memory", "malloc", 1);
			//ft_putendl_fd("loop", 2);
		}
		free(line);
		close (fdo);
		i++;
	}
	// printf("end of exec redirect\n");
	free(outtmp);
	close(fdread);
}