/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   realretn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:19:05 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	int	i;
	int	*n;
	int	r;
	int	r2;

	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	r = printf(argv[1], n);
	r2 = printf(" %d", i);
	free(n);
	return (r + r2);
}
