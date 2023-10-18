/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test14.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:58:12 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:06:06 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>

int	main(void)
{
	int		i;
	char	*str;

	i = 32;
	str = malloc(8 * 200);
	while (i < 232)
	{
		str[i - 32] = i;
		i++;
	}
	ft_putstr_fd(str, 2);
	free (str);
	return (0);
}
