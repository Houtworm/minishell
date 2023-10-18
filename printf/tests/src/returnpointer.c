/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   returnpointer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:19:08 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		r;
	int		f;

	alarm(5);
	s = strdup(argv[2]);
	r = printf(argv[1], s);
	f = ft_printf(argv[1], s);
	free(s);
	if (r != f)
		return (f);
	return (0);
}
