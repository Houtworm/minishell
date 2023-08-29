/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dupmachine.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 21:59:03 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/29 04:33:37 by houtworm     \___)=(___/                 */
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

int	ft_dupmachine(t_cmds cmds, int cmdnbr, int forknbr, t_shell shell)
{
	if (cmdnbr == 0 && forknbr > 0) // if input needs to come from pipe
	{
		ft_putendl_fd("input from pipe", 2);
		dup2(shell.pipes[forknbr][0], 0);
	}
	else if (cmds.redirect[0].fd_in == -1) // if input needs to come from heredoc
	{
		ft_putendl_fd("input from heredoc", 2);
		dup2(ft_heredoc(cmds.redirect[0].heredocdelimiter), 0);
	}
	else if (cmds.redirect[0].fd_in > 2) // if input needs to come from file
	{
		ft_putendl_fd("input from file", 2);
		if (ft_inputfile(cmds.redirect[0].infilename))
			return (1);
	}
	else // input comes from stdin
	{
		ft_putendl_fd("input from stdin", 2);
		dup2(shell.tempfdin, 0);
	}
	if (cmdnbr + 1 == cmds.cmdamount && forknbr + 1 < cmds.forkamount) // if output needs to go to pipe
	{
		ft_putendl_fd("output to pipe", 2);
		dup2(shell.pipes[forknbr][1], 1);
	}
	else if (cmds.redirect[0].fd_out > 2) // if outpuut needs to go to file
	{
		ft_putendl_fd("output to file", 2);
		if (ft_inputfile(cmds.redirect[0].infilename))
			return (1);
	}
	else // output goes to stdout
	{
		ft_putendl_fd("output to stdout", 2);
		dup2(shell.tempfdout, 1);
	}
	return (0);
}
