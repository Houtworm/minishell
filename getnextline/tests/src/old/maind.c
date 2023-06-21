/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maind.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 03:43:05 by djonker       #+#    #+#                 */
/*   Updated: 2023/03/01 01:24:29 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd[2];
	int		r[2];
	char	*line;

	r[0] = 1;
	r[1] = 1;
	fd[0] = open("tests/files/new/compare1", O_RDONLY);
	fd[1] = open("tests/files/new/compare2", O_RDONLY);
	while (r[0] > 0 || r[1] > 0)
	{
		if (r[0] > 0)
		{
			r[0] = get_next_line(fd[0], &line);
			printf("<<%d>>%s\n", r[0], line);
			free(line);
		}
		if (r[1] > 0)
		{
			r[1] = get_next_line(fd[1], &line);
			printf("<<%d>>%s\n", r[1], line);
			free(line);
		}
	}
	return (0);
}
