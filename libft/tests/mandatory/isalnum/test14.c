/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test14.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:46:32 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:09:11 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	c;

	c = ',';
	if (!ft_isalnum(c))
		return (0);
	return (1);
}
