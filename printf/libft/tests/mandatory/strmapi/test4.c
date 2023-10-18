/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test4.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: houtworm <codam@houtworm.net>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/21 02:43:27 by houtworm      #+#    #+#                 */
/*   Updated: 2023/10/18 17:06:48 by houtworm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

char	ft_test_f(unsigned int i, char c)
{
	i++;
	if (ft_isdigit(c))
		return ('y');
	return ('n');
}

int	main(void)
{
	int		ret;
	char	*r;

	ret = 0;
	r = ft_strmapi("1a2b3c", &ft_test_f);
	if (strncmp(r, "ynynyn", 10))
		ret = 1;
	free (r);
	return (ret);
}
