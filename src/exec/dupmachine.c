/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dupmachine.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 21:59:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/15 08:27:12 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_inputfile(char **file)
{
	int	fdi;
	int	i;

	i = 0;
	while (file[i])
	{
		if (ft_checkinputfile(file[i]))
			return (1);
		i++;
	}
	fdi = open(file[i - 1], O_RDONLY);
	dup2(fdi, 0);
	close (fdi);
	return (0);
}

int	ft_outputfile(char **file, int forknbr)
{
	int		fdo;
	int		i;
	char	*tmpnbr;
	char	*outtmp;

	i = 0;
	while (file[i])
	{
		if (ft_checkoutputfile(file[i]))
			return (1);
		i++;
	}
	tmpnbr = ft_itoa(forknbr);
	if (!tmpnbr)
		return (1);
	outtmp = ft_vastrjoin(3, "/tmp/minishell/outputfile", tmpnbr, ".tmp");
	fdo = open(outtmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fdo == -1) 
		return (ft_errorreturn("Is a directory", outtmp, 1));
	dup2(fdo, 1);
	close(fdo);
	free(outtmp);
	free(tmpnbr);
	return (0);
}

int	ft_heredocfile(int forknumber, int cmdnumber)
{
	char	*tmp;
	int		fd;
	char	*frkn;
	char	*cmdn;

	frkn = ft_itoa(forknumber);
	cmdn = ft_itoa(cmdnumber);
	tmp = ft_vastrjoin(6, "/tmp/minishell/heredoc", ".", frkn, ".", cmdn, ".tmp");
	fd = open(tmp, O_RDONLY);
	dup2(fd, 0);
	free(frkn);
	free(cmdn);
	free(tmp);
	close(fd);
	return (0);
}

int	ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	if (shell->debug)
		ft_printdup(cmds, cmdnbr, forknbr);
	if (forknbr > 1)
	{
		close(shell->pipes[forknbr][1]);
		close(shell->pipes[forknbr + 1][0]);
	}
	if (cmdnbr == 0 && forknbr > 0)
	{
		dup2(shell->pipes[forknbr][0], 0);
		close(shell->pipes[forknbr][0]);
		close(shell->pipes[forknbr][1]);
		close(shell->pipes[forknbr + 1][0]);
	}
	else if (shell->forks[forknbr].cmds[cmdnbr].heredoc)
		ft_heredocfile(forknbr, cmdnbr);
	else if (cmds.infile[0])
		if (ft_inputfile(cmds.infile))
			return (2);
	if (cmds.outfile[0])
	{
		if (ft_outputfile(cmds.outfile, forknbr))
			return (1);
	}
	else if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount)
	{
		dup2(shell->pipes[forknbr + 1][1], 1);
		close(shell->pipes[forknbr + 1][1]);
		close(shell->pipes[forknbr + 1][0]);
		close(shell->pipes[forknbr][1]);
		close(shell->pipes[forknbr][0]);
	}
	return (0);
}
