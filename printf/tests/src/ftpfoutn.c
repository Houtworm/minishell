/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftpfoutn.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:46 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"

int	main(int argc, char **argv)
{
	int	i;
	int	*n;

	alarm(5);
	i = atoi(argv[2]);
	n = &i;
	n = malloc(64);
	ft_printf(argv[1], n);
	ft_printf(" %d", i);
	free(n);
	return (0);
}
