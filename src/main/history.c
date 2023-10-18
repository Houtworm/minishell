/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   history.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/01 02:06:31 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:01:03 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_addlinetohistory(char *line, char *file, t_shell *msh)
{
	int		histfd;
	int		tempfd;
	char	*gnl;

	histfd = open(file, O_RDONLY);
	gnl = ft_strjoin(msh->tmpdir, "history.tmp");
	tempfd = open(gnl, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(gnl);
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

void	ft_writenewhistory(char *file, t_shell *msh)
{
	int		histfd;
	int		tempfd;
	char	*gnl;

	gnl = ft_strjoin(msh->tmpdir, "history.tmp");
	tempfd = open(gnl, O_RDONLY);
	free(gnl);
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

void	ft_writehistory(char *line, char *file, t_shell *msh)
{
	rl_clear_history();
	ft_addlinetohistory(line, file, msh);
	ft_writenewhistory(file, msh);
	ft_readhistory(file);
}
