/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dupmachine.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 21:59:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 04:45:56 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_inputfile(int forknumber, int cmdnumber, t_shell *msh)
{
	char	*tmp;
	int		fd;
	char	*frkn;
	char	*cmdn;

	frkn = ft_itoa(forknumber);
	cmdn = ft_itoa(cmdnumber);
	tmp = ft_vastrjoin(7, msh->tmpdir, "heredoc", ".", frkn, ".", cmdn, ".tmp");
	fd = open(tmp, O_RDONLY);
	dup2(fd, 0);
	ft_vafree(3, frkn, cmdn, tmp);
	close(fd);
	return (0);
}

int	ft_outputfile(char **file, int forknbr, t_shell *msh)
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
	outtmp = ft_vastrjoin(4, msh->tmpdir, "outputfile", tmpnbr, ".tmp");
	fdo = open(outtmp, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fdo == -1)
		return (ft_errorret("Is a directory", outtmp, 1));
	dup2(fdo, 1);
	close(fdo);
	ft_vafree(2, outtmp, tmpnbr);
	return (0);
}

int	ft_dupmachine(int cmdn, int frkn, t_shell *msh)
{
	if (msh->debug)
		ft_printdup(msh->frk[frkn].cmd[cmdn], cmdn, frkn);
	if (msh->frk[frkn].cmd[cmdn].infiles)
		ft_inputfile(frkn, cmdn, msh);
	else if (cmdn == 0 && frkn > 0)
	{
		dup2(msh->pipes[frkn][0], 0);
		close(msh->pipes[frkn][0]);
		close(msh->pipes[frkn][1]);
		close(msh->pipes[frkn + 1][0]);
	}
	if (msh->frk[frkn].cmd[cmdn].outfile[0])
	{
		if (ft_outputfile(msh->frk[frkn].cmd[cmdn].outfile, frkn, msh))
			return (1);
	}
	else if (cmdn + 1 == msh->frk[frkn].cmd[cmdn].cmdamount && frkn + 1 < msh->frk[frkn].cmd[cmdn].forkamount)
	{
		dup2(msh->pipes[frkn + 1][1], 1);
		close(msh->pipes[frkn + 1][1]);
		close(msh->pipes[frkn + 1][0]);
		close(msh->pipes[frkn][1]);
		close(msh->pipes[frkn][0]);
	}
	return (0);
}
