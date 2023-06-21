/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test1.c                                         |o_o || |                */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 02:43:27 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/23 15:59:43 by houtworm     \___)=(___/                 */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

char	ft_test_f(unsigned int i, char c)
{
	i = 0;
	c = 'a';
	i = i + c;
	return ('a');
}

int	main(void)
{
	int		ret;
	char	*r;

	ret = 0;
	r = ft_strmapi("Dit", &ft_test_f);
	if (strncmp(r, "aaa", 10))
		ret = 1;
	free (r);
	return (ret);
}
