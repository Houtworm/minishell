/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test16.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:45:45 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:04:39 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = ' ';
	if (!ft_isalpha(c))
		return (0);
	return (1);
}
