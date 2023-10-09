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

char	*ft_getosfromline(char *line)
{
	int		ret;
	char	*os;
	int		i;

	ret = 0;
	i = 0;
	while (line[i] != '\"')
		i++;
	i++;
	os = ft_calloc(ft_strlen(line), 8);
	while (line[i] != ' ' && line[i] != '\"')
	{
		os[ret] = line[i];
		ret++;
		i++;
	}
	os[ret + 1] = '\0';
	return (os);
}

char	*ft_getos(void)
{
	int		fd;
	char	*line;
	int		ret;
	char	*os;

	fd = open("/etc/os-release", O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (!ft_strncmp(line, "PRETTY_NAME:", 7))
		{
			os = ft_getosfromline(line);
			free(line);
			close(fd);
			return (os);
		}
		free (line);
	}
	close(fd);
	return (NULL);
}
