/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test12.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:42:46 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:06:50 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	if (!ft_strncmp(NULL, "Hello", 4))
		return (1);
	return (0);
}
