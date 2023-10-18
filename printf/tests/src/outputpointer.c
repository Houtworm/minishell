/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   outputpointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:53 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*s;

	alarm(5);
	s = strdup(argv[2]);
	ft_printf(argv[1], s);
	ft_printf("\n");
	printf(argv[1], s);
	free(s);
	return (0);
}
