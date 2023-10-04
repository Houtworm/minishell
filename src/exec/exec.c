/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                          |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/04 06:22:41 by djonker      \___)=(___/                 */
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

	outtmp = ft_vastrjoin(3, "/tmp/minishelloutputfile", ft_itoa(forknbr), ".tmp");
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
	ft_putendl_fd("", 2);
	ft_putstr_fd("last code is ", 2);
	ft_putnbr_fd(cmds.lastcode, 2);
	ft_putstr_fd("  condition is ", 2);
	ft_putnbr_fd(cmds.condition, 2);
	ft_putstr_fd("  prio is ", 2);
	ft_putnbr_fd(cmds.prio, 2);
	ft_putendl_fd("", 2);
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
			// ft_printlastcode(cmds);
			return (cmds.lastcode);
		}
	}
	if (cmds.prio && shell->forks[forknbr].cmds[cmdnbr - 1].prio == 3)
	{
		if (cmds.prio != 2)
			shell->forks[forknbr].cmds[cmdnbr].prio = 3;
		shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.lastcode;
		// ft_printlastcode(cmds);
		return (cmds.lastcode);
	}
	if ((cmds.condition == 1 && cmds.lastcode != 0) || (cmds.condition == 2 && cmds.lastcode == 0))
	{
		shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.lastcode;
		// ft_printlastcode(cmds);
		return (cmds.lastcode);
	}
	cmds.code = ft_builtincheck(cmds, cmdnbr, forknbr, shell);
	if (cmds.code == -1111)
	{
		status = ft_checkcommand(cmds);
		if (status)
			return (status);
		cmds.pid = fork();
		if (cmds.pid == 0)
		{
			signal(SIGQUIT, ft_sighandler);
			ft_dupmachine(cmds, cmdnbr, forknbr, shell);
			execve(cmds.absolute, cmds.arguments, cmds.envp);
			/*ft_errorexit("command not found", cmds.absolute, 127);*/
		}
		waitpid(cmds.pid, &status, 0);
		cmds.code = WEXITSTATUS(status);
	}
	shell->forks[forknbr].cmds[cmdnbr + 1].lastcode = cmds.code;
	return (cmds.code);
}

int	ft_executeforks(int forknbr, t_shell *shell)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (shell->forks[forknbr].cmdamount > cmdnbr)
	{
		ft_frearr(shell->envp);
		shell->envp = ft_fdtocharpp(shell->envpfd);
		shell = ft_parsecmds(shell, forknbr, cmdnbr);
		if (shell->stop)
			return (0);
		if (shell->debug)
			ft_printcmds(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr);
		status = ft_executecommand(shell->forks[forknbr].cmds[cmdnbr], cmdnbr, forknbr, shell);
		if (shell->forks[forknbr].cmds[cmdnbr].outfile[0])
			ft_executeredirect(shell->forks[forknbr].cmds[cmdnbr].outfile, shell->forks[forknbr].cmds[cmdnbr].append, forknbr);
		cmdnbr++;
	}
	return (status);
}
