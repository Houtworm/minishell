/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:00:57 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	ft_checklastcode(t_forks fork, t_shell *msh)
{
	int	fd;
	int	icmd;
	char	*file;

	icmd = 0;
	file = ft_strjoin(msh->tmpdir, "lastcode.tmp");
	while (icmd < fork.cmdamount)
	{
		if (((fork.cmd[icmd].condition == 1 && fork.cmd[icmd].lastcode != 0) || (fork.cmd[icmd].condition == 2 && fork.cmd[icmd].lastcode == 0)))
		{
			unlink(file);
			fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
			close(fd);
			break ;
		}
		icmd++;
	}
	free(file);
}


int	ft_executecommand(t_commands cmd, int cmdnbr, int forknbr, t_shell *msh)
{
	int	status;
	int	pid;

	if (cmdnbr > 0)
	{
		if (cmd.prio && !msh->frk[forknbr].cmd[cmdnbr - 1].prio)
		{
			if ((cmd.condition == 1 && cmd.lastcode != 0) || (cmd.condition == 2 && cmd.lastcode == 0))
			{
				if (cmd.prio != 2)
					msh->frk[forknbr].cmd[cmdnbr].prio = 3;
				msh->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
				return (cmd.lastcode);
			}
		}
		if (cmd.prio && msh->frk[forknbr].cmd[cmdnbr - 1].prio == 3)
		{
			if (cmd.prio != 2)
				msh->frk[forknbr].cmd[cmdnbr].prio = 3;
			msh->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
			return (cmd.lastcode);
		}
	}
	if ((cmd.condition == 1 && cmd.lastcode != 0) || (cmd.condition == 2 && cmd.lastcode == 0))
	{
		msh->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.lastcode;
		return (cmd.lastcode);
	}
	cmd.code = ft_builtincheck(cmd, cmdnbr, forknbr, msh);
	if (cmd.code == -1111)
	{
		status = ft_checkcommand(cmd.arg, msh->envp);
		if (status)
		{
			msh->frk[forknbr].cmd[cmdnbr + 1].lastcode = status;
			return (status);
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, ft_sighandler);
			if (ft_dupmachine(cmdnbr, forknbr, msh) == 2)
				return (1);
			if (msh->forkamount > 1)
			{
				close(msh->pipes[forknbr][1]);
				close(msh->pipes[forknbr][0]);
				close(msh->pipes[forknbr + 1][1]);
				close(msh->pipes[forknbr + 1][0]);
			}
			execve(cmd.absolute, cmd.arg, msh->envp);
			ft_errorexit("command not found", cmd.absolute, 127);
		}
		if (msh->forkamount > 1)
		{
			close(msh->pipes[forknbr][1]);
			close(msh->pipes[forknbr][0]);
			close(msh->pipes[forknbr + 1][0]);
		}
		waitpid(pid, &status, 0);
		cmd.code = WEXITSTATUS(status);
	}
	msh->frk[forknbr].cmd[cmdnbr + 1].lastcode = cmd.code;
	return (cmd.code);
}

int	ft_executeforks(int forknbr, t_shell *msh, int condition)
{
	int	status;
	int	cmdnbr;

	cmdnbr = 0;
	while (msh->frk[forknbr].cmdamount > cmdnbr)
	{
		ft_frearr(msh->envp);
		msh->envp = ft_fdtocharpp(msh);
		status = ft_parsecommands(msh, forknbr, cmdnbr);
		if (status == 1)
		{
			ft_createfdo(msh->frk[forknbr].cmd[cmdnbr]);
			return (0);
		}
		if (status == 2)
			return (1);
		if (msh->debug)
			ft_printcommands(msh->frk[forknbr].cmd[cmdnbr], cmdnbr, forknbr);
		status = ft_executecommand(msh->frk[forknbr].cmd[cmdnbr], cmdnbr, forknbr, msh);
		if (msh->frk[forknbr].cmd[cmdnbr].outfile[0] && status != 127)
			ft_redirectoutput(msh->frk[forknbr].cmd[cmdnbr].outfile, msh->frk[forknbr].cmd[cmdnbr].append, forknbr, msh);
		cmdnbr++;
	}
	if (condition)
		ft_checklastcode(msh->frk[forknbr], msh);
	return (status);
}
