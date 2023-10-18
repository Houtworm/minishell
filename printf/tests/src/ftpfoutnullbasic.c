/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftpfoutnullbasic.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/25 17:07:23 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:18:46 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../tmp/ft_printf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	alarm(5);
	ft_printf(NULL);
	return (0);
}
