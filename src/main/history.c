/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   history.c                                       |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/01 02:06:31 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/16 14:32:52 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_addlinetohistory(char *line, char *file)
{
	int		histfd;
	int		tempfd;
	char	*gnl;

	histfd = open(file, O_RDONLY);
	tempfd = open("/tmp/minishell/hist.tmp", O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(histfd, &gnl) > 0)
	{
		if (ft_strncmp(line, gnl, 500))
			ft_putendl_fd(gnl, tempfd);
		free(gnl);
	}
	free(gnl);
	ft_putendl_fd(line, tempfd);
	close(tempfd);
	close(histfd);
}

void	ft_writenewhistory(char *file)
{
	int		histfd;
	int		tempfd;
	char	*gnl;

	tempfd = open("/tmp/minishell/hist.tmp", O_RDONLY);
	histfd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	while (get_next_line(tempfd, &gnl) > 0)
	{
		ft_putendl_fd(gnl, histfd);
		free(gnl);
	}
	free(gnl);
	close(tempfd);
	close(histfd);
}

void	ft_readhistory(char *file)
{
	int		histfd;
	char	*line;

	histfd = open(file, O_RDONLY);
	while (get_next_line(histfd, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	free(line);
	close(histfd);
}

void	ft_writehistory(char *line, char *file)
{
	rl_clear_history();
	ft_addlinetohistory(line, file);
	ft_writenewhistory(file);
	ft_readhistory(file);
}
