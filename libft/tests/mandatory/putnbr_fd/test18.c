/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test18.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:58:12 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:10:44 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int	i;

	i = 200000;
	while (i <= 210000)
	{
		ft_putnbr_fd(i, 2);
		i++;
	}
	return (0);
}
