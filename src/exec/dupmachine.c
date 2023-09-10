/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dupmachine.c                                    |o_o || |                */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/24 21:59:03 by houtworm      #+#    #+#                 */
/*   Updated: 2023/09/10 03:43:02 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_heredoc(char *delimiter)
{
	int		fdi;
	char	*line;
	int		length;

	fdi = open("/tmp/minishellheredocfile.temp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	length = ft_strlen(delimiter);
	ft_putstr("minishell heredoc> ");
	get_next_line(0, &line);
	if (!line)
		ft_errorexit("Error allocating memory", "malloc", 1);
	while (ft_strncmp(line, delimiter, length + 1))
	{
		ft_putstr("minishell heredoc> ");
		ft_putendl_fd(line, fdi);
		free(line);
		get_next_line(0, &line);
		if (!line)
			ft_errorexit("Error allocating memory", "malloc", 1);
	}
	free(line);
	close(fdi);
	fdi = open("/tmp/minishellheredocfile.temp", O_RDONLY);
	dup2(fdi, 0);
	return (fdi);
}

int	ft_inputfile(char *file)
{
	int	fdi;

	if (ft_checkinputfile(file))
		return (1);
	fdi = open(file, O_RDONLY);
	dup2(fdi, 0);
	return (0);
}

int	ft_outputfile(char *file, int append)
{
	int	fdo;

	if (ft_checkoutputfile(file))
		return (1);
	if (append)
		fdo = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		fdo = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
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
	else if (cmds.redirect[0].delimiter)
	{
		ft_heredoc(cmds.redirect[0].delimiter);
		/*dup2(ft_heredoc(cmds.redirect[0].delimiter), 0);*/
	}
	else if (cmds.redirect[0].infilename)
	{
		if (ft_inputfile(cmds.redirect[0].infilename))
			return (1);
	}
	else
		dup2(shell->fdin, 0);
	if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount)
	{
		dup2(shell->pipes[forknbr + 1][1], 1);
	}
	else if (cmds.redirect[0].outfilename)
	{
		if (ft_outputfile(cmds.redirect[0].outfilename, cmds.redirect[0].append))
			return (1);
	}
	else
	{
		dup2(shell->fdout, 1);
	}
	return (0);
}
