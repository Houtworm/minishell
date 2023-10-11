/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dupmachine.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 21:59:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/11 10:16:23 by djonker      \___)=(___/                 */
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
		if (ft_checkinputfile(file[i])) // maybe move it to the parser
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
		if (ft_checkoutputfile(file[i])) // maybe move it to the parser
			return (1);
		i++;
	}
	tmpnbr = ft_itoa(forknbr);
	if (!tmpnbr)
		return (1);
	outtmp = ft_vastrjoin(3, "/tmp/minishelloutputfile", tmpnbr, ".tmp");
	fdo = open(outtmp, O_RDWR | O_CREAT | O_TRUNC, 0666); //we should use this for output
	if (fdo == -1) 
		return (ft_errorreturn("Is a directory", outtmp, 1));
	dup2(fdo, 1);
	close(fdo);
	free(outtmp);
	free(tmpnbr);
	return (0);
}

int	ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	/*char	*temp;*/
	/*char	*fnbr;*/
	/*int		fd;*/

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
	}
	else if (shell->forks[forknbr].cmds[cmdnbr].hdfd > 0)
	{
		dup2(cmds.hdfd, 0);
		close(cmds.hdfd);
	}
	else if (cmds.infile[0])
	{
		if (ft_inputfile(cmds.infile))
			return (2);
	}
	if (cmds.outfile[0])
	{
		if (ft_outputfile(cmds.outfile, forknbr))
			return (1);
	}
	else if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount)
	{
		dup2(shell->pipes[forknbr + 1][1], 1);
		close(shell->pipes[forknbr + 1][1]);
		close(shell->pipes[forknbr][0]);
	}
	/*else //this is for printprompt we print to file first, so the order is correct with many pipes*/
	/*{*/
		/*fnbr = ft_itoa(forknbr);*/
		/*temp = ft_vastrjoin(3, "/tmp/minishelloutputfile", fnbr, ".temp");*/
		/*free(fnbr);*/
		/*fd = open(temp, O_RDWR | O_CREAT | O_APPEND, 0666);*/
		/*free(temp);*/
		/*dup2(fd, 1);*/
		/*close(fd);*/
	/*}*/
	return (0);
}
