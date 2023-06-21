/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test11.c                                           :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:12:24 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/24 14:10:53 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		r;
	char	*dst;
	char	*src;

	r = 0;
	dst = NULL;
	src = malloc(8 * 6);
	memcpy(src, "Hello\0", 6);
	ft_memccpy(dst, src, 0, 3);
	if (dst)
		r = 1;
	free(dst);
	free(src);
	return (r);
}
