/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <djonker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 04:35:12 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/23 20:33:43 by yitoh         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_createfdo(t_commands cmd)
{
	int	fdo;
	int	i;

	i = 0;
	while (cmd.ofi[i])
	{
		if (cmd.app[i])
			fdo = open(cmd.ofi[i], O_RDWR | O_CREAT | O_APPEND, 0666);
		else
			fdo = open(cmd.ofi[i], O_RDWR | O_CREAT | O_TRUNC, 0666);
		close (fdo);
		i++;
	}
}

void	ft_checklastcode(t_forks fork, t_shell *msh)
{
	int		fd;
	int		i;
	char	*file;

	i = 0;
	file = ft_strjoin(msh->tmpdir, "lastcode.tmp");
	while (i < fork.cmds)
	{
		if (((fork.cmd[i].condition == 1 && fork.cmd[i].lastcode != 0)
				|| (fork.cmd[i].condition == 2 && fork.cmd[i].lastcode == 0)))
		{
			unlink(file);
			fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
			close(fd);
			break ;
		}
		i++;
	}
	free(file);
}

int	ft_checkexec(t_commands cmd, int c, int f, t_shell *msh)
{
	if (cmd.prio && !msh->frk[f].cmd[c - 1].prio)
	{
		if ((cmd.condition == 1 && cmd.lastcode != 0)
			|| (cmd.condition == 2 && cmd.lastcode == 0))
		{
			if (cmd.prio != 2)
				msh->frk[f].cmd[c].prio = 3;
			msh->frk[f].cmd[c + 1].lastcode = cmd.lastcode;
			return (cmd.lastcode);
		}
	}
	if (cmd.prio && msh->frk[f].cmd[c - 1].prio == 3)
	{
		if (cmd.prio != 2)
			msh->frk[f].cmd[c].prio = 3;
		msh->frk[f].cmd[c + 1].lastcode = cmd.lastcode;
		return (cmd.lastcode);
	}
	if ((cmd.condition == 1 && cmd.lastcode != 0)
		|| (cmd.condition == 2 && cmd.lastcode == 0))
	{
		msh->frk[f].cmd[c + 1].lastcode = cmd.lastcode;
		return (cmd.lastcode);
	}
	return (-1);
}

int	ft_executecommand(t_commands cmd, int c, int f, t_shell *msh)
{
	int	lastcode;
	int	status;

	if (c > 0 || (cmd.condition == 1 && cmd.lastcode != 0)
		|| (cmd.condition == 2 && cmd.lastcode == 0))
	{
		lastcode = ft_checkexec(cmd, c, f, msh);
		if (lastcode >= 0)
			return (lastcode);
	}
	cmd.code = ft_builtincheck(cmd, c, f, msh);
	if (cmd.code == -1111)
	{
		status = ft_checkcommand(cmd.arg, msh->envp);
		if (status)
		{
			msh->frk[f].cmd[c + 1].lastcode = status;
			return (status);
		}
		ft_nonbuiltinfork(&cmd, c, f, msh);
	}
	msh->frk[f].cmd[c + 1].lastcode = cmd.code;
	return (cmd.code);
}

int	ft_execforks(int f, t_shell *msh, int condition)
{
	int	status;
	int	c;

	c = 0;
	while (msh->frk[f].cmds > c)
	{
		ft_frearr(msh->envp);
		msh->envp = ft_fdtocharpp(msh);
		status = ft_parsecmds(msh, f, c, NULL);
		if (status == 1)
			return (ft_createfdo(msh->frk[f].cmd[c]), 0);
		if (status == 2)
			return (1);
		if (msh->debug)
			ft_printcommands(msh->frk[f].cmd[c], c, f);
		status = ft_executecommand(msh->frk[f].cmd[c], c, f, msh);
		if (msh->frk[f].cmd[c].ofi[0] && status != 127)
			ft_rediout(msh->frk[f].cmd[c].ofi, msh->frk[f].cmd[c].app, f, msh);
		c++;
	}
	if (condition)
		ft_checklastcode(msh->frk[f], msh);
	return (status);
}
