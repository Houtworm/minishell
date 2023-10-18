/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mainf.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 03:43:05 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:08:40 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd1;
	char	*line;

	line = "\n";
	fd1 = 0;
	while (line)
	{
		line = get_next_line(fd1);
		printf("%s\n", line);
		free(line);
	}
	return (0);
}
