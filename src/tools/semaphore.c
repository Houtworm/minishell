/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   semaphore.c                                     |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/08 02:57:55 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/08 03:14:12 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_seminit(char *file, int number)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
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
		fd = open(file, O_RDONLY);
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
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}

int	ft_semfree(char *file)
{
	int		fd;
	char	*content;
	int		number;

	fd = open(file, O_RDONLY);
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
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}
