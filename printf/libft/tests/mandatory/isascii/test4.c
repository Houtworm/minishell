/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 03:04:50 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:04:45 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = '\n';
	if (!ft_isascii(c))
		return (1);
	return (0);
}
