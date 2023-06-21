/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test2.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:43:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/03/02 05:06:06 by djonker      \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

char	ft_test_f(unsigned int i, char c)
{
	i++;
	c = ft_toupper(c);
	return (c);
}

int	main(void)
{
	int		ret;
	char	*r;

	ret = 0;
	r = ft_strmapi("Dit", &ft_test_f);
	if (strncmp(r, "DIT", 10))
		ret = 1;
	free (r);
	return (ret);
}
