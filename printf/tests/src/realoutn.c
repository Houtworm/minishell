/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   realoutn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:56 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;
	int	*n;

	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	printf(argv[1], n);
	printf(" %d", i);
	free(n);
	return (0);
}
