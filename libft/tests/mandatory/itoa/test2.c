/* ************************************************************************** */
/*                                                                            */
/*                                                    .--.  _                 */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                   |:_/ || |_ _   ___  __   */
/*   By: houtworm <codam@houtworm.net>              //   \ \ __| | | \ \/ /   */
/*                                                 (|     | )|_| |_| |>  <    */
/*   Created: 2023/02/21 03:12:17 by houtworm     /'\_   _/`\__|\__,_/_/\_\   */
/*   Updated: 2023/02/24 13:28:47 by houtworm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tmp/libft.h"
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		rtrn;
	char	*r;

	rtrn = 0;
	r = ft_itoa(-2147483648);
	if (strncmp(r, "-2147483648\0", 6))
		rtrn = 1;
	free(r);
	return (rtrn);
}
