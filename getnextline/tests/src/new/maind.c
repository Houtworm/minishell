/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maind.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: djonker <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/15 03:43:05 by djonker       #+#    #+#                 */
/*   Updated: 2023/10/18 17:08:40 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	line1 = "\n";
	line2 = "\n";
	fd1 = open("tests/files/new/compare1", O_RDONLY);
	fd2 = open("tests/files/new/compare2", O_RDONLY);
	while (line1 || line2)
	{
		if (line1)
		{
			line1 = get_next_line(fd1);
			printf("%s\n", line1);
			free(line1);
		}
		if (line2)
		{
			line2 = get_next_line(fd2);
			printf("%s\n", line2);
			free(line2);
		}
	}
	return (0);
}
