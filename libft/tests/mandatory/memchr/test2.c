/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:03:52 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/24 21:31:27 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*s;
	char	*p;

	r = 0;
	s = malloc(8 * 6);
	strcpy(s, "Hello");
	p = ft_memchr(s, 'H', 5);
	if (strncmp(p, "Hello", 6))
		r = 1;
	free(s);
	return (r);
}
