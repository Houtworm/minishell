/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   semaphore.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/08 02:57:55 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/08 11:41:39 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_seminit(char *file, int number)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC | O_SYNC, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("initializing semaphore failed", 2);
		return (1);
	}
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}

int	ft_semwait(char *file)
{
	int		fd;
	char	*content;
	int		number;

	number = 0;
	while (number == 0)
	{
		fd = open(file, O_RDONLY | O_SYNC);
		if (fd == -1)
		{
			ft_putendl_fd("lowering the semaphore failed", 2);
			return (1);
		}
		get_next_line(fd, &content);
		number = ft_atoi(content);
		free(content);
		close(fd);
	}
	number--;
	fd = open(file, O_RDWR | O_TRUNC | O_SYNC, 0777);
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}

int	ft_semfree(char *file)
{
	int		fd;
	char	*content;
	int		number;

	fd = open(file, O_RDONLY | O_SYNC);
	if (fd == -1)
	{
		ft_putendl_fd("upping the semaphore failed", 2);
		return (1);
	}
	get_next_line(fd, &content);
	number = ft_atoi(content);
	free(content);
	close(fd);
	number++;
	fd = open(file, O_RDWR | O_TRUNC | O_SYNC, 0777);
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}
