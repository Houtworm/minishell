/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainc.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 03:43:05 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:08:42 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		r1;
	char	*line;

	r1 = 1;
	fd1 = open("tests/files/new/extreme2", O_RDONLY);
	while (r1 > 0)
	{
		r1 = get_next_line(fd1, &line);
		printf("<<%d>>%s\n", r1, line);
		free(line);
	}
	return (0);
}
