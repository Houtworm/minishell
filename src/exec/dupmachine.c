/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dupmachine.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 21:59:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/13 00:57:48 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_inputfile(char *file)
{
	int	fdi;

	if (ft_checkinputfile(file))
		return (1);
	fdi = open(file, O_RDONLY);
	dup2(fdi, 0);
	close (fdi);
	return (0);
}

int	ft_outputfile(char *file, int append)
{
	int	fdo;

	if (ft_checkoutputfile(file)) // we have to make this a loop and maybe move it to the parser
	return (1);
	if (append) // this should be done in the later function
		fdo = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else // this too
		fdo = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	// fdo = open("/tmp/minishelloutputfile.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666); we should use this for output
	if (fdo == -1) 
	{
		ft_errorexit("Is a directory", file, 0);
		return (1);
	}
	dup2(fdo, 1);
	return (0);
}

int	ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell *shell)
{
	if (shell->debug)
		ft_printdup(cmds, cmdnbr, forknbr);
	if (cmdnbr == 0 && forknbr > 0)
		dup2(shell->pipes[forknbr][0], 0);
	else if (shell->forks[forknbr].cmds[cmdnbr].hdfd > 0)
		dup2(cmds.hdfd, 0);
	else if (cmds.infile[0])
	{
		if (ft_inputfile(cmds.infile[0]))
			return (1);
	}
	else
		dup2(shell->fdin, 0);
	if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount)
		dup2(shell->pipes[forknbr + 1][1], 1);
	else if (cmds.outfile[0])
	{
		if (ft_outputfile(cmds.outfile[0], cmds.append[0]))
			return (1);
	}
	else
		dup2(shell->fdout, 1);
	return (0);
}
