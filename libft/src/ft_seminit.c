/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_seminit.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/17 20:08:39 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 20:09:03 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_seminit(char *file, int number)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_putendl_fd("initializing semaphore failed", 2);
		return (1);
	}
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}
