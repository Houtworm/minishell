/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test3.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:47:24 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:04:08 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		rtrn;
	char	*c;

	rtrn = 0;
	c = ft_calloc(13, 1);
	if (memcmp(c, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 14))
		rtrn = 1;
	free(c);
	return (rtrn);
}
