/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/16 10:36:59 by houtworm     \___)=(___/                 */
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
	outtmp = ft_vastrjoin(3, "/tmp/minishell/outputfile", line, ".tmp");
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
		if (!line)
			ft_errorexit("Error allocating memory", "ft_executeredirect", 1);
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

/*void	ft_executeredirect(char **outfile, int *append, int forknbr)*/ // zsh behaviour which I think is better
/*{*/
	/*int		fdread;*/
	/*int		fdo;*/
	/*int		i;*/
	/*char	*line;*/
	/*char	*outtmp;*/
	/*int		ret;*/

	/*outtmp = ft_vastrjoin(3, "/tmp/minishell/outputfile", ft_itoa(forknbr), ".tmp");*/
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

void	ft_printlastcode(t_commands	cmd)
{
	ft_putstr_fd(cmd.pipeline, 2);
	ft_putendl_fd("------------", 2);
	ft_putstr_fd("last code is ", 2);
	ft_putnbr_fd(cmd.lastcode, 2);
	ft_putstr_fd("  condition is ", 2);
	ft_putnbr_fd(cmd.condition, 2);
	// ft_putstr_fd("  prio is ", 2);
	// ft_putnbr_fd(cmd.prio, 2);
	ft_putendl_fd("", 2);
}

void	ft_createfdo(t_commands cmd)
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
		if (((fork.cmd[icmd].condition == 1 && fork.cmd[icmd].lastcode != 0) || (fork.cmd[icmd].condition == 2 && fork.cmd[icmd].lastcode == 0)))
		{
			unlink("/tmp/minishell/lastcode.tmp");
			fd = open("/tmp/minishell/lastcode.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
			close(fd);
			break ;
		}
		icmd++;
	}
}


int	ft_executecommand(t_commands cmd, int cmdnbr, int forknbr, t_shell *shell)
{
	int	status;
	int	hdn;

	hdn = 0;
	if (cmdnbr > 0)
	{
		if (cmd.prio && !shell->frk[forknbr].cmd[cmdnbr - 1].prio)
		{
			if ((cmd.condition == 1 && cmd.lastcode != 0) || (cmd.condition == 2 && cmd.lastcode == 0))
			{
				if (cmd.prio != 2)
					shell->frk[forknbr].cmd[cmdnbr].prio = 3;
				shell->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
				return (cmd.lastcode);
			}
		}
		if (cmd.prio && shell->frk[forknbr].cmd[cmdnbr - 1].prio == 3)
		{
			if (cmd.prio != 2)
				shell->frk[forknbr].cmd[cmdnbr].prio = 3;
			shell->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
			return (cmd.lastcode);
		}
	}
	if ((cmd.condition == 1 && cmd.lastcode != 0) || (cmd.condition == 2 && cmd.lastcode == 0))
	{
		shell->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
		return (cmd.lastcode);
	}
	cmd.code = ft_builtincheck(cmd, cmdnbr, forknbr, shell);
	if (cmd.code == -1111)
	{
		status = ft_checkcommand(cmd.arg, shell->envp);
		if (status)
		{
			shell->frk[forknbr].cmd[cmdnbr + 1].lastcode = status;
			return (status);
		}
		if (shell->frk[forknbr].cmd[cmdnbr].heredoc)
		{
			while (hdn + 1 < shell->frk[forknbr].cmd[cmdnbr].heredoc)
			{
				cmd.pid = fork();
				if (cmd.pid == 0)
				{
					signal(SIGQUIT, ft_sighandler);
					if (ft_dupmachine(cmdnbr, forknbr, hdn, shell) == 2)
						return (1);
					if (shell->forkamount > 1)
					{
						close(shell->pipes[forknbr][1]);
						close(shell->pipes[forknbr][0]);
						close(shell->pipes[forknbr + 1][1]);
						close(shell->pipes[forknbr + 1][0]);
					}
					execve(cmd.absolute, cmd.arg, shell->envp);
					ft_errorexit("command not found", cmd.absolute, 127);
				}
				if (shell->forkamount > 1)
				{
					close(shell->pipes[forknbr][1]);
					close(shell->pipes[forknbr][0]);
					close(shell->pipes[forknbr + 1][0]);
				}
				waitpid(cmd.pid, &status, 0);
				cmd.code = WEXITSTATUS(status);
				hdn++;
			}

		}
		cmd.pid = fork();
		if (cmd.pid == 0)
		{
			signal(SIGQUIT, ft_sighandler);
			if (ft_dupmachine(cmdnbr, forknbr, hdn, shell) == 2)
				return (1);
			if (shell->forkamount > 1)
			{
				close(shell->pipes[forknbr][1]);
				close(shell->pipes[forknbr][0]);
				close(shell->pipes[forknbr + 1][1]);
				close(shell->pipes[forknbr + 1][0]);
			}
			execve(cmd.absolute, cmd.arg, shell->envp);
			ft_errorexit("command not found", cmd.absolute, 127);
		}
		if (shell->forkamount > 1)
		{
			close(shell->pipes[forknbr][1]);
			close(shell->pipes[forknbr][0]);
			close(shell->pipes[forknbr + 1][0]);
		}
		waitpid(cmd.pid, &status, 0);
		cmd.code = WEXITSTATUS(status);
	}
	shell->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.code;
	return (cmd.code);
}

int	ft_executeforks(int forknbr, t_shell *shell, int condition)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (shell->frk[forknbr].cmdamount > cmdnbr)
	{
		ft_frearr(shell->envp);
		shell->envp = ft_fdtocharpp(shell->envpfd);
		shell = ft_parsecommands(shell, forknbr, cmdnbr);
		if (shell->stop == 1)
		{
			ft_createfdo(shell->frk[forknbr].cmd[cmdnbr]);
			return (0);
		}
		if (shell->stop == 2)
		{
			return (1);
		}
		if (shell->debug)
			ft_printcommands(shell->frk[forknbr].cmd[cmdnbr], cmdnbr, forknbr);
		status = ft_executecommand(shell->frk[forknbr].cmd[cmdnbr], cmdnbr, forknbr, shell);
		if (shell->frk[forknbr].cmd[cmdnbr].outfile[0] && status != 127)
			ft_executeredirect(shell->frk[forknbr].cmd[cmdnbr].outfile, shell->frk[forknbr].cmd[cmdnbr].append, forknbr);
		cmdnbr++;
	}
	if (condition)
		ft_checklastcode(shell->frk[forknbr]);
	return (status);
}
