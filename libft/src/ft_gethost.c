
/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   ft_getos.c                                      |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/10/09 07:45:51 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/10/09 08:38:36 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_gethost(void)
{
	int		fd;
	char	*line;
	char	*host;

	fd = open("/etc/hostname", O_RDONLY);
	get_next_line(fd, &line);
	host = ft_strdup(line);
	free(line);
	close(fd);
	return (host);
}
