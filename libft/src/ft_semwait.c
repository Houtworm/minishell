/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_semwait.c                                    |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/17 20:09:16 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/17 20:09:26 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_semwait(char *file)
{
	int		fd;
	char	*content;
	int		number;

	number = 0;
	while (number == 0)
	{
		fd = open(file, O_RDONLY);
		content = ft_calloc(2, 8);
		read(fd, content, 2);
		number = ft_atoi(content);
		free(content);
		close(fd);
	}
	number--;
	fd = open(file, O_RDWR | O_TRUNC, 0777);
	ft_putnbr_fd(number, fd);
	close(fd);
	return (0);
}
