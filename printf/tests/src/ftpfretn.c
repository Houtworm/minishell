/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftpfretn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:51 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"

int	main(int argc, char **argv)
{
	int	i;
	int	*n;
	int	r;
	int	r2;

	alarm(5);
	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	r = ft_printf(argv[1], n);
	r2 = ft_printf(" %d", i);
	free(n);
	return (r + r2);
}
