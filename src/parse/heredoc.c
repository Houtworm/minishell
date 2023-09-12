/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   heredoc.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/09/12 11:25:43 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/09/12 11:30:28 by houtworm     \___)=(___/                 */
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
	fdi = open("/tmp/minishellheredocfile.temp", O_RDONLY); // 1 file for multiple heredocs will fail ofc
	return (fdi);
}

