/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:52:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:06:37 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		ret;
	int		r;
	char	*dst;

	ret = 0;
	dst = malloc(8 * 12);
	memcpy(dst, "yoyoyo\0", 7);
	r = ft_strlcat(dst, "Hallo\0", 10);
	if (r != 11)
		ret = 1;
	free(dst);
	return (ret);
}
