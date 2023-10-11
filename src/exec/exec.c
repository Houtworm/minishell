/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/11 06:14:18 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_executeredirect(char **outfile, int *append, int forknbr) // bash behavior
{
	int		fdread;
	int		fdo;
	int		i;
	char	*line;
	char	*outtmp;
	int		ret;

	line = ft_itoa(forknbr);
	outtmp = ft_vastrjoin(3, "/tmp/minishelloutputfile", line, ".tmp");
	free(line);
	i = 0;
	while (outfile[i])
	{
		if (append[i])
			fdo = open(outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			fdo = open(outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
		close (fdo);
		i++;
	}
	i--;
	fdread = open(outtmp, O_RDONLY);
	if (append[i])
		fdo = open(outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fdo = open(outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fdread, &line);
		/*printf("line: %s\n\n", line);*/
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
		if (ret == 0)
			ft_putstr_fd(line, fdo);
		else
			ft_putendl_fd(line, fdo);
		free(line);
	}
	close (fdo);
	close(fdread);
	free(outtmp);
}

/*void	ft_executeredirect(char **outfile, int *append, int forknbr)*/ // zsh behaviour
/*{*/
	/*int		fdread;*/
	/*int		fdo;*/
	/*int		i;*/
	/*char	*line;*/
	/*char	*outtmp;*/
	/*int		ret;*/

	/*outtmp = ft_vastrjoin(3, "/tmp/minishelloutputfile", ft_itoa(forknbr), ".tmp");*/
	/*i = 0;*/
	/*while (outfile[i])*/
	/*{*/
		/*fdread = open(outtmp, O_RDONLY);*/
		/*if (append[i])*/
			/*fdo = open(outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);*/
		/*else*/
			/*fdo = open(outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);*/
		/*ret = 1;*/
		/*while (ret)*/
		/*{*/
			/*ret = get_next_line(fdread, &line);*/
			/*if (!line)*/
				/*ft_errorexit("Error allocating memory", "malloc", 1);*/
			/*if (ret == 0)*/
				/*ft_putstr_fd(line, fdo);*/
			/*else*/
				/*ft_putendl_fd(line, fdo);*/
			/*free(line);*/
		/*}*/
		/*close (fdo);*/
		/*close(fdread);*/
		/*i++;*/
	/*}*/
	/*free(outtmp);*/
/*}*/

void	ft_printlastcode(t_cmds	cmds)
{
	ft_putstr_fd(cmds.pipeline, 2);
	ft_putendl_fd("------------", 2);
	ft_putstr_fd("last code is ", 2);
	ft_putnbr_fd(cmds.lastcode, 2);
	ft_putstr_fd("  condition is ", 2);
	ft_putnbr_fd(cmds.condition, 2);
	// ft_putstr_fd("  prio is ", 2);
	// ft_putnbr_fd(cmds.prio, 2);
	ft_putendl_fd("", 2);
}

void	ft_createfdo(t_cmds cmd)
{
	int	fdo;
	int	i;

	i = 0;
	while (cmd.outfile[i])
	{
		if (cmd.append[i])
			fdo = open(cmd.outfile[i], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			fdo = open(cmd.outfile[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
		close (fdo);
		i++;
	}
}

void	ft_checklastcode(t_forks fork)
{
	int	fd;
	int	icmd;

	icmd = 0;
	while (icmd < fork.cmdamount)
	{
		if (icmd + 1 != fork.cmdamount && ((fork.cmds[icmd].condition == 1 && fork.cmds[icmd].lastcode != 0)
			|| (fork.cmds[icmd].condition == 2 && fork.cmds[icmd].lastcode == 0)))
		{
			fd = open("/tmp/minishelllastcode.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
			close(fd);
			break ;
		}
		icmd++;
	}
}

int	ft_executecommand(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	int	status;

	if (cmds.prio && !shell->forks[forknbr].cmds[cmdnbr - 1].prio)
	{
		if ((cmds.condition == 1 && cmds.lastcode != 0) || (cmds.condition == 2 && cmds.lastcode == 0))
		{
			if (cmds.prio != 2)
				shell->forks[forknbr].cmds[cmdnbr].prio = 3;
			shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.lastcode;
			return (cmds.lastcode);
		}
	}
	if (cmds.prio && shell->forks[forknbr].cmds[cmdnbr - 1].prio == 3)
	{
		if (cmds.prio != 2)
			shell->forks[forknbr].cmds[cmdnbr].prio = 3;
		shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.lastcode;
		return (cmds.lastcode);
	}
	if ((cmds.condition == 1 && cmds.lastcode != 0) || (cmds.condition == 2 && cmds.lastcode == 0))
	{
		shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.lastcode;
		return (cmds.lastcode);
	}
	cmds.code = ft_builtincheck(cmds, cmdnbr, forknbr, shell);
	if (cmds.code == -1111)
	{
		status = ft_checkcommand(cmds, shell->envp);
		if (status)
		{
			shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = status;
			return (status);
		}
		cmds.pid = fork();
		if (cmds.pid == 0)
		{
			signal(SIGQUIT, ft_sighandler);
			if (ft_dupmachine(cmds, cmdnbr, forknbr, shell) == 2)
				return (1);
			execve(cmds.absolute, cmds.arguments, shell->envp);
			ft_errorexit("command not found", cmds.absolute, 127);
		}
		// if (shell->forkamount > 1)
		// {
		// 	close(shell->pipes[forknbr][1]);
		// 	close(shell->pipes[forknbr][0]);
			// if (forknbr > 0)
			// {
				// close(shell->pipes[forknbr - 1][1]);
				// close(shell->pipes[forknbr - 1][0]);
			// }
			// close(shell->pipes[forknbr + 1][1]);
			// close(shell->pipes[forknbr + 1][0]);
		// }
		waitpid(cmds.pid, &status, 0);
		cmds.code = WEXITSTATUS(status);
	}
	shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.code;
	return (cmds.code);
}

int	ft_executeforks(int forknbr, t_shell *shell, int condition)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (shell->forks[forknbr].cmdamount > cmdnbr)
	{
		ft_frearr(shell->envp);
		shell->envp = ft_fdtocharpp(shell->envpfd);
		shell = ft_parsecmds(shell, forknbr, cmdnbr);
		if (shell->stop == 1)
		{
			ft_createfdo(shell->forks[forknbr].cmds[cmdnbr]);
			return (0);
		}
		if (shell->stop == 2)
		{
			return (1);
		}
		if (shell->debug)
			ft_printcmds(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr);
		status = ft_executecommand(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr, shell);
		// ft_putendl_fd("test2----", 2);
		if (shell->forks[forknbr].cmds[cmdnbr].outfile[0] && status != 127)
			ft_executeredirect(shell->forks[forknbr].cmds[cmdnbr].outfile, shell->forks[forknbr].cmds[cmdnbr].append, forknbr);
		cmdnbr++;
	}
	// ft_putnbr_fd(condition, 2);
	// ft_putendl_fd("  condition", 2);
	if (condition)
		ft_checklastcode(shell->forks[forknbr]);
	return (status);
}
