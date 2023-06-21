/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maine.c                                         |o_o || |                */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 03:43:05 by djonker       #+#    #+#                 */
/*   Updated: 2023/02/23 15:00:31 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd1;
	char	*line;

	line = "\n";
	fd1 = open("tests/files/new/unicode", O_RDONLY);
	while (line)
	{
		line = get_next_line(fd1);
		printf("%s\n", line);
		free (line);
	}
	return (0);
}
