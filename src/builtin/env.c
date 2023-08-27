/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                           |o_o || |                */
/*                                                    +:+ +:+         +:+     */
/*   By: houtworm <codam@houtworm.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 18:13:16 by houtworm          #+#    #+#             */
/*   Updated: 2023/08/27 08:07:43 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(void)
{
	int		status;
	int		fd;
	char	*line;

	fd = open("/tmp/minishellenvpfile.tmp", O_RDONLY);
	status = get_next_line(fd, &line);
	while (status > 0)
	{
		ft_putendl(line);
		free(line);
		status = get_next_line(fd, &line);
	}
	close(fd);
	return (0);
}
