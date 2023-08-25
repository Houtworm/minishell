/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   dupmachine.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/08/24 21:59:03 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/08/25 04:58:01 by houtworm     \___)=(___/                 */
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

int	ft_dupmachine(t_cmds cmds)
{
	// check if cmdnbr == 0 and forknbr > 0 then fd_in is output from pipe
	if (cmds.redirect[0].fd_in == -1)
		cmds.redirect[0].fd_in = ft_heredoc(cmds.redirect[0].heredocdelimiter);
	else
		dup2(cmds.redirect[0].fd_in, 0);
	// check if cmdnumber == cmdamount and forknumber < forkamount. then fd_out is dupped to pipe.
	dup2(cmds.redirect[0].fd_out, 1);
	return (0);
}
