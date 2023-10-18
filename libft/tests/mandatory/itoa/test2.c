/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test2.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 03:12:17 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:09:45 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		rtrn;
	char	*r;

	rtrn = 0;
	r = ft_itoa(-2147483648);
	if (strncmp(r, "-2147483648\0", 6))
		rtrn = 1;
	free(r);
	return (rtrn);
}
